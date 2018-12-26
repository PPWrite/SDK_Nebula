using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
//using System.Threading.Tasks;
using System.Windows.Forms;
using RobotpenGateway;
using System.Runtime.InteropServices;
using System.Threading;
using RobotPenTestDll.ClassHelper;

namespace RobotPenTestDll
{
    /// <summary>
    /// 调试模式
    /// </summary>
    public enum demoEnum
    {
        /// <summary>
        /// 2.4G网关
        /// </summary>
        GATEWAY_DEMO,
        /// <summary>
        /// USB连接模式
        /// </summary>
        NODE_DEMO,
        /// <summary>
        /// 蓝牙dongle模式
        /// </summary>
        DONGLE_DEMO,
        /// <summary>
        /// P1模式
        /// </summary>
        P1_DEMO,
        /// <summary>
        /// T7E模式
        /// </summary>
        T7E_DEMO,
    }

    public partial class Form1 : Form
    {
        /// <summary>
        /// 2.4G模式下，小窗口
        /// </summary>
        private UserControl1[] subNodeWindow = new UserControl1[60];
        /// <summary>
        /// 横竖屏控制，默认竖屏
        /// </summary>
        private bool bScreen = true;

        /// <summary>
        /// NODE单独窗口
        /// </summary>
        private UserControl1 nodeDataWindow = null;

        /// <summary>
        /// 调试类型
        /// </summary>
        private demoEnum demo_type;

        /// <summary>
        /// 设备类型
        /// </summary>
        private eDeviceType eDeviceTy;

        private string user_id = string.Empty;
        private string secret = string.Empty;
        private int source = 0;

        public Form1()
        {
            CheckIsOem();
            demo_type = (demoEnum)(Convert.ToInt32(System.Configuration.ConfigurationSettings.AppSettings["demo_type"]));
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
            else if (demo_type == demoEnum.T7E_DEMO)
            {
                eDeviceTy = eDeviceType.T7E_TS;
            }
            GetRecognitionKey();
            initEvt();
            
            this.comboBox2.SelectedIndex = 0;

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            //设置listview表头
            this.listView1.Columns.Add("设备名称", 200, HorizontalAlignment.Center);
            this.listView1.Columns.Add("VID", 100, HorizontalAlignment.Center);
            this.listView1.Columns.Add("PID", 100, HorizontalAlignment.Center);
            loadDevice();
            

            Point pt = this.listView1.Location;
            int nSubWinStartX = pt.X + this.listView1.Width + 50;
            int nSubWinStartY = pt.Y;

            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                GATEWAY_DEMO_ControlShow();
                GATEWAY_DEMO_NodeWindowShow(nSubWinStartX, nSubWinStartY);
            }
            else if (demo_type == demoEnum.NODE_DEMO)
            {
                NODE_DEMO_NodeWindowShow(nSubWinStartX, nSubWinStartY);
            }
            else if (demo_type == demoEnum.DONGLE_DEMO)
            {
                DONGLE_DEMO_ControlShow();
                DONGLE_DEMO_NodeWindowShow(nSubWinStartX, nSubWinStartY);
            }
            else if (demo_type == demoEnum.P1_DEMO)
            {
                P1_DEMO_NodeWindowShow(nSubWinStartX, nSubWinStartY);
            }
            else if (demo_type == demoEnum.T7E_DEMO)
            {
                T7E_DEMO_NodeWindowShow(nSubWinStartX, nSubWinStartY);
            }
        }

        private void GetRecognitionKey()
        {
            user_id = System.Configuration.ConfigurationSettings.AppSettings["user_id"].ToString();
            secret = System.Configuration.ConfigurationSettings.AppSettings["secret"].ToString();
            string source_ = System.Configuration.ConfigurationSettings.AppSettings["source"].ToString();
            if(!string.IsNullOrEmpty(source_))
            {
                source = int.Parse(source_);
            }
        }

