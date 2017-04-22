#pragma once
#include <windows.h>
#include <vector>

#if defined(DLL_EXPORT)
#define DECLDIR __declspec(dllexport) 
#else 
#define DECLDIR __declspec(dllimport) 
#include "common.h"
#endif

enum eRbtType
{
	VoteBegin = 0,
	VoteEnd,
	WriteBegin,
	WriteEnd,
	SyncBegin,
	SyncEnd,
	UpdateStop,
	GetConfig,
	DongleScanStart,
	DongleScanStop,
	DongleDisconnect,
};

//回调函数
typedef void (CALLBACK *UsbDataCallback_t)(const unsigned char*,int,void*);

class IRobotEventHandler
{
public:
	virtual ~IRobotEventHandler() {}

	virtual void onDeviceChanged(int type) {
		(void)type;
	}
	virtual void onGatewayStatus(int status) {
		(void)status;
	}
	virtual void onGatewayVersion(const ST_DEVICE_INFO &info) {
		(void)info;
	}
	virtual void onOnlineStatus(int *status) {
		(void)status;
	}
	virtual void onExitVote(int *status) {
		(void)status;
	}
	virtual void onExitVoteMulit(const ST_OPTION_PACKET &packet) {
		(void)packet;
	}
	virtual void onMassData(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	virtual void onGatewayError(int error) {
		(void)error;
	}
	virtual void onSetDeviceNum(int result,int customid, int classid, int deviceid) {
		(void)result;
		(void)customid;
		(void)classid;
		(void)deviceid;
	}
	virtual void onFirmwareData(int progress) {
		(void)progress;
	}
	virtual void onRawResult(int result) {
		(void)result;
	}
	virtual void onGatewayReboot() {
	}
	virtual void onUsbPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	virtual void onNodeMode(int mode) {
		(void)mode;
	}
	virtual void onSetRtc(int result) {
		(void)result;
	}
	virtual void onKeyPress(int result) {
		(void)result;
	}
	virtual void onShowPage(int count, int current) {
		(void)count;
		(void)current;
	}
	virtual void onOriginalPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//////////////////////////////dongle//////////////////////
	virtual void onDongleStatus(int status) {
		(void)status;
	}
	virtual void onDongleVersion() {
	}
	virtual void onDongleScanRes() {
	}
	virtual void onSlaveVersion() {
	}
	virtual void onSlaveStatus(int status) {
		(void)status;
	}
	virtual void onSetName() {
	}
	virtual void onSlaveError(int error) {
		(void)error;
	}
	virtual void onDongleFirmwareData(int progress) {
		(void)progress;
	}
	virtual void onDongleRawResult(int result) {
		(void)result;
	}
	virtual void onDonglePacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
};

class RobotPenController
{
public:
	//初始化设备连接
	virtual void ConnectInitialize(int nDeviceType,bool bTransform = false,UsbDataCallback_t pCallback = NULL, void *pContext = NULL) = 0;
	virtual void ConnectInitialize(eDeviceType nDeviceType,IRobotEventHandler *pEventHander = NULL) = 0;
	//开启设备连接，成功后将自动开启数据接收
	virtual int  ConnectOpen() = 0;
	//关闭设备连接，成功后将自动关闭数据接收
	virtual void ConnectDispose() = 0;
	//判断设备是否处于连接状态
	virtual bool IsConnected() = 0;
	//发送命令
	virtual void Send(int nCmd) = 0;
	//升级
	virtual bool Update(const char *fileName,const char *fileOther) = 0;
	//设置
	virtual void SetConfig(int nCostumNum,int nClassNum,int nDeviceNum) = 0;
	//获取可用设备总数
	virtual int GetAvailableDeviceCount() = 0;
	//获取可用设备
	virtual DWORD GetAvailableDevice() = 0;
	virtual bool GetAvailableDevice(int i,USB_INFO &usbInfo) = 0;
	//根据PID和VID打开设备
	virtual int Open(int nVid,int nPid,bool bAll = true) = 0;
	//连接蓝牙设备
	virtual void ConnectSlave(int nID) = 0;
	//设置蓝牙名称
	virtual void SetSlaveName(const char *name) = 0;
	//获取硬件大小
	virtual bool GetDeviceSize(int nDeviceType, int &nDeviceWidth, int &nDeviceHeight) = 0;
	//设置画布大小
	virtual void SetCanvasSize(int nWidth,int nHeight) = 0;
	//获取设备宽
	virtual int Width() = 0;
	//获取设备高
	virtual int Height() = 0;
	//旋转角度
	virtual void Rotate(int nAngle = 0) = 0;
	//过滤坐标
	virtual void SetFilterWidth(int nPenWidth = 0) = 0;
	//开始投票
	virtual void VoteMulit(bool bMulit = true) = 0;
};

//初始化设备连接
extern "C" DECLDIR void  ConnectInitialize(int nDeviceType, bool bTransform, IN UsbDataCallback_t pCallback, void *pContext);
//开启设备连接，成功后将自动开启数据接收
extern "C" DECLDIR int   ConnectOpen();
//关闭设备连接，成功后将自动关闭数据接收
extern "C" DECLDIR void  ConnectDispose();
//判断设备是否处于连接状态
extern "C" DECLDIR bool  IsConnected();
//发送命令
extern "C" DECLDIR void  Send(int nCmd);
//升级
extern "C" DECLDIR void  Update( const char *fileName,const char *fileOther );
//设置
extern "C" DECLDIR void  SetConfig(int nCostumNum,int nClassNum,int nDeviceNum);
//获取可用设备总数
extern "C" DECLDIR int GetAvailableDeviceCount();
//获取可用设备
extern "C" DECLDIR bool GetAvailableDevice(int i,USB_INFO &usbInfo);
//根据PID和VID打开设备
extern "C" DECLDIR int  Open(int nVid,int nPid,bool bAll = true);
//连接蓝牙设备
extern "C" DECLDIR void ConnectSlave(int nID);
//设置蓝牙名称
extern "C" DECLDIR void SetSlaveName(const char *name);
//获取硬件大小
extern "C" DECLDIR bool GetDeviceSize(int nDeviceType, int &nDeviceWidth, int &nDeviceHeight);

extern "C" 
{
	//获取实例 
	DECLDIR RobotPenController* GetInstance();
	//销毁实例
	DECLDIR void DestroyInstance();
};