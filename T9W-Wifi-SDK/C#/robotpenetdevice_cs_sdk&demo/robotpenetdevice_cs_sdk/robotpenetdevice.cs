using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;

namespace robotpenetdevice_cs
{
    public class RbtNet
    {
        // 声明dll 函数接口
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_init(ref Init_Param arg);   // 初始化

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_init2(int port = 6001, int listenCount = 60, bool open = true, bool optimize = false);   // 初始化

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_uninit();     // 反初始化

        /// <summary>
        ///开始答题
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题</param>
        /// <param name="totalTopic">题目总数</param>
        /// <param name="pTopicType">题目类型 1判断 2单选 3多选 4抢答</param>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_startanswer(int type, int totalTopic, IntPtr pTopicType, string mac);     // 发送开始答题命令
        //mac 为空时，发送命令到所有设备，否则为当前mac设备
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_stopanswer(string mac);   // 停止答题命令
        //mac 为空时，发送命令到所有设备，否则为当前mac设备
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_endanswer(string mac);   // 结束答题命令

        /// <summary>
        /// 发送命令
        /// </summary>
        /// <param name="cmdId"></param>
        /// <param name=""></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send(int cmdId, string mac = "");   // 结束答题命令

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_start();   // 开启监听

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_open_module(bool open,string mac);   // 打开模组

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_stop();   // 停止监听

        /// <summary>
        /// 设置学生id（不支持中文）
        /// </summary>
        /// <param name="strDeviceMac">学生mac地址</param>
        /// <param name="strDeviceStu"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_stu(string strDeviceMac, string strDeviceStu);

        /// <summary>
        /// 设置学生id（支持中文）
        /// </summary>
        /// <param name="strDeviceMac"></param>
        /// <param name="strDeviceStu"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_bmp_stu(string strDeviceMac, string strDeviceStuNo, string strDeviceStuName);

        /// <summary>
        /// 设置学生id（支持中文）
        /// </summary>
        /// <param name="strDeviceMac"></param>
        /// <param name="strDeviceStu"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_bmp_stu2(string strDeviceMac, string strDeviceStuName);

        /// <summary>
        /// 批量配置wifi信息
        /// </summary>
        /// <param name="strDeviceSSID"></param>
        /// <param name="strDevicePwd"></param>
        /// <param name="strDeviceSrc"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_wifi(string strDeviceSSID, string strDevicePwd, string strDeviceSrc);
        /// <summary>
        /// UDP广播，广播主机ip地址
        /// 建议每隔两秒一次
        /// </summary>
        /// <param name="strIP">传空自动获取IP地址</param>
        /// <param name="nPort"></param>
        /// <param name="bMQTT"></param>
        /// <param name="bTCP"></param>
        /// <param name="strDeviceSrc"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_net(string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc);
        
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_wifi_net(string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc);
        /// <summary>
        /// 绑定获取设备MAC地址回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicemac_cb(onDeviceMac arg);   // 设备mac地址上报函数地址
        /// <summary>
        /// 绑定点数据
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_origindata_cb(onOriginDataNew arg);   // 设备坐标上报函数地址
        /// <summary>
        /// 绑定点数据拓展
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_origindata_ex_cb(onOriginDataNewEx arg);   // 设备坐标上报函数地址
        /// <summary>
        /// 绑定设备断开连接事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devivedisconnect_cb(onDeviceDisconnect arg);   // 设备断开连接函数地址
        /// <summary>
        /// 绑定按键回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicekeypress_cb(onDeviceKeyPress arg);   // 设备按键函数地址
        /// <summary>
        /// 绑定设备页码回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceshowpage_cb(onDeviceShowPageNew arg);   // 设备页码识别函数地址
        /// <summary>
        /// 绑定设备按键结果
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult arg);   // 设备选择题结果函数地址
        /// <summary>
        /// 绑定设备名称回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicename_cb(onDeviceName arg);
        /// <summary>
        /// 绑定设备设置名称回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicenameresult_cb(onDeviceNameResult arg);
        /// <summary>
        ///设置标点率
        /// </summary>
        /// <param name="freq"></param>
        /// <param name="mac"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_freq(int freq,string mac);
        /// <summary>
        /// 设置休眠事件
        /// </summary>
        /// <param name="mins"></param>
        /// <param name="mac"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_sleep(int mins, string mac);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_error_cb(onError arg);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_canvasid_cb(onCanvasID arg);

