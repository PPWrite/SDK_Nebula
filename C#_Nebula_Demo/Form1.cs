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
    public partial class Form1 : Form
    {
        // 子设备窗口
        private myControl[] subNodeWindow = new myControl[60];
        private bool bScreen = true;
        public Form1()
        {
            InitializeComponent();
            init();

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // 获取最右边控件的坐标
            Point pt = this.device_textBox.Location;
            int nSubWinStartX = pt.X + this.device_textBox.Width + 50;
            int xCount = 0;
            int nSubWinStartY = 20;

            Size size = this.Size;
            int nWinSize = 100;
            // 计算一行可以放下多少个窗口
            int nColumCount = (this.ClientRectangle.Width - nSubWinStartX) / (120);
            int nNeedCount = 60 / (nColumCount);
            if (60%nColumCount != 0)
            {
                nNeedCount += 1;
            }

            // 计算可以放下多少行
            int nRowCount = this.Height / (120);
            if (nNeedCount > nRowCount)  // 需要的行数大于窗口高度 需要缩小波形窗口
            {
                while (nWinSize-- > 0)
                {
                    int nTempRowCount = (this.ClientRectangle.Width - nSubWinStartX) / (nWinSize+20);
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
                int nX = nSubWinStartX + (xCount * (nWinSize+20));
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

                this.subNodeWindow[i] = new myControl();
                this.subNodeWindow[i].m_nIndex = i + 1;
                this.subNodeWindow[i].canvasShowEvt += dbClkCanvas;
                this.subNodeWindow[i].setControlSize(nWinSize, nWinSize);
                this.subNodeWindow[i].Location = new Point(nX, nSubWinStartY);
                this.subNodeWindow[i].BackColor = Color.Black;
                this.Controls.Add(this.subNodeWindow[i]);
                //this.subNodeWindow[i].start();  
                this.SuspendLayout();
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
        }
        private TrailsShowFrom[] canvasWindow = new TrailsShowFrom[60];
        private void dbClkCanvas(string strIndex)
        {
            int nIndex = Convert.ToInt32(strIndex);
            if (canvasWindow[nIndex-1] == null || canvasWindow[nIndex-1].IsDisposed)
            {
                canvasWindow[nIndex - 1] = new TrailsShowFrom();
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

        public void init()
        {
            robotpenController.GetInstance()._ConnectInitialize(0, IntPtr.Zero);
            robotpenController.GetInstance().gateWayStatusEvt += Form1_gateWayStatusEvt;
            robotpenController.GetInstance().nodeStatusEvt += Form1_nodeStatusEvt;
            robotpenController.GetInstance().gatewayErrorEvt += Form1_gatewayErrorEvt;
            robotpenController.GetInstance().exitVotePatternEvt += Form1_exitVotePatternEvt;
            robotpenController.GetInstance().gatewatVersionEvt += Form1_gatewatVersionEvt;
            robotpenController.GetInstance().bigDataReportEvt += Form1_bigDataReportEvt;
            robotpenController.GetInstance().onlineStatusEvt += Form1_onlineStatusEvt;
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

        private void Form1_bigDataReportEvt(byte bIndex, byte bPenStatus, short bx, short by, short bPress)
        {
            int nIndex = Convert.ToInt32(bIndex);
            if (nIndex >= subNodeWindow.Length)
                return;
            
            if (null != subNodeWindow[nIndex])
            {
                subNodeWindow[nIndex].dataArrive(Convert.ToInt32(bx), Convert.ToInt32(by));
                updateBoxingEx(nIndex);
            }

            if (canvasWindow[nIndex] == null || canvasWindow[nIndex].IsDisposed)
                return;

            canvasWindow[nIndex].recvData(Convert.ToInt32(bPress), Convert.ToInt32(bx), Convert.ToInt32(by), 0);
        }

        // 设备版本号 
        private void Form1_gatewatVersionEvt(string strVersion, byte bCustomNum, byte bClassNum, byte bDeviceNum)
        {
            updateDeviceVersionLabel(strVersion);
            string strCustomNum = bCustomNum.ToString();
            string strClassNum = bClassNum.ToString();
            string strDeviceNum = bDeviceNum.ToString();
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
                case NODE_STATUS.DEVICE_SEMI_FINISHED_PRODUCT_TEST:
                    {
                        strStatus = "DEVICE_SEMI_FINISHED_PRODUCT_TEST";
                    }
                    break;
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
            robotpenController.GetInstance()._ConnectDispose();

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
            robotpenController.GetInstance()._Send(cmdId.VoteStart);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.VoteEnd);
        }

        private void open_button_Click(object sender, EventArgs e)
        {
            if (this.open_button.Text == "打开设备")
            {
                robotpenController.GetInstance()._ConnectOpen();
                this.open_button.Text = "关闭设备";
            }
            else
            {
                robotpenController.GetInstance()._ConnectDispose();
                this.open_button.Text = "打开设备";
            }
        }

        // MS模式
        private void ns_start_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.WriteStart);
        }

        // 结束MS模式
        private void ms_end_button_Click(object sender, EventArgs e)
        {
            robotpenController.GetInstance()._Send(cmdId.WriteEnd);
        }

        // 设置
        private void set_button_Click(object sender, EventArgs e)
        {

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
    }
}
