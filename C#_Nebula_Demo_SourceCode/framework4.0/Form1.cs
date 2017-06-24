using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using RobotpenGateway;
using System.Runtime.InteropServices;
using System.Threading;

namespace RobotPenTestDll
{
    public enum demoEnum
    {
        GATEWAY_DEMO,
        NODE_DEMO,
        DONGLE_DEMO,
        P1_DEMO,
    }

    public partial class Form1 : Form
    {
        // 子设备窗口
        private myControl[] subNodeWindow = new myControl[60];
        private bool bScreen = true;


        // NODE单独窗口
        private myControl nodeDataWindow = null;

        private demoEnum demo_type = demoEnum.NODE_DEMO;
        private eDeviceType eDeviceTy;

        public Form1()
        {
            InitializeComponent();

            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                eDeviceTy = eDeviceType.Gateway;
            }
            else if (demo_type == demoEnum.NODE_DEMO) {
                eDeviceTy = eDeviceType.T8A;
            }
            else if (demo_type == demoEnum.DONGLE_DEMO)
            {
                eDeviceTy = eDeviceType.Dongle;
            }
            else if (demo_type == demoEnum.P1_DEMO)
            {
                eDeviceTy = eDeviceType.RobotPen_P1;
            }
            init();
            this.comboBox2.SelectedIndex = 0;

        }

        private void loadDevice()
        {
            int nDeviceCount = robotpenController.GetInstance()._GetDeviceCount();
            if (nDeviceCount > 0)
            {
                this.listView1.BeginUpdate();
                for (int i = 0; i < nDeviceCount; ++i)
                {
                    ushort npid = 0;
                    ushort nvid = 0;
                    string strDeviceName = string.Empty;

                    if (robotpenController.GetInstance()._GetAvailableDevice(i, ref npid, ref nvid, ref strDeviceName))
                    {
                        this.listView1.Items.Add(strDeviceName);
                        string strVID = Convert.ToString(nvid);
                        this.listView1.Items[i].SubItems.Add(strVID);
                        string strPID = Convert.ToString(npid);
                        this.listView1.Items[i].SubItems.Add(strPID);
                    }
                }
                this.listView1.EndUpdate();
            }

            if (this.listView1.Items.Count > 0)
            {
                this.listView1.Select();
                this.listView1.Items[0].Selected = true;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            // init device list
            this.listView1.Columns.Add("设备名称", 200, HorizontalAlignment.Center);
            this.listView1.Columns.Add("VID", 100, HorizontalAlignment.Center);
            this.listView1.Columns.Add("PID", 100, HorizontalAlignment.Center);

            loadDevice();

            Point pt = this.device_textBox.Location;
            int nSubWinStartX = pt.X + this.device_textBox.Width + 50;
            int nSubWinStartY = 20;

            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                // 获取最右边控件的坐标
                int xCount = 0;

                Size size = this.Size;
                int nWinSize = 100;
                // 计算一行可以放下多少个窗口
                int nColumCount = (this.ClientRectangle.Width - nSubWinStartX) / (120);
                int nNeedCount = 60 / (nColumCount);
                if (60 % nColumCount != 0)
                {
                    nNeedCount += 1;
                }

                // 计算可以放下多少行
                int nRowCount = this.Height / (120);
                if (nNeedCount > nRowCount)  // 需要的行数大于窗口高度 需要缩小波形窗口
                {
                    while (nWinSize-- > 0)
                    {
                        int nTempRowCount = (this.ClientRectangle.Width - nSubWinStartX) / (nWinSize + 20);
                        int nTmpNeedRow = 60 / nTempRowCount;
                        if (60 % nTmpNeedRow != 0)
                        {
                            nTmpNeedRow += 1;
                        }
                        int nTmpFactRow = this.Height / (nWinSize + 20);
                        if (nTmpNeedRow > nTmpFactRow)
                            continue;
                        else
                            break;

                    }
                }
                for (int i = 0; i < subNodeWindow.Length; ++i)
                {
                    int nX = nSubWinStartX + (xCount * (nWinSize + 20));
                    if (nX + nWinSize + 20 > this.Width)
                    {
                        nX = nSubWinStartX;
                        xCount = 1;
                        nSubWinStartY += (nWinSize + 20);
                    }
                    else
                    {
                        xCount++;
                    }

                    this.subNodeWindow[i] = new myControl(canvasType.GATEWAY);
                    this.subNodeWindow[i].m_nIndex = i + 1;
                    this.subNodeWindow[i].canvasShowEvt += dbClkCanvas;
                    this.subNodeWindow[i].setControlSize(nWinSize, nWinSize);
                    this.subNodeWindow[i].Location = new Point(nX, nSubWinStartY);
                    this.subNodeWindow[i].BackColor = Color.Black;
                    this.Controls.Add(this.subNodeWindow[i]);
                    //this.subNodeWindow[i].start();
                    this.SuspendLayout();
                }

                this.device_label.Hide();
                this.device_textBox.Hide();

                notDongleMode();
            }
            else if (demo_type == demoEnum.NODE_DEMO)
            {
                nodeDataWindow = new myControl(canvasType.NODE);
                this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
                this.nodeDataWindow.setControlSize(200, 200);
                this.nodeDataWindow.Location = new Point(nSubWinStartX, nSubWinStartY);
                this.nodeDataWindow.BackColor = Color.Black;
                this.Controls.Add(this.nodeDataWindow);
                //this.subNodeWindow[i].start();
                this.SuspendLayout();


                // 隐藏相关窗口
                //this.version_label.Hide();
                //this.version_label_show.Hide();
                //this.status_button_query.Hide();
                //this.status_label_title.Hide();
                //this.status_label.Hide();
                this.button1.Hide();
                this.button2.Hide();
                this.voteClear_button.Hide();
                this.ns_start_button.Hide();
                this.ms_end_button.Hide();
                this.msClear_button.Hide();
                //this.set_button.Hide();

                this.update_button.Hide();
                this.mode_label_tip.Hide();

                this.WindowState = FormWindowState.Normal;

                // 移动控件
                this.custom_label.Location = new Point(this.custom_label.Location.X, this.custom_label.Location.Y - 200);
                this.custom_textBox.Location = new Point(this.custom_textBox.Location.X, this.custom_textBox.Location.Y - 200);
                this.class_label.Location = new Point(this.class_label.Location.X, this.class_label.Location.Y - 200);
                this.class_textBox.Location = new Point(this.class_textBox.Location.X, this.class_textBox.Location.Y - 200);
                this.device_label.Location = new Point(this.device_label.Location.X, this.device_label.Location.Y - 200);
                this.device_textBox.Location = new Point(this.device_textBox.Location.X, this.device_textBox.Location.Y - 200);
                this.set_button.Location = new Point(this.set_button.Location.X, this.set_button.Location.Y - 150);
                this.screen_set_label.Location = new Point(this.screen_set_label.Location.X, this.screen_set_label.Location.Y - 300);
                this.comboBox1.Location = new Point(this.comboBox1.Location.X, this.comboBox1.Location.Y - 300);
                this.Size = new System.Drawing.Size(1146, 630);

                notDongleMode();
            }
            else if (demo_type == demoEnum.DONGLE_DEMO)
            {
                this.WindowState = FormWindowState.Normal;
                isDongleMode();

                nodeDataWindow = new myControl(canvasType.DONGLE);
                this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
                this.nodeDataWindow.setControlSize(200, 200);
                this.nodeDataWindow.Location = new Point(630, 500);
                this.nodeDataWindow.BackColor = Color.Black;
                this.Controls.Add(this.nodeDataWindow);
                //this.subNodeWindow[i].start();
                this.SuspendLayout();

                this.Size = new System.Drawing.Size(1146, 800);
            }
            else if (demo_type == demoEnum.P1_DEMO)
            {
                isP1Mode();
                this.WindowState = FormWindowState.Normal;
                nodeDataWindow = new myControl(canvasType.P1);
                this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
                this.nodeDataWindow.setControlSize(200, 200);
                this.nodeDataWindow.Location = new Point(500, 20);
                this.nodeDataWindow.BackColor = Color.Black;
                this.Controls.Add(this.nodeDataWindow);
                this.SuspendLayout();

                this.Size = new System.Drawing.Size(800, 300);
            }


            // 判断画布是否横竖屏
            string strPath = System.Windows.Forms.Application.StartupPath;
            strPath += "\\demo.ini";
            String str = string.Empty;
            str = OperateIniFile.ReadIniData("SET", "screenO", "0", strPath);
            if (str == null || str == string.Empty)
            {
                // 更新字段
                bScreen = false;
                OperateIniFile.WriteIniData("SET", "screenO", "2", strPath);
            }
            else if (str == "2")
            {
                bScreen = false;
            }
            else
            {
                bScreen = true;
            }

            this.comboBox1.Text = bScreen ? "横屏" : "竖屏";
            this.set_button.Enabled = false;
        }

