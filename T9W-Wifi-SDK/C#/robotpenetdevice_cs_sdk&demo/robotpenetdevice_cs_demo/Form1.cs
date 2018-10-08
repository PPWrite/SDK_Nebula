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

namespace rbt_win32_2_demo
{
    public partial class Form1 : Form
    {
        public RbtNet rbtnet_ = null;

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
            //param.optimize = true;
            rbtnet_.init(ref param);


            comboBox1.Items.Add("判断题");
            comboBox1.Items.Add("单选题");
            comboBox1.Items.Add("多选题");
            comboBox1.Items.Add("多道客观题");
            comboBox1.SelectedIndex = 0;
            /*
            * 所有事件响应接口都是在内部SDK线程中上报出来
            */
            rbtnet_.deviceMacEvt_ += Rbtnet__deviceMacEvt_;

            rbtnet_.deviceNameEvt_ += Rbtnet__deviceNameEvt_;
            rbtnet_.deviceNameResult_ += Rbtnet__eviceNameResultEvt_;
            rbtnet_.deviceDisconnectEvt_ += Rbtnet__deviceDisconnectEvt_;
            rbtnet_.deviceOriginDataEvt_ += Rbtnet__deviceOriginDataEvt_;
            rbtnet_.deviceShowPageEvt_ += Rbtnet__deviceShowPageEvt_;
            rbtnet_.deviceKeyPressEvt_ += Rbtnet__deviceKeyPressEvt_;
            rbtnet_.deviceAnswerResultEvt_ += Rbtnet__deviceAnswerResultEvt_;

            rbtnet_.deviceError_ += Rbtnet__deviceEvt;
            rbtnet_.deviceClearCanvas_ += Rbtnet__deviceClearCanvas;
        }
        public void Rbtnet__deviceEvt(IntPtr ctx, String pmac, int cmd, String msg)
        {
            updateLable(this.label3,string.Format(@"命令：{0}，错误信息：{1}", cmd.ToString(), msg));
        }

        public void Rbtnet__deviceClearCanvas(IntPtr ctx, String pmac)
        {
            string sMac = pmac;
            if (dicMac2DrawForm_.ContainsKey(sMac))
            {
                dicMac2DrawForm_[sMac].clearCanvasEvtCall();
            }
        }