        /// <summary>
        /// 初始化事件
        /// </summary>
        public void initEvt()
        {
            //监听USB插拔事件
            //robotpenController.GetInstance()._ConnectInitialize(eDeviceTy, IntPtr.Zero);
            robotpenController.GetInstance()._ConnectInitialize(eDeviceType.Gateway, IntPtr.Zero);

            robotpenController.GetInstance().deviceChangeEvt += new robotpenController.DeviceChange(Form1_deviceChangeEvt);
            robotpenController.GetInstance().nodeDeviceModeEvt += new robotpenController.NodeDeviceMode(Form1_nodeDeviceModeEvt);
            //
            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                robotpenController.GetInstance().gateWayStatusEvt += Form1_gateWayStatusEvt;
                robotpenController.GetInstance().gatewayErrorEvt += Form1_gatewayErrorEvt;
                robotpenController.GetInstance().exitVotePatternEvt += Form1_exitVotePatternEvt;
                robotpenController.GetInstance().onlineStatusEvt += Form1_onlineStatusEvt;
                robotpenController.GetInstance().setDeviceNetNumEvt += Form1_setDeviceNetNumEvt;
                robotpenController.GetInstance().exitVoteEvt += Form1_ExitVoteEvt;

                robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
                robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;

                robotpenController.GetInstance().multiVoteResultEvt += new robotpenController.multiVoteResult(Form1_multiVoteResultEvt);
                robotpenController.GetInstance().voteAnswerResultEvt += new robotpenController.voteAnswerResult(Form1_voteAnswerResultEvt);
                robotpenController.GetInstance().subDeviceMacEvt += new robotpenController.subDeviceMac(Form1_subDeviceMacEvt);
            }
            else if (demo_type == demoEnum.NODE_DEMO|| demo_type == demoEnum.T7E_DEMO)
            {
                // 绑定相关事件即可
                robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
                robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;
                robotpenController.GetInstance().setDeviceNetNumEvt += Form1_setDeviceNetNumEvt;
            }
            else if (demo_type == demoEnum.DONGLE_DEMO)
            {
                robotpenController.GetInstance().dongleStatusEvt += new robotpenController.dongleStatus(Form1_dongleStatusEvt);
                robotpenController.GetInstance().dongleScanResultEvt += new robotpenController.dongleSanResult(Form1_dongleScanResultEvt);
                robotpenController.GetInstance().dongleVersionEvt += new robotpenController.dongleVersion(Form1_dongleVersionEvt);
                robotpenController.GetInstance().dongleDataPacketEvt += new robotpenController.dongleDataPacket(Form1_dongleDataPacketEvt);
                robotpenController.GetInstance().slaveStatusEvt += new robotpenController.slaveStatus(Form1_slaveStatusEvt);
                robotpenController.GetInstance().slaveVersionEvt += new robotpenController.slaveVersion(Form1_slaveVersionEvt);
                robotpenController.GetInstance().enterAdjustModeEvt += new robotpenController.enterAdjustMode(Form1_enterAdjustModeEvt);
                robotpenController.GetInstance().adjustResultEvt += new robotpenController.adjustResult(Form1_adjustResultEvt);
                robotpenController.GetInstance().dongleDataOptimizePacketEvt += new robotpenController.dongleOptimizeDataPacket(Form1_dongleOptimizeDataPacketEvt);
            }
            else if (demo_type == demoEnum.P1_DEMO)
            {
                robotpenController.GetInstance().returnP1PointDataEvt += new robotpenController.returnP1PointData(Form1_returnP1PointDataEvt);
                robotpenController.GetInstance().returnP1OptimizePointDataEvt += new robotpenController.returnP1OptimizePointData(Form1_returnP1OptimizePointDataEvt);
            }

            // 所有设备均消费此事件
            date = new RobotpenGateway.robotpenController.returnPointData(Form1_bigDataReportEvt1);
            robotpenController.GetInstance().initDeletgate(ref date);
            robotpenController.GetInstance().returnOptimizePointDataEvt += new robotpenController.returnOptimizePointData(Form1_returnOptimizePointDataEvt);

            //////////////////////////////////////////////////////////////////////////
            // 所有设备均注册该页码显示消息 目前只有T9设备才会有页码识别功能, 客户代码可以根据设备来判断是否消费该事件
            robotpenController.GetInstance().showPageEvt += new robotpenController.ShowPage(Form1_showPageEvt);
            // T8A 按键消息 为了适应其他demo也能响应， 所以任何demo都消费此事件， 客户代码可根据设备类型判断是否消费此事件
            robotpenController.GetInstance().keyPressEvt += new robotpenController.KeyPress(Form1_keyPressEvt);
            //////////////////////////////////////////////////////////////////////////

            // offline note event
            // 离线笔记同步中
            robotpenController.GetInstance().startSyncNoteDataEvt += new robotpenController.startSyncNoteData(Form1_startSyncNoteDataEvt);
            robotpenController.GetInstance().syncNoteDataEvt += new robotpenController.syncNoteData(Form1_syncNoteDataEvt);
            robotpenController.GetInstance().endSyncNoteDataEvt += new robotpenController.endSyncNoteData(Form1_endSyncNoteDataEvt);
            robotpenController.GetInstance().getOfflineNoteDataEvt += new robotpenController.getOfflineNoteData(Form1_getOfflineNoteDataEvt);

            //robotpenController.GetInstance().resultCallback_tEvt += new robotpenController.ResultCallback_t(rCall);
            //robotpenController.GetInstance().SetOnResultCallback();
            //robotpenController.GetInstance().SetUserInfo(user_id, secret, source);
            //robotpenController.GetInstance().SetSyncTimeout();