        /// <summary>
        /// 绑定设备优化笔迹回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_optimizedata_cb(onOptimizeData arg);
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_optimizedata_ex_cb(onOptimizeDataEx arg);


        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_accept_cb(onAccept arg);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_errorpacket_cb(onErrorPacket arg);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_open_suspension(bool open);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_get_canvas_id(int canvasID = 0);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_screen_freq(int seconds);


        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceip_cb(onDeviceIpOld arg);

        /// <summary>
        /// 绑定设备状态回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicetype_cb(onDeviceType arg);
        /// <summary>
        /// 绑定设备状态回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_keyanswer_cb(onKeyAnswer arg);
        /// <summary>
        /// 绑定设备信息回到事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceinfo_cb(onDeviceInfo arg);
        /// <summary>
        /// 绑定设备硬件信息回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_hardinfo_cb(onHardInfo arg);
        /// <summary>
        /// 绑定设备电量信息回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicebattery_cb(onDeviceBattery arg);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_oidpageinfo_cb(onOidPageInfo arg);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_offset_center(int x = 0, int y = 0, string mac = "");

        //#笔迹优化
        //设置笔宽度
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setPenWidth(float width);
        //设置拖尾阈值，设置的越小，拖尾越长(0~1)
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setPointDelay(float delay);
        //设置粗细变化阈值，设置的越小，粗细变化越小
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setPointDamping(float damping);
        //设置基础宽度，用于过滤点和点之间的距离，默认取PenWidth
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setBaseWidth(float width);
        //设置结尾宽度，此参数决定拖尾笔锋终点宽度，默认取BaseWidth * 0.1
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setEndWidth(float width);
        //笔锋收尾触发速度判断，当速度大于笔宽度/decrease时会触发笔锋
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setWidthDecrease(float decrease);


        public event onDeviceMac deviceMacEvt_;
        public event onOriginData deviceOriginDataEvt_;
        public event onOriginDataNew deviceOriginDataNewEvt_;
        public event onDeviceDisconnect deviceDisconnectEvt_;
        public event onDeviceKeyPress deviceKeyPressEvt_;
        public event onDeviceShowPage deviceShowPageEvt_;
        public event onDeviceShowPageNew deviceShowPageNewEvt_;
        public event onDeviceAnswerResult deviceAnswerResultEvt_;
        public event onDeviceName deviceNameEvt_;
        public event onDeviceNameResult deviceNameResult_;
        public event onError deviceError_ = null;
        public event onCanvasID deviceCanvasID_ = null;
        public event onOptimizeData deviceOptimizeDataEvt_ = null;
        public event onDeviceIpOld DeviceIpOldEvt_ = null;
        public event onDeviceIp DeviceIpEvt_ = null;

        public event onDeviceType DeviceTypeEvt_ = null;
        public event onKeyAnswer KeyAnswerEvt_ = null;
        public event onDeviceInfo DeviceInfoEvt_ = null;
        public event onHardInfo HardInfoEvt_ = null;
        public event onDeviceBattery DeviceBatteryEvt_ = null;


        //private onOriginData originDataDeletegate = new onOriginData(originDataNotify);
        // 用于存储this对象主要保证该变量的生命周期
        private GCHandle gchandld;
        private IntPtr iPtrThis_ = IntPtr.Zero;
        private static onDeviceMac ondevicemac;
        private static onOriginData onorigindata;
        private static onOriginDataNew onorigindatanew;
        private static onDeviceAnswerResult ondeviceanswerresult;
        private static onDeviceKeyPress ondevicekeyPress = null;
        private static onDeviceShowPage ondeviceshowpage = null;
        private static onDeviceShowPageNew ondeviceshowpagenew = null;
        private static onDeviceNameResult ondevicenameresult = null;
        private static onDeviceName ondevicename = null;
        private static onDeviceDisconnect ondevicedisconnect = null;
        private static onError onerror = null;
        private static onCanvasID oncanvasid = null;
        private static onOptimizeData onoptimizedata = null;
        private static onDeviceIpOld ondeviceipold = null;
        private static onDeviceIp ondeviceip = null;

        private static onDeviceType ondevicetype = null;
        private static onKeyAnswer onkeyanswer = null;
        private static onDeviceInfo ondeviceinfo = null;
        private static onHardInfo onhardinfo = null;
        private static onDeviceBattery ondevicebattery = null;




        // 构造函数
        public RbtNet()
        {
        }