        private void notDongleMode()
        {
            this.slave_listView.Hide();
            this.dongle_san_button.Hide();
            this.dongle_stopsan_button.Hide();
            this.dg_con_button.Hide();
            this.dg_discon_button.Hide();
            this.slave_ststus_label.Hide();
            this.slave_status_label1.Hide();
            this.slave_version_label.Hide();
            this.slave_version1_label.Hide();
            this.slave_name_textBox.Hide();

            this.slave_name_set_button.Hide();
            this.adjust_button.Hide();
            this.start_sync_button.Hide();
            this.end_sync_button.Hide();
            this.offline_label.Hide();
        }

        private void isDongleMode()
        {
            this.comboBox2.Hide();
            this.button1.Hide();
            this.button2.Hide();
            this.voteClear_button.Hide();
            this.ns_start_button.Hide();
            this.ms_end_button.Hide();
            this.msClear_button.Hide();
            this.set_button.Hide();

            this.custom_label.Hide();
            this.custom_textBox.Hide();
            this.class_label.Hide();
            this.class_textBox.Hide();
            this.device_label.Hide();
            this.msClear_button.Hide();
            this.device_textBox.Hide();

            this.slave_listView.Columns.Add("Num", 50, HorizontalAlignment.Center);
            this.slave_listView.Columns.Add("名称", 120, HorizontalAlignment.Center);
            this.slave_listView.Columns.Add("Mac地址", 300, HorizontalAlignment.Center);


            robotpenController.GetInstance().dongleStatusEvt += new robotpenController.dongleStatus(Form1_dongleStatusEvt);
            robotpenController.GetInstance().dongleScanResultEvt += new robotpenController.dongleSanResult(Form1_dongleScanResultEvt);
            robotpenController.GetInstance().dongleVersionEvt += new robotpenController.dongleVersion(Form1_dongleVersionEvt);
            robotpenController.GetInstance().dongleDataPacketEvt += new robotpenController.dongleDataPacket(Form1_dongleDataPacketEvt);
            robotpenController.GetInstance().slaveStatusEvt += new robotpenController.slaveStatus(Form1_slaveStatusEvt);
            robotpenController.GetInstance().slaveVersionEvt += new robotpenController.slaveVersion(Form1_slaveVersionEvt);
            robotpenController.GetInstance().startSyncNoteDataEvt += new robotpenController.startSyncNoteData(Form1_startSyncNoteDataEvt);
            robotpenController.GetInstance().syncNoteDataEvt += new robotpenController.syncNoteData(Form1_syncNoteDataEvt);
            robotpenController.GetInstance().endSyncNoteDataEvt += new robotpenController.endSyncNoteData(Form1_endSyncNoteDataEvt);
            robotpenController.GetInstance().enterAdjustModeEvt += new robotpenController.enterAdjustMode(Form1_enterAdjustModeEvt);
            robotpenController.GetInstance().adjustResultEvt += new robotpenController.adjustResult(Form1_adjustResultEvt);
        }

        private void isP1Mode()
        {
            notDongleMode();

            this.comboBox2.Hide();
            this.button1.Hide();
            this.button2.Hide();
            this.voteClear_button.Hide();
            this.ns_start_button.Hide();
            this.ms_end_button.Hide();
            this.msClear_button.Hide();
            this.set_button.Hide();
            this.update_button.Hide();
            this.mode_label_tip.Hide();
            this.version_label.Hide();
            this.status_button_query.Hide();
            this.status_label_title.Hide();
            this.version_label_show.Hide();
            this.status_label.Hide();

            this.custom_label.Hide();
            this.custom_textBox.Hide();
            this.class_label.Hide();
            this.class_textBox.Hide();
            this.device_label.Hide();
            this.msClear_button.Hide();
            this.device_textBox.Hide();

            robotpenController.GetInstance().returnP1PointDataEvt += new robotpenController.returnP1PointData(Form1_returnP1PointDataEvt);
        }

