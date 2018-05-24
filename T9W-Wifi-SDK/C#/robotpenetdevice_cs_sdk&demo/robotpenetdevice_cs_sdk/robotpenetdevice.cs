﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace robotpenetdevice_cs
{
    public class RbtNet
    {
        // 声明dll 函数接口
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_init(ref Init_Param arg);   // 初始化

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_uninit();     // 反初始化

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_startanswer(int type, int totalTopic, IntPtr pTopicType);     // 发送开始答题命令

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_stopanswer();   // 结束答题命令

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_start();   // 开启监听

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_open_module(bool open);   // 打开模组

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_stop();   // 停止监听

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_stu(string strDeviceMac, string strDeviceStu);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_wifi(string strDeviceSSID, string strDevicePwd, string strDeviceStu, string strDeviceSrc);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_net(string strGroup, string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicemac_cb(onDeviceMac arg);   // 设备mac地址上报函数地址

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_origindata_cb(onOriginData arg);   // 设备坐标上报函数地址

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devivedisconnect_cb(onDeviceDisconnect arg);   // 设备断开连接函数地址

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicekeypress_cb(onDeviceKeyPress arg);   // 设备按键函数地址

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceshowpage_cb(onDeviceShowPage arg);   // 设备页码识别函数地址

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult arg);   // 设备选择题结果函数地址

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicename_cb(onDeviceName arg);  

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicenameresult_cb(onDeviceNameResult arg);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_freq(int freq);

        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_config_sleep(int mins);


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
        private static onDeviceMac ondevicemac;
        private static onOriginData onorigindata;
        private static onDeviceAnswerResult ondeviceanswerresult;
        private static onDeviceKeyPress ondevicekeyPress = null;
        private static onDeviceShowPage ondeviceshowpage = null;
        private static onDeviceNameResult ondevicenameresult = null;
        private static onDeviceName ondevicename = null;
        private static onDeviceDisconnect ondevicedisconnect = null;

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
           // thisHandle.Free();
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
        private static void deviceAnswerResult(IntPtr ctx, IntPtr strDeviceMac, int resID, IntPtr result, int nResultSize) {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null && rbtNetThis.deviceAnswerResultEvt_ != null)
            {
                rbtNetThis.deviceAnswerResultEvt_(ctx, strDeviceMac, resID, result, nResultSize);
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

            onorigindata = new onOriginData(originDataNotify);
            rbt_win_set_origindata_cb(onorigindata);
            ondevicemac = new onDeviceMac(deviceMacNotify);
            rbt_win_set_devicemac_cb(ondevicemac);
            ondevicekeyPress = new onDeviceKeyPress(deviceKeyPress);
            rbt_win_set_devicekeypress_cb(ondevicekeyPress);
            ondeviceshowpage = new onDeviceShowPage(deviceShowPage);
            rbt_win_set_deviceshowpage_cb(ondeviceshowpage);
            ondevicedisconnect = new onDeviceDisconnect(deviceDisconnect);
            rbt_win_set_devivedisconnect_cb(ondevicedisconnect);
            ondeviceanswerresult = new onDeviceAnswerResult(deviceAnswerResult);
            rbt_win_set_deviceanswerresult_cb(ondeviceanswerresult);
            ondevicename = new onDeviceName(deviceNameNotify);
            rbt_win_set_devicename_cb(ondevicename);
            ondevicenameresult = new onDeviceNameResult(deviceNameResultNotify);
            rbt_win_set_devicenameresult_cb(ondevicenameresult);
        }

        // 反初始化
        public void unInit() {
             rbt_win_uninit();
            gchandld.Free();
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
        public bool sendStartAnswer(int type, int totalTopic, IntPtr pTopicType) {
            return rbt_win_send_startanswer(type, totalTopic, pTopicType);
        }

        /// <summary>
        /// 发送结束答题命令
        /// </summary>
        public void sendStopAnswer() {
            rbt_win_send_stopanswer();
        }

        /// <summary>
        /// TY板子打开模组
        /// </summary>
        /// <param name="open">true:打开，false:关闭</param>
        /// <returns></returns>
        public void openModule(bool open)
        {
           rbt_win_open_module(open);
        }

        /// <summary>
        /// 设置学号
        /// </summary>
        public void configStu(string strDeviceMac, string strDeviceStu)
        {
            rbt_win_config_stu(strDeviceMac, strDeviceStu);
        }

        /// <summary>
        /// 切换网络
        /// </summary>
        public int configWifi(string strDeviceSSID, string strDevicePwd, string strDeviceStu, string strDeviceSrc)
        {
            return rbt_win_config_wifi(strDeviceSSID, strDevicePwd, strDeviceStu, strDeviceSrc);
        }

        /// <summary>
        /// 配网
        /// </summary>
        public int configNet(string strGroup, string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc)
        {
            return rbt_win_config_net(strGroup, strIP, nPort, bMQTT, bTCP, strDeviceSrc);
        }

        /// <summary>
        /// 设置报点率(范围是0到5)
        /// </summary>
        public void configFreq(int freq)
        {
            rbt_win_config_freq(freq);
        }

        /// <summary>
        /// 设置睡眠时间(分钟)
        /// </summary>
        public void configSleep(int mins)
        {
            rbt_win_config_sleep(mins);
        }
    }
}