            //robotpenController.GetInstance().SetCacheStatus(true);
            //robotpenController.GetInstance().setSyncTimeout();
        }

        public void rCall(int i, string s, IntPtr IntPtr)
        {
            string result = string.Empty;
            if(i==2)
            {
                result=Base64.DecodeBase64(s);
            }
            else
            {
                result = s;
            }
            MessageBox.Show(result);
        }

        private void CheckIsOem()
        {
            bool isOem = Convert.ToBoolean(System.Configuration.ConfigurationSettings.AppSettings["isoem"]);
            if(isOem)
            {
                string oemKey = System.Configuration.ConfigurationSettings.AppSettings["oemkey"];
                robotpenController.GetInstance().setKey(oemKey);
            }
        }

        #region GATEWAY_DEMO界面控制
        /// <summary>
        /// 2.4G网关调试模式下，书写波动控件加载
        /// </summary>
        private void GATEWAY_DEMO_NodeWindowShow(int nSubWinStartX,int nSubWinStartY)
        {
            // 获取最右边控件的坐标
            int xCount = 0;
            this.Width = 1386;
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

                this.subNodeWindow[i] = new UserControl1(canvasType.GATEWAY);
                this.subNodeWindow[i].m_nIndex = i + 1;
                this.subNodeWindow[i].canvasShowEvt += dbClkCanvas;
                this.subNodeWindow[i].setControlSize(nWinSize, nWinSize);
                this.subNodeWindow[i].Location = new Point(nX, nSubWinStartY);
                this.subNodeWindow[i].BackColor = Color.Black;
                this.Controls.Add(this.subNodeWindow[i]);
                //this.subNodeWindow[i].start();
                this.SuspendLayout();
            }
        }
        /// <summary>
        /// 2.4G网关调试模式下，界面显示
        /// </summary>
        private void GATEWAY_DEMO_ControlShow()
        {
            this.GATEWAYGroup.Location = this.USBOfflineGroup.Location;
            this.GATEWAYGroup.Show();
            this.USBOfflineGroup.Hide();
        }
        #endregion

        #region NODE_DEMO界面控制
        private void NODE_DEMO_NodeWindowShow(int nSubWinStartX, int nSubWinStartY) {
            nodeDataWindow = new UserControl1(canvasType.NODE);
            this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
            this.nodeDataWindow.setControlSize(200, 200);
            this.nodeDataWindow.Location = new Point(nSubWinStartX, nSubWinStartY);
            this.nodeDataWindow.BackColor = Color.Black;
            this.Controls.Add(this.nodeDataWindow);
            //this.subNodeWindow[i].start();
            this.SuspendLayout();

            this.WindowState = FormWindowState.Normal;
            this.Size = new Size(800, 730);
        }
        #endregion

        #region DONGLE_DEMO界面控制
        private void DONGLE_DEMO_NodeWindowShow(int nSubWinStartX, int nSubWinStartY)
        {
            this.WindowState = FormWindowState.Normal;
            this.slave_listView.Columns.Add("Num", 50, HorizontalAlignment.Center);
            this.slave_listView.Columns.Add("名称", 120, HorizontalAlignment.Center);
            this.slave_listView.Columns.Add("Mac地址", 300, HorizontalAlignment.Center);

            nodeDataWindow = new UserControl1(canvasType.DONGLE);
            this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
            this.nodeDataWindow.setControlSize(200, 200);
            this.nodeDataWindow.Location = new Point(nSubWinStartX, nSubWinStartY);
            this.nodeDataWindow.BackColor = Color.Black;
            this.Controls.Add(this.nodeDataWindow);
            //this.subNodeWindow[i].start();
            this.SuspendLayout();
            this.Size = new Size(800, 800);
        }
        private void DONGLE_DEMO_ControlShow()
        {
            this.BLEGroup.Location = this.USBOfflineGroup.Location;
            this.BLEGroup.Show();
            this.USBOfflineGroup.Hide();
            this.groupBox1.Hide();
        }
        #endregion

        #region P1_DEMO界面控制
        private void P1_DEMO_NodeWindowShow(int nSubWinStartX, int nSubWinStartY)
        {
            this.WindowState = FormWindowState.Normal;
            nodeDataWindow = new UserControl1(canvasType.P1);
            this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
            this.nodeDataWindow.setControlSize(200, 200);
            this.nodeDataWindow.Location = new Point(nSubWinStartX, nSubWinStartY);
            this.nodeDataWindow.BackColor = Color.Black;
            this.Controls.Add(this.nodeDataWindow);
            this.SuspendLayout();
            this.Size = new Size(800, 530);
            this.groupBox1.Hide();
        }
        #endregion

        #region T7E_DEMO界面控制
        private void T7E_DEMO_NodeWindowShow(int nSubWinStartX, int nSubWinStartY)
        {
            this.WindowState = FormWindowState.Normal;
            nodeDataWindow = new UserControl1(canvasType.T7E_TS);
            this.nodeDataWindow.canvasShowEvt += dbClkCanvas;
            this.nodeDataWindow.setControlSize(200, 200);
            this.nodeDataWindow.Location = new Point(nSubWinStartX, nSubWinStartY);
            this.nodeDataWindow.BackColor = Color.Black;
            this.Controls.Add(this.nodeDataWindow);
            this.SuspendLayout();
            this.Size = new Size(800, 530);
            this.groupBox1.Hide();
        }
        #endregion

        #region listview更新
        /// <summary>
        /// 第一次加载页面，加载当前usb连接设备
        /// </summary>
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
                    eDeviceType dtype = eDeviceType.Unknow;
                    if (robotpenController.GetInstance()._GetAvailableDevice(i, ref npid, ref nvid, ref strDeviceName, ref dtype))
                    {
                        this.listView1.Items.Add(strDeviceName);
                        string strVID = Convert.ToString(nvid);
                        this.listView1.Items[i].SubItems.Add(strVID);
                        string strPID = Convert.ToString(npid);
                        this.listView1.Items[i].SubItems.Add(strPID);
                        string strDType = Convert.ToString((int)dtype);
                        this.listView1.Items[i].SubItems.Add(strDType);
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
        /// <summary>
        /// 委托函数，用于异步修改listview显示的USB连接设备信息
        /// </summary>
        private delegate void LvDelegate();
        /// <summary>
        /// 委托实例函数，用于异步修改listview显示的USB连接设备信息
        /// </summary>
        private void SetListView()
        {
            if (this.listView1.InvokeRequired)
            {
                LvDelegate lvD = new LvDelegate(this.SetListView);
                this.Invoke(lvD, new object[] {  });
            }
            else
            {
                if (this.open_button.Text == "关闭设备")
                {
                    robotpenController.GetInstance()._CloseConnect();
                    resetDevice();
                }
                else
                {
                    this.listView1.Items.Clear();
                    loadDevice();
                }
            }
        }


        #endregion

        // 重置相关参数
        public void resetDevice()
        {
            this.open_button.Text = "打开设备";

            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                for (int i = 0; i < subNodeWindow.Length; ++i)
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

            this.version_label_show.Text = "版本号";
            this.status_label.Text = "状态";
            this.mac_label_show.Text = "mac地址";
            this.DeviceSize.Text = "";

            this.listView1.Items.Clear();

            // 重新加载设备
            loadDevice();
        }

        // 打开或关闭设备
        private void open_button_Click(object sender, EventArgs e)
        {
            if (this.open_button.Text == "关闭设备")
            {
                robotpenController.GetInstance()._CloseConnect();
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
            string strDeviceType = this.listView1.SelectedItems[0].SubItems[3].Text;
            eDeviceType deviceType = (eDeviceType)Convert.ToInt32(strDeviceType);

            if (nPid == Convert.ToUInt16(RobotpenGateway.DEIVE_PID.GATEWAY_PID))
            {
                if (demo_type == demoEnum.NODE_DEMO)
                {
                    MessageBox.Show("当前为node USB模式 无法演示网关设备功能, 如需打开网关设备请切换到网关demo模式!");
                    return;
                }

            }

            if (deviceType==eDeviceType.T7PL|| deviceType == eDeviceType.T7E || deviceType == eDeviceType.S1_DE || deviceType == eDeviceType.J7E)
            {
                this.SwichModeBtn.Visible = true;
            }

            robotpenController.GetInstance()._ConnectInitialize(deviceType, IntPtr.Zero);

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
                else
                {
                    robotpenController.GetInstance()._Send(cmdId.GetMassMac);
                }
            }
            else
            {
                robotpenController.GetInstance()._CloseConnect();
                this.open_button.Text = "打开设备";
                this.set_button.Enabled = false;
            }
        }

        /// <summary>
        /// 按键回调函数，T8A
        /// </summary>
        /// <param name="Value"></param>
        void Form1_keyPressEvt(eKeyPress Value)
        {
            switch (Value)
            {
                case eKeyPress.CLICK:
                    break;
                case eKeyPress.DBCLICK:
                    break;
                case eKeyPress.PAGEUP:
                    break;
                case eKeyPress.PAGEDOWN:
                    break;
                case eKeyPress.CREATEPAGE:
                    break;
                case eKeyPress.KEY_A:
                    break;
                case eKeyPress.KEY_B:
                    break;
                case eKeyPress.KEY_C:
                    break;
                case eKeyPress.KEY_D:
                    break;
                case eKeyPress.KEY_E:
                    break;
                case eKeyPress.KEY_F:
                    break;
                case eKeyPress.KEY_UP:
                    break;
                case eKeyPress.KEY_DOWN:
                    break;
                case eKeyPress.KEY_YES:
                    break;
                case eKeyPress.KEY_NO:
                    break;
                case eKeyPress.KEY_CANCEL:
                    break;
                case eKeyPress.KEY_OK:
                    break;
                case eKeyPress.PAGEUPCLICK:
                    break;
                case eKeyPress.PAGEUPDBCLICK:
                    break;
                case eKeyPress.PAGEUPPRESS:
                    break;
                case eKeyPress.PAGEDOWNCLICK:
                    break;
                case eKeyPress.PAGEDOWNDBCLICK:
                    break;
                case eKeyPress.PAGEDOWNPRESS:
                    break;
            }
            CallDelegate(Value.ToString());
        }
        /// <summary>
        /// 设备插拔消息，更新listview
        /// </summary>
        /// <param name="bStatus"></param>
        /// <param name="uPid"></param>
        void Form1_deviceChangeEvt(bool bStatus, ushort uPid)
        {
            //throw new NotImplementedException();
            //Console.WriteLine("设备状态{0} PID = {1}", bStatus, uPid);
            SetListView();
        }

        private ushort m_nPageNumber = 0;
        private ushort m_nNoteNumber = 0;

        Dictionary<int, KeyValuePair<int, int>> noteAndPageNumberCache = new Dictionary<int, KeyValuePair<int, int>>();

        // T9页码识别事件
        void Form1_showPageEvt(byte deviceIndex, byte pageNumber, byte noteNumber)
        {
            if (demo_type == demoEnum.GATEWAY_DEMO)
            {
                if (canvasWindow[deviceIndex] != null)
                {
                    canvasWindow[deviceIndex].noteNumber = noteNumber;
                    canvasWindow[deviceIndex].pageNumber = pageNumber;
                    canvasWindow[deviceIndex].updatePageInfo();
                }

                if (noteAndPageNumberCache.ContainsKey(deviceIndex))
                {
                    noteAndPageNumberCache[deviceIndex] = new KeyValuePair<int, int>(pageNumber, noteNumber);
                }
                else
                {
                    noteAndPageNumberCache.Add(deviceIndex, new KeyValuePair<int, int>(pageNumber, noteNumber));
                }
            }
            else
            {
                m_nPageNumber = pageNumber;
                m_nNoteNumber = noteNumber;

                if (nodeCanvasWindow != null)
                {
                    nodeCanvasWindow.noteNumber = m_nNoteNumber;
                    nodeCanvasWindow.pageNumber = m_nPageNumber;
                    nodeCanvasWindow.updatePageInfo();
                }
            }
        }

        // 收到设备优化点数据
        void Form1_returnOptimizePointDataEvt(byte bPenStatus, ushort bx, ushort by, float fPenWidthF)
        {

            if (null != nodeDataWindow)
            {
                nodeDataWindow.dataArrive(Convert.ToInt32(bx), Convert.ToInt32(by));
            }
            if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                return;

            int npenStatus = Convert.ToInt32(bPenStatus);
            if (fPenWidthF == 0)
            {
                npenStatus = 0;
            }
            nodeCanvasWindow.recvOptimizeData(npenStatus, Convert.ToInt32(bx), Convert.ToInt32(by), fPenWidthF);

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

        // 收到P1优化点数据
        private void Form1_returnP1OptimizePointDataEvt(byte bPenStatus, ushort sx, ushort sy, float fPenWidth)
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
            nodeCanvasWindow.recvOptimizeData(npenStatus, Convert.ToUInt16(sx), Convert.ToUInt16(sy), fPenWidth);
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

        // dongle优化数据上报
        private void Form1_dongleOptimizeDataPacketEvt(byte bPenStatus, ushort sx, ushort sy, float fPenWidth)
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
            nodeCanvasWindow.recvOptimizeData(npenStatus, Convert.ToUInt16(sx), Convert.ToUInt16(sy), fPenWidth);
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
                        SetDeviceHW();
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
            IsSyncNodeData = false;
            if (demo_type == demoEnum.DONGLE_DEMO)
            {
                UpdateControlUI(strNoteCount, updateControl.eofflinecount);
                robotpenController.GetInstance()._Send(cmdId.SyncEnd);
            }
            else
            {
                UpdateControlUI(strNoteCount, updateControl.esyncofflinenotefinish);
            }
        }

        private void Form1_syncNoteDataEvt(byte bPenStatus, short sx, short sy, short sPress)
        {
            if (null != nodeDataWindow)
            {
                nodeDataWindow.dataArrive(Convert.ToInt32(sx), Convert.ToInt32(sy));
            }
            if (!IsSyncNodeData)
            {
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                    return;

                Console.WriteLine("sPress={0} | sx={1} | y={2}", sPress, sx, sy);
                nodeCanvasWindow.recvData(sPress, Convert.ToInt32(sx), Convert.ToInt32(sy), 0);
            }
            else
            {
                nodeOfflineCanvasWindow.recvData(sPress, Convert.ToInt32(sx), Convert.ToInt32(sy), 0);
            }
        }

        private bool IsSyncNodeData = false;
        private void Form1_startSyncNoteDataEvt(byte noteCount, ref note_header_info noteHeaderInfo)
        {
            string strNoteCount = "离线笔迹:" + Convert.ToInt32(noteCount) + "条";
            IsSyncNodeData = true;
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
            esyncofflinenotefinish,
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
                        System.Windows.Forms.Label label;
                        if (demo_type == demoEnum.DONGLE_DEMO)
                        {
                            label = this.offline_label;
                        }
                        else
                        {
                            label = this.labelnote;
                        }
                        if (label.InvokeRequired)
                        {
                            while (!label.IsHandleCreated)
                            {
                                if (label.Disposing || label.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            label.Invoke(d, new object[] { param, uty });
                        }
                        else
                        {
                            label.Text = param;
                        }
                    }
                    break;
                case updateControl.esyncofflinenotefinish:
                    {
                        if (this.label_sync_offline_tip.InvokeRequired)
                        {
                            while (!this.label_sync_offline_tip.IsHandleCreated)
                            {
                                if (this.label_sync_offline_tip.Disposing || this.label_sync_offline_tip.IsDisposed)
                                {
                                    return;
                                }
                            }
                            UpdateControlDelegate d = new UpdateControlDelegate(UpdateControlUI);
                            this.label_sync_offline_tip.Invoke(d, new object[] { "", uty });
                        }
                        else
                        {
                            this.label_sync_offline_tip.Text = "同步离线笔记完成";
                            end_sync_button_Click(null, null);

                        }
                    }break;
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
        private TrailsShowFrom nodeOfflineCanvasWindow = null;

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

                    // 获取页码信息
                    if (noteAndPageNumberCache.ContainsKey(nIndex - 1))
                    {
                        canvasWindow[nIndex - 1].pageNumber = noteAndPageNumberCache[nIndex - 1].Key;
                        canvasWindow[nIndex - 1].noteNumber = noteAndPageNumberCache[nIndex - 1].Value;
                    }
                }
                else
                {
                    canvasWindow[nIndex - 1].TopMost = true;
                    canvasWindow[nIndex - 1].Show();
                    canvasWindow[nIndex - 1].Text = strIndex;
                }
            }
            else if (demo_type == demoEnum.NODE_DEMO )
            {
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                {
                    nodeCanvasWindow = CreateNodeCanvasWindow(nodeCanvasWindow, strIndex);
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
                    if (this.slave_name_textBox.Text != "" && this.slave_name_textBox.Text.Contains("T9"))
                    {
                        nodeCanvasWindow = new TrailsShowFrom(16650, 22015);
                    }
                    else
                    {
                        nodeCanvasWindow = new TrailsShowFrom(canvasType.DONGLE);
                    }
                    nodeCanvasWindow.bScreenO = bScreen;
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                    nodeCanvasWindow.canvastype = canvasType.DONGLE;
                    if (!bScreen)
                    {
                        //nodeCanvasWindow.Size = new Size(426, 625);
                        nodeCanvasWindow.Size = new Size(826, 1025);
                    }
                    else
                    {
                        nodeCanvasWindow.Size = new Size(625, 480);
                    }
                    nodeCanvasWindow.pageNumber = m_nPageNumber;
                    nodeCanvasWindow.noteNumber = m_nNoteNumber;
                }
                else
                {
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                }
            }
            else if (demo_type == demoEnum.P1_DEMO || demo_type == demoEnum.T7E_DEMO)
            {
                canvasType ctype = (demo_type == demoEnum.P1_DEMO) ? canvasType.P1 : canvasType.T7E_TS;
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                {
                    nodeCanvasWindow = new TrailsShowFrom(ctype);
                    nodeCanvasWindow.bScreenO = bScreen;
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                    nodeCanvasWindow.canvastype = ctype;
                    nodeCanvasWindow.pageNumber = m_nPageNumber;
                    nodeCanvasWindow.noteNumber = m_nNoteNumber;
//                     if (!bScreen)
//                     {
//                         nodeCanvasWindow.Size = new Size(426, 625);
//                     }
//                     else
//                     {
//                         nodeCanvasWindow.Size = new Size(625, 480);
//                     }
                }
                else
                {
                    nodeCanvasWindow.TopMost = true;
                    nodeCanvasWindow.Show();
                    nodeCanvasWindow.Text = strIndex;
                }
            }
        }

        public TrailsShowFrom CreateNodeCanvasWindow(TrailsShowFrom _nodeCanvasWindow, string _strIndex)
        {
            _nodeCanvasWindow = new TrailsShowFrom(canvasType.NODE);
            _nodeCanvasWindow.bScreenO = bScreen;
            _nodeCanvasWindow.TopMost = true;
            _nodeCanvasWindow.Show();
            _nodeCanvasWindow.Text = _strIndex;
            _nodeCanvasWindow.canvastype = canvasType.NODE;
            _nodeCanvasWindow.pageNumber = m_nPageNumber;
            _nodeCanvasWindow.noteNumber = m_nNoteNumber;
            if (!bScreen)
            {
                _nodeCanvasWindow.Size = new Size(480, 625);
            }
            else
            {
                _nodeCanvasWindow.Size = new Size(625, 480);
            }
            return _nodeCanvasWindow;
        }

        private RobotpenGateway.robotpenController.returnPointData date = null;//new RobotpenGateway.robotpenController.returnPointData(Form1_bigDataReportEvt1);


        
        // 打开设备时上报离线笔记数量
        void Form1_getOfflineNoteDataEvt(byte noteCount)
        {
            //throw new NotImplementedException();
            string strNoteCount = "离线笔迹:" + Convert.ToInt32(noteCount) + "条";
            UpdateControlUI(strNoteCount, updateControl.eofflinecount);

        }

        void Form1_subDeviceMacEvt(int nIndex, string strMac)
        {
            //throw new NotImplementedException();
            Console.WriteLine("recv device mac addr deviceIndex={0} macAddr={1}", nIndex, strMac);
        }

        // 抢答结果事件
        void Form1_voteAnswerResultEvt(byte deviceIndex, byte result)
        {
            if (deviceIndex >= subNodeWindow.Length || subNodeWindow[deviceIndex] == null)
                return;

            string str = Convert.ToChar(result).ToString();
            subNodeWindow[deviceIndex].setVoteMode(str);
        }

        // 多选结果
        void Form1_multiVoteResultEvt(multi_vote_result res)
        {
            if (subNodeWindow[res.deviceIndex] == null)
                return;

            string str = System.Text.Encoding.ASCII.GetString(res.res, 0, res.res.Length);
            subNodeWindow[res.deviceIndex].setVoteMode(str);
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
                Console.WriteLine("sPress={0} | sx={1} | y={2} | status={3}", bPress, bx, by, bPenStatus);
                if(bPenStatus!=17&& bPenStatus!=33)
                {
                    bPenStatus = 0;
                }
                nodeCanvasWindow.recvData(bPenStatus, Convert.ToInt32(bx), Convert.ToInt32(by), bPress);
            }
            else if (demo_type == demoEnum.T7E_DEMO)
            {
                if (null != nodeDataWindow)
                {
                    nodeDataWindow.dataArrive(Convert.ToInt32(bx), Convert.ToInt32(by));
                }
                if (nodeCanvasWindow == null || nodeCanvasWindow.IsDisposed)
                    return;

                int npenStatus = Convert.ToInt32(bPenStatus);
                if (npenStatus != 17)
                {
                    npenStatus = 0;
                }
                nodeCanvasWindow.recvData(npenStatus, Convert.ToInt32(bx), Convert.ToInt32(by), 0);
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
        private void Form1_gatewatVersionEvt(string strVersion, byte bCustomNum, byte bClassNum, byte bDeviceNum, string strMac)
        {
            updateDeviceVersionLabel(strVersion);
            updateMacTextBox(strMac);
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
                        Thread t = new Thread(Thread_NodeSTANDBY);
                        t.Start();
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
                        Thread t1 = new Thread(Thread_NodeActive);
                        t1.Start();
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
                case GATEWAY_STATUS.NEBULA_STATUS_VOTE_ANSWER:
                    strStatus = ("VOTE_ANSWER");
                    break;
                case GATEWAY_STATUS.NEBULA_STATUS_CONFIG:
                    strStatus = ("CONFIG");
                    break;
                case GATEWAY_STATUS.NEBULA_STATUS_DFU:
                   strStatus = ("DFU");
                    break;
                case GATEWAY_STATUS.NEBULA_STATUS_MULTI_VOTE:
                    strStatus = ("MULTI_VOTE");
                    break;
                default:
                    {
                        strStatus = "UNKNOW";
                    }
                    break;
            }
            CallDelegate(strStatus);
        }

        private void Form1_nodeDeviceModeEvt(byte nStatus)
        {
            string str = string.Empty;
            switch (nStatus)
            {
                case 0:
                    str = "BLE";
                    break;
                case 1:
                    str = "2.4G";
                    break;
                case 2:
                    str = "USB";
                    break;
                default:
                    str = "Unknow";
                    break;
            }
            updateModeLabel(str);
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

        // 更新连接模式
        public void updateModeLabel(string strMode)
        {
            if (this.mode_label.InvokeRequired)
            {
                while (!this.mode_label.IsHandleCreated)
                {
                    if (this.mode_label.Disposing || this.mode_label.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateModeLabel);
                this.mode_label.Invoke(d, new object[] { strMode });
            }
            else
            {
                this.mode_label.Text = strMode;
            }
        }

        /// <summary>
        /// 更新设备MacNum
        /// </summary>
        /// <param name="strMacNum"></param>
        public void updateMacTextBox(string strMacNum)
        {
            if (this.mac_label_show.InvokeRequired)
            {
                while (!this.mac_label_show.IsHandleCreated)
                {
                    if (this.mac_label_show.Disposing || this.device_textBox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateStatusLabel d = new UpdateStatusLabel(updateMacTextBox);
                this.mac_label_show.Invoke(d, new object[] { strMacNum });
            }
            else
            {
                this.mac_label_show.Text = strMacNum;
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
            //if (this.open_button.Text == "关闭设备")
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
                robotpenController.GetInstance()._Send(cmdId.VoteMulti);
            }else if (this.comboBox2.SelectedIndex == 2)
            {
                robotpenController.GetInstance()._Send(cmdId.VoteAnswer);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.VoteEnd);
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
            this.DeviceSize.Text = "";
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

        private void button4_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.SyncBegin);
        }

        private void update_button_Click(object sender, EventArgs e)
        {

        }

        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            this.toolStripStatusLabel1.Text = this.Width.ToString() + "," + this.Height.ToString();
            this.statusStrip1.Location = new Point(0, this.Height - 61);
            this.statusStrip1.Width = this.Width - 16;
        }

        private void BaseOpenOfflineNote_Click(object sender, EventArgs e)
        {
            //离线画布
            if (nodeOfflineCanvasWindow == null || nodeOfflineCanvasWindow.IsDisposed)
            {
                nodeOfflineCanvasWindow = CreateNodeCanvasWindow(nodeOfflineCanvasWindow, "OfflineNotes");
            }
            else
            {
                nodeOfflineCanvasWindow.TopMost = true;
                nodeOfflineCanvasWindow.Show();
                nodeOfflineCanvasWindow.Text = "OfflineNotes";
            }
            this.StartSyncBtn.Visible = true;
            this.EndSyncBtn.Visible = true;
        }

        private void BleOpenOfflineNote_Click(object sender, EventArgs e)
        {
            //离线画布
            if (nodeOfflineCanvasWindow == null || nodeOfflineCanvasWindow.IsDisposed)
            {
                nodeOfflineCanvasWindow = CreateNodeCanvasWindow(nodeOfflineCanvasWindow, "OfflineNotes");
            }
            else
            {
                nodeOfflineCanvasWindow.TopMost = true;
                nodeOfflineCanvasWindow.Show();
                nodeOfflineCanvasWindow.Text = "OfflineNotes";
            }
            this.start_sync_button.Visible = true;
            this.end_sync_button.Visible = true;
        }

        private void EndSyncBtn_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.SyncEnd);
        }

        private void SwichModeBtn_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.SwitchMode);
        }


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.comboBox1.SelectedIndex)
            {
                case 0:
                    {
                        bScreen = true;
                        robotpenController.GetInstance().rotate(-180);
                        break;
                    }
                case 1:
                    {
                        bScreen = false;
                        robotpenController.GetInstance().rotate(-90);
                        break;
                    }
                case 2:
                    {
                        bScreen = true;
                        //robotpenController.GetInstance().setIsHorizontal(bScreen);
                        robotpenController.GetInstance().rotate(0);
                        break;
                    }
                default:
                    break;
            }
        }


        #region 更新from控件的方法
        public delegate void UpdateLabel(string str1, System.Windows.Forms.Label lable);
        // 更新lable标签
        public void updateLabel(string param, System.Windows.Forms.Label lable)
        {
            if (lable.InvokeRequired)
            {
                while (!lable.IsHandleCreated)
                {
                    if (lable.Disposing || lable.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateLabel d = new UpdateLabel(updateLabel);
                lable.Invoke(d, new object[] { param, lable });
            }
            else
            {
                lable.Text = param;
            }
        }


        public delegate void UpdateComboBox(int selectIndex, System.Windows.Forms.ComboBox combobox);
        // 更新lable标签
        public void updateComboBox(int selectIndex, System.Windows.Forms.ComboBox combobox)
        {
            if (combobox.InvokeRequired)
            {
                while (!combobox.IsHandleCreated)
                {
                    if (combobox.Disposing || combobox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateComboBox d = new UpdateComboBox(updateComboBox);
                combobox.Invoke(d, new object[] { selectIndex, combobox });
            }
            else
            {
                combobox.SelectedIndex = selectIndex;
            }
        }
        #endregion

        /// <summary>
        /// DEVICE_ACTIVE状态异步线程
        /// </summary>
        private void Thread_NodeActive()
        {
            Thread.Sleep(200);
            //int t = robotpenController.GetInstance().OpenRecog(3000, true);
            //Console.WriteLine("OpenRecog:" + t);
            SetDeviceHW();
            ReSetScreen();
        }
        /// <summary>
        /// DEVICE_STANDBY状态异步线程
        /// </summary>
        private void Thread_NodeSTANDBY()
        {
            Thread.Sleep(200);
            SetDeviceHW();
            ReSetScreen();
            SetDevicePen();
        }

        /// <summary>
        /// 获取宽高
        /// </summary>
        private void SetDeviceHW()
        {
            int width = robotpenController.GetInstance().getWidth();
            int height = robotpenController.GetInstance().getHeight();
            updateLabel(string.Format("宽:{0},高:{1}", width, height), this.DeviceSize);
        }

        /// <summary>
        /// 模式切换
        /// </summary>
        private void SetDevicePen()
        {
            robotpenController.GetInstance()._Send(cmdId.SwitchMode);
        }

        /// <summary>
        /// 打开设备设置横竖屏
        /// </summary>
        private void ReSetScreen()
        {
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
            if (bScreen)
            {
                updateComboBox(0, this.comboBox1);
            }
            else
            {
                updateComboBox(1, this.comboBox1);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if(this.button3.Text== "开启优化笔记")
            {
                this.button3.Text = "关闭优化笔记";
                // 设置笔宽度
                robotpenController.GetInstance().setPenWidthF((float)2);
                // 是否开启笔记优化
                robotpenController.GetInstance().setTrailsIsOptimize(true);
                // 是否开启压感
                robotpenController.GetInstance().setPressStatus(true);
                //设置拖尾阈值，设置的越小，拖尾越长(0~1) 默认0.4
                robotpenController.GetInstance().setPointDelay((float)0.4);
                // 设置粗细变化阈值，设置的越小，粗细变化越小 默认0.026
                robotpenController.GetInstance().setPointDamping((float)0.026);
            }
            else
            {
                this.button3.Text = "开启优化笔记";
                // 是否开启笔记优化
                robotpenController.GetInstance().setTrailsIsOptimize(false);
                // 是否开启压感
                robotpenController.GetInstance().setPressStatus(false);
            }
        }

        string note_key = string.Empty;


        private void button4_Click_1(object sender, EventArgs e)
        {
            note_key = Guid.NewGuid().ToString();
            Console.WriteLine(note_key);
            int t= robotpenController.GetInstance().CreateRecogNote(note_key,3,0);
            Console.WriteLine(t);
            
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Console.WriteLine("key"+note_key);
            int t2 = robotpenController.GetInstance().AppendNote(note_key);
            int t = robotpenController.GetInstance().RecogNote(user_id, note_key);
            Console.WriteLine(t);
        }
    }
}