        // 收到P1设备数据
        private void Form1_returnP1PointDataEvt(byte bPenStatus, short sx, short sy, short sPress)
        {
            if (null != nodeDataWindow)
            {
                nodeDataWindow.dataArrive(Convert.ToInt32(sx), Convert.ToInt32(sy));
            }
            if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                return;

            int npenStatus = Convert.ToInt32(bPenStatus);
            if (npenStatus != 17)
            {
                npenStatus = 0;
            }
            nodeCanvasWindow.recvData(npenStatus, Convert.ToInt32(sx), Convert.ToInt32(sy), 0);
        }

        void Form1_slaveVersionEvt(st_version version)
        {
            string str = Convert.ToString((int)version.version) + "." +
                    Convert.ToString((int)version.version2) + "." + Convert.ToString((int)version.version3) + "." +
                    Convert.ToString((int)version.version4);
            UpdateControlUI(str, updateControl.eslaveversion);
        }

        void Form1_slaveStatusEvt(node_status status)
        {
            string str;
            switch ((NODE_STATUS)status.device_status)
            {
                case NODE_STATUS.DEVICE_POWER_OFF:
                    str = "DEVICE_POWER_OFF";
                    break;
                case NODE_STATUS.DEVICE_STANDBY:
                    str = "DEVICE_STANDBY";
                    break;
                case NODE_STATUS.DEVICE_INIT_BTN:
                    str = "DEVICE_INIT_BTN";
                    break;
                case NODE_STATUS.DEVICE_OFFLINE:
                    str = "DEVICE_OFFLINE";
                    break;
                case NODE_STATUS.DEVICE_ACTIVE:
                    str = "DEVICE_ACTIVE";
                    break;
                case NODE_STATUS.DEVICE_LOW_POWER_ACTIVE:
                    str ="DEVICE_LOW_POWER_ACTIVE";
                    break;
                case NODE_STATUS.DEVICE_OTA_MODE:
                    str = "DEVICE_OTA_MODE";
                    break;
                case NODE_STATUS.DEVICE_OTA_WAIT_SWITCH:
                    str = "DEVICE_OTA_WAIT_SWITCH";
                    break;
                case NODE_STATUS.DEVICE_TRYING_POWER_OFF:
                    str = "DEVICE_TRYING_POWER_OFF";
                    break;
                case NODE_STATUS.DEVICE_FINISHED_PRODUCT_TEST:
                    str = "DEVICE_FINISHED_PRODUCT_TEST";
                    break;
                case NODE_STATUS.DEVICE_SYNC_MODE:
                    str = "DEVICE_SYNC_MODE";
                    break;
                default:
                    str = "error";
                    break;
            }

            UpdateControlUI(str, updateControl.eslavestatus);
            string strNoteCount = "离线笔迹:" + Convert.ToInt32(status.note_num) + "条";
            UpdateControlUI(strNoteCount, updateControl.eofflinecount);
        }

        // dongle数据上报
        private void Form1_dongleDataPacketEvt(PEN_INFO data)
        {
            if (null != nodeDataWindow)
            {
                nodeDataWindow.dataArrive(Convert.ToInt32(data.nX), Convert.ToInt32(data.nY));
            }
            if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                return;
            
            nodeCanvasWindow.recvData(Convert.ToInt32(data.nPress), Convert.ToInt32(data.nX), Convert.ToInt32(data.nY), 0);
        }

        private void Form1_dongleVersionEvt(st_version version)
        {
            string str = Convert.ToString((int)version.version) + "." + 
                Convert.ToString((int)version.version2) + "." + Convert.ToString((int)version.version3) + "." + 
                Convert.ToString((int)version.version4);
            UpdateControlUI(str, updateControl.edongleversion);
        }

        private void Form1_dongleScanResultEvt(st_ble_device slaveInfo)
        {
            string strSlaveName = System.Text.Encoding.ASCII.GetString(slaveInfo.device_name);
            string strMac = Convert.ToString(slaveInfo.addr[0], 16) + ":" + Convert.ToString(slaveInfo.addr[1], 16) + ":" +
                Convert.ToString(slaveInfo.addr[2], 16) + ":" + Convert.ToString(slaveInfo.addr[3], 16) + ":" +
                Convert.ToString(slaveInfo.addr[4], 16) + ":" + Convert.ToString(slaveInfo.addr[5], 16);
            UpdateSlaveDeviceListView(slaveInfo.num, strSlaveName, strMac);
        }

        private void Form1_dongleStatusEvt(eDongleStatus status)
        {
            string str;
            switch (status)
            {
                case eDongleStatus.BLE_STANDBY:
                    str = ("BLE_STANDBY");
                    break;
                case eDongleStatus.BLE_SCANNING:			//正在扫描	
                    str = ("BLE_SCANNING");
                    break;
                case eDongleStatus.BLE_CONNECTING:		//连接中
                    str = ("BLE_CONNECTING");
                    break;
                case eDongleStatus.BLE_CONNECTED:			//连接成功
                    {
                        str = ("BLE_CONNECTED");
                        UpdateControlUI("", updateControl.econnectSlaveName);
                    }
                    break;
                case eDongleStatus.BLE_ACTIVE_DISCONNECT://正在断开链接
                    str = ("BLE_ACTIVE_DISCONNECT");
                    break;
                case eDongleStatus.BLE_RECONNECTING:		//重新连接
                    str = ("BLE_RECONNECTING");
                    break;
                case eDongleStatus.BLE_LINK_BREAKOUT:		//蓝牙正在升级中
                   str = ("BLE_LINK_BREAKOUT");
                    break;
                case eDongleStatus.BLE_DFU_START:			//蓝牙dfu模式
                    str = ("BLE_DFU_START");
                    break;
                default:
                    {
                        str = "UNKNOW:";
                        string strStatus = Convert.ToString((int)status);
                    }
                    break;
            }
            UpdateControlUI(str, updateControl.edonglestatus);
        }

