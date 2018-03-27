using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace rbt_win32_2
{
    public class RbtNet
    {
        // 声明dll 函数接口
        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_init(ref Init_Param arg);   // 初始化

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_uninit();     // 反初始化

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_startanswer(int nTotalTopic, ref string strTopicType);     // 发送开始答题命令

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_stopanswer();   // 结束答题命令

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_start();   // 开启监听

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_stop();   // 停止监听

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_stu(ref string strDeviceMac, ref string strDeviceStu);

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_wifi(ref string strDeviceSSID, ref string strDevicePwd, ref string strDeviceStu, ref string strDeviceSrc);

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_net(ref string strIP, int nPort, bool bMQTT, bool bTCP, ref string strDeviceSrc);

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicemac_cb(onDeviceMac arg);   // 设备mac地址上报函数地址

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_origindata_cb(onOriginData arg);   // 设备坐标上报函数地址

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devivedisconnect_cb(onDeviceDisconnect arg);   // 设备断开连接函数地址

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicekeypress_cb(onDeviceKeyPress arg);   // 设备按键函数地址

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceshowpage_cb(onDeviceShowPage arg);   // 设备页码识别函数地址

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult arg);   // 设备选择题结果函数地址

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicename_cb(onDeviceName arg);  

        [DllImport("rbt_win32.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicenameresult_cb(onDeviceNameResult arg);  


        public event onDeviceMac deviceMacEvt_;
        public event onOriginData deviceOriginDataEvt_;
        public event onDeviceDisconnect deviceDisconnectEvt_;
        public event onDeviceKeyPress deviceKeyPressEvt_;
        public event onDeviceShowPage deviceShowPageEvt_;
        public event onDeviceAnswerResult deviceAnswerResultEvt_;
        public event onDeviceName deviceNameEvt_;
        public event onDeviceNameResult deviceNameResult_;

        //private onOriginData originDataDeletegate = new onOriginData(originDataNotify);
        // 用于存储this对象主要保证该变量的生命周期
        private GCHandle gchandld;
        private IntPtr iPtrThis_ = IntPtr.Zero;

        // 构造函数
        public RbtNet() {
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
        private static void originDataNotify(IntPtr ctx, IntPtr strDeviceMac, ushort us, ushort ux, ushort uy, ushort up) {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null && rbtNetThis.deviceOriginDataEvt_ != null) {
                rbtNetThis.deviceOriginDataEvt_(ctx, strDeviceMac, us, ux, uy, up);
            }
        }

        /// <summary>
        /// 响应设备MAC地址通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void deviceMacNotify(IntPtr ctx, System.String strDeviceMac) {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceMacEvt_ != null)
            {
                rbtNetThis.deviceMacEvt_(ctx,  strDeviceMac);
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
                rbtNetThis.deviceNameEvt_(ctx, strDeviceMac,strDeviceName);
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
                rbtNetThis.deviceNameResult_(ctx, strDeviceMac,res,strDeviceName);
            }
        }

        /// <summary>
        /// 响应设备连接断开消息
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void deviceDisconnect(IntPtr ctx, IntPtr strDeviceMac) {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceDisconnectEvt_ != null) {
                rbtNetThis.deviceDisconnectEvt_(ctx, strDeviceMac);
            }
        }

        /// <summary>
        /// 设备按键消息上报通知
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="keyValue"></param>
        private static void deviceKeyPress(IntPtr ctx, IntPtr strDeviceMac, int keyValue) {
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
        private static void deviceShowPage(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId) {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceShowPageEvt_ != null)
            {
                rbtNetThis.deviceShowPageEvt_(ctx, strDeviceMac, nNoteId, nPageId);
            }
        }

        /// <summary>
        /// 设备上报选择题答题结果事件
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="result"></param>
        /// <param name="nResultSize"></param>
        private static void deviceAnswerResult(IntPtr ctx, IntPtr strDeviceMac, IntPtr result, int nResultSize) {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceAnswerResultEvt_ != null)
            {
                rbtNetThis.deviceAnswerResultEvt_(ctx, strDeviceMac, result, nResultSize);
            }
        }

        /// <summary>
        /// 初始化
        /// </summary>
        /// <param name="arg"></param>
        public void init(ref Init_Param arg) {
            gchandld = GCHandle.Alloc(this);
            iPtrThis_ = GCHandle.ToIntPtr(gchandld);
            arg.ctx = iPtrThis_;
            rbt_win_init(ref arg);

            rbt_win_set_origindata_cb(originDataNotify);
            rbt_win_set_devicemac_cb(deviceMacNotify);
            rbt_win_set_devicekeypress_cb(deviceKeyPress);
            rbt_win_set_deviceshowpage_cb(deviceShowPage);
            rbt_win_set_devivedisconnect_cb(deviceDisconnect);
            rbt_win_set_deviceanswerresult_cb(deviceAnswerResult);
            rbt_win_set_devicename_cb(deviceNameNotify);
            rbt_win_set_devicenameresult_cb(deviceNameResultNotify);
        }

        // 反初始化
        public void unInit() {
             rbt_win_uninit();
        }

        /// <summary>
        /// 开启服务
        /// </summary>
        /// <returns>bool</returns>
        public bool start() {
            return rbt_win_start();
        }

        /// <summary>
        /// 停止服务
        /// </summary>
        public void stop() {
            rbt_win_stop();
        }

        /// <summary>
        /// 发送开始答题
        /// </summary>
        /// <param name="nTotalTopic"></param>
        /// <param name="strTopicType"></param>
        /// <returns></returns>
        public bool sendStartAnswer(int nTotalTopic, ref string strTopicType) {
            return rbt_win_send_startanswer(nTotalTopic, ref strTopicType);
        }

        /// <summary>
        /// 发送结束答题命令
        /// </summary>
        public void sendStopAnswer() {
            rbt_win_send_stopanswer();
        }

        /// <summary>
        /// 设置学号
        /// </summary>
        public void configStu(ref string strDeviceMac, ref string strDeviceStu)
        {
            rbt_win_config_stu(ref strDeviceMac, ref strDeviceStu);
        }

        /// <summary>
        /// 切换网络
        /// </summary>
        public int configWifi(ref string strDeviceSSID, ref string strDevicePwd, ref string strDeviceStu, ref string strDeviceSrc)
        {
            return rbt_win_config_wifi(ref strDeviceSSID, ref strDevicePwd, ref strDeviceStu, ref strDeviceSrc);
        }

        /// <summary>
        /// 配网
        /// </summary>
        public int configNet(ref string strIP, int nPort, bool bMQTT, bool bTCP, ref string strDeviceSrc)
        {
            return rbt_win_config_net(ref strIP, nPort, bMQTT, bTCP, ref strDeviceSrc);
        }
    }
}
