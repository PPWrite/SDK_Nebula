
using System;
using System.Runtime.InteropServices;

namespace robotpenetdevice_cs
{
    /// <summary>
    /// 设备上线回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    public delegate void onAccept(IntPtr ctx, System.String strDeviceMac);

    /// <summary>
    /// 错误包回调
    /// </summary>
    /// <param name="ctx"></param>
    public delegate void onErrorPacket(IntPtr ctx);

    /// <summary>
    /// 笔迹数据回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="us"></param>
    /// <param name="ux"></param>
    /// <param name="uy"></param>
    /// <param name="up"></param>
    public delegate void onOriginData(IntPtr ctx, IntPtr strDeviceMac, ushort us, ushort ux, ushort uy, ushort up);
    public delegate void onOriginDataNew(IntPtr ctx, IntPtr strDeviceMac, ushort us, ushort ux, ushort uy, ushort up, IntPtr buffer, int len);
    /// <summary>
    /// 多主观题笔迹数据回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="currentPage"></param>
    /// <param name="us"></param>
    /// <param name="ux"></param>
    /// <param name="uy"></param>
    /// <param name="up"></param>
    /// <param name="buffer"></param>
    /// <param name="len"></param>
    public delegate void onOriginDataNewEx(IntPtr ctx, IntPtr strDeviceMac, int currentPage, ushort us, ushort ux, ushort uy, ushort up, IntPtr buffer, int len);

    /// <summary>
    /// Mac地址回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    public delegate void onDeviceMac(IntPtr ctx, string strDeviceMac);
    /// <summary>
    /// 设备名称回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="strDeviceName"></param>
    public delegate void onDeviceName(IntPtr ctx, String strDeviceMac, String strDeviceName);
    /// <summary>
    /// 设置设备名称回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="res"></param>
    /// <param name="strDeviceName"></param>
    public delegate void onDeviceNameResult(IntPtr ctx, String strDeviceMac, int res, String strDeviceName);

    /// <summary>
    /// 设备断开回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    public delegate void onDeviceDisconnect(IntPtr ctx, IntPtr strDeviceMac);
    /// <summary>
    /// 按键回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="keyValue"></param>
    public delegate void onDeviceKeyPress(IntPtr ctx, IntPtr strDeviceMac, int keyValue);
    /// <summary>
    /// 答案回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="resID"></param>
    /// <param name="result"></param>
    /// <param name="nResultSize"></param>
    public delegate void onDeviceAnswerResult(IntPtr ctx, IntPtr strDeviceMac, int resID, IntPtr result, int nResultSize);
    /// <summary>
    /// 页面显示回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="strDeviceMac"></param>
    /// <param name="nNoteId"></param>
    /// <param name="nPageId"></param>
    public delegate void onDeviceShowPage(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId);
    public delegate void onDeviceShowPageNew(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId, int nPageInfo);

    /// <summary>
    /// 错误回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pmac"></param>
    /// <param name="cmd"></param>
    /// <param name="msg"></param>
    public delegate void onError(IntPtr ctx, String pmac, int cmd, String msg);
    /// <summary>
    /// 画布ID回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pmac"></param>
    /// <param name="type"></param>
    /// <param name="canvasID"></param>
    public delegate void onCanvasID(IntPtr ctx, String pmac, int type, int canvasID);

    /// <summary>
    /// 优化笔记回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pmac"></param>
    /// <param name="us"></param>
    /// <param name="ux"></param>
    /// <param name="uy"></param>
    /// <param name="width"></param>
    /// <param name="speed"></param>
    public delegate void onOptimizeData(IntPtr ctx, IntPtr pmac,ushort us, ushort ux, ushort uy, float width, float speed);
    /// <summary>
    /// 多主观题优化笔记回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pmac"></param>
    /// <param name="currentPage"></param>
    /// <param name="us"></param>
    /// <param name="ux"></param>
    /// <param name="uy"></param>
    /// <param name="width"></param>
    /// <param name="speed"></param>
    public delegate void onOptimizeDataEx(IntPtr ctx, IntPtr pmac, int currentPage, ushort us, ushort ux, ushort uy, float width, float speed);

    /// <summary>
    /// 设备类型回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="type"></param>
    public delegate void onDeviceType(IntPtr ctx, String pMac, int type);

    /// <summary>
    /// C5W按键回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="key"></param>
    public delegate void onKeyAnswer(IntPtr ctx, String pMac, int key);

    /// <summary>
    /// 设备信息回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="version">版本号</param>
    /// <param name="deviceMac"></param>
    /// <param name="hardNum">硬件号</param>
    public delegate void onDeviceInfo(IntPtr ctx, String pMac, String version, String deviceMac, int hardNum);