        private void Form1_endSyncNoteDataEvt()
        {
            string strNoteCount = "同步结束";
            UpdateControlUI(strNoteCount, updateControl.eofflinecount);
        }

        private void Form1_syncNoteDataEvt(byte bPenStatus, short sx, short sy, short sPress)
        {
            if (null != nodeDataWindow)
            {
                nodeDataWindow.dataArrive(Convert.ToInt32(sx), Convert.ToInt32(sy));
            }
            if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                return;

            Console.WriteLine("sPress={0} | sx={1} | y={2}", sPress, sx, sy);
            nodeCanvasWindow.recvData(sPress, Convert.ToInt32(sx), Convert.ToInt32(sy), 0);
        }

        private void Form1_startSyncNoteDataEvt(byte noteCount)
        {
            string strNoteCount = "离线笔迹:" + Convert.ToInt32(noteCount) + "条";
            UpdateControlUI(strNoteCount, updateControl.eofflinecount);
        }

        // 进入校准模式
        private void Form1_enterAdjustModeEvt()
        {
            string str = "进入校准模式";
            UpdateControlUI(str, updateControl.edonglestatus);
        }


        private void Form1_adjustResultEvt(eAdujstResult result)
        {
            string str;
            switch (result)
            {
                case eAdujstResult.ADJUST_SUCCESSED:
                    str = ("校准成功");
                    break;
                case eAdujstResult.ADJUST_FAILED:
                    str = ("校准失败");
                    break;
                case eAdujstResult.ADJUST_TIMEOUT:
                    str = ("校准超时");
                    break;
                default:
                    str = "未知错误";
                    break;
            }
            UpdateControlUI(str, updateControl.edonglestatus);
        }

        // 
        public enum updateControl
        {
            edongleversion,
            edonglestatus,
            eslavestatus,
            eofflinecount,
            eslaveversion,
            econnectSlaveName,
        }

        public delegate void UpdateControlDelegate(string str1, updateControl uty);
        public delegate void UpdateSlaveDeviceListViewDelegate(int nNum, string strSlaveName, string strMac);

