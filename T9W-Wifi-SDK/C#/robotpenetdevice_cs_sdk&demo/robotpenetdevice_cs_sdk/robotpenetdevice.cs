using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;

namespace robotpenetdevice_cs
{
    public partial class RbtNet
    {
        // 构造函数
        public RbtNet()
        {
        }

        public event onAccept acceptEvt_;
        public event onErrorPacket errorPacketEvt_;

        public event onOriginData deviceOriginDataEvt_;
        public event onOriginDataNew deviceOriginDataNewEvt_;
        public event onOriginDataNewEx originDataNewExEvt_;

        public event onDeviceMac deviceMacEvt_;
        public event onDeviceName deviceNameEvt_;
        public event onDeviceNameResult deviceNameResult_;

        public event onDeviceDisconnect deviceDisconnectEvt_;
        public event onDeviceKeyPress deviceKeyPressEvt_;
        public event onDeviceAnswerResult deviceAnswerResultEvt_;
        public event onDeviceShowPage deviceShowPageEvt_;
        public event onDeviceShowPageNew deviceShowPageNewEvt_;

        public event onError deviceError_ = null;
        public event onCanvasID deviceCanvasID_ = null;

        public event onOptimizeData deviceOptimizeDataEvt_ = null;
        public event onOptimizeDataEx optimizeDataExEvt_ = null;

        public event onDeviceType DeviceTypeEvt_ = null;
        public event onKeyAnswer KeyAnswerEvt_ = null;
        public event onDeviceInfo DeviceInfoEvt_ = null;
        public event onHardInfo HardInfoEvt_ = null;
        public event onDeviceBattery DeviceBatteryEvt_ = null;

        public event onDeleteNotes deleteNotesEvt_ = null;

        public event onDeviceIp DeviceIpEvt_ = null;

        public event onOidPageInfo oidPageInfoEvt_ = null;
        public event onCurrentWritingNum CurrentWritingNumEvt_ = null;


        private GCHandle gchandld;
        private IntPtr iPtrThis_ = IntPtr.Zero;
        PrintType pt = PrintType.Base;
        public static Dictionary<string, string> ipdic = new Dictionary<string, string>();

        /// <summary>
        /// 初始化
        /// </summary>
        /// <param name="arg"></param>
        public void init(ref Init_Param arg, bool open = true)
        {
            gchandld = GCHandle.Alloc(this);
            iPtrThis_ = GCHandle.ToIntPtr(gchandld);
            arg.ctx = iPtrThis_;
            arg.open = open;
            if (arg.port == 0)
            {
                arg.port = 6001;
            }
            if (arg.listenCount == 0)
            {
                arg.listenCount = 60;
            }
            bool sus = rbt_win_init(ref arg);
            BindEvent();
        }

        public void init(int port = 6001, int listenCount = 60, bool open = true, bool optimize = false)
        {
            gchandld = GCHandle.Alloc(this);
            iPtrThis_ = GCHandle.ToIntPtr(gchandld);
            rbt_win_init2(port, listenCount, open, optimize);
            BindEvent();
        }

