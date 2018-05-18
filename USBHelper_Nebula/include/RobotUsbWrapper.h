#pragma once
#include <windows.h>

#if defined(DLL_EXPORT)
#define ROBOT_API __declspec(dllexport) 
#else 
#define ROBOT_API __declspec(dllimport) 
#include "common.h"
#endif

enum eRbtType
{
	VoteBegin = 0,
	VoteMulti,
	VotePoll,
	VoteEnd,
	WriteBegin,
	WriteEnd,
	SyncBegin,
	SyncEnd,
	UpdateStop,
	GetConfig,
	DongleVersion,
	DongleScanStart,
	DongleScanStop,
	DongleDisconnect,
	VoteAnswer,
	EnterUsb,
	ExitUsb,
	AdjustMode,
	GetMac,
	GetNodeInfo,
	ModuleVersion,
	GetDeviceID,
	SearchMode,
	SwitchMode,
	UpdateSearch,
	UpdateWifi,
	GetMassMac,
};

//回调函数
typedef void (CALLBACK *UsbDataCallback_t)(const unsigned char*,int,void*);

class IRobotEventHandler
{
public:
	virtual ~IRobotEventHandler() {}
	//设备插拔事件
	virtual void onDeviceChanged(eDeviceStatus status,int pid) {
		(void)status;
		(void)pid;
	}
	//设备插拔事件
	virtual void onDeviceChanged(eDeviceStatus status,eDeviceType type) {
		(void)status;
		(void)type;
	}
	//网关状态事件
	virtual void onGatewayStatus(eGatewayStatus status){
		(void)status;
	}
	//node状态事件
	virtual void onNodeStatus(const NODE_STATUS &status){
		(void)status;
	}
	//版本事件
	virtual void onDeviceInfo(const ST_DEVICE_INFO &info) {
		(void)info;
	}
	//在线状态事件
	virtual void onOnlineStatus(uint8_t *status) {
		(void)status;
	}
	//单选结束事件
	virtual void onExitVote(uint8_t *status) {
		(void)status;
	}
	//多选结束事件
	virtual void onExitVoteMulit(const ST_OPTION_PACKET &packet) {
		(void)packet;
	}
	//大数据坐标数据事件
	virtual void onMassData(int index,const PEN_INFO &penInfo) {
		(void)index;
		(void)penInfo;
	}
	//网关错误事件
	virtual void onGatewayError(eNebulaError error) {
		(void)error;
	}
	//设置设备结果事件
	virtual void onSetDeviceNum(int result,int customid, int classid, int deviceid) {
		(void)result;
		(void)customid;
		(void)classid;
		(void)deviceid;
	}
	//升级进度事件
	virtual void onFirmwareData(int progress) {
		(void)progress;
	}
	//升级结果事件
	virtual void onRawResult(int result) {
		(void)result;
	}
	//重启事件
	virtual void onGatewayReboot() {
	}
	//坐标数据事件
	virtual void onOriginalPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//node模式事件
	virtual void onNodeMode(eNodeMode mode) {
		(void)mode;
	}
	//设置rtc事件
	virtual void onSetRtc(int result) {
		(void)result;
	}
	//按键按下事件
	virtual void onKeyPress(int result) {
		(void)result;
	}
	//页面显示事件
	virtual void onShowPage(const PAGE_INFO &pageInfo) {
		(void)pageInfo;
	}
	//离线笔记坐标数据事件
	virtual void onSyncPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//离线笔记开始
	virtual void onSyncBegin(int leftNum,int noteNum,const ST_RTC_INFO &rtcInfo){
		(void)leftNum;
		(void)noteNum;
		(void)rtcInfo;
	}
	//离线笔记结束
	virtual void onSyncEnd(int result){
		(void)result;
	}
	//上报页码
	virtual void onMassShowPage(int index,const PAGE_INFO &pageInfo){
		(void)index;
		(void)pageInfo;
	}
	//抢答事件
	virtual void onVoteAnswer(int index,int answer){
		(void)index;
		(void)answer;
	}
	//x8 mac事件
	virtual void onX8Mac(uint8_t *mac){
		(void)mac;
	}
	//2.4g mac事件
	virtual void onMassMac(int index,uint8_t *mac){
		(void)index;
		(void)mac;
	}
	//////////////////////////////dongle//////////////////////
	//Dongle状态事件
	virtual void onDongleStatus(eDongleStatus status,int mode) {
		(void)status;
		(void)mode;
	}
	//Dongle版本事件
	virtual void onDongleVersion(const ST_VERSION &version) {
		(void)version;
	}
	//Dongle扫描事件
	virtual void onDongleScanRes(const ST_BLE_DEVICE &device) {
		(void)device;
	}
	//slave版本事件
	virtual void onSlaveVersion(eDeviceType type,const ST_VERSION &version) {
		(void)type;
		(void)version;
	}
	//slave状态事件
	virtual void onSlaveStatus(const NODE_STATUS &status) {
		(void)status;
	}
	//设置名称事件
	virtual void onSetName(int result) {
		(void)result;
	}
	//slave错误事件
	virtual void onSlaveError(eSlaveError error) {
		(void)error;
	}
	//模组版本事件
	virtual void onModuleVersion(const ST_MODULE_VERSION &version) {
		(void)version;
	}
	//进入模组校准事件
	virtual void onAjdustMode() {
	}
	//模组校准结果事件
	virtual void onAjdustResult(int result) {
		(void)result;
	}
	//模式状态
	virtual void onDeviceMode(eDeviceMode mode) {
		(void)mode;
	}

