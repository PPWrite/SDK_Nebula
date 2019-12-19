using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using RobotpenGateway;
using RobotPenTestDll.ClassHelper;
using WindowsForms.Class;

namespace WindowsForms
{
    public partial class Form1_NoAngle : Form
    {
        [System.Runtime.InteropServices.DllImport("kernel32.dll", CharSet = System.Runtime.InteropServices.CharSet.Auto)]
        public static extern void OutputDebugString(string message);

        public bool usbIsConnected = false;

        Angle angle = Angle._270;
        eDeviceType deviceType = eDeviceType.Unknow;
        /// <summary>
        /// 点缩放比例
        /// </summary>
        private double m_nCompress = 0;
        private double m_nCompress_x = 0;
        private double m_nCompress_y = 0;

        /// <summary>
        /// 0:画布根据板子适配
        /// 1:板子根据画布适配
        /// </summary>
        private int type = 1;//默认画笔根据板子适配
        bool bScreenO = false;//判断是否是横屏，默认横屏,true:横屏幕；false:竖屏
        Drawing drawing;

        List<RobotPoint> plist = new List<RobotPoint>();

        //画布宽高
        private int m_nDeviceW = 29700;
        private int m_nDeviceH = 21000;

        private RobotpenGateway.robotpenController.returnPointData date = null;

        private int nResource = 0;
        private ReportRate RR = ReportRate.R_200;

        eDeviceType pid = eDeviceType.T9W_H;
        string Mac = string.Empty;

        int Recog_create = 0;
        int Recog_adddate = 0;
        int Recog_start = 0;

        public bool isOpen = true;

        public Form1_NoAngle()
        {
            InitPen();
            InitializeComponent();
        }

        #region 罗博智慧笔
        //初始化笔服务
        private void InitPen()
        {
            //robotpenController.GetInstance().setKey("robotpen");
            //robotpenController.GetInstance().setKey("36e4a46f689611e8b441060400ef5315");
            robotpenController.GetInstance()._ConnectInitialize(eDeviceType.Gateway, IntPtr.Zero);
            robotpenController.GetInstance().deviceChangeEvt += new robotpenController.DeviceChange(Form1_deviceChangeEvt);
            robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;
            robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
            robotpenController.GetInstance().searchModeEvt += Form1_searchModeEvt;

            // 所有设备均注册该页码显示消息 目前只有T9设备才会有页码识别功能, 客户代码可以根据设备来判断是否消费该事件
            robotpenController.GetInstance().showPageEvt += new robotpenController.ShowPage(Form1_showPageEvt);
            // T8A 按键消息 为了适应其他demo也能响应， 所以任何demo都消费此事件， 客户代码可根据设备类型判断是否消费此事件
            robotpenController.GetInstance().keyPressEvt += new robotpenController.KeyPress(Form1_keyPressEvt);

            robotpenController.GetInstance().PageSensorCallback_Evt += Rbtnet__PageSensorEvt_;

            date = new RobotpenGateway.robotpenController.returnPointData(Form1_bigDataReportEvt1);
            robotpenController.GetInstance().initDeletgate(ref date);

            robotpenController.GetInstance().returnOptimizePointDataEvt += new robotpenController.returnOptimizePointData(Form1_returnOptimizePointDataEvt);        
            

        }