        private void BindEvent()
        {
            onaccept = new onAccept(accept);
            rbt_win_set_accept_cb(onaccept);
            onerrorpacket = new onErrorPacket(errorPacket);
            rbt_win_set_errorpacket_cb(onerrorpacket);

            onorigindatanew = new onOriginDataNew(originDataNotifyNew);
            rbt_win_set_origindata_cb(onorigindatanew);
            onorigindatanewex = new onOriginDataNewEx(originDataNotifyEx);
            rbt_win_set_origindata_ex_cb(onorigindatanewex);

            ondevicemac = new onDeviceMac(deviceMacNotify);
            rbt_win_set_devicemac_cb(ondevicemac);
            ondevicename = new onDeviceName(deviceNameNotify);
            rbt_win_set_devicename_cb(ondevicename);
            ondevicenameresult = new onDeviceNameResult(deviceNameResultNotify);
            rbt_win_set_devicenameresult_cb(ondevicenameresult);

            ondevicedisconnect = new onDeviceDisconnect(deviceDisconnect);
            rbt_win_set_devivedisconnect_cb(ondevicedisconnect);
            ondevicekeyPress = new onDeviceKeyPress(deviceKeyPress);
            rbt_win_set_devicekeypress_cb(ondevicekeyPress);
            ondeviceanswerresult = new onDeviceAnswerResult(deviceAnswerResult);
            rbt_win_set_deviceanswerresult_cb(ondeviceanswerresult);
            ondeviceshowpagenew = new onDeviceShowPageNew(deviceShowPageNew);
            rbt_win_set_deviceshowpage_cb(ondeviceshowpagenew);
            
            onerror = new onError(deviceError);
            rbt_win_set_error_cb(onerror);
            oncanvasid = new onCanvasID(deviceClearCanvas);
            rbt_win_set_canvasid_cb(oncanvasid);

            onoptimizedata = new onOptimizeData(optimizeData);
            rbt_win_set_optimizedata_cb(onoptimizedata);
            onoptimizedataex = new onOptimizeDataEx(optimizeDataEx);
            rbt_win_set_optimizedata_ex_cb(onoptimizedataex);

            ondevicetype = new onDeviceType(deviceType);
            rbt_win_set_devicetype_cb(ondevicetype);
            onkeyanswer = new onKeyAnswer(keyAnswer);
            rbt_win_set_keyanswer_cb(onkeyanswer);
            ondeviceinfo = new onDeviceInfo(deviceInfo);
            rbt_win_set_deviceinfo_cb(ondeviceinfo);
            onhardinfo = new onHardInfo(hardInfo);
            rbt_win_set_hardinfo_cb(onhardinfo);
            ondevicebattery = new onDeviceBattery(deviceBattery);
            rbt_win_set_devicebattery_cb(ondevicebattery);

            ondeletenotes = new onDeleteNotes(deleteNotes);
            rbt_win_set_deletenotes_cb(ondeletenotes);

            ondeviceipold = new onDeviceIpOld(deviceip);
            rbt_win_set_deviceip_cb(ondeviceipold);

            onoidpageinfo = new onOidPageInfo(oidPageInfo);
            rbt_win_set_oidpageinfo_cb(onoidpageinfo);
            oncurrentwritingnum = new onCurrentWritingNum(currentWritingNum);
            rbt_wib_set_currentwritingnum_cb(oncurrentwritingnum);
        }


        /// <summary>
        /// 设置页码打印模式
        /// </summary>
        /// <param name="_pt"></param>
        public void setPrintType(PrintType _pt)
        {
            pt = _pt;
        }

        // 反初始化
        public void unInit()
        {
            rbt_win_uninit();
            gchandld.Free();
        }

        /// <summary>
        /// 发送命令（获取设备信息能用到）
        /// </summary>
        /// <param name="cmdkey"></param>
        /// <param name="mac"></param>
        public bool SendCmd(int cmdkey, string mac = "")
        {
            return rbt_win_send(cmdkey, mac);
        }
        /// <summary>
        /// 发送命令（获取设备信息能用到）
        /// </summary>
        /// <param name="cmdkey">命令枚举值</param>
        /// <param name="mac">设备号，为空获取所有设备信息</param>
        public bool SendCmd(DeviceCmd cmdkey, string mac = "")
        {
            return rbt_win_send((int)cmdkey, mac);
        }

        /// <summary>
        /// 发送开始答题
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题 2为投票 3为不定选择 4为测试 5为书写</param>
        /// <param name="totalTopic">totalTopic 题目总数</param>
        /// <param name="pTopicType">pTopicType 题目类型 1判断 2单选 3多选 4抢答 5解答</param>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        public bool sendStartAnswer(int type, int totalTopic, IntPtr pTopicType, string mac = "")
        {
            return rbt_win_send_startanswer(type, totalTopic, pTopicType, mac);
        }
        /// <summary>
        /// 发送开始答题
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题 2为投票 3为不定选择 4为测试 5为书写</param>
        /// <param name="pTopicTypeArray">题目集合，存储每道题对应的题目类型 1判断 2单选 3多选 4抢答 5解答</param>
        /// <param name="mac"></param>
        /// <returns></returns>
        public bool sendStartAnswer(int type, byte[] pTopicTypeArray, string mac = "")
        {
            if(pTopicTypeArray.Count()<=0)
            {
                return false;
            }
            int totalTopic = pTopicTypeArray.Count();

            IntPtr pTopicType = Marshal.AllocHGlobal(totalTopic);
            Marshal.Copy(pTopicTypeArray, 0, pTopicType, totalTopic);
            bool result= rbt_win_send_startanswer(type, totalTopic, pTopicType, mac);
            Marshal.FreeHGlobal(pTopicType);
            return result;
        }