        public void UpdateSlaveDeviceListView(int nNum, string strSlaveName, string strMac)
        {
            if (this.slave_listView.InvokeRequired)
            {
                while (!this.slave_listView.IsHandleCreated)
                {
                    if (this.slave_listView.Disposing || this.slave_listView.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateSlaveDeviceListViewDelegate d = new UpdateSlaveDeviceListViewDelegate(UpdateSlaveDeviceListView);
                this.slave_listView.Invoke(d, new object[] { nNum, strSlaveName, strMac });
            }
            else
            {
                addSlaveDevice(nNum, ref strSlaveName, ref strMac);
            }
        }

        public void UpdateControlUI(string param, updateControl uty)
        {
            switch (uty)
            {
                case updateControl.edongleversion:
                    {
                        if (this.version_label_show.InvokeRequired)
                        {
                            while (!this.version_label_show.IsHandleCreated)
                            {
                                if (this.version_label_show.Disposing || this.version_label_show.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.version_label_show.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            this.version_label_show.Text = param;
                        }
                    }
                    break;
                case updateControl.edonglestatus:
                    {
                        if (this.status_label.InvokeRequired)
                        {
                            while (!this.status_label.IsHandleCreated)
                            {
                                if (this.status_label.Disposing || this.status_label.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.status_label.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            this.status_label.Text = param;
                        }
                    }
                    break;
                case updateControl.eslavestatus:
                    {
                        if (this.slave_status_label1.InvokeRequired)
                        {
                            while (!this.slave_status_label1.IsHandleCreated)
                            {
                                if (this.slave_status_label1.Disposing || this.slave_status_label1.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.slave_status_label1.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            this.slave_status_label1.Text = param;
                        }
                    }
                    break;
                case updateControl.eofflinecount:
                    {
                        if (this.offline_label.InvokeRequired)
                        {
                            while (!this.offline_label.IsHandleCreated)
                            {
                                if (this.offline_label.Disposing || this.offline_label.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.offline_label.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            this.offline_label.Text = param;
                        }
                    }
                    break;
                case updateControl.eslaveversion:
                    {
                        if (this.slave_version1_label.InvokeRequired)
                        {
                            while (!this.slave_version1_label.IsHandleCreated)
                            {
                                if (this.slave_version1_label.Disposing || this.slave_version1_label.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.slave_version1_label.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            this.slave_version1_label.Text = param;
                        }
                    }
                    break;
                case updateControl.econnectSlaveName:
                    {
                        if (this.slave_name_textBox.InvokeRequired)
                        {
                            while (!this.slave_name_textBox.IsHandleCreated)
                            {
                                if (this.slave_name_textBox.Disposing || this.slave_name_textBox.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.slave_name_textBox.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            if (this.slave_listView.SelectedItems.Count != 1)
                            {
                                return;
                            }
                            string strSlaveName = this.slave_listView.SelectedItems[0].SubItems[1].Text;
                            this.slave_name_textBox.Text = strSlaveName;
                        }
                    }
                    break;
            }

        }

        private TrailsShowFrom[] canvasWindow = new TrailsShowFrom[60];
        private TrailsShowFrom nodeCanvasWindow = null;

        private void dbClkCanvas(string strIndex)
        {
            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                int nIndex = Convert.ToInt32(strIndex);
                if (canvasWindow[nIndex - 1] == null || canvasWindow[nIndex - 1].IsDisposed)
                {
                    canvasWindow[nIndex - 1] = new TrailsShowFrom(canvasType.GATEWAY);
                    canvasWindow[nIndex - 1].bScreenO = bScreen;
                    canvasWindow[nIndex - 1].TopMost = true;
                    canvasWindow[nIndex - 1].Show();
                    canvasWindow[nIndex - 1].Text = strIndex;
                    if (!bScreen)
                    {
                        canvasWindow[nIndex - 1].Size = new Size(426, 625);
                    }
                    else
                    {
                        canvasWindow[nIndex - 1].Size = new Size(625, 480);
                    }
                }
                else
                {
                    canvasWindow[nIndex - 1].TopMost = true;
                    canvasWindow[nIndex - 1].Show();
                    canvasWindow[nIndex - 1].Text = strIndex;
                }
            }
            else if (demo_type == demoEnum.NODE_DEMO)
            {
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                {
                    nodeCanvasWindow = new TrailsShowFrom(canvasType.NODE);
                    nodeCanvasWindow.bScreenO = bScreen;
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                    nodeCanvasWindow.canvastype = canvasType.NODE;
                    if (!bScreen)
                    {
                        nodeCanvasWindow.Size = new Size(426, 625);
                    }
                    else
                    {
                        nodeCanvasWindow.Size = new Size(625, 480);
                    }
                }
                else
                {
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                }
            } else if (demo_type == demoEnum.DONGLE_DEMO)
            {
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                {
                    nodeCanvasWindow = new TrailsShowFrom(canvasType.DONGLE);
                    nodeCanvasWindow.bScreenO = bScreen;
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                    nodeCanvasWindow.canvastype = canvasType.DONGLE;
                    if (!bScreen)
                    {
                        nodeCanvasWindow.Size = new Size(426, 625);
                    }
                    else
                    {
                        nodeCanvasWindow.Size = new Size(625, 480);
                    }
                }
                else
                {
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                }
            }
            else if (demo_type == demoEnum.P1_DEMO)
            {
                  if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                {
                    nodeCanvasWindow = new TrailsShowFrom(canvasType.P1);
                    nodeCanvasWindow.bScreenO = bScreen;
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                    nodeCanvasWindow.canvastype = canvasType.P1;
                    if (!bScreen)
                    {
                        nodeCanvasWindow.Size = new Size(426, 625);
                    }
                    else
                    {
                        nodeCanvasWindow.Size = new Size(625, 480);
                    }
                }
                else
                {
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                }
            }
        }

        private RobotpenGateway.robotpenController.returnPointData date = null;//new RobotpenGateway.robotpenController.returnPointData(Form1_bigDataReportEvt1);

        public void init()
        {
            robotpenController.GetInstance()._ConnectInitialize(eDeviceTy, IntPtr.Zero);
            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                robotpenController.GetInstance().gateWayStatusEvt += Form1_gateWayStatusEvt;
                //robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
                robotpenController.GetInstance().gatewayErrorEvt += Form1_gatewayErrorEvt;
                robotpenController.GetInstance().exitVotePatternEvt += Form1_exitVotePatternEvt;
                //robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;
                //robotpenController.GetInstance().bigDataReportEvt += Form1_bigDataReportEvt;
                robotpenController.GetInstance().onlineStatusEvt += Form1_onlineStatusEvt;
                robotpenController.GetInstance().setDeviceNetNumEvt += Form1_setDeviceNetNumEvt;
                robotpenController.GetInstance().exitVoteEvt += Form1_ExitVoteEvt;

                robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
                robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;
                date = new RobotpenGateway.robotpenController.returnPointData(Form1_bigDataReportEvt1);
                robotpenController.GetInstance().initDeletgate(ref date);
            }
            else if (demo_type == demoEnum.NODE_DEMO)
            {
                // 绑定相关事件即可
                robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
                robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;
                date = new RobotpenGateway.robotpenController.returnPointData(Form1_bigDataReportEvt1);
                robotpenController.GetInstance().initDeletgate(ref date);
            }
            //robotpenController.GetInstance().gateWayStatusEvt += Form1_gateWayStatusEvt;

        }

        private void Form1_setDeviceNetNumEvt(bool bres, byte b1, byte b2, byte b3)
        {
            if (bres)
            {
                strCustomNum = b1.ToString();
                strClassNum = b2.ToString();
                strDeviceNum = b3.ToString();
                updateCustomTextBox(strCustomNum);
                updateClassTextBox(strClassNum);
                updateDeviceTextBox(strDeviceNum);
            }

            showSettingRes(bres);
        }

        // 设备在线状态
        private void Form1_onlineStatusEvt(int nIndex, bool bOnLine)
        {
            //for (int i = 0; i < subNodeWindow.Length; ++i)
            {
                if (subNodeWindow[nIndex] != null)
                {
                    subNodeWindow[nIndex].m_onLine = bOnLine;
                    updateBoxingEx(nIndex);
                }
            }
        }

        private void Form1_bigDataReportEvt1(byte bIndex, byte bPenStatus, short bx, short by, short bPress)
        {
            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                int nIndex = Convert.ToInt32(bIndex);

                if (nIndex >= subNodeWindow.Length)
                    return;

                if (null != subNodeWindow[nIndex])
                {
                    subNodeWindow[nIndex].dataArrive(Convert.ToInt32(bx), Convert.ToInt32(by));
                    //updateBoxingEx(nIndex);
                }


                if (nIndex >= canvasWindow.Length)
                    return;

                if (canvasWindow[nIndex] == null || canvasWindow[nIndex].IsDisposed)
                    return;

                //Console.WriteLine(nIndex);

                canvasWindow[nIndex].recvData(Convert.ToInt32(bPress), Convert.ToInt32(bx), Convert.ToInt32(by), 0);
            }
            else if (demo_type == demoEnum.NODE_DEMO)
            {
                if (null != nodeDataWindow)
                {
                    nodeDataWindow.dataArrive(Convert.ToInt32(bx), Convert.ToInt32(by));
                }
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                    return;

                nodeCanvasWindow.recvData(Convert.ToInt32(bPress), Convert.ToInt32(bx), Convert.ToInt32(by), 0);
            }
        }

        private void Form1_bigDataReportEvt(byte bIndex, byte bPenStatus, short bx, short by, short bPress)
        {
            return;

            int nIndex = Convert.ToInt32(bIndex);

            if (nIndex >= canvasWindow.Length)
                return;

            if (canvasWindow[nIndex] == null || canvasWindow[nIndex].IsDisposed)
                return;

            Console.WriteLine(nIndex);

            canvasWindow[nIndex].recvData(Convert.ToInt32(bPress), Convert.ToInt32(bx), Convert.ToInt32(by), 0);

            if (nIndex >= subNodeWindow.Length)
                return;
            
            if (null != subNodeWindow[nIndex])
            {
                subNodeWindow[nIndex].dataArrive(Convert.ToInt32(bx), Convert.ToInt32(by));
                updateBoxingEx(nIndex);
            }
        }

        // 
        private string strCustomNum = string.Empty;
        private string strClassNum = string.Empty;
        private string strDeviceNum = string.Empty;

        // 设备版本号 
        private void Form1_gatewatVersionEvt(string strVersion, byte bCustomNum, byte bClassNum, byte bDeviceNum)
        {
            updateDeviceVersionLabel(strVersion);
            strCustomNum = bCustomNum.ToString();
            strClassNum = bClassNum.ToString();
            strDeviceNum = bDeviceNum.ToString();
            updateCustomTextBox(strCustomNum);
            updateClassTextBox(strClassNum);
            updateDeviceTextBox(strDeviceNum);
        }

        // 退出投票模式
        private void Form1_exitVotePatternEvt(string strValue)
        {
            for (int i = 0; i < subNodeWindow.Length; ++i)
            {
                if (subNodeWindow[i] == null)
                    continue;
                updateBoxing(strValue, i);
            }
        }

        private void Form1_ExitVoteEvt(byte[] status)
        {
            for (int i = 0; i < status.Length; ++i )
            {
                string str = System.Text.Encoding.ASCII.GetString(status, i, 1);
                if (subNodeWindow[i] == null)
                    continue;
                subNodeWindow[i].setVoteMode(str);
            }
        }

        // 设备错误事件
        private void Form1_gatewayErrorEvt(NEBULA_ERROR errorCode)
        {
            string strStatus = string.Empty;
            switch (errorCode)
            {
                case NEBULA_ERROR.ERROR_NONE:
                    {
                        strStatus = "ERROR_NONE";
                    }
                    break;
                case NEBULA_ERROR.ERROR_FLOW_NUM:
                    {
                        strStatus = "ERROR_FLOW_NUM";
                    }
                    break;
                case NEBULA_ERROR.ERROR_FW_LEN:
                    {
                        strStatus = "ERROR_FW_LEN";
                    }
                    break;
                case NEBULA_ERROR.ERROR_FW_CHECKSUM:
                    {
                        strStatus = "ERROR_FW_CHECKSUM";
                    }
                    break;
                case NEBULA_ERROR.ERROR_STATUS:
                    {
                        strStatus = "ERROR_STATUS";
                    }
                    break;
                case NEBULA_ERROR.ERROR_VERSION:
                    {
                        strStatus = "ERROR_VERSION";
                    }
                    break;
                case NEBULA_ERROR.ERROR_NAME_CONTENT:
                    {
                        strStatus = "ERROR_NAME_CONTENT";
                    }
                    break;
                case NEBULA_ERROR.ERROR_NO_NOTE:
                    {
                        strStatus = "ERROR_NO_NOTE";
                    }
                    break;
                default:
                    {
                        strStatus = "UNKNOW ERROR";
                    }
                    break;
            }
            CallDelegate(strStatus);
        }

        // 子节点设备状态改变事件
        private void Form1_nodeStatusEvt(NODE_STATUS ns)
        {
            string strStatus = string.Empty;
            switch (ns)
            {
                case NODE_STATUS.DEVICE_POWER_OFF:
                    {
                        strStatus = "DEVICE_POWER_OFF";
                    }
                    break;
                case NODE_STATUS.DEVICE_STANDBY:
                    {
                        strStatus = "DEVICE_STANDBY";
                    }
                    break;
                case NODE_STATUS.DEVICE_INIT_BTN:
                    {
                        strStatus = "DEVICE_INIT_BTN";
                    }
                    break;
                case NODE_STATUS.DEVICE_OFFLINE:
                    {
                        strStatus = "DEVICE_OFFLINE";
                    }
                    break;
                case NODE_STATUS.DEVICE_ACTIVE:
                    {
                        strStatus = "DEVICE_ACTIVE";
                    }
                    break;
                case NODE_STATUS.DEVICE_LOW_POWER_ACTIVE:
                    {
                        strStatus = "DEVICE_LOW_POWER_ACTIVE";
                    }
                    break;
                case NODE_STATUS.DEVICE_OTA_MODE:
                    {
                        strStatus = "DEVICE_OTA_MODE";
                    }
                    break;
                case NODE_STATUS.DEVICE_OTA_WAIT_SWITCH:
                    {
                        strStatus = "DEVICE_OTA_WAIT_SWITCH";
                    }
                    break;
                case NODE_STATUS.DEVICE_DFU_MODE:
                    {
                        strStatus = "DEVICE_DFU_MODE";
                    }
                    break;
                case NODE_STATUS.DEVICE_TRYING_POWER_OFF:
                    {
                        strStatus = "DEVICE_TRYING_POWER_OFF";
                    }
                    break;
                case NODE_STATUS.DEVICE_FINISHED_PRODUCT_TEST:
                    {
                        strStatus = "DEVICE_FINISHED_PRODUCT_TEST";
                    }
                    break;
                case NODE_STATUS.DEVICE_SYNC_MODE:
                    {
                        strStatus = "DEVICE_SYNC_MODE";
                    }
                    break;
//                 case NODE_STATUS.DEVICE_SEMI_FINISHED_PRODUCT_TEST:
//                     {
//                         strStatus = "DEVICE_SEMI_FINISHED_PRODUCT_TEST";
//                     }
//                     break;
                default:
                    {
                        strStatus = "UNKNOW";
                    }
                    break;
            }
            CallDelegate(strStatus);
        }

        // 收到网关状态改变事件
        private void Form1_gateWayStatusEvt(GATEWAY_STATUS gwS)
        {
            string strStatus = string.Empty;
            switch (gwS)
            {
                case GATEWAY_STATUS.NEBULA_STATUS_OFFLINE:
                    {
                        strStatus = "NEBULA_STATUS_OFFLINE";
                    }break;
                case GATEWAY_STATUS.NEBULA_STATUS_STANDBY:
                    {
                        strStatus = "NEBULA_STATUS_STANDBY";
                    }break;
                case GATEWAY_STATUS.NEBULA_STATUS_VOTE:
                    {
                        strStatus = "NEBULA_STATUS_VOTE";
                    }break;
                case GATEWAY_STATUS.NEBULA_STATUS_MASSDATA:
                    {
                        strStatus = "NEBULA_STATUS_MASSDATA";
                    }break;
                case GATEWAY_STATUS.NEBULA_STATUS_END:
                    {
                        strStatus = "NEBULA_STATUS_END";
                    } break;
                default:
                    {
                        strStatus = "UNKNOW";
                    }
                    break;
            }
            CallDelegate(strStatus);
        }


        // 声明更新委托
        public delegate void UpdateStatusLabel(string str1);
        public delegate void UpdateBoxing(string str1, int index);
        public delegate void UpdateBoxingEx(int index);
        // 更新设置结果
        public delegate void UpdateSettingRes(bool bres);

        // 
        public void showSettingRes(bool bres)
        {
            this.Invoke(new UpdateSettingRes(showSettingRes_F), new object[] { bres });
        }
        public void showSettingRes_F(bool bres)
        {
            string strMsg = bres ? "设置成功" : "设置失败";
            MessageBox.Show(strMsg, "提示信息", MessageBoxButtons.OK);

            resetDevice();
        }

        // 更新设备状态Label
        public void CallDelegate(string param)
        {
            if (this.status_label.InvokeRequired)
            {
                while (!this.status_label.IsHandleCreated)
                {
                    if (this.status_label.Disposing || this.status_label.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(CallDelegate);
                this.status_label.Invoke(d, new object[] { param });
            }
            else
            {
                this.status_label.Text = param;
            }
        }

        // 错误label提示
        public void updateErrorLabel(string strErrorInfo)
        {
            if (this.Error_label.InvokeRequired)
            {
                while (!this.Error_label.IsHandleCreated)
                {
                    if (this.Error_label.Disposing || this.Error_label.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateErrorLabel);
                this.Error_label.Invoke(d, new object[] { strErrorInfo });
            }
            else
            {
                this.Error_label.Text = strErrorInfo;
            }
        }

        // 更新设备版本号
        public void updateDeviceVersionLabel(string strVersionInfo)
        {
            if (this.version_label_show.InvokeRequired)
            {
                while (!this.version_label_show.IsHandleCreated)
                {
                    if (this.version_label_show.Disposing || this.version_label_show.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateDeviceVersionLabel);
                this.version_label_show.Invoke(d, new object[] { strVersionInfo });
            }
            else
            {
                this.version_label_show.Text = strVersionInfo;
            }
        }

        // 更新customNum
        public void updateCustomTextBox(string strCustomNum)
        {
            if (this.custom_textBox.InvokeRequired)
            {
                while (!this.custom_textBox.IsHandleCreated)
                {
                    if (this.custom_textBox.Disposing || this.custom_textBox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateCustomTextBox);
                this.custom_textBox.Invoke(d, new object[] { strCustomNum });
            }
            else
            {
                this.custom_textBox.Text = strCustomNum;
            }
        }

        // 更新classNum
        public void updateClassTextBox(string strClassNum)
        {
            if (this.class_textBox.InvokeRequired)
            {
                while (!this.class_textBox.IsHandleCreated)
                {
                    if (this.class_textBox.Disposing || this.class_textBox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateClassTextBox);
                this.class_textBox.Invoke(d, new object[] { strClassNum });
            }
            else
            {
                this.class_textBox.Text = strClassNum;
            }
        }

        // 更新设备Num
        public void updateDeviceTextBox(string strDeviceNum)
        {
            if (this.device_textBox.InvokeRequired)
            {
                while (!this.device_textBox.IsHandleCreated)
                {
                    if (this.device_textBox.Disposing || this.device_textBox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateDeviceTextBox);
                this.device_textBox.Invoke(d, new object[] { strDeviceNum });
            }
            else
            {
                this.device_textBox.Text = strDeviceNum;
            }
        }

        // 更新窗口
        public void updateBoxing(string param, int index)
        {
            if (this.subNodeWindow[index].InvokeRequired)
            {
                while (!this.subNodeWindow[index].IsHandleCreated)
                {
                    if (this.subNodeWindow[index].Disposing || this.subNodeWindow[index].IsDisposed)
                    {
                        return;
                    }
                }
                UpdateBoxing d = new UpdateBoxing(updateBoxing);
                this.subNodeWindow[index].Invoke(d, new object[] { param, index });
            }
            else
            {
                this.subNodeWindow[index].setVoteMode(param);
            }
        }

        public void updateBoxingEx(int index)
        {
            if (this.subNodeWindow[index].InvokeRequired)
            {
                while (!this.subNodeWindow[index].IsHandleCreated)
                {
                    if (this.subNodeWindow[index].Disposing || this.subNodeWindow[index].IsDisposed)
                    {
                        return;
                    }
                }

                UpdateBoxingEx d = new UpdateBoxingEx(updateBoxingEx);
                this.subNodeWindow[index].Invoke(d, new object[] { index });
            }
            else
            {
                this.subNodeWindow[index].refreshWindow();
            }
        }

        // 窗口关闭时
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (this.open_button.Text == "关闭设备")
            {
                robotpenController.GetInstance()._ConnectDispose();
            }

            string strScreen = this.comboBox1.Text;
            string strPath = System.Windows.Forms.Application.StartupPath;
            strPath += "\\demo.ini";
            if (strScreen == "横屏")
            {
                OperateIniFile.WriteIniData("SET", "screenO", "1", strPath);
            }
            else
            {
                OperateIniFile.WriteIniData("SET", "screenO", "2", strPath);
            }
        }

        // 开始投票
        private void button1_Click(object sender, EventArgs e)
        {
            if (this.comboBox2.SelectedIndex == 0)
            {
                robotpenController.GetInstance()._Send(cmdId.VoteBegin);
            }
            else if (this.comboBox2.SelectedIndex == 1)
            {
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.VoteEnd);
        }

        // 打开或关闭设备
        private void open_button_Click(object sender, EventArgs e)
        {
            if (this.open_button.Text == "关闭设备")
            {
                robotpenController.GetInstance()._ConnectDispose();
                resetDevice();
                return; 
            }

            if (this.listView1.SelectedItems.Count != 1)
            {
                MessageBox.Show("请先选择需要打开的设备!");
                return;
            }

            string strPID = this.listView1.SelectedItems[0].SubItems[2].Text;
            UInt16 nPid = Convert.ToUInt16(strPID);

            if (nPid == Convert.ToUInt16(RobotpenGateway.DEIVE_PID.GATEWAY_PID))
            {
                if (demo_type == demoEnum.NODE_DEMO)
                {
                    MessageBox.Show("当前为node USB模式 无法演示网关设备功能, 如需打开网关设备请切换到网关demo模式!");
                    return;
                }

                robotpenController.GetInstance()._ConnectInitialize(eDeviceTy, IntPtr.Zero);
            }
            else if (nPid == Convert.ToUInt16(RobotpenGateway.DEIVE_PID.T8A_PID) || nPid == Convert.ToUInt16(RobotpenGateway.DEIVE_PID.T9A_PID))
            {
                eDeviceTy = eDeviceType.T8A;   // node节点
                robotpenController.GetInstance()._ConnectInitialize(eDeviceTy, IntPtr.Zero);
            }

            if (this.open_button.Text == "打开设备")
            {
                int nRes = robotpenController.GetInstance()._ConnectOpen();
                if (nRes != 0)
                {
                    MessageBox.Show("设备打开失败!");
                    return;
                }
                this.open_button.Text = "关闭设备";
                this.set_button.Enabled = true;
                if (eDeviceTy != eDeviceType.Gateway)
                {
                    status_button_query_Click(null, null);
                }
            }
            else
            {
                robotpenController.GetInstance()._ConnectDispose();
                this.open_button.Text = "打开设备";
                this.set_button.Enabled = false;
            }
        }

        // MS模式
        private void ns_start_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.WriteBegin);
        }

        // 结束MS模式
        private void ms_end_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.WriteEnd);
        }

        // 设置
        private void set_button_Click(object sender, EventArgs e)
        {
            setForm setWindow = new setForm(eDeviceTy, strCustomNum, strClassNum, strDeviceNum);
            setWindow.StartPosition = FormStartPosition.CenterParent;
            DialogResult res = setWindow.ShowDialog();
            if (res != DialogResult.Cancel)
            {
                // 获取数据
                string strCustomID = setWindow.strCustomNum;
                string strClassID = setWindow.strClassNum;

                string strDevice = setWindow.strDeviceNum;

                int nCustomNum = Convert.ToInt32(strCustomID);
                int nClassNum = Convert.ToInt32(strClassID);
                int nDeviceNum = ((eDeviceTy == eDeviceType.Gateway) ? 0 : Convert.ToInt32(strDevice));

                robotpenController.GetInstance()._SetConfig(nCustomNum, nClassNum, nDeviceNum);
            }

            setWindow.Dispose();
        }

        // 投票清除
        private void voteClear_button_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < subNodeWindow.Length; ++ i)
            {
                if (null == subNodeWindow[i])
                    continue;
                subNodeWindow[i].setVoteMode(string.Empty);
            }
        }

        // ms 模式清除
        private void msClear_button_Click(object sender, EventArgs e)
        {

        }

        private void status_button_query_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.GetConfig);
        }

        // 重置相关参数
        public void resetDevice()
        {
            this.open_button.Text = "打开设备";
            this.set_button.Enabled = false;

            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                for (int i = 0; i < subNodeWindow.Length; ++i )
                {
                    if (subNodeWindow[i] != null)
                    {
                        subNodeWindow[i].m_onLine = false;
                        subNodeWindow[i].updateNodeConnectionStatus();
                    }
                }
            }
            else if (demo_type == demoEnum.NODE_DEMO)
            {
                if (nodeDataWindow != null)
                {
                    nodeDataWindow.m_onLine = false;
                    nodeDataWindow.updateNodeConnectionStatus();
                }
            }

            this.custom_textBox.Text = "";
            this.class_textBox.Text = "";
            this.device_textBox.Text = "";

            this.version_label_show.Text = "";
            this.status_label.Text = "";

            this.listView1.Items.Clear();

            // 重新加载设备
            loadDevice();
        }


        // dongle 开始扫描
        private void dongle_san_button_Click(object sender, EventArgs e)
        {
            this.slave_listView.BeginUpdate();
 
            while (this.slave_listView.Items.Count > 0)
            {
                this.slave_listView.Items.RemoveAt(0);
            }

            this.slave_listView.EndUpdate();

            robotpenController.GetInstance()._Send(cmdId.DongleScanStart);
        }

        // dongle stop scan
        private void dongle_stopsan_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.DongleScanStop);
        }

        // 添加扫描到的设备到列表
        private void addSlaveDevice(int nNum, ref string slaveName, ref string slaveMacAddr)
        {
            // 过滤扫描到的重复设备
            this.slave_listView.BeginUpdate();
            int nItemCount = this.slave_listView.Items.Count;
            for (int i = 1; i < nItemCount; ++i)
            {
                string strNum = this.slave_listView.Items[0].SubItems[0].Text;
                int iNum = Convert.ToInt32(strNum);
                if (iNum == nNum)
                    return;
            }
           
            string strNumber = Convert.ToString(nNum);
            this.slave_listView.Items.Add(strNumber);
            this.slave_listView.Items[nItemCount].SubItems.Add(slaveName);
            this.slave_listView.Items[nItemCount].SubItems.Add(slaveMacAddr);
            this.slave_listView.EndUpdate();
        }

        // 连接蓝牙设备
        private void dg_con_button_Click(object sender, EventArgs e)
        {
            if (this.slave_listView.SelectedItems.Count != 1)
            {
                MessageBox.Show("请先选择需要连接的设备!");
                return;
            }

            string strNum = this.slave_listView.SelectedItems[0].SubItems[0].Text;
            int nNum = Convert.ToInt32(strNum);
            robotpenController.GetInstance().connectSlaveDevice(nNum);
        }

        // 断开蓝牙设备的连接
        private void dg_discon_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.DongleDisconnect);
        }

        // 设置蓝牙名称
        private void slave_name_set_button_Click(object sender, EventArgs e)
        {
            string strSlaveNewName = this.slave_name_textBox.Text;
            if (strSlaveNewName == "")
            {
                MessageBox.Show("名称不能为空!");
                return;
            }
            robotpenController.GetInstance().setSlaveDeviceName(strSlaveNewName);
        }

        // 离线笔记开始同步
        private void start_sync_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.SyncBegin);
        }

        // 结束同步
        private void end_sync_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.SyncEnd);
        }

        private void adjust_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.AdjustMode);
        }
    }
}
