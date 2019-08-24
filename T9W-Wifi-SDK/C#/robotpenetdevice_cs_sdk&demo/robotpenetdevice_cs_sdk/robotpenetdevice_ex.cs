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
        #region 基础命令
        /// <summary>
        /// 初始化
        /// </summary>
        /// <param name="arg"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_init(ref Init_Param arg);

        /// <summary>
        /// 初始化2，方便部分转化不方面的的调用
        /// </summary>
        /// <param name="port"></param>
        /// <param name="listenCount"></param>
        /// <param name="open"></param>
        /// <param name="optimize"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_init2(int port = 6001, int listenCount = 60, bool open = true, bool optimize = false);

        /// <summary>
        /// 释放资源
        /// </summary>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_uninit();

        /// <summary>
        /// 发送命令（获取设备信息能用到）
        /// </summary>
        /// <param name="cmdId"></param>
        /// <param name=""></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send(int cmdId, string mac = "");

        /// <summary>
        ///开始答题
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题 2为投票 3为不定选择 4为测试 5为书写</param>
        /// <param name="totalTopic">totalTopic 题目总数</param>
        /// <param name="pTopicType">pTopicType 题目类型 1判断 2单选 3多选 4抢答 5解答</param>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_startanswer(int type, int totalTopic, IntPtr pTopicType, string mac = "");
        /// <summary>
        ///开始答题(若支持多主观题用此接口)
        /// </summary>
        /// <param name="type">type 0为主观题 1为客观题</param>
        /// <param name="totalTopic">totalTopic 题目总数</param>
        /// <param name="pTopicType">pTopicType 题目类型 1判断 2单选 3多选 4抢答</param>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_startanswerEx(int type, int totalTopic, IntPtr pTopicType, string mac = "");
        /// <summary>
        /// 停止答题
        /// </summary>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_stopanswer(string mac = "");
        /// <summary>
        /// 结束答题
        /// </summary>
        /// <param name="mac">mac 为空时，发送命令到所有设备，否则为当前mac设备</param>
        /// <returns></returns>
        //mac 为空时，发送命令到所有设备，否则为当前mac设备
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_send_endanswer(string mac = "");


        /// <summary>
        /// 开启服务
        /// </summary>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_start();
        /// <summary>
        /// 停止服务
        /// </summary>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_stop();

        /// <summary>
        /// 设置学生学号（不支持中文）
        /// </summary>
        /// <param name="strDeviceMac">学生mac地址</param>
        /// <param name="strDeviceStu">学生学号</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_stu(string strDeviceMac, string strDeviceStu);

        /// <summary>
        /// 设置学生姓名（支持中文）
        /// </summary>
        /// <param name="strDeviceMac">学生mac地址</param>
        /// <param name="strDeviceStuNo">学生学号</param>
        /// <param name="strDeviceStuName">学生名称</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_bmp_stu(string strDeviceMac, string strDeviceStuNo, string strDeviceStuName);

        /// <summary>
        /// 设置学生中文姓名 超过3个...显示（支持中文）
        /// </summary>
        /// <param name="strDeviceMac">学生mac地址</param>
        /// <param name="strDeviceStuNo">学生学号</param>
        /// <param name="strDeviceStuName">学生名称</param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_bmp_stu_more(string strDeviceMac, string strDeviceStuNo, string strDeviceStuName);

        /// <summary>
        /// 设置学生中文姓名2
        /// </summary>
        /// <param name="strDeviceMac"></param>
        /// <param name="strDeviceStuName"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_bmp_stu2(string strDeviceMac, string strDeviceStuName);

        /// <summary>
        /// 批量配置wifi信息
        /// </summary>
        /// <param name="strDeviceSSID"></param>
        /// <param name="strDevicePwd"></param>
        /// <param name="strDeviceSrc"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_wifi(string strDeviceSSID, string strDevicePwd, string strDeviceSrc = "");

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
        internal static extern int rbt_win_config_net(string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc = "");

        /// <summary>
        /// 配网并切换网络
        /// </summary>
        /// <param name="strDeviceSSID"></param>
        /// <param name="strDevicePwd"></param>
        /// <param name="strIP"></param>
        /// <param name="nPort"></param>
        /// <param name="bMQTT"></param>
        /// <param name="bTCP"></param>
        /// <param name="strDeviceSrc"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_wifi_net(string strDeviceSSID, string strDevicePwd, string strIP, int nPort, bool bMQTT, bool bTCP, string strDeviceSrc = "");

        /// <summary>
        ///设置标点率
        /// </summary>
        /// <param name="freq">freq范围为0-4，0为最高，4为最低</param>
        /// <param name="mac"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_freq(int freq, string mac = "");

        /// <summary>
        /// 设置休眠事件
        /// </summary>
        /// <param name="mins">分钟</param>
        /// <param name="mac"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_config_sleep(int mins, string mac = "");

        /// <summary>
        /// 设置打开模组
        /// </summary>
        /// <param name="open"></param>
        /// <param name="mac"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int rbt_win_open_module(bool open, string mac = "");

        /// <summary>
        /// 设置打开悬浮点
        /// </summary>
        /// <param name="open"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_open_suspension(bool open);

        /// <summary>
        /// 获取画布ID
        /// </summary>
        /// <param name="canvasID"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_get_canvas_id(int canvasID = 0);

        /// <summary>
        /// 设置刷新时间 1-5秒
        /// </summary>
        /// <param name="seconds"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_screen_freq(int seconds);

        /// <summary>
        /// 设置心跳(测试)
        /// </summary>
        /// <param name="channel"></param>
        /// <param name="enable"></param>
        /// <param name="keepintvl"></param>
        /// <param name="keepcnt"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_keepalive(int channel, int enable, int keepintvl, int keepcnt);

        /// <summary>
        /// 删除离线笔记
        /// </summary>
        /// <param name="del"></param>
        /// <param name="mac"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool rbt_win_del_notes(int del, string mac = "");

        /// <summary>
        /// 优化笔迹转成path
        /// </summary>
        /// <param name="mac"></param>
        /// <param name="points"></param>
        /// <param name="len"></param>
        /// <param name="nLen"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern float[] rbt_win_toPath(string mac, float[] points, int len, ref int nLen);

        /// <summary>
        /// 转成优化轨迹的path
        /// </summary>
        /// <param name="mac"></param>
        /// <param name="points"></param>
        /// <param name="len"></param>
        /// <param name="nLen"></param>
        /// <returns></returns>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern float[] rbt_win_toTrailsPath(string mac, float[] points, int len, ref int nLen);

        /// <summary>
        /// 设置线条是否进行spline处理
        /// </summary>
        /// <param name="open"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setIsSpline(bool open);

        /// <summary>
        /// 设置笔宽度
        /// </summary>
        /// <param name="width"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setPenWidth(float width);

        /// <summary>
        /// 设置拖尾阈值，设置的越小，拖尾越长(0~1)
        /// </summary>
        /// <param name="delay"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setPointDelay(float delay);

        /// <summary>
        /// 设置粗细变化阈值，设置的越小，粗细变化越小
        /// </summary>
        /// <param name="damping"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setPointDamping(float damping);

        /// <summary>
        /// 设置基础宽度，用于过滤点和点之间的距离，默认取PenWidth
        /// </summary>
        /// <param name="width"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setBaseWidth(float width);

        /// <summary>
        /// 设置结尾宽度，此参数决定拖尾笔锋终点宽度，默认取BaseWidth * 0.1
        /// </summary>
        /// <param name="width"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setEndWidth(float width);

        /// <summary>
        /// 笔锋收尾触发速度判断，当速度大于笔宽度/decrease时会触发笔锋
        /// </summary>
        /// <param name="decrease"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_setWidthDecrease(float decrease);
        #endregion

        #region 绑定事件
        /// <summary>
        /// 设备上线回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_accept_cb(onAccept arg);

        /// <summary>
        /// 错误包回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_errorpacket_cb(onErrorPacket arg);

        /// <summary>
        /// 绑定点数据
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_origindata_cb(onOriginDataNew arg);
        /// <summary>
        /// 绑定点数据拓展
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_origindata_ex_cb(onOriginDataNewEx arg);

        /// <summary>
        /// 绑定获取设备MAC地址回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicemac_cb(onDeviceMac arg);

        /// <summary>
        /// 绑定学生名称回调事件
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
        /// 绑定按键回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devicekeypress_cb(onDeviceKeyPress arg);

        /// <summary>
        /// 绑定设备断开连接事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_devivedisconnect_cb(onDeviceDisconnect arg);

        /// <summary>
        /// 绑定设备页码回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceshowpage_cb(onDeviceShowPageNew arg);

        /// <summary>
        /// 绑定设备按键结果
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult arg);

        /// <summary>
        /// 绑定错误回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_error_cb(onError arg);
        /// <summary>
        /// 绑定画布回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_canvasid_cb(onCanvasID arg);

        /// <summary>
        /// 绑定设备优化笔迹回调事件
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_optimizedata_cb(onOptimizeData arg);
        /// <summary>
        /// 绑定设备优化笔迹回调事件（多页）
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_optimizedata_ex_cb(onOptimizeDataEx arg);

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

        /// <summary>
        /// 删除笔记回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deletenotes_cb(onDeleteNotes arg);

        /// <summary>
        /// 绑定回调地址
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_deviceip_cb(onDeviceIpOld arg);

        /// <summary>
        /// X10扫描回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_win_set_oidpageinfo_cb(onOidPageInfo arg);

        /// <summary>
        /// 绑定题目回调
        /// </summary>
        /// <param name="arg"></param>
        [DllImport("robotpenetdevice.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void rbt_wib_set_currentwritingnum_cb(onCurrentWritingNum arg);
        #endregion
    }
}