	//设置班级SSID
	virtual void onSetClassSSID(int result,unsigned char *ssid) {
		(void)result;
		(void)ssid;
	}
	//设置班级密码
	virtual void onSetClassPwd(int result,unsigned char *pwd) {
		(void)result;
		(void)pwd;
	}
	//设置学生ID
	virtual void onSetStudentID(int result,unsigned char *id) {
		(void)result;
		(void)id;
	}
	//设置密码
	virtual void onSetPwd(int result,unsigned char *pwd) {
		(void)result;
		(void)pwd;
	}
	//设置密码
	virtual void onSetSecret(int result,unsigned char *secret) {
		(void)result;
		(void)secret;
	}
	//切换模式
	virtual void onSwitchMode(int mode) {
		(void)mode;
	}
	//笔记优化输出
	virtual void onOut(float x,float y,float width,float speed,int status){
		(void)x;
		(void)y;
		(void)width;
		(void)speed;
		(void)status;
	}
};

class RobotPenController
{
public:
	//初始化 回调
	virtual void ConnectInitialize(eDeviceType nDeviceType,UsbDataCallback_t pCallback = NULL, void *pContext = NULL) = 0;
	//初始化 事件
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
	virtual bool Update(const char *fileMcu,const char *fileBle,eDeviceType type = Unknow) = 0;
	//设置
	virtual void SetConfig(int nCostumNum,int nClassNum,int nDeviceNum) = 0;
	//获取可用设备总数
	virtual int GetDeviceCount() = 0;
	//获取可用设备
	virtual DWORD GetAvailableDevice() = 0;
	virtual bool GetDeviceInfo(int index,USB_INFO &usbInfo) = 0;
	virtual bool GetDeviceInfo(int index,DEVICE_INFO &devInfo) = 0;
	//根据PID和VID打开设备
	virtual int Open(int nVid,int nPid,bool bAll = true) = 0;
	//连接蓝牙设备
	virtual void ConnectSlave(int nID) = 0;
	//绑定
	virtual void Bind(unsigned char *mac) = 0;
	//设置蓝牙名称
	virtual void SetSlaveName(const char *name) = 0;
	//设置设备类型
	virtual void SetDeviceType(eDeviceType nDeviceType) = 0;
	//设置中心偏移
	virtual void SetOffset(int nOffsetX,int nOffsetY) = 0;
	//设置竖屏
	virtual void SetIsHorizontal(bool bHorizontal) = 0;
	//获取设备宽
	virtual int Width() = 0;
	//获取设备高
	virtual int Height() = 0;
	//旋转角度
	virtual void Rotate(int nAngle = 0) = 0;
	//开始投票
	virtual void VoteMulit(bool bMulit = true) = 0;
	//设置笔宽度
	virtual void SetPenWidth(float nPenWidth = 0) = 0;
	//设置画布大小
	virtual void SetCanvasSize(int nWidth,int nHeight) = 0;
	//笔记优化
	virtual void In(const PEN_INFO &penInfo) = 0;
	//是否开启压感
	virtual void SetPressStatus(bool bPress) = 0;
	//是否开启笔记优化
	virtual void SetOptimizeStatus(bool bOptimize) = 0;
	//设置页码
	virtual void SetPage(int nPage) = 0;
	//设置拖尾阈值，设置的越小，拖尾越长(0~1) 默认0.4
	virtual void SetPointDelay(float delay) = 0;
	//设置粗细变化阈值，设置的越小，粗细变化越小 默认0.026
	virtual void SetPointDamping(float damping) = 0;
	//获取当前设备类型
	virtual eDeviceType GetDeviceType(bool bSlave = false) = 0;
	//设置班级SSID
	virtual void SetClassSSID(unsigned char *ssid,int len) = 0;
	//设置班级密码
	virtual void SetClassPwd(unsigned char *pwd,int len) = 0;
	//设置学生ID
	virtual void SetStudentID(unsigned char *id,int len) = 0;
	//设置密码
	virtual void SetPwd(unsigned char *pwd) = 0;
	//设置Secret
	virtual void SetSecret(unsigned char *sercet) = 0;
	//升级字体
	virtual void UpdateFont(const char *fileFont) = 0;
};