        private void Rbtnet__deviceNameEvt_(IntPtr ctx, string strDeviceMac, string strDeviceName)
        {
            // Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);
            updateDeviceNameListView(strDeviceMac, strDeviceName);
            Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);
        }

        private void Rbtnet__eviceNameResultEvt_(IntPtr ctx, string strDeviceMac,int res, string strDeviceName)
        {
            // Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);
            updateDeviceNameListView(strDeviceMac, strDeviceName);
        }

        // 
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

        private void Rbtnet__deviceShowPageEvt_(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            updateDeviceMacListView_ShowPage(sMac, nNoteId, nPageId);
        }

        private void Rbtnet__deviceDisconnectEvt_(IntPtr ctx, IntPtr strDeviceMac)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            updateDeviceMacListView_Disconnect(sMac);
        }

        private void initListView() {
            this.listView1.Columns.Add("设备MAC地址", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("学号", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("状态", 60, HorizontalAlignment.Left);
            this.listView1.Columns.Add("答题提交通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("按键通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("页码通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("学生姓名", 120, HorizontalAlignment.Left);
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
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            if (dicMac2DrawForm_.ContainsKey(sMac)) {
                int npenStatus = Convert.ToInt32(us);
                if (npenStatus != 17&& npenStatus != 33)
                {
                    npenStatus = 0;
                }
                dicMac2DrawForm_[sMac].recvData(npenStatus, ux, uy, up);
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
        private void Rbtnet__deviceOptimizeDataEvt_(IntPtr ctx, IntPtr pmac, ushort us, ushort ux, ushort uy, float width, float speed)
        {
            string sMac = Marshal.PtrToStringAnsi(pmac);
            if (dicMac2DrawForm_.ContainsKey(sMac))
            {
                int npenStatus = Convert.ToInt32(us);
                if (width>0)
                {
                    npenStatus = 17;
                }
                if (npenStatus != 17 && npenStatus != 33)
                {
                    npenStatus = 0;
                }
                dicMac2DrawForm_[sMac].recvData(npenStatus, ux, uy, 0);
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
                this.dicMac2DrawForm_.Clear();

                this.label3.Text = "关闭服务，手写板小房子消失，上位机不能发送命令和响应消息";
            }
        }

        /// <summary>
        /// 答题开始或结束按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_answer_Click(object sender, EventArgs e)
        {
            if (this.button_answer.Text == "开始答题")
            {
                int totalTopic = 1;
                byte[] topicType;
                bool bRes = false;

                int index = comboBox1.SelectedIndex;
                switch (index)
                {
                    case 0:
                        {
                            topicType = new byte[totalTopic];
                            topicType[0] = 1;
                            break;
                        }
                    case 1:
                        {
                            topicType = new byte[totalTopic];
                            topicType[0] = 2;
                            break;
                        }
                    case 2:
                        {
                            topicType = new byte[totalTopic];
                            topicType[0] = 3;
                            break;
                        }
                    case 3:
                        {
                            totalTopic = 3;
                            topicType = new byte[totalTopic];
                            topicType[0] = 3;
                            topicType[1] = 2;
                            topicType[2] = 1;
                            break;
                        }
                    default:
                        totalTopic = 3;
                        topicType = new byte[totalTopic];
                        topicType[0] = 1;
                        topicType[1] = 2;
                        topicType[2] = 3;
                        break;
                }
                IntPtr ptr = Marshal.AllocHGlobal(totalTopic);
                Marshal.Copy(topicType, 0, ptr, totalTopic);

                bRes = rbtnet_.sendStartAnswer(1, totalTopic, ptr);
                if (bRes)
                {
                    this.button_answer.Text = "结束答题";
                }
                else
                {
                    MessageBox.Show("发送开始答题失败");
                }

                Marshal.FreeHGlobal(ptr);
                this.label3.Text = "进入答题模式，按键事件失效，只接收手写板确认提交答案的事件";
            }
            else
            {
                rbtnet_.sendEndAnswer();
                this.button_answer.Text = "开始答题";
                this.label3.Text = "恢复到正常模式，开始响应按键事件";
            }
        }
        /// <summary>
        /// 更新设备MAC地址
        /// </summary>
        /// <param name="strMac"></param>
        private delegate void updateDeviceMac(string strMac);
        private Dictionary<string, drawForm> dicMac2DrawForm_ = new Dictionary<string, drawForm>();
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
                            dicMac2DrawForm_.Add(strMac, new drawForm());
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

                if (!dicMac2DrawForm_.ContainsKey(strMac)) {
                    dicMac2DrawForm_.Add(strMac, new drawForm());
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
        private delegate void updateDeviceMac_ShowPage(string strMac, int nNoteId, int nPageId);
        public void updateDeviceMacListView_ShowPage(string strMac, int nNoteId, int nPageId)
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
                this.listView1.Invoke(d, new object[] { strMac, nNoteId, nPageId });
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
                    this.listView1.Items[nFindItem].SubItems[5].Text = "noteid=" + Convert.ToString(nNoteId) + " pageid=" + Convert.ToString(nPageId);
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

        /// <summary>
        /// 收到答题消息
        /// </summary>
        /// <param name="strMac"></param>
        /// <param name="keyValue"></param>
        private delegate void updateDeviceMac_AnswerResult(string strMac, int resID, byte[] strResult, int nResultSize);
        public void updateDeviceMacListView_AnswerResult(string strMac, int resID, byte[] strResult,int nResultSize)
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
                    string strKeyValue = string.Empty;
                    if (resID!=110)
                    {
                        strKeyValue = GetResultKey(resID, strResult);
                    }
                    else
                    {
                        int count = nResultSize / 8;
                        for (int i = 0; i < count; i++)
                        {
                            byte[] byteRes = new byte[6];
                            Array.Copy(strResult,i*8+2, byteRes,0,6);
                            strKeyValue+= GetResultKey(i+1, byteRes)+"；";
                        }
                    }
                    
                    this.listView1.Items[nFindItem].SubItems[3].Text = strKeyValue;

                }
            }
        }
        private string GetResultKey(int resultId,byte[] strResult)
        {
            string strKeyValue = string.Format("{0}：", resultId);
            foreach (var c in strResult)
            {
                keyPressEnum keyValueE = (keyPressEnum)c;
                switch (keyValueE)
                {
                    case keyPressEnum.K_A:
                        strKeyValue += "A";
                        break;
                    case keyPressEnum.K_B:
                        strKeyValue += "B";
                        break;
                    case keyPressEnum.K_C:
                        strKeyValue += "C";
                        break;
                    case keyPressEnum.K_D:
                        strKeyValue += "D";
                        break;
                    case keyPressEnum.K_E:
                        strKeyValue += "E";
                        break;
                    case keyPressEnum.K_F:
                        strKeyValue += "F";
                        break;
                    case keyPressEnum.K_SUCC:
                        strKeyValue += "正确";
                        break;
                    case keyPressEnum.K_ERROR:
                        strKeyValue += "错误";
                        break;
                    case keyPressEnum.K_CACLE:
                        strKeyValue += "取消";
                        break;
                    case keyPressEnum.K_SURE:
                        strKeyValue += "确认";
                        break;
                    default:
                        break;
                }
            }
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
            if(!startConfigNet)
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
        private bool GetListViewSelectMac(out string strMac,out string strNum,out string strName)
        {
            var items = this.listView1.SelectedItems;
            strMac = string.Empty;
            strNum = string.Empty;
            strName = string.Empty;
            if (items.Count>0)
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
            if(GetListViewSelectMac(out macStr,out numStr, out nameStr))
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
                    string strIP = this.IpComboBox.Text;
                    if (!string.IsNullOrEmpty(strIP))
                    {
                        rbtnet_.configNet(strIP, 6001, false, true, "");
                    }
                }

                if (string.IsNullOrEmpty(this.IpComboBox.Text)&& this.IpComboBox.Items.Count>0)
                {
                    this.IpComboBox.Text=this.IpComboBox.Items[0].ToString();
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
                    if(delayClose<=0)
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

        private void button3_Click(object sender, EventArgs e)
        {
            if (this.button3.Text == "开始答题")
            {
                //rbtnet_.openModule(true);
                bool bRes = rbtnet_.sendStartAnswer(0, 0, IntPtr.Zero);

                if (bRes)
                {
                    this.button3.Text = "停止答题";
                }
                else
                {
                    MessageBox.Show("发送开始答题失败");
                }
                this.label4.Text = "调用主观题开始答题接口，手写板LED显示“开始答题”";
            }
            else if (this.button3.Text == "停止答题")
            {
                rbtnet_.sendStopAnswer();
                this.button3.Text = "结束答题";
                this.label4.Text = "调用停止答题命令，手写板LED显示“已停止答题”";
            }
            else
            {
                rbtnet_.sendEndAnswer();
                this.button3.Text = "开始答题";
                this.label4.Text = "恢复非答题状态";
            }
        }



        private delegate void updateLable_Evt(Label _lable, string Text);
        public void updateLable(Label _lable, string Text)
        {
            if(_lable.InvokeRequired)
            {
                while(!_lable.IsHandleCreated)
                {
                    if(_lable.Disposing|| _lable.IsDisposed)
                    {
                        return;
                    }
                }
                updateLable_Evt uLEvt = new updateLable_Evt(updateLable);
                _lable.Invoke(uLEvt,new object[] { _lable , Text });
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
                item.Value.NotExit = false;
                item.Value.Close();
            }
            dicMac2DrawForm_.Clear();
            try
            {
                if(!isClosing)
                {
                    rbtnet_.stop();
                    e.Cancel = true;
                    isClosing = true;
                }
                
                
            }
            catch (Exception)
            {
                //Environment.Exit(0);
            }
            finally
            {
                //Environment.Exit(0);
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
            for (int i = 0; i < nItemCount; ++i)
            {
                DeviceSettingInfo dsInfo = new DeviceSettingInfo()
                {
                    DeviceNum = this.listView1.Items[i].SubItems[0].Text,
                    StudentNum = this.listView1.Items[i].SubItems[1].Text,
                    StudentName = this.listView1.Items[i].SubItems[6].Text,
                };
                deviceSettingInfos.Add(dsInfo);
            }

            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = @"CSV文件|*.csv";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                string file = sfd.FileName;
                FileHelper fh = new FileHelper();
                fh.FileWriteForDeviceInfo(file, deviceSettingInfos);
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
    }
}
