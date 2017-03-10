#pragma once
#include <windows.h>
#include <vector>

#if defined(DLL_EXPORT)
#define DECLDIR __declspec(dllexport) 
#else 
#define DECLDIR __declspec(dllimport) 
#include "common.h"
#endif

enum cmdId
{
	VoteStart = 0,
	VoteEnd,
	WriteStart,
	WriteEnd,
	SyncStart,
	SyncEnd,
	UpdateStop,
	GetConfig,
};

//回调函数
typedef void (CALLBACK *UsbDataCallback_t)(const unsigned char*,int,void*);

class RobotPenController
{
public:
	//初始化设备连接
	virtual void ConnectInitialize(int nDeviceType, UsbDataCallback_t pCallback = NULL, void *pContext = NULL) = 0;
	//开启设备连接，成功后将自动开启数据接收
	virtual int  ConnectOpen() = 0;
	//关闭设备连接，成功后将自动关闭数据接收
	virtual void ConnectDispose() = 0;
	//判断设备是否处于连接状态
	virtual bool IsConnected() = 0;
	//发送命令
	virtual void Send(cmdId nCmd) = 0;
	//升级
	virtual bool Update(const char *fileNameMcu,const char *fileNameBle) = 0;
	//设置
	virtual void SetConfig(int nCostumNum,int nClassNum,int nDeviceNum) = 0;
	// 返回所有可用设备集合的地址句柄
	virtual DWORD GetAvailableDevice() = 0;
	//根据PID和VID打开设备
	virtual int Open(int nVid,int nPid,bool bAll = true) = 0;
};



	//初始化设备连接
	extern "C" DECLDIR void  ConnectInitialize(int nDeviceType, IN UsbDataCallback_t pCallback, void *pContext);
	//开启设备连接，成功后将自动开启数据接收
	extern "C" DECLDIR int   ConnectOpen();
	//关闭设备连接，成功后将自动关闭数据接收
	extern "C" DECLDIR void  ConnectDispose();
	//判断设备是否处于连接状态
	extern "C" DECLDIR bool  IsConnected();
	//发送命令
	extern "C" DECLDIR void  Send(cmdId nCmd);
	//升级
	extern "C" DECLDIR void  Update( const char *fileNameMcu,const char *fileNameBle );
	//设置
	extern "C" DECLDIR void  SetConfig(int nCostumNum,int nClassNum,int nDeviceNum);
	//根据PID和VID打开设备
	extern "C" DECLDIR int  Open(int nVid,int nPid,bool bAll = true);

extern "C" 
{
	//获取实例 
	DECLDIR RobotPenController* GetInstance();
	//销毁实例
	DECLDIR void DestroyInstance();
};