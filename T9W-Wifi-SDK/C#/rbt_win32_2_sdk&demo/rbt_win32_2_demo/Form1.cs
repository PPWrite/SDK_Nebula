using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using rbt_win32_2;
using System.Runtime.InteropServices;

namespace rbt_win32_2_demo
{
    public partial class Form1 : Form
    {
        private RbtNet rbtnet_ = null;

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
            param.port = 6001;
            param.listenCount = 60;
            rbtnet_.init(ref param);

            /*
            * 所有事件响应接口都是在内部SDK线程中上报出来
            */
            rbtnet_.deviceMacEvt_ += Rbtnet__deviceMacEvt_;
            rbtnet_.deviceNameEvt_ += Rbtnet__deviceNameEvt_;
            rbtnet_.deviceDisconnectEvt_ += Rbtnet__deviceDisconnectEvt_;
            rbtnet_.deviceOriginDataEvt_ += Rbtnet__deviceOriginDataEvt_;
            rbtnet_.deviceShowPageEvt_ += Rbtnet__deviceShowPageEvt_;
            rbtnet_.deviceKeyPressEvt_ += Rbtnet__deviceKeyPressEvt_;
            rbtnet_.deviceAnswerResultEvt_ += Rbtnet__deviceAnswerResultEvt_;
        }

        private void Rbtnet__deviceNameEvt_(IntPtr ctx, string strDeviceMac, string strDeviceName)
        {
            Console.WriteLine("Rbtnet__deviceMacEvt_:{0}-{1}", strDeviceMac, strDeviceName);

        }
        // 
        private void Rbtnet__deviceAnswerResultEvt_(IntPtr ctx, IntPtr strDeviceMac, int resID, IntPtr result, int nResultSize)
        {
            string sMac = Marshal.PtrToStringAnsi(strDeviceMac);
            string sResult = Marshal.PtrToStringAnsi(result);
            byte[] byteRes = new byte[nResultSize];
            Marshal.Copy(result, byteRes, 0, nResultSize);
            Console.WriteLine("Rbtnet__deviceAnswerResultEvt_:{0}-{1}", sMac, sResult);
            updateDeviceMacListView_AnswerResult(sMac, resID, byteRes);
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
            this.listView1.Columns.Add("状态", 60, HorizontalAlignment.Left);
            this.listView1.Columns.Add("选择题通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("按键通知", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("页码通知", 120, HorizontalAlignment.Left);
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
                if (npenStatus != 17)
                {
                    npenStatus = 0;
                }
                dicMac2DrawForm_[sMac].recvData(npenStatus, ux, uy, up);
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
            }
            else {
                rbtnet_.stop();
                this.button_start_stop.Text = "开始";
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
                int totalTopic = 3;
                byte []topicType = new byte[totalTopic];
                topicType[0] = 1;
                topicType[1] = 2;
                topicType[2] = 3;
                IntPtr ptr = Marshal.AllocHGlobal(totalTopic);
                Marshal.Copy(topicType, 0, ptr, totalTopic);

                if (rbtnet_.sendStartAnswer(totalTopic,ptr))
                {
                    this.button_answer.Text = "结束答题";
                }
                else
                {
                    MessageBox.Show("发送开始答题失败");
                }

                Marshal.FreeHGlobal(ptr);
            }
            else
            {
                rbtnet_.sendStopAnswer();
                this.button_answer.Text = "开始答题";
            }
        }
        /// <summary>
        /// 更新设备MAC地址
        /// </summary>
        /// <param name="strMac"></param>
        private delegate void updateDeviceMac(string strMac);
        private Dictionary<string, drawForm> dicMac2DrawForm_ = new Dictionary<string, drawForm>();
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
                updateDeviceMac d = new updateDeviceMac(updateDeviceMacListView_Mac);
                this.listView1.Invoke(d, new object[] { strMac });
            }
            else
            {
                int nItemCount = this.listView1.Items.Count;
                for (int i = 0; i < nItemCount; ++i) {
                    string strAMac = this.listView1.Items[i].SubItems[0].Text;
                    if (strAMac == strMac) {
                        this.listView1.Items[i].SubItems[1].Text = "在线";
                        return;
                    }
                }

                this.listView1.Items.Add(strMac);
                this.listView1.Items[nItemCount].SubItems.Add("在线");
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
                    this.listView1.Items[nFindItem].SubItems[1].Text = "离线";

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
                    this.listView1.Items[nFindItem].SubItems[4].Text = "noteid=" + Convert.ToString(nNoteId) + " pageid=" + Convert.ToString(nPageId);
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
                    this.listView1.Items[nFindItem].SubItems[3].Text = strKeyValue;

                }
            }
        }


        /// <summary>
        /// 收到答题消息
        /// </summary>
        /// <param name="strMac"></param>
        /// <param name="keyValue"></param>
        private delegate void updateDeviceMac_AnswerResult(string strMac, int resID, byte[] strResult);
        public void updateDeviceMacListView_AnswerResult(string strMac, int resID, byte[] strResult)
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
                this.listView1.Invoke(d, new object[] { strMac, strResult });
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
                    string strKeyValue = string.Format("{0}", resID);

                    foreach (var c in strResult) {
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
                    this.listView1.Items[nFindItem].SubItems[2].Text = strKeyValue;

                }
            }
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

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            foreach (var item in dicMac2DrawForm_)
            {
                item.Value.NotExit = false;
                item.Value.Close();
            }
            dicMac2DrawForm_.Clear();

            rbtnet_.stop();
            rbtnet_.unInit();
        }

        private void button_test_Click(object sender, EventArgs e)
        {
            string strStu = "222";
            string strMac = "1b2200000050";
            //rbtnet_.configStu(strMac, strStu);//*/
            string strSSID = "C_68E";
            string strPWD = "test1234";
            rbtnet_.configWifi(strSSID, strPWD, "", "");//*/
        }

        private void button_switch_Click(object sender, EventArgs e)
        {
            string strIP = textBox1.Text;
            rbtnet_.configNet(strIP, 6001, false, true, "");
        }
    }
}
