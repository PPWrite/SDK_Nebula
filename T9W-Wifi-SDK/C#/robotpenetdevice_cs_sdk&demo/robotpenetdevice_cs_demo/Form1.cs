using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using robotpenetdevice_cs;
using System.Runtime.InteropServices;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using rbt_win32_2_demo.Helper;
using robopenetdevice_cs_demo;
using System.Diagnostics;

namespace rbt_win32_2_demo
{
    public partial class Form1 : Form
    {
        [System.Runtime.InteropServices.DllImport("kernel32.dll", CharSet = System.Runtime.InteropServices.CharSet.Auto)]
        public static extern void OutputDebugString(string message);

        public static RbtNet rbtnet_ = null;
        public static bool _optimize = false;

        public static string oemkey = string.Empty;


        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 窗口加载过程函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            initListView();

            rbtnet_ = new RbtNet();
            // 初始化
            Init_Param param = new Init_Param();

            _optimize = Convert.ToBoolean(System.Configuration.ConfigurationSettings.AppSettings["optimize"]);
            oemkey = System.Configuration.ConfigurationSettings.AppSettings["OEMKEY"];

            param.optimize = _optimize;
            rbtnet_.init(ref param);
            //rbtnet_.init();
            if(oemkey=="TY")
            {
                rbtnet_.setPrintType(PrintType.TyMode);
            }
            else if(oemkey == "FB")
            {
                rbtnet_.setPrintType(PrintType.NoMarkCode_FB_FT);
                //rbtnet_.setPrintType(PrintType.NoMarkCode);
            }
            else
            {
                rbtnet_.setPrintType(PrintType.Base);
            }
            

            comboBox_Qtype.Items.Add("主观题");
            comboBox_Qtype.Items.Add("客观题");
           
            comboBox_Qtype.SelectedIndex = 0;

            if(oemkey=="FB")
            {
                SetFBMenuItem.Visible = true;
            }
            if (oemkey == "YJ"|| oemkey == "ZHL")
            {
                comboBox_Qtype.Items.Add("投票");
                comboBox_Qtype.Items.Add("不定项");
                comboBox_Qtype.Items.Add("测试");
                comboBox_Qtype.Items.Add("书写");
                //LookAnswerResultToolStripMenuItem.Visible = true;
            }

            /*
            * 所有事件响应接口都是在内部SDK线程中上报出来
            */
            rbtnet_.deviceMacEvt_ += Rbtnet__deviceMacEvt_;

            rbtnet_.deviceNameEvt_ += Rbtnet__deviceNameEvt_;
            rbtnet_.deviceNameResult_ += Rbtnet__eviceNameResultEvt_;
            rbtnet_.deviceDisconnectEvt_ += Rbtnet__deviceDisconnectEvt_;
            rbtnet_.deviceOriginDataEvt_ += Rbtnet__deviceOriginDataEvt_;
            rbtnet_.deviceOptimizeDataEvt_ += Rbtnet__deviceOptimizeDataEvt_;

            rbtnet_.deviceShowPageNewEvt_ += Rbtnet__deviceShowPageEvt_;
            rbtnet_.deviceKeyPressEvt_ += Rbtnet__deviceKeyPressEvt_;
            rbtnet_.deviceAnswerResultEvt_ += Rbtnet__deviceAnswerResultEvt_;

            rbtnet_.deviceError_ += Rbtnet__deviceEvt;
            rbtnet_.DeviceIpEvt_ += Rbtnet_DeviceIpEvt;

            rbtnet_.deviceCanvasID_ += Rbtnet__deviceCanvasID;

            rbtnet_.DeviceInfoEvt_ += Rbtnet__deviceInfo;
            rbtnet_.HardInfoEvt_ += Rbtnet__hardInfo;
            rbtnet_.DeviceBatteryEvt_ += deviceBattery;

            rbtnet_.CurrentWritingNumEvt_ += Rbtnet__CurrentWritingNumEvt_;
            OutputDebugString("绑定20位模拟量回调事件");
            rbtnet_.pageSensorEvt_ += Rbtnet__PageSensorEvt_;
        }

        

        /// <summary>
        /// IP地址回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="ip"></param>
        /// <param name="sendip"></param>
        public void Rbtnet_DeviceIpEvt(IntPtr ctx, String pMac, String ip, String sendip)
        {
            useIp = sendip;
        }
        /// <summary>
        /// 错误信息回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pmac"></param>
        /// <param name="cmd"></param>
        /// <param name="msg"></param>
        public void Rbtnet__deviceEvt(IntPtr ctx, String pmac, int cmd, String msg)
        {
            updateLable(this.label3, string.Format(@"命令：{0}，错误信息：{1}", cmd.ToString(), msg));
        }
        /// <summary>
        /// 清空画布回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pmac"></param>
        /// <param name="type"></param>
        /// <param name="canvasID"></param>
        public void Rbtnet__deviceCanvasID(IntPtr ctx, String pmac, int type, int canvasID)
        {
            string sMac = pmac;
            //if (dicMac2DrawForm_.ContainsKey(sMac))
            //{
            //    dicMac2DrawForm_[sMac].clearCanvasEvtCall();
            //}
        }
        /// <summary>
        /// 设备名称回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="strDeviceName"></param>
        private void Rbtnet__deviceNameEvt_(IntPtr ctx, string strDeviceMac, string strDeviceName)
        {
            // Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);
            updateDeviceNameListView(strDeviceMac, strDeviceName);
            //Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);
        }
        
        /// <summary>
        /// 设置名称成功回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="res"></param>
        /// <param name="strDeviceName"></param>
        private void Rbtnet__eviceNameResultEvt_(IntPtr ctx, string strDeviceMac, int res, string strDeviceName)
        {
            // Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);
            updateDeviceNameListView(strDeviceMac, strDeviceName);
        }