        /// <summary>
        /// 开始答题(若支持多主观题用此接口)
        /// 客户定制，中性不支持
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题</param>
        /// <param name="totalTopic">totalTopic 题目总数</param>
        /// <param name="pTopicType">pTopicType 题目类型 1判断 2单选 3多选 4抢答</param>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        public bool sendStartAnswerEx(int type, int totalTopic, IntPtr pTopicType, string mac = "")
        {
            return rbt_win_send_startanswerEx(type, totalTopic, pTopicType, mac);
        }
        /// <summary>
        /// 开始答题(若支持多主观题用此接口)
        /// 客户定制，中性不支持
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题 2为投票 3为不定选择 4为测试 5为书写</param>
        /// <param name="pTopicTypeArray">题目集合，存储每道题对应的题目类型 1判断 2单选 3多选 4抢答 5解答</param>
        /// <param name="mac"></param>
        /// <returns></returns>
        public bool sendStartAnswerEx(int type, byte[] pTopicTypeArray, string mac = "")
        {
            if (pTopicTypeArray.Count() <= 0)
            {
                return false;
            }
            int totalTopic = pTopicTypeArray.Count();

            IntPtr pTopicType = Marshal.AllocHGlobal(totalTopic);
            Marshal.Copy(pTopicTypeArray, 0, pTopicType, totalTopic);
            return rbt_win_send_startanswerEx(type, totalTopic, pTopicType, mac);
        }

        /// <summary>
        /// 发送结束答题命令
        /// </summary>
        public void sendStopAnswer(string mac = "")
        {
            rbt_win_send_stopanswer(mac);
        }

        /// <summary>
        /// 发送结束答题命令
        /// </summary>
        public void sendEndAnswer(string mac = "")
        {
            rbt_win_send_endanswer(mac);
        }


        /// <summary>
        /// 开启服务
        /// </summary>
        /// <returns>bool</returns>
        public bool start()
        {
            return rbt_win_start();
        }

        /// <summary>
        /// 停止服务
        /// </summary>
        public void stop()
        {
            rbt_win_stop();
        }

        /// <summary>
        /// 设置学生学号（不支持中文）
        /// </summary>
        /// <param name="strDeviceMac">设备mac地址</param>
        /// <param name="strDeviceStu">学生学号</param>
        /// <returns></returns>
        public int configStu(string strDeviceMac, string strDeviceStu)
        {
            return rbt_win_config_stu(strDeviceMac, strDeviceStu);
        }

        /// <summary>
        /// 设置学生姓名（支持中文）
        /// </summary>
        /// <param name="strDeviceMac">设备mac地址</param>
        /// <param name="strDeviceStuNo">学生学号</param>
        /// <param name="strDeviceStuName">学生名称</param>
        /// <returns></returns>
        public int configBmpStu(string strDeviceMac, string strDeviceStuNo, string strDeviceStuName)
        {
            return rbt_win_config_bmp_stu(strDeviceMac, strDeviceStuNo, strDeviceStuName);
        }

        /// <summary>
        /// 设置学生中文姓名 超过3个...显示（支持中文）
        /// 客户定制固件，中性不支持
        /// </summary>
        /// <param name="strDeviceMac">设备mac地址</param>
        /// <param name="strDeviceStuNo">学生学号</param>
        /// <param name="strDeviceStuName">学生名称</param>
        /// <returns></returns>
        public int configBmpStuMore(string strDeviceMac, string strDeviceStuNo, string strDeviceStuName)
        {
            return rbt_win_config_bmp_stu_more(strDeviceMac, strDeviceStuNo, strDeviceStuName);
        }

        /// <summary>
        /// 设置学号(支持中文)
        /// 客户单独定制接口，中性不支持
        /// </summary>
        /// <param name="strDeviceMac">设备mac地址</param>
        /// <param name="strDeviceStuName">学生名称</param>
        public void configBmpStu2(string strDeviceMac, string strDeviceStuName)
        {
            rbt_win_config_bmp_stu2(strDeviceMac, strDeviceStuName);
        }

