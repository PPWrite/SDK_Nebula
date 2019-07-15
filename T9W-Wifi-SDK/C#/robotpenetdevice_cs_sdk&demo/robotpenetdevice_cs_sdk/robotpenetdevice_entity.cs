
using System;
using System.Runtime.InteropServices;

namespace robotpenetdevice_cs
{
    // 
    public delegate void onAccept(IntPtr ctx, System.String strDeviceMac);
    // 
    public delegate void onErrorPacket(IntPtr ctx);

    // 设备MAC地址上报
    public delegate void onDeviceMac(IntPtr ctx, string strDeviceMac);
    // 原点数据上报
    public delegate void onOriginData(IntPtr ctx, IntPtr strDeviceMac, ushort us, ushort ux, ushort uy, ushort up);
    public delegate void onOriginDataNew(IntPtr ctx, IntPtr strDeviceMac, ushort us, ushort ux, ushort uy, ushort up, IntPtr buffer, int len);
    public delegate void onOriginDataNewEx(IntPtr ctx, IntPtr strDeviceMac,int currentPage, ushort us, ushort ux, ushort uy, ushort up, IntPtr buffer, int len);

    //
    public delegate void onDeviceDisconnect(IntPtr ctx, IntPtr strDeviceMac);
    //
    public delegate void onDeviceKeyPress(IntPtr ctx, IntPtr strDeviceMac, int keyValue);
    // 
    public delegate void onDeviceShowPage(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId);
    public delegate void onDeviceShowPageNew(IntPtr ctx, IntPtr strDeviceMac, int nNoteId, int nPageId, int nPageInfo);
    //
    public delegate void onDeviceAnswerResult(IntPtr ctx, IntPtr strDeviceMac, int resID, IntPtr result, int nResultSize);

    public delegate void onDeviceName(IntPtr ctx, String strDeviceMac, String strDeviceName);

    public delegate void onDeviceNameResult(IntPtr ctx, String strDeviceMac, int res, String strDeviceName);

    public delegate void onError(IntPtr ctx, String pmac, int cmd, String msg);

    public delegate void onCanvasID(IntPtr ctx, String pmac, int type, int canvasID);

    public delegate void onOptimizeData(IntPtr ctx, IntPtr pmac,ushort us, ushort ux, ushort uy, float width, float speed);
    public delegate void onOptimizeDataEx(IntPtr ctx, IntPtr pmac, int currentPage, ushort us, ushort ux, ushort uy, float width, float speed);

    //设备上线上报设备的ip地址
    public delegate void onDeviceIpOld(IntPtr ctx, String pMac, String ip);
    public delegate void onDeviceIp(IntPtr ctx, String pMac, String ip, String sendip);
    //设备类型回调
    public delegate void onDeviceType(IntPtr ctx, String pMac, int type);
    //C5W按键回调
    public delegate void onKeyAnswer(IntPtr ctx, String pMac, int key);
    //设备信息回调
    public delegate void onDeviceInfo(IntPtr ctx, String pMac, String version,String deviceMac,int hardNum);
    //设备硬件信息回调
    public delegate void onHardInfo(IntPtr ctx, String pMac, int xRange, int yRange, int LPI, int pageNum);
    //设备电量信息回调
    public delegate void onDeviceBattery(IntPtr ctx, String pMac, eBatteryStatus battery);
    //设备删除离线笔记回调
    public delegate void onDeleteNotes(IntPtr ctx, String pMac,int result);
    //X10上报扫描信息(x坐标,y坐标,旋转角度)
    public delegate void onOidPageInfo(IntPtr ctx, String pMac, float fX, float fY, int nAngle);

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
        Fault_tolerance2
    }
}
