﻿#pragma once
#include <windows.h>

#ifdef DLL_EXPORT
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
	UpdateEmrStop,
	DeleteSync,
	GetPenType,
	SearchStorage,
	GetProperty,
	SlaveStatus,
	GetAdjustValue,
	ExitAdjustMode,
};

//回调函数
typedef void (CALLBACK *UsbDataCallback_t)(const unsigned char*,int,void*);
//识别回调
typedef void (CALLBACK *ResultCallback_t)(int,char*,void*);

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
	//设备信息事件
	virtual void onDeviceInfoEx(const ST_DEVICE_INFO &info) {
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
	//坐标原始数据事件
	virtual void onDataPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
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
	//OID页码事件
	virtual void onShowOIDPage(const OID_INFO &pageInfo) {
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

	//离线笔记开始KZ
	virtual void onSyncBegin(int leftNum,int noteStart,int noteLen,int subject,int topic,const ST_RTC_INFO &rtc,int useTimes){
		(void)leftNum;
		(void)noteStart;
		(void)noteLen;
		(void)subject;
		(void)topic;
		(void)rtc;
		(void)useTimes;
	}
	//离线笔记结束
	virtual void onSyncEnd(bool exit){
		(void)exit;
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
	virtual void onAjdustMode(int ret,int low,int high) {
		(void)ret;
		(void)low;
		(void)high;
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
	//设置MqttIP
	virtual void onSetMqttIp(int result) {
		(void)result;
	}
	//设置模拟值
	virtual void onSetAnalogValue(int result,uint8_t *value) {
		(void)result;
		(void)value;
	}
	//设置密码
	virtual void onSetSecret(int result,unsigned char *secret) {
		(void)result;
		(void)secret;
	}
	//切换模式
	virtual void onSwitchMode(eDeviceMode mode) {
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
	//按钮生效
	virtual void onButtonActive(bool active){
		(void)active;
	}
	//设备属性
	virtual void onDeviceProperty(const HARD_INFO &hardInfo){
		(void)hardInfo;
	}
	//设备特性
	virtual void onFeature(int type){
		(void)type;
	}
	//T7_C5 HZ测试
	virtual void onTestT7_C5(int type){
		(void)type;
	}
	//获取无源笔校准相位值
	virtual void onAjdustValue(int nValue){
		(void)nValue;
	}
	//设置无源笔校准相位值事件
	virtual void onSetAdjustValueResult(int nValue){
		(void)nValue;
	}

	//X10工装偏差设置成功事件
	virtual void onSetX10OffsetValueResult(int nValue){
		(void)nValue;
	}
	//FB 设备消息设置事件
	virtual void onSetFBDeviceMsg(int ret){
		(void)ret;
	}
	//页码传感器20个值上报事件
	virtual void onPageSensor(const ST_PAGE_SENSOR &pageSensor)
	{
		(void)pageSensor;
	}	
	//当前固件模式 1 采集模式 2 检测模式
	virtual void onTestFirmwareMode(int mode)
	{
		(void)mode;
	}
	//上报X/Y 通道号,增益值,ADC值
	virtual void onTestFirmwareValue(int mode, const st_test_firmware_info *infoList, int length)
	{
		(void)mode;
		(void)infoList;
		(void)length;
	}
	//上报设备生产日期和延保日期
	virtual void onProductDate(const char *datestr){
		(void)datestr;
	}
	//上报当前使用场景纸类型
	virtual void onPaperType(ePaperType paperType){
		(void)paperType;
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
	virtual void SendTest(int nCmd, int nType) = 0;
	//设置x10页码
	virtual void SetX10PageNum(int nNum) = 0;
	//升级
	virtual bool Update(const char *fileMcu,const char *fileBle,eDeviceType type = Unknow) = 0;
	//对于支持Telink设备的手写板升级MCU使用此接口
	virtual bool UpdateMcu(const char *fileMcu) = 0;
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
	//设置基础宽度，用于过滤点和点之间的距离，默认取PenWidth
	virtual void SetBaseWidth(float width) = 0;
	//设置结尾宽度，此参数决定拖尾笔锋终点宽度，默认取BaseWidth * 0.1
	virtual void SetEndWidth(float width) = 0;
	//笔锋收尾触发速度判断，当速度大于笔宽度/decrease时会触发笔锋
	virtual void SetWidthDecrease(float decrease) = 0;
	//转成path
	virtual float *ToPath(float* points, size_t len, int *nLen) = 0;
	//转成优化轨迹的path
	virtual float *ToTrailsPath(float* points, int len, int *nLen) = 0;
	//释放点数组
	virtual void FreeMemory(void* context) = 0;
	//获取当前设备类型
	virtual eDeviceType GetDeviceType(bool bSlave = false) = 0;
	//设置班级SSID
	virtual void SetClassSSID(unsigned char *ssid,int len) = 0;
	//设置班级密码
	virtual void SetClassPwd(unsigned char *pwd,int len) = 0;
	//设置学生ID
	virtual void SetStudentID(unsigned char *id,int len) = 0;
	//设置MqttIp地址以及端口(格式192.168.99.20,6001)
	virtual void SetMqttIp(unsigned char *ip, int len) = 0;
	//设置模拟值
	virtual void SetAnalogValue(bool write, int value) = 0;
	//设置Secret
	virtual void SetSecret(unsigned char *sercet) = 0;
	//升级字体
	virtual void UpdateFont(const char *fileFont) = 0;
	//设置Key
	virtual void SetKey(const char *key) = 0;
	//设置bmp
	virtual void SetBmp(unsigned char *buffer,int len) = 0;
	//升级模组
	virtual bool UpdateEmr(const char *file) = 0;
	//设置mac
	virtual void SetMac(int type,unsigned char *mac,int len) = 0;
	//设置E3W mac
	virtual void SetE3WMac(int type,unsigned char *mac,int len) = 0;
	//设置笔类型
	virtual void SetPenType(ePenType type) = 0;
	//设置纸张类型
	virtual void SetPaperType(ePaperType type) = 0;
	//设置设备模式
	virtual void SetDeviceMode(eDeviceMode type) = 0;
	//设置按钮生效
	virtual void SetButtonActive(bool active) = 0;
	//设置特性
	virtual void SetFeature(int type) = 0;
	//设置无源笔校准相位值(范围[0,104])
	virtual void SetAdujustValue(int nValue) = 0;
	//设置X10工装偏差
	virtual void SetX10InstallOffset(int jediOffsetX, int jediOffsetY, int oid3sOffsetX, int oid3sOffsetY, int nAngle) = 0;
	//是否开启X10偏移，默认开启
	virtual void openX10Offset(bool isOpen) = 0;
	//是否开启X10角度偏移，默认开启
	virtual void openX10AngleOffset(bool isOpen) = 0;
	//设置FB设备消息
	virtual void SetFBDeviceMessgae(const char *msg) = 0;
	//切换测试固件模式(0查询当前模式 1 采集模式 2 检测模式)
	virtual void SetTestFirmwareMode(int mode) = 0;
	//设置测试通道号，增益，ADC值
	virtual void SetTestFirmwareValue(int mode, const st_test_firmware_info *infoList, int length) = 0;
	//设置/获取设备生产日期和延保日期(K7-C5-XF-年月日(占6个字符)-05-序列号(4个字符))
	//datastr为空代表获取
	virtual void SetProductDate(const char*datestr) = 0;
#ifdef USE_RECOG
	//////////////////////////////////////////////笔记识别接口//////////////////////////////////////////////
	//设置识别回调函数
	virtual void SetOnResultCallback(ResultCallback_t pCallBack,void *pContext) = 0;
	//设置用户信息
	virtual void SetUserInfo(const char *user_id,const char *secret, int source) = 0;
	//设置超时 毫秒
	virtual void SetSyncTimeout(int ms = 5000) = 0;
	//打开识别接口 缓存最大点数
	virtual int OpenRecog(int maxSize = 3000,bool autoAppend = false) = 0;
	//设置缓存状态
	virtual void SetCacheStatus(bool cache) = 0;
	//创建识别笔记,language,1英语 2中文 3数学公式,direct,0为竖屏,1为横屏
	virtual int CreateRecogNote(char *note_key,int language, int direct = 0) = 0;
	//追加笔记
	virtual int AppendNote(void *pen_array,int array_size,const char *note_key,int draw = 0) = 0;
	virtual int AppendNote(const char *note_key,int draw = 0) = 0;
	//识别笔记
	virtual int RecogNote(const char *user_id,const char *note_key) = 0;
	//获取原始笔迹
	virtual int getOriginalTrails(const char *user_id, const char *note_key) = 0;
	//关闭识别接口
	virtual void CloseRecog() = 0;
	/**************************   云笔迹API   **********************************/
	//创建笔记
	virtual int createCloudNote(char *note_key, const char *user_id, const char *title, int direct = 0) = 0;
	//分页获取笔迹队列
	virtual int getCloudNoteList(const char *user_id, int offset = 0, int limit = 50) = 0;
	//搜索笔迹队列（根据关键字查询笔迹）
	virtual int searchCloudNoteList(const char *search_key , const char *user_id, int offset = 0, int limit = 50) = 0;
	//获取笔迹分页信息
	virtual int getPagingInfo(const char *note_key, const char *user_id) = 0;
	//创建笔迹分页信息
	virtual int createPagingInfo(const char *note_key, const char *user_id, const char *last_key) = 0;
	//新增单条轨迹（在指定分⻚页下新增一条轨迹）
	virtual int addSingleTrails(const char *trails_key, const char *user_id, const char *block_key, const char *data, const char *start_at, const char *end_at, const char *ext, int color, int type = 0) = 0;
	//批量新增轨迹
	virtual int addBatchTrails(const char *block_key, const char *user_id, const char *trails) = 0;
	//获取分页轨迹集合（获取分页下的轨迹列队）
	virtual int getCurrentBlockTrailsList(const char *user_id, const char *note_key, const char *block_key, int offset = 0, int limit = 50) = 0;
	//创建笔迹分页并增加识别目标（在指定笔记下创建分页，并设置识别目标）
	virtual int createAndAddTarget(const char *note_key, const char *user_id, const char *last_key, int language = 0, int follow = 0) = 0;
	//获取识别结果(同步) 根据notekey获取识别结果
	virtual int getBlockNoteRecog(const char *block_key, const char *user_id) = 0;
	//主动识别分页（根据block_key主动开始识别任务）
	virtual int startRecog(const char *block_key, const char *user_id) = 0;
#endif // USE_RECOG
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
//对于支持Telink设备的手写板升级MCU使用此接口
extern "C" ROBOT_API bool UpdateMcu(const char *fileMcu);
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
//设置基础宽度，用于过滤点和点之间的距离，默认取PenWidth
extern "C" ROBOT_API void SetBaseWidth(float width);
//设置结尾宽度，此参数决定拖尾笔锋终点宽度，默认取BaseWidth * 0.1
extern "C" ROBOT_API void SetEndWidth(float width);
//笔锋收尾触发速度判断，当速度大于笔宽度/decrease时会触发笔锋
extern "C" ROBOT_API void SetWidthDecrease(float decrease);
//转成path
extern "C" ROBOT_API float *ToPath(float* points, size_t len, int *nLen);
//转成优化轨迹的path
extern "C" ROBOT_API float *ToTrailsPath(float* points, int len, int *nLen);
//释放点数组
extern "C" ROBOT_API void FreeMemory(void* context);
//设置班级SSID
extern "C" ROBOT_API void SetClassSSID(unsigned char *ssid,int len);
//设置班级密码
extern "C" ROBOT_API void SetClassPwd(unsigned char *pwd,int len);
//设置学生ID
extern "C" ROBOT_API void SetStudentID(unsigned char *id,int len);
//设置MqttIp地址以及端口(格式192.168.99.20,6001)
extern "C" ROBOT_API void SetMqttIp(unsigned char *ip, int len);
//设置密
extern "C" ROBOT_API void SetPwd(unsigned char *pwd);
//设置Secret
extern "C" ROBOT_API void SetSecret(unsigned char *sercet);
//获取当前设备类型
extern "C" ROBOT_API eDeviceType GetDeviceType(bool bSlave = false);
//设置Key
extern "C" ROBOT_API void SetKey(const char *key);
//设置bmp
extern "C" ROBOT_API void SetBmp(unsigned char *buffer,int len);
//升级模组
extern "C" ROBOT_API bool UpdateEmr(const char *file);
//设置mac
extern "C" ROBOT_API void SetMac(int type,unsigned char *mac,int len);
//设置E3W mac
extern "C" ROBOT_API void SetE3WMac(int type,unsigned char *mac,int len);
//设置笔类型
extern "C" ROBOT_API void SetPenType(ePenType type);
//设置X10工装偏差
extern "C" ROBOT_API void SetX10InstallOffset(int jediOffsetX, int jediOffsetY, int oid3sOffsetX, int oid3sOffsetY, int nAngle);
//是否开启X10偏移以及角度偏移，默认开启
extern "C" ROBOT_API void openX10Offset(bool isOpen);
//是否开启X10角度偏移，默认开启
extern "C" ROBOT_API void openX10AngleOffset(bool isOpen);
//设置FB设备消息
extern "C" ROBOT_API void SetFBDeviceMessgae(const char *msg);
//切换测试固件模式(1 采集模式 2 检测模式)
extern "C" ROBOT_API void SetTestFirmwareMode(int mode);
//设置测试通道号，增益，ADC值(1代表 x轴 2代表 y轴)
extern "C" ROBOT_API void SetTestFirmwareValue(int mode, const st_test_firmware_info *infoList, int length);
//设置/获取设备生产日期和延保日期(K7-C5-XF-年月日(占6个字符)-05-序列号(4个字符))
extern "C" ROBOT_API void SetProductDate(const char*datestr);
#ifdef USE_RECOG
//////////////////////////////////////////////笔记识别接口//////////////////////////////////////////////
//设置识别回调函数
extern "C" ROBOT_API void setOnResultCallback(ResultCallback_t pCallBack,void *pContext);
//设置用户信息
extern "C" ROBOT_API void setUserInfo(const char *user_id,const char *secret, int source);
//设置超时 毫秒
extern "C" ROBOT_API void setSyncTimeout(int ms = 5000);
//打开识别接口 缓存最大点数
extern "C" ROBOT_API int openRecog(int maxSize = 3000,bool autoAppend = false);
//设置缓存状态
extern "C" ROBOT_API void setCacheStatus(bool cache);
//创建识别笔记,language,1英语 2中文 3数学公式,direct,0为竖屏,1为横屏
extern "C" ROBOT_API int createRecogNote(char *note_key,int language, int direct = 0);
//追加笔记
extern "C" ROBOT_API int appendNote(void *pen_array,int array_size,const char *note_key,int draw = 0);
extern "C" ROBOT_API int appendNote2(const char *note_key,int draw = 0);
//识别笔记
extern "C" ROBOT_API int recogNote(const char *user_id,const char *note_key);
//获取原始笔迹
extern "C" ROBOT_API int getOriginalTrails(const char *user_id, const char *note_key);
//关闭识别接口
extern "C" ROBOT_API void closeRecog();
#endif

extern "C" 
{
	//获取实例 
	ROBOT_API RobotPenController* GetInstance();
	//销毁实例
	ROBOT_API void DestroyInstance();
};