        /// <summary>
        /// 批量配置wifi信息
        /// </summary>
        /// <param name="strDeviceSSID">wifi名称</param>
        /// <param name="strDevicePwd">wifi密码</param>
        /// <param name="strDeviceSrc">预留字段</param>
        /// <returns></returns>
        public int configWifi(string strDeviceSSID, string strDevicePwd, string strDeviceSrc="")
        {
            return rbt_win_config_wifi(strDeviceSSID, strDevicePwd, strDeviceSrc);
        }

        /// <summary>
        /// 批量配置wifi信息
        /// </summary>
        /// <param name="strIP">传空自动获取IP地址</param>
        /// <param name="nPort">默认6001</param>
        /// <param name="bMQTT">true切换MQTT服务</param>
        /// <param name="bTCP">true切换TCP服务</param>
        /// <param name="strDeviceSrc">预留字段</param>
        /// <returns></returns>
        public int configNet(string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc="")
        {
            try
            {
                string HostName = Dns.GetHostName();
                IPHostEntry IpEntry = Dns.GetHostEntry(HostName);
                for (int i = 0; i < IpEntry.AddressList.Length; i++)
                {
                    //从IP地址列表中筛选出IPv4类型的IP地址
                    //AddressFamily.InterNetwork表示此IP为IPv4,
                    //AddressFamily.InterNetworkV6表示此地址为IPv6类型
                    if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetwork)
                    {
                        if (!string.IsNullOrEmpty(IpEntry.AddressList[i].ToString()))
                        {
                            string wd = IpEntry.AddressList[i].ToString().Substring(0, IpEntry.AddressList[i].ToString().LastIndexOf('.'));
                            if (ipdic.ContainsKey(wd))
                            {
                                if (ipdic[wd] != IpEntry.AddressList[i].ToString())
                                {
                                    ipdic[wd] = IpEntry.AddressList[i].ToString();
                                }
                            }
                            else
                            {
                                ipdic.Add(wd, IpEntry.AddressList[i].ToString());
                            }
                        }
                        
                    }
                }
            }
            catch (Exception ex)
            {

            }

            return rbt_win_config_net(strIP, nPort, bMQTT, bTCP, strDeviceSrc);
        }

        /// <summary>
        /// 配网并切换网络
        /// </summary>
        /// <param name="strDeviceSSID">wifi名称</param>
        /// <param name="strDevicePwd">wifi密码</param>
        /// <param name="strIP">传空自动获取IP地址</param>
        /// <param name="nPort">默认6001</param>
        /// <param name="bMQTT">true切换MQTT服务</param>
        /// <param name="bTCP">true切换TCP服务</param>
        /// <param name="strDeviceSrc">预留字段</param>
        /// <returns></returns>
        public int configWifiNet(string strDeviceSSID, string strDevicePwd,string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc = "")
        {
            try
            {
                string HostName = Dns.GetHostName();
                IPHostEntry IpEntry = Dns.GetHostEntry(HostName);
                for (int i = 0; i < IpEntry.AddressList.Length; i++)
                {
                    //从IP地址列表中筛选出IPv4类型的IP地址
                    //AddressFamily.InterNetwork表示此IP为IPv4,
                    //AddressFamily.InterNetworkV6表示此地址为IPv6类型
                    if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetwork)
                    {
                        if (!string.IsNullOrEmpty(IpEntry.AddressList[i].ToString()))
                        {
                            string wd = IpEntry.AddressList[i].ToString().Substring(0, IpEntry.AddressList[i].ToString().LastIndexOf('.'));
                            if (ipdic.ContainsKey(wd))
                            {
                                if (ipdic[wd] != IpEntry.AddressList[i].ToString())
                                {
                                    ipdic[wd] = IpEntry.AddressList[i].ToString();
                                }
                            }
                            else
                            {
                                ipdic.Add(wd, IpEntry.AddressList[i].ToString());
                            }
                        }

                    }
                }
            }
            catch (Exception ex)
            {

            }