//初始化 回调
extern "C" ROBOT_API void  ConnectInitialize(eDeviceType nDeviceType, IN UsbDataCallback_t pCallback, void *pContext);
//初始化 事件
extern "C" ROBOT_API void  ConnectInitialize2(eDeviceType nDeviceType, IN IRobotEventHandler *pEventHander);
//开启设备连接，成功后将自动开启数据接收
extern "C" ROBOT_API int   ConnectOpen();
//关闭设备连接，成功后将自动关闭数据接收
extern "C" ROBOT_API void  ConnectDispose();
//判断设备是否处于连接状态
extern "C" ROBOT_API bool  IsConnected();
//发送命令
extern "C" ROBOT_API void  Send(int nCmd);
//升级
extern "C" ROBOT_API void  Update(const char *fileMcu,const char *fileBle,eDeviceType type = Unknow);
//设置
extern "C" ROBOT_API void  SetConfig(int nCostumNum,int nClassNum,int nDeviceNum);
//获取可用设备总数
extern "C" ROBOT_API int GetDeviceCount();
//获取可用设备
extern "C" ROBOT_API bool GetDeviceInfo(int index,USB_INFO &usbInfo);
//获取可用设备
extern "C" ROBOT_API bool GetDeviceInfo2(int index,DEVICE_INFO &devInfo);
//根据PID和VID打开设备
extern "C" ROBOT_API int  Open(int nVid,int nPid,bool bAll = true);
//连接蓝牙设备
extern "C" ROBOT_API void ConnectSlave(int nID);
//设置蓝牙名称
extern "C" ROBOT_API void SetSlaveName(const char *name);
//设置画布大小
extern "C" ROBOT_API void SetCanvasSize(int nWidth,int nHeight);
//设置设备类型
extern "C" ROBOT_API void SetDeviceType(eDeviceType nDeviceType);
//设置中心偏移
extern "C" ROBOT_API void SetOffset(int nOffsetX,int nOffsetY);
//设置竖屏
extern "C" ROBOT_API void SetIsHorizontal(bool bHorizontal);
//获取设备宽
extern "C" ROBOT_API int Width();
//获取设备高
extern "C" ROBOT_API int Height();
//旋转角度
extern "C" ROBOT_API void Rotate(int nAngle);
//过滤坐标
extern "C" ROBOT_API void SetPenWidth(float nPenWidth);
//开始投票
extern "C" ROBOT_API void VoteMulit(bool bMulit);
//笔记优化
extern "C" ROBOT_API void In(const PEN_INFO &penInfo);
//是否开启压感
extern "C" ROBOT_API void SetPressStatus(bool bPress);
//是否开启笔记优化
extern "C" ROBOT_API void SetOptimizeStatus(bool bOptimize);
//设置页码
extern "C" ROBOT_API void SetPage(int nPage);
//设置拖尾阈值，设置的越小，拖尾越长(0~1) 默认0.4
extern "C" ROBOT_API void SetPointDelay(float delay);
//设置粗细变化阈值，设置的越小，粗细变化越小 默认0.026
extern "C" ROBOT_API void SetPointDamping(float damping);
//设置班级SSID
extern "C" ROBOT_API void SetClassSSID(unsigned char *ssid,int len);
//设置班级密码
extern "C" ROBOT_API void SetClassPwd(unsigned char *pwd,int len);
//设置学生ID
extern "C" ROBOT_API void SetStudentID(unsigned char *id,int len);
//设置密码
extern "C" ROBOT_API void SetPwd(unsigned char *pwd);
//设置Secret
extern "C" ROBOT_API void SetSecret(unsigned char *sercet);
//获取当前设备类型
extern "C" ROBOT_API eDeviceType GetDeviceType(bool bSlave = false);

extern "C" 
{
	//获取实例 
	ROBOT_API RobotPenController* GetInstance();
	//销毁实例
	ROBOT_API void DestroyInstance();
};