    /// <summary>
    /// 设备硬件信息回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="xRange">x轴范围</param>
    /// <param name="yRange">y轴范围</param>
    /// <param name="LPI">报点规则</param>
    /// <param name="pageNum">页码位数</param>
    public delegate void onHardInfo(IntPtr ctx, String pMac, int xRange, int yRange, int LPI, int pageNum);
    /// <summary>
    /// 设备电量信息回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="battery"></param>
    public delegate void onDeviceBattery(IntPtr ctx, String pMac, eBatteryStatus battery);
    /// <summary>
    /// 设备删除离线笔记回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="result"></param>
    public delegate void onDeleteNotes(IntPtr ctx, String pMac, int result);

    /// <summary>
    /// 设备上线上报设备的ip地址
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="ip"></param>
    public delegate void onDeviceIpOld(IntPtr ctx, String pMac, String ip);
    public delegate void onDeviceIp(IntPtr ctx, String pMac, String ip, String sendip);

    /// <summary>
    /// X10上报扫描信息(x坐标,y坐标,旋转角度)
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="fX"></param>
    /// <param name="fY"></param>
    /// <param name="nAngle"></param>
    public delegate void onOidPageInfo(IntPtr ctx, String pMac, float fX, float fY, int nAngle);
    /// <summary>
    /// 解答,书写,测试类题目切换题目上报的题号
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="nNum"></param>
    public delegate void onCurrentWritingNum(IntPtr ctx, String pMac, int nNum);

    /// <summary>
    /// 打开模组回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="isOpen"></param>
    public delegate void onOpenModule(IntPtr ctx, String pMac, bool isOpen);

    /// <summary>
    /// FB设置消息回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="ret"></param>
    public delegate void onFBSetMessage(IntPtr ctx, String pMac, bool ret);

    /// <summary>
    /// 页码传感器20个值上报回调
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="pMac"></param>
    /// <param name="pageSensor"></param>
    public delegate void onPageSensor(IntPtr ctx, String pMac, ST_PAGE_SENSOR pageSensor);



    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Init_Param
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string strIp;
        public Int32 port;
        public Int32 listenCount;
        [MarshalAs(UnmanagedType.I1)]
        public bool open;
        [MarshalAs(UnmanagedType.I1)]
        public bool optimize;
        public IntPtr ctx;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct ST_PAGE_SENSOR
    {
        public UInt16 sensor1;
        public UInt16 sensor2;
        public UInt16 sensor3;
        public UInt16 sensor4;
        public UInt16 sensor5;
        public UInt16 sensor6;
        public UInt16 sensor7;
        public UInt16 sensor8;
        public UInt16 sensor9;
        public UInt16 sensor10;
        public UInt16 sensor11;
        public UInt16 sensor12;
        public UInt16 sensor13;
        public UInt16 sensor14;
        public UInt16 sensor15;
        public UInt16 sensor16;
        public UInt16 sensor17;
        public UInt16 sensor18;
        public UInt16 sensor19;
        public UInt16 sensor20;
    }

    public enum keyPressEnum
    {
        K_A = 0x06,
        K_B = 0x07,
        K_C = 0x08,
        K_D = 0x09,
        K_E = 0x10,
        K_F = 0x11,
        K_SUCC = 0x12,
        K_ERROR = 0x13,
        K_CACLE = 0x14,
        K_SURE = 0x15,
        K_G = 0x16,
    };

    public enum answerResultKey
    {
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        Y = 6,
        N = 7,
        G = 8,
    }

    public enum eBatteryStatus
    {
        BATTERY_LOW_POWER = 0,//低电
        BATTERY_FIVE = 5,   //5%电量
        BATTERY_TWENTY = 20,//20%电量
        BATTERY_FORTY = 40,//40%电量
        BATTERY_SIXTY = 60,//60%电量
        BATTERY_EIGHTY = 80,//80%电量
        BATTERY_ONEHUNDREDTY = 100,//100%电量
        BATTERY_CHARGING = 254, //充电中
        BATTERY_COMPLETE = 255, //充电完成
    };

    //命令类型
    public enum DeviceCmd
    {
        CMD_DEVICE_INFO, //获取设备信息
        CMD_DEVICE_HARD_INFO //获取硬件信息
    };

    public enum PrintType
    {
        /// <summary>
        /// 原始模型
        /// </summary>
        Base,
        /// <summary>
        /// 容错模型,三位一体，左右间隔两个容错位，有效位5个
        /// </summary>
        Fault_tolerance,
        /// <summary>
        /// 容错模型2，三位一体，左右间隔一个容错位，有效位8个
        /// </summary>
        Fault_tolerance2,
        /// <summary>
        /// 第三拓展模型
        /// 1000     0000           111100111
        /// pageid   nodeid高4位    nodeid低9位 
        /// </summary>
        TyMode,
        /// <summary>
        /// 没有标志位的页码
        /// </summary>
        NoMarkCode,
        /// <summary>
        /// FB新页码，方案1
        /// 00-01111011-11011110-00
        /// </summary>
        NoMarkCode_FB1,
        /// <summary>
        ///  FB新页码，方案2
        ///  0111101111-1111011110
        /// </summary>
        NoMarkCode_FB2,

        /// <summary>
        ///  FB新页码，方案2
        ///  0111101111-1111011110
        /// </summary>
        NoMarkCode_FB_FT
    }
}