        /// <summary>
        /// 坐标原点数据通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="us"></param>
        /// <param name="ux"></param>
        /// <param name="uy"></param>
        /// <param name="up"></param>
        /// <param name="buffer"></param>
        /// <param name="len"></param>
        private static void originDataNotifyNew(IntPtr ctx, IntPtr strDeviceMac, ushort us, ushort ux, ushort uy, ushort up, IntPtr buffer, int len)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                if(rbtNetThis.deviceOriginDataNewEvt_ != null)
                {
                    rbtNetThis.deviceOriginDataNewEvt_(ctx, strDeviceMac, us, ux, uy, up, buffer, len);
                }
                else if(rbtNetThis.deviceOriginDataEvt_ != null)
                {
                    string bufferStr = Marshal.PtrToStringAnsi(buffer);
                    rbtNetThis.deviceOriginDataEvt_(ctx, strDeviceMac, us, ux, uy, up);
                }
                
            }
        }

        private static void optimizeData(IntPtr ctx, IntPtr pmac, ushort us, ushort ux, ushort uy, float width, float speed)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                if (rbtNetThis.deviceOptimizeDataEvt_!= null)
                {
                    rbtNetThis.deviceOptimizeDataEvt_(ctx, pmac, us, ux, uy, width, speed);
                }
            }
        }

        private static void deviceip(IntPtr ctx, String pMac, String ip)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                if (rbtNetThis.DeviceIpEvt_ != null)
                {
                    string wd = ip.Substring(0, ip.LastIndexOf('.'));
                    if(ipdic.ContainsKey(wd))
                    {
                        rbtNetThis.DeviceIpEvt_(ctx, pMac, ip, ipdic[wd]);
                    }

                    //
                }
            }
        }

        /// <summary>
        /// 响应设备MAC地址通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void deviceMacNotify(IntPtr ctx, System.String strDeviceMac)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceMacEvt_ != null)
            {
                rbtNetThis.deviceMacEvt_(ctx, strDeviceMac);
            }
        }

        /// <summary>
        /// 响应设备设置name通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void deviceNameNotify(IntPtr ctx, System.String strDeviceMac, System.String strDeviceName)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceNameEvt_ != null)
            {
                rbtNetThis.deviceNameEvt_(ctx, strDeviceMac, strDeviceName);
            }
        }

        /// <summary>
        /// 响应设备设置name结果通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void deviceNameResultNotify(IntPtr ctx, String strDeviceMac, int res, String strDeviceName)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceNameResult_ != null)
            {
                rbtNetThis.deviceNameResult_(ctx, strDeviceMac, res, strDeviceName);
            }
            // thisHandle.Free();
        }

        /// <summary>
        /// 响应设备连接断开消息
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void deviceDisconnect(IntPtr ctx, IntPtr strDeviceMac)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceDisconnectEvt_ != null)
            {
                rbtNetThis.deviceDisconnectEvt_(ctx, strDeviceMac);
            }
        }

        /// <summary>
        /// 设备按键消息上报通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="keyValue"></param>
        private static void deviceKeyPress(IntPtr ctx, IntPtr strDeviceMac, int keyValue)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceKeyPressEvt_ != null)
            {
                rbtNetThis.deviceKeyPressEvt_(ctx, strDeviceMac, keyValue);
            }
        }

        /// <summary>
        /// 设备上报页码识别事件
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="nNoteId"></param>
        /// <param name="nPageId"></param>
        private static void deviceShowPageNew(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId, int nPageInfo)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                int _nPageInfo = 0;
                if (nPageInfo != 0)
                {
                    string d = System.Convert.ToString(nPageInfo, 2);
                    int dlen = d.Length;
                    for (int j = 0; j < 17 - dlen; j++)
                    {
                        d = "0" + d;
                    }
                    switch (rbtNetThis.pt)
                    {
                        case PrintType.Base:
                        default:
                            _nPageInfo = nPageInfo;
                            break;
                        case PrintType.Fault_tolerance:
                            string code = "" + d[1] + d[6] + d[9] + d[12] + d[15];
                            _nPageInfo = Convert.ToInt32(code, 2);
                            break;
                        case PrintType.Fault_tolerance2:
                            string code2 = "" + d[0] + d[2] + d[5] + d[7] + d[9] + d[11] + d[13] + d[15];
                            _nPageInfo = Convert.ToInt32(code2, 2);
                            break;
                    }
                }

                if (rbtNetThis.deviceShowPageNewEvt_ != null)
                {
                    rbtNetThis.deviceShowPageNewEvt_(ctx, strDeviceMac, nNoteId, nPageId, _nPageInfo);
                }
                else if (rbtNetThis.deviceShowPageEvt_ != null)
                {
                    rbtNetThis.deviceShowPageEvt_(ctx, strDeviceMac, nNoteId, nPageId);
                }

            }
        }

        /// <summary>
        /// 设备上报选择题答题结果事件
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="result"></param>
        /// <param name="nResultSize"></param>
        private static void deviceAnswerResult(IntPtr ctx, IntPtr strDeviceMac, int resID, IntPtr result, int nResultSize)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceAnswerResultEvt_ != null)
            {
                rbtNetThis.deviceAnswerResultEvt_(ctx, strDeviceMac, resID, result, nResultSize);
            }
        }

        /// <summary>
        /// 处理设备错误信息的方法
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pmac"></param>
        /// <param name="cmd"></param>
        /// <param name="msg"></param>
        private static void deviceError(IntPtr ctx, String pmac, int cmd, String msg)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceError_ != null)
            {
                rbtNetThis.deviceError_(ctx, pmac, cmd, msg);
            }
        }

        /// <summary>
        /// 处理画布清空事件
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pmac"></param>
        private static void deviceClearCanvas(IntPtr ctx, String pmac, int type, int canvasID)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceError_ != null)
            {
                rbtNetThis.deviceCanvasID_(ctx, pmac, type, canvasID);
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="type"></param>
        private static void deviceType(IntPtr ctx, String pMac, int type)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.DeviceTypeEvt_ != null)
            {
                rbtNetThis.DeviceTypeEvt_(ctx, pMac, type);
            }
        }
        private static void keyAnswer(IntPtr ctx, String pMac, int key)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.KeyAnswerEvt_ != null)
            {
                rbtNetThis.KeyAnswerEvt_(ctx, pMac, key);
            }
        }
        private static void deviceInfo(IntPtr ctx, String pMac, String version, String deviceMac, int hardNum)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.DeviceInfoEvt_ != null)
            {
                rbtNetThis.DeviceInfoEvt_(ctx, pMac, version, deviceMac, hardNum);
            }
        }
        private static void hardInfo(IntPtr ctx, String pMac, int xRange, int yRange, int LPI, int pageNum)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.HardInfoEvt_ != null)
            {
                rbtNetThis.HardInfoEvt_(ctx, pMac, xRange, yRange, LPI, pageNum);
            }
        }
        private static void deviceBattery(IntPtr ctx, String pMac, eBatteryStatus battery)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.DeviceBatteryEvt_ != null)
            {
                rbtNetThis.DeviceBatteryEvt_(ctx, pMac, battery);
            }
        }


        PrintType pt = PrintType.Base;

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
            /*int size = Marshal.SizeOf(typeof(Init_Param));
            System.Diagnostics.Debug.WriteLine(size);//*/

            BindEvent();
        }

        public void init(int port = 6001, int listenCount = 60, bool open = true, bool optimize = false)
        {
            gchandld = GCHandle.Alloc(this);
            iPtrThis_ = GCHandle.ToIntPtr(gchandld);

            rbt_win_init2();

            /*int size = Marshal.SizeOf(typeof(Init_Param));
            System.Diagnostics.Debug.WriteLine(size);//*/

            BindEvent();
        }

        private void BindEvent()
        {
            onorigindatanew = new onOriginDataNew(originDataNotifyNew);
            rbt_win_set_origindata_cb(onorigindatanew);
            ondevicemac = new onDeviceMac(deviceMacNotify);
            rbt_win_set_devicemac_cb(ondevicemac);
            ondevicekeyPress = new onDeviceKeyPress(deviceKeyPress);
            rbt_win_set_devicekeypress_cb(ondevicekeyPress);
            ondeviceshowpagenew = new onDeviceShowPageNew(deviceShowPageNew);
            rbt_win_set_deviceshowpage_cb(ondeviceshowpagenew);
            ondevicedisconnect = new onDeviceDisconnect(deviceDisconnect);
            rbt_win_set_devivedisconnect_cb(ondevicedisconnect);
            ondeviceanswerresult = new onDeviceAnswerResult(deviceAnswerResult);
            rbt_win_set_deviceanswerresult_cb(ondeviceanswerresult);
            ondevicename = new onDeviceName(deviceNameNotify);
            rbt_win_set_devicename_cb(ondevicename);
            ondevicenameresult = new onDeviceNameResult(deviceNameResultNotify);
            rbt_win_set_devicenameresult_cb(ondevicenameresult);
            onerror = new onError(deviceError);
            rbt_win_set_error_cb(onerror);
            oncanvasid = new onCanvasID(deviceClearCanvas);
            rbt_win_set_canvasid_cb(oncanvasid);
            onoptimizedata = new onOptimizeData(optimizeData);
            rbt_win_set_optimizedata_cb(onoptimizedata);
            ondeviceipold = new onDeviceIpOld(deviceip);
            rbt_win_set_deviceip_cb(ondeviceipold);

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
        /// 发送开始答题
        /// </summary>
        /// <param name="nTotalTopic"></param>
        /// <param name="strTopicType"></param>
        /// <returns></returns>
        public bool sendStartAnswer(int type, int totalTopic, IntPtr pTopicType,string mac="")
        {
            return rbt_win_send_startanswer(type, totalTopic, pTopicType, mac);
        }

        /// <summary>
        /// 发送结束答题命令
        /// </summary>
        public void sendStopAnswer(string mac = "")
        {
            rbt_win_send_endanswer(mac);
        }

        /// <summary>
        /// 发送结束答题命令
        /// </summary>
        public void sendEndAnswer(string mac = "")
        {
            rbt_win_send_endanswer(mac);
        }

        /// <summary>
        /// TY板子打开模组
        /// </summary>
        /// <param name="open">true:打开，false:关闭</param>
        /// <returns></returns>
        public void openModule(bool open,string mac="")
        {
            rbt_win_open_module(open, mac);
        }

        /// <summary>
        /// 设置学号
        /// </summary>
        public void configStu(string strDeviceMac, string strDeviceStu)
        {
            rbt_win_config_stu(strDeviceMac, strDeviceStu);
        }

        /// <summary>
        /// 设置学号(支持中文)
        /// </summary>
        public int configBmpStu(string strDeviceMac, string strDeviceStuNo, string strDeviceStuName)
        {
           return rbt_win_config_bmp_stu(strDeviceMac, strDeviceStuNo, strDeviceStuName);
        }

        /// <summary>
        /// 设置学号(支持中文)
        /// 天喻单独定制接口
        /// </summary>
        public void configBmpStu2(string strDeviceMac, string strDeviceStuName)
        {
            rbt_win_config_bmp_stu2(strDeviceMac, strDeviceStuName);
        }

        /// <summary>
        /// 切换网络
        /// </summary>
        public int configWifi(string strDeviceSSID, string strDevicePwd, string strDeviceSrc)
        {
            return rbt_win_config_wifi(strDeviceSSID, strDevicePwd, strDeviceSrc);
        }

        public static Dictionary<string, string> ipdic = new Dictionary<string, string>();
        /// <summary>
        /// 配网
        /// </summary>
        public int configNet(string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc)
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
                            if(ipdic.ContainsKey(wd))
                            {
                                if(ipdic[wd]!= IpEntry.AddressList[i].ToString())
                                {
                                    ipdic[wd] = IpEntry.AddressList[i].ToString();
                                }
                            }
                            else
                            {
                                ipdic.Add(wd, IpEntry.AddressList[i].ToString());
                            }
                        }

                        //rbtnet_.configNet(IpEntry.AddressList[i].ToString(), 6001, false, true, "");
                    }
                }
            }
            catch(Exception ex)
            {

            }
            
            return rbt_win_config_net(strIP, nPort, bMQTT, bTCP, strDeviceSrc);
        }

        /// <summary>
        /// 设置报点率(范围是0到5)
        /// </summary>
        public void configFreq(int freq, string mac = "")
        {
            rbt_win_config_freq(freq,mac);
        }

        /// <summary>
        /// 设置睡眠时间(分钟)
        /// </summary>
        public void configSleep(int mins, string mac = "")
        {
            rbt_win_config_sleep(mins,mac);
        }

        /// <summary>
        /// 获取画布ID
        /// </summary>
        public void getCanvasID(int canvasID)
        {
            rbt_win_get_canvas_id(canvasID);
        }

        /// <summary>
        /// 获取画布ID
        /// </summary>
        public void setScreenFreq(int seconds)
        {
            rbt_win_set_screen_freq(seconds);
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
        public void PointDamping(float damping)
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

        public void SendCmd(int cmdkey,string mac="")
        {
            rbt_win_send(cmdkey, mac);
        }
    }
}