        /// <summary>
        /// 设备答题回调
        /// </summary>
        /// <param name="ctx">内存地址结构体，不需要操作</param>
        /// <param name="strDeviceMac">设备号</param>
        /// <param name="resID">题号：当题号110的时候是结束答题回调事件；21为主观题下确认提交</param>
        /// <param name="result">结果数据包</param>
        /// <param name="nResultSize">数据包总长度</param>
        private void Rbtnet__deviceAnswerResultEvt_(IntPtr ctx, IntPtr strDeviceMac, int resID, IntPtr result, int nResultSize)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            string sResult = Marshal.PtrToStringAnsi(result);
            byte[] byteRes = new byte[nResultSize];
            Marshal.Copy(result, byteRes, 0, nResultSize);
            //Console.WriteLine("Rbtnet__deviceAnswerResultEvt_:{0}-{1}", sMac, sResult);
            updateDeviceMacListView_AnswerResult(sMac, resID, byteRes, nResultSize);

        }

        private void Rbtnet__deviceKeyPressEvt_(IntPtr ctx, IntPtr strDeviceMac, int keyValue)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            updateDeviceMacListView_KeyPress(sMac, keyValue);
        }

        private void Rbtnet__deviceShowPageEvt_(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId, int nPageInfo)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            updateDeviceMacListView_ShowPage(sMac, nNoteId, nPageId, nPageInfo);
        }

        private void Rbtnet__CurrentWritingNumEvt_(IntPtr ctx, String pMac, int nNum)
        {
            string sMac = pMac;
            if (dicMac2DrawForm_.ContainsKey(sMac))
            {
                dicMac2DrawForm_[sMac].UpdateJDNum(nNum);
            }
        }

        private void Rbtnet__PageSensorEvt_(IntPtr ctx, String pMac, ST_PAGE_SENSOR pageSensor)
        {
            Console.WriteLine(string.Format(@"{0}的模拟量：{1}.{2}.{3}.{4}.{5}.{6}.{7}.{8}.{9}.{10}.{11}.{12}.{13}.{14}.{15}.{16}.{17}.{18}.{19},{20}", pMac
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
            OutputDebugString(string.Format(@"{0}的模拟量：{1}.{2}.{3}.{4}.{5}.{6}.{7}.{8}.{9}.{10}.{11}.{12}.{13}.{14}.{15}.{16}.{17}.{18}.{19},{20}",pMac
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

        private void Rbtnet__FBSetMessageEvt_(IntPtr ctx, String pMac, bool ret)
        {
            Console.WriteLine("设置FB消息回调{0}:{1}", pMac, ret);
        }

        private void Rbtnet__deviceDisconnectEvt_(IntPtr ctx, IntPtr strDeviceMac)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            updateDeviceMacListView_Disconnect(sMac);
        }


        private delegate void updateDeviceInfo(string strDeviceMac, string hardNum, string version, string resolution, string electricity);
        public void updateDeviceInfoListView(string strDeviceMac, string hardNum, string version, string resolution, string electricity)
        {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                updateDeviceInfo d = new updateDeviceInfo(updateDeviceInfoListView);
                this.listView1.Invoke(d, new object[] { strDeviceMac, hardNum, version, resolution, electricity });
            }
            else
            {
                foreach (ListViewItem item in this.listView1.Items)
                {
                    string strMac = item.SubItems[0].Text;
                    if (strDeviceMac == (strMac))
                    {
                        if (!string.IsNullOrEmpty(hardNum))
                        {
                            item.SubItems[7].Text = hardNum;
                        }
                        if (!string.IsNullOrEmpty(version))
                        {
                            item.SubItems[10].Text = version;
                        }
                        if (!string.IsNullOrEmpty(resolution))
                        {
                            item.SubItems[9].Text = resolution;
                        }
                        if (!string.IsNullOrEmpty(electricity))
                        {
                            item.SubItems[8].Text = electricity;
                        }
                        break;
                    }
                }
            }
        }
        private void Rbtnet__deviceInfo(IntPtr ctx, String pMac, String version, String deviceMac, int hardNum)
        {
            updateDeviceInfoListView(pMac, hardNum.ToString(), version, "", "");
        }
        private void Rbtnet__hardInfo(IntPtr ctx, String pMac, int xRange, int yRange, int LPI, int pageNum)
        {
            updateDeviceInfoListView(pMac, "", "", yRange.ToString() + "*" + xRange.ToString(), "");
        }
        private void deviceBattery(IntPtr ctx, String pMac, eBatteryStatus battery)
        {
            string result = string.Empty;
            switch (battery)
            {
                case eBatteryStatus.BATTERY_LOW_POWER:
                    result = "低电";
                    break;
                case eBatteryStatus.BATTERY_FIVE:
                    result = "<=5%电量";
                    break;
                case eBatteryStatus.BATTERY_TWENTY:
                    result = "<=20%电量";
                    break;
                case eBatteryStatus.BATTERY_FORTY:
                    result = "<=40%电量";
                    break;
                case eBatteryStatus.BATTERY_SIXTY:
                    result = "<=60%电量";
                    break;
                case eBatteryStatus.BATTERY_EIGHTY:
                    result = "<=80%电量";
                    break;
                case eBatteryStatus.BATTERY_ONEHUNDREDTY:
                    result = "<=100%电量";
                    break;
                case eBatteryStatus.BATTERY_CHARGING:
                    result = "<=充电中";
                    break;
                case eBatteryStatus.BATTERY_COMPLETE:
                    result = "<=充电完成";
                    break;
            }
            updateDeviceInfoListView(pMac, "", "", "", result);
        }

        private void initListView() {
            this.listView1.Columns.Add("设备MAC地址", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("学号", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("状态", 60, HorizontalAlignment.Left);
            this.listView1.Columns.Add("答题提交通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("按键通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("页码通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("学生姓名", 120, HorizontalAlignment.Left);

            this.listView1.Columns.Add("硬件号", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("电量", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("分辨率", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("固件版本号", 120, HorizontalAlignment.Left);
        }
        /// <summary>
        /// 接收到设备坐标点数据
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="us"></param>
        /// <param name="ux"></param>
        /// <param name="uy"></param>
        /// <param name="up"></param>
        private void Rbtnet__deviceOriginDataEvt_(IntPtr ctx, IntPtr strDeviceMac,
            ushort us,
            ushort ux,
            ushort uy,
            ushort up)
        {
            try
            {
                Console.WriteLine("x:{0},y:{1},s:{2}",ux,uy,us);
                if (_optimize)
                {
                    return;
                }
                string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
                if (dicMac2DrawForm_.ContainsKey(sMac))
                {
                    //int npenStatus = Convert.ToInt32(us);
                    //if (npenStatus != 17&& npenStatus != 33)
                    //{
                    //    npenStatus = 0;
                    //}
                    dicMac2DrawForm_[sMac].RememberData(us, ux, uy, up);
                }
            }
            catch(Exception ex)
            {

            }
            
        }

        /// <summary>
        /// 优化笔记
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="us"></param>
        /// <param name="ux"></param>
        /// <param name="uy"></param>
        /// <param name="up"></param>
        private void Rbtnet__deviceOptimizeDataEvt_(IntPtr ctx, IntPtr pmac, ushort us, ushort ux, ushort uy, float fPenWidthF, float speed)
        {
            if (!_optimize)
            {
                return;
            }
            string sMac = Marshal.PtrToStringAnsi(pmac);
            if (dicMac2DrawForm_.ContainsKey(sMac))
            {
                //int npenStatus = Convert.ToInt32(us);
                //if (fPenWidthF == 0)
                //{
                //    npenStatus = 0;
                //}
                dicMac2DrawForm_[sMac].RememberData(us, ux, uy, fPenWidthF, speed);
            }
        }

        /// <summary>
        /// 接收到设备mac上报事件 
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>

        private void Rbtnet__deviceMacEvt_(IntPtr ctx, System.String strDeviceMac)
        {
            //string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            //Console.WriteLine("设备MAC地址为:{0}", sMac);
            // 更新UI
            updateDeviceMacListView_Mac(strDeviceMac);
            //updateListStuName(strDeviceMac, "学生" + strDeviceMac.Substring(8, 3));

            Thread t = new Thread(new ParameterizedThreadStart(setCmd));
            t.Start(strDeviceMac);
        }
        /// <summary>
        /// 开新线程，进行下发学生姓名，获取设备信息和硬件信息
        /// </summary>
        /// <param name="strDeviceMacObj"></param>
        public void setCmd(object strDeviceMacObj)
        {
            string strDeviceMac = strDeviceMacObj as string;
            if (!string.IsNullOrEmpty(strDeviceMac))
            {
                Thread.Sleep(200);
                if(oemkey=="TY")
                {
                    rbtnet_.configBmpStu2(strDeviceMac, "学生" + strDeviceMac.Substring(10, 2));
                }
                else
                {
                    rbtnet_.configBmpStu(strDeviceMac, strDeviceMac, "学生" + strDeviceMac.Substring(10, 2));
                }
                
            }

            //Thread.Sleep(400);
            //rbtnet_.SendCmd((int)DeviceCmd.CMD_DEVICE_INFO, strDeviceMac);
            //Thread.Sleep(400);
            //rbtnet_.SendCmd((int)DeviceCmd.CMD_DEVICE_HARD_INFO, strDeviceMac);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_start_stop_Click(object sender, EventArgs e)
        {
            if (this.button_start_stop.Text == "开始")
            {
                bool bStartRes = rbtnet_.start();
                if (!bStartRes) {
                    MessageBox.Show("启动失败");
                    return;
                }
                this.button_start_stop.Text = "停止";
                this.label3.Text = "开始服务，连接上的手写板会有小房子，上位机能够发送命令并能响应消息";
            }
            else {
                rbtnet_.stop();
                this.button_start_stop.Text = "开始";
                this.listView1.Items.Clear();
                //this.dicMac2DrawForm_.Clear();

                this.label3.Text = "关闭服务，手写板小房子消失，上位机不能发送命令和响应消息";
            }
        }

        /// <summary>
        /// 更新设备MAC地址
        /// </summary>
        /// <param name="strMac"></param>
        private delegate void updateDeviceMac(string strMac);
        private Dictionary<string, drawFormForA4> dicMac2DrawForm_ = new Dictionary<string, drawFormForA4>();
        private static updateDeviceMac d;
        public void updateDeviceMacListView_Mac(string strMac) {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                d = new updateDeviceMac(updateDeviceMacListView_Mac);
                this.listView1.Invoke(d, new object[] { strMac });
            }
            else
            {
                int nItemCount = this.listView1.Items.Count;
                for (int i = 0; i < nItemCount; ++i) {
                    string strAMac = this.listView1.Items[i].SubItems[0].Text;
                    if (strAMac == strMac) {
                        this.listView1.Items[i].SubItems[2].Text = "在线";
                        if (!dicMac2DrawForm_.ContainsKey(strMac))
                        {
                            drawFormForA4 fa4F = new drawFormForA4(strMac);
                            dicMac2DrawForm_.Add(strMac, fa4F);
                            fa4F.Show();
                        }
                        return;
                    }
                }

                this.listView1.Items.Add(strMac);
                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("在线");
                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("");

                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("");
                this.listView1.Items[nItemCount].SubItems.Add("");

                if (!dicMac2DrawForm_.ContainsKey(strMac)) {
                    drawFormForA4 fa4F = new drawFormForA4(strMac);
                    dicMac2DrawForm_.Add(strMac, fa4F);
                    fa4F.Show();
                }
            }
        }


        /// <summary>
        /// 设备下线
        /// </summary>
        /// <param name="strMac"></param>
        private delegate void updateDeviceMac_Disconnect(string strMac);
        public void updateDeviceMacListView_Disconnect(string strMac)
        {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                updateDeviceMac_Disconnect d = new updateDeviceMac_Disconnect(updateDeviceMacListView_Disconnect);
                this.listView1.Invoke(d, new object[] { strMac });
            }
            else
            {
                int nItemCount = this.listView1.Items.Count;
                int nFindItem = -1;
                for (int i = 0; i < nItemCount; ++i)
                {
                    string strAMac = this.listView1.Items[i].SubItems[0].Text;
                    if (strAMac == strMac) {
                        nFindItem = i;
                        break;
                    }
                }

                if (nFindItem > -1) {
                    this.listView1.Items[nFindItem].SubItems[2].Text = "离线";

                    if (dicMac2DrawForm_.ContainsKey(strMac))
                    {
                        if (dicMac2DrawForm_[strMac].Visible) {
                            dicMac2DrawForm_[strMac].Close();
                        }

                        dicMac2DrawForm_.Remove(strMac);
                    }
                }
            }
        }

        /// <summary>
        /// 更新页码listview节点
        /// </summary>
        /// <param name="strMac"></param>
        /// <param name="nNoteId"></param>
        /// <param name="nPageId"></param>
        private delegate void updateDeviceMac_ShowPage(string strMac, int nNoteId, int nPageId, int nPageInfo);
        public void updateDeviceMacListView_ShowPage(string strMac, int nNoteId, int nPageId, int nPageInfo)
        {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                updateDeviceMac_ShowPage d = new updateDeviceMac_ShowPage(updateDeviceMacListView_ShowPage);
                this.listView1.Invoke(d, new object[] { strMac, nNoteId, nPageId, nPageInfo });
            }
            else
            {
                // 过滤扫描到的重复设备
                int nItemCount = this.listView1.Items.Count;
                int nFindItem = -1;
                for (int i = 0; i < nItemCount; ++i)
                {
                    string strAMac = this.listView1.Items[i].SubItems[0].Text;
                    if (strAMac == strMac)
                    {
                        nFindItem = i;
                        break;
                    }
                }

                if (nFindItem > -1)
                {
                    //Console.WriteLine(Convert.ToString(nPageInfo));
                    this.listView1.Items[nFindItem].SubItems[5].Text = "nPageInfo=" + Convert.ToString(nPageInfo)+" noteid=" + Convert.ToString(nNoteId) + " pageid=" + Convert.ToString(nPageId) ;
                    
                    if(PageNumberContrast&& nPageInfo!=pageNumber)
                    {
                        this.listView1.Items[nFindItem].ForeColor = Color.Red;
                    }
                    else
                    {
                        this.listView1.Items[nFindItem].ForeColor = Color.Black;
                    }
                    //this.listView1.Items[nFindItem].ForeColor = Color.Red;
                    this.listView1.Refresh();
                    //rbtnet_.SetFBDeviceMessages(strMac, "pageid=" + Convert.ToString(nPageInfo));
                }
            }
        }

        /// <summary>
        /// 收到按键消息
        /// </summary>
        /// <param name="strMac"></param>
        /// <param name="keyValue"></param>
        private delegate void updateDeviceMac_KeyPress(string strMac, int keyValue);
        public void updateDeviceMacListView_KeyPress(string strMac, int keyValue)
        {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                updateDeviceMac_KeyPress d = new updateDeviceMac_KeyPress(updateDeviceMacListView_KeyPress);
                this.listView1.Invoke(d, new object[] { strMac, keyValue });
            }
            else
            {
                // 过滤扫描到的重复设备
                int nItemCount = this.listView1.Items.Count;
                int nFindItem = -1;
                for (int i = 0; i < nItemCount; ++i)
                {
                    string strAMac = this.listView1.Items[i].SubItems[0].Text;
                    if (strAMac == strMac)
                    {
                        nFindItem = i;
                        break;
                    }
                }

                if (nFindItem > -1)
                {
                    keyPressEnum keyValueE = (keyPressEnum)keyValue;
                    string strKeyValue = string.Empty;
                    switch (keyValueE)
                    {
                        case keyPressEnum.K_A:
                            strKeyValue = "A";
                            break;
                        case keyPressEnum.K_B:
                            strKeyValue = "B";
                            break;
                        case keyPressEnum.K_C:
                            strKeyValue = "C";
                            break;
                        case keyPressEnum.K_D:
                            strKeyValue = "D";
                            break;
                        case keyPressEnum.K_E:
                            strKeyValue = "E";
                            break;
                        case keyPressEnum.K_F:
                            strKeyValue = "F";
                            break;
                        case keyPressEnum.K_SUCC:
                            strKeyValue = "正确";
                            break;
                        case keyPressEnum.K_ERROR:
                            strKeyValue = "错误";
                            break;
                        case keyPressEnum.K_CACLE:
                            strKeyValue = "取消";
                            break;
                        case keyPressEnum.K_SURE:
                            strKeyValue = "确认";
                            break;
                        case keyPressEnum.K_G:
                            strKeyValue = "G";
                            break;
                        default:
                            break;

                    }
                    this.listView1.Items[nFindItem].SubItems[4].Text = strKeyValue;

                }
            }
        }

        private delegate void updateDeviceName(string strDeviceMac, string strDeviceName);
        public void updateDeviceNameListView(string strDeviceMac, string strDeviceName) {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                updateDeviceName d = new updateDeviceName(updateDeviceNameListView);
                this.listView1.Invoke(d, new object[] { strDeviceMac, strDeviceName });
            } else {
                foreach (ListViewItem item in this.listView1.Items)
                {
                    string strMac = item.SubItems[0].Text;
                    if (strDeviceMac == (strMac))
                    {
                        item.SubItems[1].Text = strDeviceName;
                        break;
                    }
                }
            }
        }

        private Dictionary<string, string> AnswerResultDic = new Dictionary<string, string>();
        private Dictionary<string, Dictionary<int, string>> AnswerResultDicDetail = new Dictionary<string, Dictionary<int, string>>();
        /// <summary>
        /// 收到答题消息
        /// </summary>
        /// <param name="strMac"></param>
        /// <param name="keyValue"></param>
        private delegate void updateDeviceMac_AnswerResult(string strMac, int resID, byte[] strResult, int nResultSize);
        public void updateDeviceMacListView_AnswerResult(string strMac, int resID, byte[] strResult, int nResultSize)
        {
            if (this.listView1.InvokeRequired)
            {
                while (!this.listView1.IsHandleCreated)
                {
                    if (this.listView1.Disposing || this.listView1.IsDisposed)
                    {
                        return;
                    }
                }
                updateDeviceMac_AnswerResult d = new updateDeviceMac_AnswerResult(updateDeviceMacListView_AnswerResult);
                this.listView1.Invoke(d, new object[] { strMac, resID, strResult, nResultSize });
            }
            else
            {
                int Packet_len = 8;//包长
                int resultList_len = 6;//其中结果集合的长度

                if (oemkey == "YJ")
                {
                    Packet_len = 9;
                    resultList_len = 7;
                }
                else if(oemkey == "ZHL")
                {
                    Packet_len = 5;
                    resultList_len = 4;
                }




                int nItemCount = this.listView1.Items.Count;
                int nFindItem = -1;
                string strAMac = string.Empty;
                for (int i = 0; i < nItemCount; ++i)
                {
                    strAMac = this.listView1.Items[i].SubItems[0].Text;
                    if (strAMac == strMac)
                    {
                        nFindItem = i;
                        break;
                    }
                }

                if (nFindItem > -1)
                {
                    string strKeyValue = string.Empty;
                    string answerKeyValue = string.Empty;
                    if (resID != 110)
                    {
                        strKeyValue = GetResultKey(resID, strResult,out answerKeyValue,"");
                        if(AnswerResultDicDetail.ContainsKey(strAMac))
                        {
                            if(AnswerResultDicDetail[strAMac].ContainsKey(resID))
                            {
                                AnswerResultDicDetail[strAMac][resID] = answerKeyValue;
                            }
                            else
                            {
                                AnswerResultDicDetail[strAMac].Add(resID, answerKeyValue);
                            }
                        }
                        else
                        {
                            Dictionary<int, string> arDic = new Dictionary<int, string>();
                            arDic.Add(resID, answerKeyValue);
                            AnswerResultDicDetail.Add(strAMac, arDic);
                        }
                    }
                    else
                    {
                        int count = nResultSize / Packet_len;
                        int resultKeyNum = 0;
                        if (AnswerResultDicDetail.ContainsKey(strAMac) && oemkey == "YJ")
                        {
                            resultKeyNum = AnswerResultDicDetail[strAMac].Max(p => p.Key);
                        }
                        for (int i = 0; i < count; i++)
                        {
                            string answerKeyValueItem = string.Empty;
                            int questionNum = 0;
                            if (oemkey == "ZHL")
                            {
                                //获取题号
                                byte[] byteRes_zhl_num = new byte[1];
                                Array.Copy(strResult, i * Packet_len, byteRes_zhl_num, 0, 1);
                                questionNum = Convert.ToInt32(byteRes_zhl_num[0]);
                                //获取答题内容
                                byte[] byteRes_zhl = new byte[resultList_len];
                                Array.Copy(strResult, i * Packet_len + 1, byteRes_zhl, 0, resultList_len);

                                strKeyValue += GetResultKey(questionNum, byteRes_zhl, out answerKeyValueItem, oemkey) + "；";
                            }
                            else
                            {
                                questionNum = resultKeyNum + i + 1;
                                byte[] byteRes = new byte[resultList_len];
                                Array.Copy(strResult, i * Packet_len + 2, byteRes, 0, resultList_len);
                                strKeyValue += GetResultKey(questionNum, byteRes, out answerKeyValueItem, oemkey) + "；";
                            }
                           
                            
                            

                            if (AnswerResultDicDetail.ContainsKey(strAMac))
                            {
                                
                                if (AnswerResultDicDetail[strAMac].ContainsKey(resultKeyNum + i + 1))
                                {
                                    AnswerResultDicDetail[strAMac][resultKeyNum + i + 1] = answerKeyValueItem;
                                }
                                else
                                {
                                    AnswerResultDicDetail[strAMac].Add(resultKeyNum + i + 1, answerKeyValueItem);
                                }
                            }
                            else
                            {
                                Dictionary<int, string> arDic = new Dictionary<int, string>();
                                arDic.Add(resultKeyNum + i + 1, answerKeyValueItem);
                                AnswerResultDicDetail.Add(strAMac, arDic);
                            }
                        }

                        strKeyValue = string.Empty;
                        if(AnswerResultDicDetail.ContainsKey(strAMac))
                        {
                            foreach (var item in AnswerResultDicDetail[strAMac])
                            {
                                strKeyValue+=string.Format("{0}：{1}；", item.Key,item.Value);
                            }
                        }
                    }

                    this.listView1.Items[nFindItem].SubItems[3].Text = strKeyValue;

                }
            }
        }
        private string GetResultKey(int resultId, byte[] strResult,out string strAnswerKeyValue,string _oemkey)
        {
            string strKeyValue = string.Format("{0}：", resultId);
            strAnswerKeyValue = "";
            if(_oemkey == "ZHL")
            {
                int t = 0;
                foreach (var c in strResult)
                {
                    t++;
                    string d = System.Convert.ToString(c, 2);
                    int len = d.Length;
                    for (int j = 0; j < 8 - len; j++)
                    {
                        d = "0" + d;
                    }
                    for (int i = 0; i < d.Length; i++)
                    {
                        answerResultKey arkey = (answerResultKey)i;
                        if (d[i] == '1')
                        {
                            strAnswerKeyValue += arkey.ToString();
                        }
                    }
                    if(t!= strResult.Length)
                    {
                        strAnswerKeyValue += "|";
                    }
                }
            }
            else
            {
                foreach (var c in strResult)
                {
                    keyPressEnum keyValueE = (keyPressEnum)c;
                    switch (keyValueE)
                    {
                        case keyPressEnum.K_A:
                            strAnswerKeyValue += "A";
                            break;
                        case keyPressEnum.K_B:
                            strAnswerKeyValue += "B";
                            break;
                        case keyPressEnum.K_C:
                            strAnswerKeyValue += "C";
                            break;
                        case keyPressEnum.K_D:
                            strAnswerKeyValue += "D";
                            break;
                        case keyPressEnum.K_E:
                            strAnswerKeyValue += "E";
                            break;
                        case keyPressEnum.K_F:
                            strAnswerKeyValue += "F";
                            break;
                        case keyPressEnum.K_SUCC:
                            strAnswerKeyValue += "正确";
                            break;
                        case keyPressEnum.K_ERROR:
                            strAnswerKeyValue += "错误";
                            break;
                        case keyPressEnum.K_CACLE:
                            strAnswerKeyValue += "取消";
                            break;
                        case keyPressEnum.K_SURE:
                            strAnswerKeyValue += "确认";
                            break;
                        case keyPressEnum.K_G:
                            strAnswerKeyValue += "G";
                            break;
                        default:
                            break;
                    }
                }
            }
            
            strKeyValue += strAnswerKeyValue;
            return strKeyValue;
        }


        /// <summary>
        /// 双击弹出画布
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            var items = this.listView1.SelectedItems;
            foreach (ListViewItem item in items)
            {
                string strMac = item.SubItems[0].Text;
                if (dicMac2DrawForm_.ContainsKey(strMac)) {
                    dicMac2DrawForm_[strMac].Text = strMac;
                    dicMac2DrawForm_[strMac].Show();
                    dicMac2DrawForm_[strMac].TopMost = true;
                }
            }
        }

        private void button_test_Click(object sender, EventArgs e)
        {
            SettingPanel sp = new SettingPanel(this);
            sp.ShowDialog();
        }

        private bool startConfigNet = false;
        private void button_switch_Click(object sender, EventArgs e)
        {
            string strIP = this.IpComboBox.Text;
            if (!startConfigNet)
            {
                if (!string.IsNullOrEmpty(strIP))
                {
                    startConfigNet = true;
                    this.button2.Text = "停止切换";
                }
            }
            else
            {
                startConfigNet = false;
                this.button2.Text = "切换";
            }

        }

        /// <summary>
        /// 获取listview选中的MAC地址
        /// </summary>
        /// <returns></returns>
        private bool GetListViewSelectMac(out string strMac, out string strNum, out string strName)
        {
            var items = this.listView1.SelectedItems;
            strMac = string.Empty;
            strNum = string.Empty;
            strName = string.Empty;
            if (items.Count > 0)
            {
                foreach (ListViewItem item in items)
                {
                    strMac = item.SubItems[0].Text;
                    strNum = item.SubItems[1].Text;
                    strName = item.SubItems[6].Text;
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        /// <summary>
        /// 设置学号，不支持中文
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TSMI_SetStu_Click(object sender, EventArgs e)
        {
            string macStr = string.Empty;
            string numStr = string.Empty;
            string nameStr = string.Empty;
            if (GetListViewSelectMac(out macStr, out numStr, out nameStr))
            {
                SetStuName ssN = new SetStuName(false, macStr, numStr, nameStr, this);
                ssN.ShowDialog();
            }
        }
        /// <summary>
        /// 设置学号，支持中文
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TSMI_SetBmpStu_Click(object sender, EventArgs e)
        {
            string macStr = string.Empty;
            string numStr = string.Empty;
            string nameStr = string.Empty;
            if (GetListViewSelectMac(out macStr, out numStr, out nameStr))
            {
                SetStuName ssN = new SetStuName(true, macStr, numStr, nameStr, this);
                ssN.ShowDialog();
            }
        }
        /// <summary>
        /// 更新修改后的学生姓名
        /// </summary>
        /// <param name="name"></param>
        public void UpdateListViewSelectedStuName(string stuNum, string stuName = "")
        {
            var items = this.listView1.SelectedItems;
            foreach (ListViewItem item in items)
            {
                item.SubItems[1].Text = stuNum;
                if (!string.IsNullOrEmpty(stuName))
                {
                    item.SubItems[6].Text = stuName;
                }
            }
        }

        private int delayClose = 2;
        string useIp = string.Empty;
        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                string HostName = Dns.GetHostName(); //得到主机名
                IPHostEntry IpEntry = Dns.GetHostEntry(HostName);
                this.IpComboBox.Items.Clear();
                for (int i = 0; i < IpEntry.AddressList.Length; i++)
                {
                    //从IP地址列表中筛选出IPv4类型的IP地址
                    //AddressFamily.InterNetwork表示此IP为IPv4,
                    //AddressFamily.InterNetworkV6表示此地址为IPv6类型
                    if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetwork)
                    {
                        this.IpComboBox.Items.Add(IpEntry.AddressList[i].ToString());
                        //rbtnet_.configNet(IpEntry.AddressList[i].ToString(), 6001, false, true, "");
                    }
                }
                if (startConfigNet)
                {
                    rbtnet_.configNet(useIp, 6001, false, true, "");
                    //string strIP = this.IpComboBox.Text;
                    //if (!string.IsNullOrEmpty(strIP))     
                    //{
                    //    rbtnet_.configNet(strIP, 6001, false, true, "");
                    //}
                }

                if (string.IsNullOrEmpty(this.IpComboBox.Text) && this.IpComboBox.Items.Count > 0)
                {
                    this.IpComboBox.Text = this.IpComboBox.Items[0].ToString();
                }

                int nItemCount = this.listView1.Items.Count;
                int count = 0;
                for (int i = 0; i < nItemCount; ++i)
                {
                    if (this.listView1.Items[i].SubItems[2].Text == "在线")
                    {
                        count++;
                    }
                }
                this.label5.Text = count.ToString();

                if (isClosing)
                {
                    delayClose--;
                    if (delayClose <= 0)
                    {
                        this.Close();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("获取本机IP出错:" + ex.Message);
            }
        }

        private delegate void updateLable_Evt(Label _lable, string Text);
        public void updateLable(Label _lable, string Text)
        {
            if (_lable.InvokeRequired)
            {
                while (!_lable.IsHandleCreated)
                {
                    if (_lable.Disposing || _lable.IsDisposed)
                    {
                        return;
                    }
                }
                updateLable_Evt uLEvt = new updateLable_Evt(updateLable);
                _lable.Invoke(uLEvt, new object[] { _lable, Text });
            }
            else
            {
                _lable.Text = Text;
            }
        }

        private bool isClosing = false;
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            foreach (var item in dicMac2DrawForm_)
            {
                item.Value.Close();
            }
            dicMac2DrawForm_.Clear();
            try
            {
                if (!isClosing)
                {
                    rbtnet_.stop();
                    e.Cancel = true;
                    isClosing = true;
                }
            }
            catch (Exception)
            {
                Environment.Exit(0);
            }
            finally
            {
                Environment.Exit(0);
            }
        }
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //Thread.Sleep(3000);
        }

        List<DeviceSettingInfo> deviceSettingInfos = new List<DeviceSettingInfo>();
        private void button5_Click(object sender, EventArgs e)
        {
            int nItemCount = this.listView1.Items.Count;
            StringBuilder sqlList = new StringBuilder();
            StringBuilder sqlLIst2 = new StringBuilder();

            for (int i = 0; i < nItemCount; ++i)
            {
                DeviceSettingInfo dsInfo = new DeviceSettingInfo()
                {
                    DeviceNum = this.listView1.Items[i].SubItems[0].Text,
                    StudentNum = this.listView1.Items[i].SubItems[1].Text,
                    StudentName = this.listView1.Items[i].SubItems[6].Text,
                };
                deviceSettingInfos.Add(dsInfo);

                string sql1 = string.Format(@"insert into device_tb(device_mac,device_state)values('{0}',0);
", dsInfo.DeviceNum);
                string sql2 = string.Format(@"
insert into stu_tb(stu_name,stu_sex,stu_num,class_id,device_id)
select '学生'+device_id,0,001,14,device_id from device_tb
where device_mac = '{0}';
", dsInfo.DeviceNum);
                sqlList.Append(sql1);
                sqlLIst2.Append(sql2);
            }

            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = @"CSV文件|*.csv";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                string file = sfd.FileName;
                FileHelper fh = new FileHelper();
                fh.FileWriteForDeviceInfo(file, deviceSettingInfos);
            }
            SaveFileDialog sfd2 = new SaveFileDialog();
            sfd2.Filter = @"TXT文件|*.TXT";
            if (sfd2.ShowDialog() == DialogResult.OK)
            {
                string file = sfd2.FileName;
                FileHelper fh = new FileHelper();
                fh.FileWriteStr(file, sqlList.ToString());
            }
            SaveFileDialog sfd3 = new SaveFileDialog();
            sfd3.Filter = @"TXT文件|*.TXT";
            if (sfd3.ShowDialog() == DialogResult.OK)
            {
                string file = sfd3.FileName;
                FileHelper fh = new FileHelper();
                fh.FileWriteStr(file, sqlLIst2.ToString());
            }
            deviceSettingInfos = new List<DeviceSettingInfo>();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = false;
            fileDialog.Title = "请选择文件";
            fileDialog.Filter = "CSV文件|*.csv";
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = fileDialog.FileName;
                FileHelper fh = new FileHelper();
                List<DeviceSettingInfo> dic = fh.FileReadForDeviceInfo(filePath);

                foreach (var item in dic)
                {
                    rbtnet_.configBmpStu(item.DeviceNum, item.StudentNum, item.StudentName);
                    updateListStuName(item.DeviceNum, item.StudentName);
                }

            }
        }

        private void updateListStuName(string mac, string stuName)
        {
            int nItemCount = this.listView1.Items.Count;
            for (int i = 0; i < nItemCount; ++i)
            {
                string strAMac = this.listView1.Items[i].SubItems[0].Text;
                if (strAMac == mac)
                {
                    this.listView1.Items[i].SubItems[6].Text = stuName;
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            rbtnet_.configFreq(3);
        }


        /// <summary>
        /// 答题开始或结束按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_start_Click(object sender, EventArgs e)
        {
            AnswerResultDic.Clear();
            AnswerResultDicDetail.Clear();
            bool bRes = false;

            int totalTopic = 0;
            if (int.TryParse(textBox_num.Text,out totalTopic))
            {
                if(totalTopic<=0)
                {
                    MessageBox.Show("请输入题目数量");
                    return;
                }
            }
            else
            {
                MessageBox.Show("请输入题目数量");
                return;
            }
            if (oemkey == "YJ")
            {
                if(totalTopic>75)
                {
                    MessageBox.Show("最多75道题");
                    return;
                }
            }
            else
            {
                if (totalTopic > 20)
                {
                    MessageBox.Show("最多20道题");
                    return;
                }
            }

            int type = comboBox_Qtype.SelectedIndex;

            if (type == 3 && oemkey == "ZHL")
            {
                MessageBox.Show("不支持不定项选择题");
                return;
            }

            int index = comboBox_Qlist.SelectedIndex;
            
            byte[] topicType;

            List<int> qlist = new List<int>();
            if (index == 5||(index == 4&& oemkey != "YJ" && oemkey != "ZHL"))
            {
                totalTopic = 6;
                topicType = new byte[totalTopic];
                if (oemkey == "YJ" || oemkey == "ZHL")
                {
                    totalTopic = 8;
                    topicType = new byte[totalTopic];
                    topicType[6] = 5;
                    topicType[7] = 5;
                    qlist.Add(7);
                    qlist.Add(8);
                }
                
                topicType[0] = 1;
                topicType[1] = 1;
                topicType[2] = 2;
                topicType[3] = 2;
                topicType[4] = 3;
                topicType[5] = 3;
            }
            else
            {
                topicType = new byte[totalTopic];
                for (int i = 0; i < totalTopic; i++)
                {
                    if (type == 2)
                    {
                        topicType[i] = Convert.ToByte(index + 2);
                    }
                    else
                    {
                        topicType[i] = Convert.ToByte(index + 1);
                    }
                    
                    if(type==2)
                    {
                        if(index == 4)
                        {
                            qlist.Add(i + 1);
                        }
                    }
                    else if(type==0||type==4||type==5)
                    {
                        qlist.Add(i + 1);
                    }
                }
            }

            IntPtr ptr = Marshal.AllocHGlobal(totalTopic);
            Marshal.Copy(topicType, 0, ptr, totalTopic);

            bRes = rbtnet_.sendStartAnswer(type, totalTopic, ptr);
            Marshal.FreeHGlobal(ptr);
        }

        private void button_stop_Click(object sender, EventArgs e)
        {
            rbtnet_.sendStopAnswer();
            foreach (var item in dicMac2DrawForm_)
            {
                item.Value.UpdateJDNum(0);
            }
        }

        private void button_end_Click(object sender, EventArgs e)
        {
            rbtnet_.sendEndAnswer();
            foreach (var item in dicMac2DrawForm_)
            {
                item.Value.UpdateJDNum(0);
            }
        }

        private void comboBox_Qtype_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBox_Qlist.Items.Clear();
            textBox_num.Text = "1";
            this.button_start.Enabled = true;
            switch (comboBox_Qtype.SelectedIndex)
            {
                case 0:
                    {
                        comboBox_Qlist.Items.Add("无");
                        comboBox_Qlist.SelectedIndex = 0;
                        comboBox_Qlist.Enabled = false;
                        textBox_num.Text = "1";
                        textBox_num.Enabled = false;
                        break;
                    }
                case 1:
                    {
                        comboBox_Qlist.Enabled = true;
                        comboBox_Qlist.Items.Add("判断题");
                        comboBox_Qlist.Items.Add("单选题");
                        comboBox_Qlist.Items.Add("多选题");
                        comboBox_Qlist.Items.Add("抢答题");
                        if (oemkey == "YJ" || oemkey == "ZHL")
                        {
                            comboBox_Qlist.Items.Add("解答题");
                        }
                        comboBox_Qlist.Items.Add("混合模拟");
                        comboBox_Qlist.SelectedIndex = 0;
                        break;
                    }
                case 2:
                    {
                        comboBox_Qlist.Enabled = true;
                        comboBox_Qlist.Items.Add("单选题");
                        comboBox_Qlist.Items.Add("多选题");
                        comboBox_Qlist.SelectedIndex = 0;
                        textBox_num.Text = "1";
                        textBox_num.Enabled = false;

                        if (oemkey == "YJ")
                        {
                            this.button_start.Enabled = false;
                            MessageBox.Show("当前固件不支持");
                        }

                        break;
                    }
                case 3:
                    {
                        comboBox_Qlist.Items.Add("无");
                        comboBox_Qlist.SelectedIndex = 0;
                        comboBox_Qlist.Enabled = false;
                        textBox_num.Enabled = true;
                        break;
                    }
                case 4:
                    {
                        comboBox_Qlist.Items.Add("无");
                        comboBox_Qlist.SelectedIndex = 0;
                        comboBox_Qlist.Enabled = false;
                        textBox_num.Enabled = true;

                        if (oemkey == "YJ")
                        {
                            this.button_start.Enabled = false;
                            MessageBox.Show("当前固件不支持");
                        }

                        break;
                    }
                case 5:
                    {
                        comboBox_Qlist.Items.Add("无");
                        comboBox_Qlist.SelectedIndex = 0;
                        comboBox_Qlist.Enabled = false;
                        textBox_num.Text = "1";
                        textBox_num.Enabled = false;

                        if (oemkey == "YJ")
                        {
                            this.button_start.Enabled = false;
                            MessageBox.Show("当前固件不支持");
                        }

                        break;
                    }
                default:
                    {
                        break;
                    }
            }
        }

        private void comboBox_Qlist_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox_Qtype.SelectedIndex == 1)
            {
                if (comboBox_Qlist.SelectedIndex == 3 || comboBox_Qlist.SelectedIndex == 5||(comboBox_Qlist.SelectedIndex == 4 && oemkey != "YJ" && oemkey != "ZHL"))
                {
                    textBox_num.Enabled = false;
                }
                else
                {
                    textBox_num.Enabled = true;
                }
            }
        }

        private void LookAnswerResultToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string macStr = string.Empty;
            string numStr = string.Empty;
            string nameStr = string.Empty;
            if (GetListViewSelectMac(out macStr, out numStr, out nameStr))
            {
                if(AnswerResultDicDetail.ContainsKey(macStr))
                {
                    ShowAnswerResult saform = new ShowAnswerResult(AnswerResultDicDetail[macStr]);
                    saform.ShowDialog();
                }
                else
                {
                    MessageBox.Show(string.Format(@"{1}暂未提交答案", macStr));
                }
            }
            
        }

        private void SetFBMenuItem_Click(object sender, EventArgs e)
        {
            string macStr = string.Empty;
            string numStr = string.Empty;
            string nameStr = string.Empty;
            if (GetListViewSelectMac(out macStr, out numStr, out nameStr))
            {
                SetFBMsg setFBMsgForm = new SetFBMsg(macStr,this);
                setFBMsgForm.ShowDialog();
            }

        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= '0' && e.KeyChar <= '9') || (e.KeyChar == 8))
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }
        bool PageNumberContrast = false;
        int pageNumber = 0;
        private void button3_Click(object sender, EventArgs e)
        {
            if(PageNumberContrast)
            {
                this.button3.Text = "开启页码对比"; ;
                PageNumberContrast = false;
                this.textBox1.Enabled = true;
            }
            else
            {
                this.button3.Text = "关闭页码对比"; ;
                pageNumber = int.Parse(this.textBox1.Text);
                this.textBox1.Enabled = false;
                PageNumberContrast = true; 
            }
        }
    }
}