            return rbt_win_config_wifi_net(strDeviceSSID, strDevicePwd,strIP, nPort, bMQTT, bTCP, strDeviceSrc);
        }

        /// <summary>
        /// 设置标点率
        /// </summary>
        /// <param name="freq">freq范围为0-4，0为最高，4为最低</param>
        /// <param name="mac"></param>
        public int configFreq(int freq, string mac = "")
        {
            return rbt_win_config_freq(freq, mac);
        }

        /// <summary>
        /// 设置休眠事件
        /// </summary>
        /// <param name="mins">分钟</param>
        /// <param name="mac"></param>
        public int configSleep(int mins, string mac = "")
        {
            return rbt_win_config_sleep(mins, mac);
        }

        /// <summary>
        /// 板子打开模组
        /// </summary>
        /// <param name="open">true:打开，false:关闭</param>
        /// <returns></returns>
        public int openModule(bool open,string mac="")
        {
            return rbt_win_open_module(open, mac);
        }

        /// <summary>
        /// 设置打开悬浮点
        /// </summary>
        /// <param name="open">true:打开，false:关闭</param>
        /// <returns></returns>
        public void openSuspension(bool open)
        {
            rbt_win_open_suspension(open);
        }

        /// <summary>
        /// 获取画布ID
        /// </summary>
        public void getCanvasID(int canvasID)
        {
            rbt_win_get_canvas_id(canvasID);
        }

        /// <summary>
        /// 设置刷新时间 1-5秒
        /// </summary>
        public void setScreenFreq(int seconds)
        {
            rbt_win_set_screen_freq(seconds);
        }

        /// <summary>
        /// 设置心跳(测试)
        /// </summary>
        /// <param name="channel"></param>
        /// <param name="enable"></param>
        /// <param name="keepintvl"></param>
        /// <param name="keepcnt"></param>
        public void setScreenFreq(int channel, int enable, int keepintvl, int keepcnt)
        {
            rbt_win_set_keepalive(channel, enable, keepintvl, keepcnt);
        }

        /// <summary>
        /// 删除离线笔记
        /// </summary>
        /// <param name="del"></param>
        /// <returns></returns>
        public bool delNotes(int del, string mac = "")
        {
            return rbt_win_del_notes(del, mac);
        }

        /// <summary>
        /// 优化笔迹转成path
        /// </summary>
        /// <param name="mac">设备MAC地址</param>
        /// <param name="points">点集合</param>
        /// <param name="len">点集合长度</param>
        /// <param name="nLen">path点长度</param>
        public float[] toPath(string mac, float[] points, int len, ref int nLen)
        {
            return rbt_win_toPath(mac, points, len, ref nLen);
        }

        /// <summary>
        /// 优化笔迹转成path
        /// </summary>
        /// <param name="mac">设备MAC地址</param>
        /// <param name="points">点集合</param>
        /// <param name="len">点集合长度</param>
        /// <param name="nLen">path点长度</param>
        public float[] toTrailsPath(string mac, float[] points, int len, ref int nLen)
        {
            return rbt_win_toTrailsPath(mac, points, len, ref nLen);
        }

        /// <summary>
        /// 设置线条是否进行spline处理
        /// </summary>
        /// <param name="open"></param>
        public void SetPenWidth(bool open)
        {
            rbt_win_setIsSpline(open);
        }
        /// <summary>
        /// 设置笔宽度
        /// </summary>
        /// <param name="width"></param>
        public void SetPenWidth(float width)
        {
            rbt_win_setPenWidth(width);
        }
        /// <summary>
        /// 设置拖尾阈值，设置的越小，拖尾越长(0~1)
        /// </summary>
        /// <param name="delay"></param>
        public void SetPointDelay(float delay)
        {
            rbt_win_setPointDelay(delay);
        }
        /// <summary>
        /// 设置粗细变化阈值，设置的越小，粗细变化越小
        /// </summary>
        /// <param name="damping"></param>
        public void SetPointDamping(float damping)
        {
            rbt_win_setPointDamping(damping);
        }
        /// <summary>
        /// 设置基础宽度，用于过滤点和点之间的距离，默认取PenWidth
        /// </summary>
        /// <param name="width"></param>
        public void SetBaseWidth(float width)
        {
            rbt_win_setBaseWidth(width);
        }
        /// <summary>
        /// 设置结尾宽度，此参数决定拖尾笔锋终点宽度，默认取BaseWidth * 0.1
        /// </summary>
        /// <param name="width"></param>
        public void SetEndWidth(float width)
        {
            rbt_win_setEndWidth(width);
        }
        /// <summary>
        /// 笔锋收尾触发速度判断，当速度大于笔宽度/decrease时会触发笔锋
        /// </summary>
        /// <param name="decrease"></param>
        public void SetWidthDecrease(float decrease)
        {
            rbt_win_setWidthDecrease(decrease);
        }



        
    }
}
