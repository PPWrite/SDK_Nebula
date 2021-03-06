﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace robotpenetdevice_cs
{
    public partial class RbtNet
    {
        private static onAccept onaccept;
        private static onErrorPacket onerrorpacket;

        private static onOriginDataNew onorigindatanew;
        private static onOriginDataNewEx onorigindatanewex;

        private static onDeviceMac ondevicemac;
        private static onDeviceName ondevicename = null;
        private static onDeviceNameResult ondevicenameresult = null;

        private static onDeviceDisconnect ondevicedisconnect = null;
        private static onDeviceKeyPress ondevicekeyPress = null;
        private static onDeviceAnswerResult ondeviceanswerresult;
        private static onDeviceShowPageNew ondeviceshowpagenew = null;

        private static onError onerror = null;
        private static onCanvasID oncanvasid = null;

        private static onOptimizeData onoptimizedata = null;
        private static onOptimizeDataEx onoptimizedataex = null;

        private static onDeviceType ondevicetype = null;
        private static onKeyAnswer onkeyanswer = null;
        private static onDeviceInfo ondeviceinfo = null;
        private static onHardInfo onhardinfo = null;
        private static onDeviceBattery ondevicebattery = null;

        private static onDeleteNotes ondeletenotes = null;

        private static onDeviceIpOld ondeviceipold = null;

        private static onOidPageInfo onoidpageinfo = null;
        private static onCurrentWritingNum oncurrentwritingnum = null;

        private static onOpenModule onopenmodule = null;
        private static onFBSetMessage onfbsetmessage = null;

        private static onPageSensor onpagesensor = null;


        /// <summary>
        /// 设备上线回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        private static void accept(IntPtr ctx, string strDeviceMac)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                rbtNetThis.acceptEvt_?.Invoke(ctx, strDeviceMac);
            }
        }

        private static void errorPacket(IntPtr ctx)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                rbtNetThis.errorPacketEvt_?.Invoke(ctx);
            }
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
                rbtNetThis.deviceOriginDataNewEvt_?.Invoke(ctx, strDeviceMac, us, ux, uy, up, buffer, len);
                rbtNetThis.deviceOriginDataEvt_?.Invoke(ctx, strDeviceMac, us, ux, uy, up);
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="strDeviceMac"></param>
        /// <param name="us"></param>
        /// <param name="ux"></param>
        /// <param name="uy"></param>
        /// <param name="up"></param>
        /// <param name="buffer"></param>
        /// <param name="len"></param>
        private static void originDataNotifyEx(IntPtr ctx, IntPtr strDeviceMac, int currentPage, ushort us, ushort ux, ushort uy, ushort up, IntPtr buffer, int len)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                rbtNetThis.originDataNewExEvt_?.Invoke(ctx, strDeviceMac, currentPage, us, ux, uy, up, buffer, len);
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceMacEvt_?.Invoke(ctx, strDeviceMac);

                Thread.Sleep(100);
                rbtNetThis.SendCmd((int)DeviceCmd.CMD_DEVICE_INFO, strDeviceMac);
                Thread.Sleep(100);
                rbtNetThis.SendCmd((int)DeviceCmd.CMD_DEVICE_HARD_INFO, strDeviceMac);
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceNameEvt_?.Invoke(ctx, strDeviceMac, strDeviceName);
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceNameResult_?.Invoke(ctx, strDeviceMac, res, strDeviceName);
            }
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceDisconnectEvt_?.Invoke(ctx, strDeviceMac);
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceKeyPressEvt_?.Invoke(ctx, strDeviceMac, keyValue);
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceAnswerResultEvt_?.Invoke(ctx, strDeviceMac, resID, result, nResultSize);
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
                    if (rbtNetThis.pt== PrintType.NoMarkCode|| rbtNetThis.pt == PrintType.NoMarkCode_FB1|| rbtNetThis.pt == PrintType.NoMarkCode_FB2|| rbtNetThis.pt == PrintType.NoMarkCode_FB_FT)
                    {
                        if(nPageInfo==1048575)
                        {
                            nPageInfo = 0;
                            nNoteId = 0;
                            nPageId = 0;
                        }
                    }

                    string d = string.Empty;
                    switch (rbtNetThis.pt)
                    {
                        case PrintType.Base:
                        case PrintType.NoMarkCode:
                        default:
                            _nPageInfo = nPageInfo;
                            break;
                        case PrintType.Fault_tolerance:
                            d = getPageSequence(nPageInfo, 17);
                            string code = "" + d[1] + d[6] + d[9] + d[12] + d[15];
                            _nPageInfo = Convert.ToInt32(code, 2);
                            break;
                        case PrintType.Fault_tolerance2:
                            d = getPageSequence(nPageInfo, 17);
                            string code2 = "" + d[0] + d[2] + d[5] + d[7] + d[9] + d[11] + d[13] + d[15];
                            _nPageInfo = Convert.ToInt32(code2, 2);
                            break;
                        case PrintType.TyMode:
                            d = getPageSequence(nPageInfo, 17);
                            string code3 = "" + d[9] + d[10] + d[11] + d[12] + d.Substring(0, 9);
                            string code4 = "" + d[13] + d[14] + d[15] + d[16];
                            //_nPageInfo = nPageInfo;
                            nNoteId = Convert.ToInt32(code3, 2);
                            nPageId = Convert.ToInt32(code4, 2);

                            string d2 = "" + d[9] + d[10] + d[11] + d[12] + d.Substring(0, 9) + d[13] + d[14] + d[15] + d[16];

                            _nPageInfo = Convert.ToInt32(d2, 2);
                            break;
                        case PrintType.NoMarkCode_FB1:
                            d = getPageSequence(nPageInfo, 20);
                            //判断标志位
                            if (d[0] == '1' || d[1] == '1' || d[18] == '1' || d[19] == '1')
                            {
                                nPageInfo = 0;
                                nNoteId = 0;
                                nPageId = 0;
                                break;
                            }
                            //页码业务逻辑部分                            
                            string codeFB1 = string.Empty;
                            if(d[3]=='1'|| d[4] == '1' || d[5] == '1' || d[6] == '1')
                            {
                                codeFB1 = "1";
                            }
                            else
                            {
                                codeFB1 = "0";
                            }
                            if (d[8] == '1' || d[9] == '1' || d[10] == '1' || d[11] == '1')
                            {
                                codeFB1 += "1";
                            }
                            else
                            {
                                codeFB1 += "0";
                            }
                            if (d[13] == '1' || d[14] == '1' || d[15] == '1' || d[16] == '1')
                            {
                                codeFB1 += "1";
                            }
                            else
                            {
                                codeFB1 += "0";
                            }
                            _nPageInfo = Convert.ToInt32(codeFB1, 2);
                            break;
                        case PrintType.NoMarkCode_FB2:
                            d = getPageSequence(nPageInfo, 20);
                            string codeFB2 = string.Empty;
                            if (d[1] == '1' || d[2] == '1' || d[3] == '1' || d[4] == '1')
                            {
                                codeFB2 = "1";
                            }
                            else
                            {
                                codeFB2 = "0";
                            }
                            if (d[6] == '1' || d[7] == '1' || d[8] == '1' || d[9] == '1')
                            {
                                codeFB2 += "1";
                            }
                            else
                            {
                                codeFB2 += "0";
                            }
                            if (d[10] == '1' || d[11] == '1' || d[12] == '1' || d[13] == '1')
                            {
                                codeFB2 += "1";
                            }
                            else
                            {
                                codeFB2 += "0";
                            }
                            if (d[15] == '1' || d[16] == '1' || d[17] == '1' || d[18] == '1')
                            {
                                codeFB2 += "1";
                            }
                            else
                            {
                                codeFB2 += "0";
                            }
                            _nPageInfo = Convert.ToInt32(codeFB2, 2);
                            break;
                        case PrintType.NoMarkCode_FB_FT:
                            d = getPageSequence(nPageInfo, 20);
                            //判断标志位
                            if (d[19] != '0' || d[5] != '1' || d[4] != '0' )
                            {
                                nPageInfo = 0;
                                nNoteId = 0;
                                nPageId = 0;
                                break;
                            }
                            string code_ft = "" + d[0] + d[2] + d[7] + d[9] + d[11] + d[13] + d[15] + d[17];
                            _nPageInfo = Convert.ToInt32(code_ft, 2);
                            break;
                    }
                }

                rbtNetThis.deviceShowPageNewEvt_?.Invoke(ctx, strDeviceMac, nNoteId, nPageId, _nPageInfo);
                rbtNetThis.deviceShowPageEvt_?.Invoke(ctx, strDeviceMac, nNoteId, nPageId);
            }
        }

        private static string getPageSequence(int nPageInfo,int maxNum)
        {
            string d = System.Convert.ToString(nPageInfo, 2);
            int dlen = d.Length;
            for (int j = 0; j < maxNum - dlen; j++)
            {
                d = "0" + d;
            }
            return d;
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceError_?.Invoke(ctx, pmac, cmd, msg);
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

            if (rbtNetThis != null)
            {
                rbtNetThis.deviceCanvasID_?.Invoke(ctx, pmac, type, canvasID);
            }
        }

        /// <summary>
        /// 优化笔记数据回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pmac"></param>
        /// <param name="us"></param>
        /// <param name="ux"></param>
        /// <param name="uy"></param>
        /// <param name="width"></param>
        /// <param name="speed"></param>
        private static void optimizeData(IntPtr ctx, IntPtr pmac, ushort us, ushort ux, ushort uy, float width, float speed)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                rbtNetThis.deviceOptimizeDataEvt_?.Invoke(ctx, pmac, us, ux, uy, width, speed);
            }
        }

        /// <summary>
        /// 优化笔记数据回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pmac"></param>
        /// <param name="us"></param>
        /// <param name="ux"></param>
        /// <param name="uy"></param>
        /// <param name="width"></param>
        /// <param name="speed"></param>
        private static void optimizeDataEx(IntPtr ctx, IntPtr pmac, int currentPage, ushort us, ushort ux, ushort uy, float width, float speed)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                rbtNetThis.optimizeDataExEvt_?.Invoke(ctx, pmac, currentPage, us, ux, uy, width, speed);
            }
        }

        /// <summary>
        /// 获取设备类型
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="type"></param>
        private static void deviceType(IntPtr ctx, String pMac, int type)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.DeviceTypeEvt_?.Invoke(ctx, pMac, type);
            }
        }
        /// <summary>
        /// C5键值回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="key"></param>
        private static void keyAnswer(IntPtr ctx, String pMac, int key)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.KeyAnswerEvt_?.Invoke(ctx, pMac, key);
            }
        }
        /// <summary>
        /// 设备信息
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="version"></param>
        /// <param name="deviceMac"></param>
        /// <param name="hardNum"></param>
        private static void deviceInfo(IntPtr ctx, String pMac, String version, String deviceMac, int hardNum)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.DeviceInfoEvt_?.Invoke(ctx, pMac, version, deviceMac, hardNum);
            }
        }
        /// <summary>
        /// 硬件信息
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="xRange"></param>
        /// <param name="yRange"></param>
        /// <param name="LPI"></param>
        /// <param name="pageNum"></param>
        private static void hardInfo(IntPtr ctx, String pMac, int xRange, int yRange, int LPI, int pageNum)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.HardInfoEvt_?.Invoke(ctx, pMac, xRange, yRange, LPI, pageNum);
            }
        }
        /// <summary>
        /// 电量信息
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="battery"></param>
        private static void deviceBattery(IntPtr ctx, String pMac, eBatteryStatus battery)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.DeviceBatteryEvt_?.Invoke(ctx, pMac, battery);
            }
        }

        /// <summary>
        /// 设备删除离线笔记回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="result"></param>
        private static void deleteNotes(IntPtr ctx, String pMac, int result)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.deleteNotesEvt_?.Invoke(ctx, pMac, result);
            }
        }


        /// <summary>
        /// 设备ip地址回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="ip"></param>
        private static void deviceip(IntPtr ctx, String pMac, String ip)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;
            if (rbtNetThis != null)
            {
                string wd = ip.Substring(0, ip.LastIndexOf('.'));
                if (ipdic.ContainsKey(wd))
                {
                    rbtNetThis.DeviceIpEvt_?.Invoke(ctx, pMac, ip, ipdic[wd]);
                }
            }
        }

        /// <summary>
        /// X10上报扫描信息(x坐标,y坐标,旋转角度)
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="fX"></param>
        /// <param name="fY"></param>
        /// <param name="nAngle"></param>
        private static void oidPageInfo(IntPtr ctx, String pMac, float fX, float fY, int nAngle)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.oidPageInfoEvt_?.Invoke(ctx, pMac, fX, fY, nAngle);
            }
        }

        /// <summary>
        /// 测试类题目切换题目上报的题号
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="nNum"></param>
        private static void currentWritingNum(IntPtr ctx, String pMac, int nNum)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.CurrentWritingNumEvt_?.Invoke(ctx, pMac, nNum);
            }
        }

        /// <summary>
        /// 打开模组回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="isOpen"></param>
        private static void openModule(IntPtr ctx, String pMac, bool isOpen)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.openModuleEvt_?.Invoke(ctx, pMac, isOpen);
            }
        }

        /// <summary>
        /// FB设置消息回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="ret"></param>
        private static void fBSetMessage(IntPtr ctx, String pMac, bool ret)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.fBSetMessageEvt_?.Invoke(ctx, pMac, ret);
            }
        }

        /// <summary>
        /// 页码传感器20个值上报回调
        /// </summary>
        /// <param name="ctx"></param>
        /// <param name="pMac"></param>
        /// <param name="pageSensor"></param>
        private static void pageSensor(IntPtr ctx, String pMac, ST_PAGE_SENSOR pageSensor)
        {
            GCHandle thisHandle = GCHandle.FromIntPtr(ctx);
            RbtNet rbtNetThis = (RbtNet)thisHandle.Target;

            if (rbtNetThis != null)
            {
                rbtNetThis.pageSensorEvt_?.Invoke(ctx, pMac, pageSensor);
            }
        }
    }
}
