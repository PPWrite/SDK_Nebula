﻿
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
    };
}