        //---------------------------------------------------------------------
        bool isOptimize = false;
        private RobotPoint PreviousPoint = new RobotPoint();
        private List<RobotPoint> PointList = new List<RobotPoint>();
        private void Form1_returnOptimizePointDataEvt(byte bPenStatus, ushort bx, ushort by, float fPenWidthF)
        {
            switch (RR)
            {
                case ReportRate.R_200:
                    OptimizePointDataReport(bPenStatus, bx, by, fPenWidthF);
                    return;
                case ReportRate.R_160:
                case ReportRate.R_120:
                case ReportRate.R_80:
                case ReportRate.R_40:
                    RobotPoint rp = new RobotPoint()
                    {
                        bPenStatus = bPenStatus,
                        bx = bx,
                        by = by,
                        bWidth = fPenWidthF
                    };
                    if (bPenStatus != PreviousPoint.bPenStatus)
                    {
                        foreach (var item in PointList)
                        {
                            OptimizePointDataReport(item.bPenStatus, item.bx, item.by, item.bWidth);
                        }
                        PointList.Clear();
                        OptimizePointDataReport(bPenStatus, bx, by, fPenWidthF);
                    }
                    else
                    {
                        PointList.Add(rp);
                        if (PointList.Count == 6)
                        {
                            ReportRatePoint(PointList);
                        }
                    }
                    PreviousPoint = rp;
                    break;
            }

        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="bIndex"></param>
        /// <param name="bPenStatus"></param>
        /// <param name="bx"></param>
        /// <param name="by"></param>
        /// <param name="bPress"></param>
        private void Form1_bigDataReportEvt1(byte bIndex, byte bPenStatus, short bx, short by, short bPress)
        {
            Console.WriteLine(string.Format(@"x={0},y={1},s={2},p={3}", bx, by, bPenStatus, bPress));
            switch (RR)
            {
                case ReportRate.R_200:
                    bigDataReport(bIndex, bPenStatus, bx, by, bPress);
                    return;
                case ReportRate.R_160:
                case ReportRate.R_120:
                case ReportRate.R_80:
                case ReportRate.R_40:
                    RobotPoint rp = new RobotPoint()
                    {
                        bIndex = bIndex,
                        bPenStatus = bPenStatus,
                        bx = bx,
                        by = by,
                        bPress = bPress
                    };
                    if (bPenStatus != PreviousPoint.bPenStatus)
                    {
                        foreach (var item in PointList)
                        {
                            bigDataReport(item.bIndex, item.bPenStatus, item.bx, item.by, item.bPress);
                        }
                        PointList.Clear();
                        bigDataReport(bIndex, bPenStatus, bx, by, bPress);
                    }
                    else
                    {
                        PointList.Add(rp);
                        if (PointList.Count == 6)
                        {
                            ReportRatePoint(PointList);
                        }
                    }
                    PreviousPoint = rp;
                    break;
            }

        }
        private void ReportRatePoint(List<RobotPoint> _pList)
        {
            switch (RR)
            {
                case ReportRate.R_160:
                    PointList.RemoveAt(3);
                    break;
                case ReportRate.R_120:
                    PointList.RemoveAt(2);
                    PointList.RemoveAt(4);
                    break;
                case ReportRate.R_80:
                    PointList.RemoveAt(1);
                    PointList.RemoveAt(2);
                    PointList.RemoveAt(3);
                    break;
                case ReportRate.R_40:
                    PointList.RemoveAt(1);
                    PointList.RemoveAt(1);
                    PointList.RemoveAt(2);
                    PointList.RemoveAt(2);
                    break;
            }
            foreach (var item in PointList)
            {
                if(isOptimize)
                {
                    OptimizePointDataReport(item.bPenStatus, item.bx, item.by, item.bWidth);
                }
                else
                {
                    bigDataReport(item.bIndex, item.bPenStatus, item.bx, item.by, item.bPress);
                }
                
            }
            PointList.Clear();
        }
        private void bigDataReport(int bIndex, int bPenStatus, int bx, int by, int bPress)
        {
            RobotPoint rp = new RobotPoint()
            {
                bIndex = bIndex,
                bPenStatus = bPenStatus,
                bx = bx,
                by = by,
                bPress = bPress
            };
            plist.Add(rp);
            if (drawing != null&&isOpen)
            {
                drawing.recvData(Convert.ToInt32(bPenStatus), Convert.ToInt32(bx), Convert.ToInt32(by), bPress);
            }
        }
        private void OptimizePointDataReport(int bPenStatus, int bx, int by, float fPenWidthF)
        {
            RobotPoint rp = new RobotPoint()
            {
                bPenStatus = bPenStatus,
                bx = bx,
                by = by,
                bWidth = fPenWidthF
            };
            plist.Add(rp);
            if (drawing != null && isOpen)
            {
                drawing.recvOptimizeData(Convert.ToInt32(bPenStatus), Convert.ToInt32(bx), Convert.ToInt32(by), fPenWidthF);
            }
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
                        Thread t = new Thread(Thread_NodeSTANDBY);
                        t.Start();
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
                        Thread t2 = new Thread(Thread_NodeSTANDBY);
                        t2.Start();
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
                default:
                    {
                        strStatus = "UNKNOW";
                    }
                    break;
            }
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

        private void Form1_searchModeEvt(int modeType)
        {
            if(modeType==0)
            {
                robotpenController.GetInstance()._Send(cmdId.SwitchMode);
            }
        }

        // 设备版本号 
        private void Form1_gatewatVersionEvt(string strVersion, byte bCustomNum, byte bClassNum, byte bDeviceNum, string strMac)
        {
            Mac = strMac;
            updateLabel(strVersion, this.FirmwareLabel);
            updateLabel(Mac, this.MacLabel);
        }
        //---------------------------------------------------------------------

        /// <summary>
        /// 判断是否有设备连接
        /// </summary>
        public void CheckUsbConnect()
        {
            usbIsConnected = false;
            Thread.Sleep(200);
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
                        if(!usbIsConnected)
                        {
                            usbIsConnected = true;
                            deviceType = dtype;
                            robotpenController.GetInstance()._ConnectInitialize(deviceType, IntPtr.Zero);
                            int nRes = robotpenController.GetInstance()._ConnectOpen();
                            if (nRes != 0)
                            {
                                MessageBox.Show("设备自动连接失败，请重新插拔设备或尝试手动连接!");
                                usbIsConnected = false;
                                break;
                            }
                            //robotpenController.GetInstance()._Send(cmdId.SwitchMode);
                            robotpenController.GetInstance()._Send(cmdId.GetConfig);
                        }
 
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
        }
        /// <summary>
        /// DEVICE_ACTIVE状态异步线程
        /// </summary>
        private void Thread_NodeActive()
        {
            Thread.Sleep(200);
            ReSetScreen();
            SetDeviceHW();
        }
        /// <summary>
        /// DEVICE_STANDBY状态异步线程
        /// </summary>
        private void Thread_NodeSTANDBY()
        {
            Thread.Sleep(200);
            ReSetScreen();
            SetDevicePen();
            SetDeviceHW();
        }
        /// <summary>
        /// 模式切换
        /// </summary>
        private void SetDevicePen()
        {
            Thread.Sleep(100);
            robotpenController.GetInstance()._Send(cmdId.SearchMode);
            
        }
        /// <summary>
        /// 打开设备设置横竖屏
        /// </summary>
        private void ReSetScreen()
        {
            Thread.Sleep(100);
            if (bScreenO)
            {
                updateComboBox(2, this.comboBox1);
            }
            else
            {
                updateComboBox(1, this.comboBox1);
            }
        }
        /// <summary>
        /// 获取宽高
        /// </summary>
        private void SetDeviceHW()
        {
            Thread.Sleep(100);
            m_nDeviceW = robotpenController.GetInstance().getWidth();
            Thread.Sleep(100);
            m_nDeviceH = robotpenController.GetInstance().getHeight();

            updateLabel(string.Format("宽:{0},高:{1}", m_nDeviceW, m_nDeviceH), this.CoordinatesLabel);
            SetPictureBox();


        }

        /// <summary>
        /// 按键回调函数
        /// </summary>
        /// <param name="Value"></param>
        private void Form1_keyPressEvt(eKeyPress Value)
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
            updateLabel(Value.ToString(),this.KeyCodeLabel);
        }
        /// <summary>
        /// 页码回调
        /// </summary>
        /// <param name="deviceIndex"></param>
        /// <param name="pageNumber"></param>
        /// <param name="noteNumber"></param>
        void Form1_showPageEvt(byte deviceIndex, int pageNumber, int noteNumber)
        {
            int pageData = (noteNumber << 8) | pageNumber;
            updateLabel(pageData.ToString(), this.PageLabel);
            robotpenController.GetInstance().setFBDeviceMessgae("pageid:"+ pageData);

        }
        /// <summary>
        /// T9Y页码传感器
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="pageSensor"></param>
        private void Rbtnet__PageSensorEvt_(ST_PAGE_SENSOR pageSensor)
        {

            OutputDebugString(string.Format(@"{0}的模拟量：{1}.{2}.{3}.{4}.{5}.{6}.{7}.{8}.{9}.{10}.{11}.{12}.{13}.{14}.{15}.{16}.{17}.{18}.{19},{20}", Mac
                , pageSensor.sensor1, pageSensor.sensor2
                , pageSensor.sensor3, pageSensor.sensor4
                , pageSensor.sensor5, pageSensor.sensor6
                , pageSensor.sensor7, pageSensor.sensor8
                , pageSensor.sensor9, pageSensor.sensor10
                , pageSensor.sensor11, pageSensor.sensor12
                , pageSensor.sensor13, pageSensor.sensor14
                , pageSensor.sensor15, pageSensor.sensor16
                , pageSensor.sensor17, pageSensor.sensor18
                , pageSensor.sensor19, pageSensor.sensor20
                ));
        }
        #endregion

        #region 修改界面的委托方法
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
                this.Invoke(lvD, new object[] { });
            }
            else
            {
                if (usbIsConnected)
                {
                    robotpenController.GetInstance()._CloseConnect();
                }
                this.listView1.Items.Clear();
                CheckUsbConnect();
            }
        }

        private delegate void PictureBoxDelegate();
        private void SetPictureBox()
        {
            if (this.pictureBox1.InvokeRequired)
            {
                PictureBoxDelegate lvD = new PictureBoxDelegate(this.SetPictureBox);
                this.pictureBox1.Invoke(lvD, new object[] { });
            }
            else
            {
                compressPictureBox();
            }
        }
        /// <summary>
        /// 设置屏幕宽度，并生成点坐标缩放比例
        /// </summary>
        private void compressPictureBox()
        {
            int nBordereW = this.pictureBox1.Width;
            int nBordereH = this.pictureBox1.Height;

            if (bScreenO)  // 横屏 根据
            {
                m_nCompress = ((double)(m_nDeviceH) / nBordereH);  // 设备与屏幕的宽比例
                nBordereW = (int)Math.Ceiling(m_nDeviceW / m_nCompress);
                m_nCompress_x = ((double)(m_nDeviceW) / nBordereW);
                m_nCompress_y = ((double)(m_nDeviceH) / nBordereH);
            }
            else   // 竖屏
            {
                m_nCompress = ((double)(m_nDeviceW) / nBordereH);  // 设备与屏幕的宽比例
                nBordereW = (int)Math.Ceiling(m_nDeviceH / m_nCompress);                                                    // 计算高的比例
                m_nCompress_x = ((double)(m_nDeviceW) / nBordereH);
                m_nCompress_y = ((double)(m_nDeviceH) / nBordereW);
            }

            if (nBordereW > this.pictureBox1.Width)
            {
                int len = nBordereW - this.pictureBox1.Width;
                this.pictureBox1.Width = nBordereW;
            }
            else if(nBordereW < this.pictureBox1.Width)
            {
                int len = this.pictureBox1.Width - nBordereW;
                this.pictureBox1.Width = nBordereW;
            }
            drawing = new Drawing(this.pictureBox1,angle, m_nDeviceW, m_nDeviceH);
            drawing.DrawingCallbackBrushstroke_Evt += new Drawing.DrawingCallbackBrushstroke(FormDrawingCallbackBrushstroke_Evt);
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

        private delegate void UpdateTextBox(string str, System.Windows.Forms.TextBox textBox);
        public void updateTextBox(string str, System.Windows.Forms.TextBox textBox)
        {
            if (textBox.InvokeRequired)
            {
                while (!textBox.IsHandleCreated)
                {
                    if (textBox.Disposing || textBox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateTextBox d = new UpdateTextBox(updateTextBox);
                textBox.Invoke(d, new object[] { str, textBox });
            }
            else
            {
                textBox.Text = str;
            }
        }

        private delegate void UpdateLabel(string str, System.Windows.Forms.Label label);
        public void updateLabel(string str, System.Windows.Forms.Label label)
        {
            if (label.InvokeRequired)
            {
                while (!label.IsHandleCreated)
                {
                    if (label.Disposing || label.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateLabel d = new UpdateLabel(updateLabel);
                label.Invoke(d, new object[] { str, label });
            }
            else
            {
                label.Text = str;
            }
        }

        private delegate void UpdateButtonEnable(bool check, System.Windows.Forms.Button btn);
        public void updateButtonEnable(bool check, System.Windows.Forms.Button btn)
        {
            if (btn.InvokeRequired)
            {
                while (!btn.IsHandleCreated)
                {
                    if (btn.Disposing || btn.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateButtonEnable d = new UpdateButtonEnable(updateButtonEnable);
                btn.Invoke(d, new object[] { check, btn });
            }
            else
            {
                btn.Enabled = check;
            }
        }

        private delegate void UpdateLabelEnable(bool check, System.Windows.Forms.Label lab);
        public void updateLabelEnable(bool check, System.Windows.Forms.Label lab)
        {
            if (lab.InvokeRequired)
            {
                while (!lab.IsHandleCreated)
                {
                    if (lab.Disposing || lab.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateLabelEnable d = new UpdateLabelEnable(updateLabelEnable);
                lab.Invoke(d, new object[] { check, lab });
            }
            else
            {
                lab.Visible = check;
            }
        }

        public void updateTextBox2(string str, System.Windows.Forms.TextBox textBox)
        {
            if (textBox.InvokeRequired)
            {
                while (!textBox.IsHandleCreated)
                {
                    if (textBox.Disposing || textBox.IsDisposed)
                    {
                        return;
                    }
                }
                UpdateTextBox d = new UpdateTextBox(updateTextBox2);
                textBox.Invoke(d, new object[] { str, textBox });
            }
            else
            {
                this.pictureBox1.Image = null;
            }
        }

        #endregion


        private void Form1_Load(object sender, EventArgs e)
        {
            this.listView1.Columns.Add("设备名称", 200, HorizontalAlignment.Center);
            this.listView1.Columns.Add("VID", 100, HorizontalAlignment.Center);
            this.listView1.Columns.Add("PID", 100, HorizontalAlignment.Center);
            this.WindowState = FormWindowState.Maximized;

            CheckUsbConnect();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //robotpenController.GetInstance()._CloseConnect();
            //if (!usbIsConnected)
            //{
                if (this.listView1.SelectedItems.Count != 1)
                {
                    MessageBox.Show("请先选择需要打开的设备!");
                    return;
                }
                string strPID = this.listView1.SelectedItems[0].SubItems[2].Text;
                UInt16 nPid = Convert.ToUInt16(strPID);
                string strDeviceType = this.listView1.SelectedItems[0].SubItems[3].Text;
                eDeviceType deviceType = (eDeviceType)Convert.ToInt32(strDeviceType);
                robotpenController.GetInstance()._ConnectInitialize(deviceType, IntPtr.Zero);
                int nRes = robotpenController.GetInstance()._ConnectOpen();
                if (nRes != 0)
                {
                    MessageBox.Show("设备打开失败!");
                    return;
                }
                robotpenController.GetInstance()._Send(cmdId.GetConfig);
            //}
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            robotpenController.GetInstance()._CloseConnect();
            //Application.dis();
            Environment.Exit(Environment.ExitCode);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            string str = SerializeHelper.JsonSerializer<List<RobotPoint>>(plist);
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = @"txt文件|*.txt";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                string file = sfd.FileName;
                FileHelper fh = new FileHelper();
                fh.FileWriteStr(file, str);
            }
        }


        Thread t;
        private void button5_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = false;
            fileDialog.Title = "请选择文件";
            fileDialog.Filter = "txt所有文件|*.txt";
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = fileDialog.FileName;
                FileHelper fh = new FileHelper();

                string dic = fh.FileReadStr(filePath);
                TalData RpList = SerializeHelper.JsonDeserialize<TalData>(dic);

                t = new Thread(new ParameterizedThreadStart(DrawingData));
                t.Start(RpList);
            }
        }

        private void DrawingData(object _RpList)
        {
            TalData RpList = _RpList as TalData;
            foreach (string item in RpList.data.data)
            {
                if (string.IsNullOrEmpty(item))
                {
                    continue;
                }
                string[] c = item.Trim().Split('#');
                RobotPoint point = new RobotPoint()
                {
                    bPenStatus = c[1] == "0" ? 16 : 17,
                    bx = int.Parse(c[2]),
                    by = int.Parse(c[3]),
                    bPress = int.Parse(c[1])
                };
                plist.Add(point);
                if (drawing == null)
                {
                    compressPictureBox();
                }
                if(isOpen)
                {
                    drawing.recvData(point.bPenStatus, point.bx, point.by, point.bPress);
                }
            }
        }

        private void pictureBox1_DoubleClick(object sender, EventArgs e)
        {
            reSetRecrog();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (!isOptimize)
            {
                robotpenController.GetInstance().setPenWidthF((float)2);
                // 是否开启笔记优化
                robotpenController.GetInstance().setTrailsIsOptimize(true);
                // 是否开启压感
                robotpenController.GetInstance().setPressStatus(true);
                //设置拖尾阈值，设置的越小，拖尾越长(0~1) 默认0.4
                robotpenController.GetInstance().setPointDelay((float)0.4);
                // 设置粗细变化阈值，设置的越小，粗细变化越小 默认0.026
                robotpenController.GetInstance().setPointDamping((float)0.026);
                isOptimize = true;
                this.button6.Text = "关闭优化笔记";
                return;
            }
            else
            {
                isOptimize = false;
                this.button6.Text = "开启优化笔记";
                return;
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.comboBox1.SelectedIndex)
            {
                case 0:
                    {
                        bScreenO = true;
                        angle = Angle._180;
                        SetDeviceHW();
                        reSetRecrog();
                        break;
                    }
                case 1:
                    {
                        bScreenO = false;
                        angle = Angle._270;
                        SetDeviceHW();
                        reSetRecrog();
                        break;
                    }
                case 2:
                    {
                        bScreenO = true;
                        angle = Angle._0;
                        SetDeviceHW();
                        reSetRecrog();
                        break;
                    }
                default:
                    break;
            }
        }
        public void FormDrawingCallbackBrushstroke_Evt(List<RobotPoint> _plist)
        {
        }

        private void reSetRecrog()
        {
            plist.Clear();
            this.pictureBox1.Image = null;
        }

        private void comboBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }


        private void Form1_NoAngle_SizeChanged(object sender, EventArgs e)
        {
            if (isOpen)
            {
                if (this.Size.Height <= 73)
                {
                    return;
                }
                

                isOpen = false;
                this.pictureBox1.Image = null;
                int heightChange = this.Size.Height - 73;
                double picboxHeight = heightChange;
                double picboxWidth = (heightChange / Convert.ToDouble(this.pictureBox1.Height)) * Convert.ToDouble(this.pictureBox1.Width);
                if (picboxHeight > 0 && picboxWidth > 0)
                {
                    this.pictureBox1.Height = Convert.ToInt32(Math.Ceiling(picboxHeight));
                    this.pictureBox1.Width = Convert.ToInt32(Math.Ceiling(picboxWidth));
                    SetPictureBox();
                }
            }
        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.comboBox4.SelectedIndex)
            {
                case 0:
                    {
                        RR = ReportRate.R_200;
                        break;
                    }
                case 1:
                    {
                        RR = ReportRate.R_160;
                        break;
                    }
                case 2:
                    {
                        RR = ReportRate.R_120;
                        break;
                    }
                case 3:
                    {
                        RR = ReportRate.R_80;
                        break;
                    }
                case 4:
                    {
                        RR = ReportRate.R_40;
                        break;
                    }
                default:
                    break;
            }
        }


        Thread thread_paint;
        private void Form1_NoAngle_Paint(object sender, PaintEventArgs e)
        {
            if (thread_paint != null && thread_paint.ThreadState == ThreadState.Running)
            {
                return;
            }
            thread_paint = new Thread(ReDrawing);
            thread_paint.Start();
        }

        private void ReDrawing()
        {
            Thread.Sleep(200);
            if (isOpen)
            {
                return;
            }
            int count = plist.Count;
            for (int i = 0; i < count; i++)
            {
                if (plist[i].isOptimize)
                {
                    drawing.recvOptimizeData(plist[i].bPenStatus, plist[i].bx, plist[i].by, plist[i].bWidth);
                }
                else
                {
                    drawing.recvData(plist[i].bPenStatus, plist[i].bx, plist[i].by, plist[i].bPress);
                }

            }
            this.isOpen = true;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= ' ' && e.KeyChar <= '~') || e.KeyChar == '\b')
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance().setFBDeviceMessgae(this.textBox1.Text);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance().setClassSSID(this.SSIDTEXT.Text, this.SSIDTEXT.Text.Length);
            Thread.Sleep(200);
            robotpenController.GetInstance().setClassPwd(this.PSDTEXT.Text, this.PSDTEXT.Text.Length);
            Thread.Sleep(200);
            MessageBox.Show("设置完成");
        }

        private void SSIDTEXT_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= ' ' && e.KeyChar <= '~') || e.KeyChar == '\b')
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void PSDTEXT_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= ' ' && e.KeyChar <= '~') || e.KeyChar == '\b')
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = false;
            fileDialog.Title = "请选择文件";
            fileDialog.Filter = "image文件|*.bmp;*.ico;*.gif;*.jpeg;*.jpg;*.png;*.tif;*.tiff";
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = fileDialog.FileName;
                this.pictureBox1.ImageLocation = filePath;
            }
        }
    }
    public enum ReportRate
    {
        R_200,
        R_160,
        R_120,
        R_80,
        R_40
    }
}
