#pragma once
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
};

//�ص�����
typedef void (CALLBACK *UsbDataCallback_t)(const unsigned char*,int,void*);
//ʶ��ص�
typedef void (CALLBACK *ResultCallback_t)(int,char*,void*);

class IRobotEventHandler
{
public:
	virtual ~IRobotEventHandler() {}
	//�豸����¼�
	virtual void onDeviceChanged(eDeviceStatus status,int pid) {
		(void)status;
		(void)pid;
	}
	//�豸����¼�
	virtual void onDeviceChanged(eDeviceStatus status,eDeviceType type) {
		(void)status;
		(void)type;
	}
	//����״̬�¼�
	virtual void onGatewayStatus(eGatewayStatus status){
		(void)status;
	}
	//node״̬�¼�
	virtual void onNodeStatus(const NODE_STATUS &status){
		(void)status;
	}
	//�汾�¼�
	virtual void onDeviceInfo(const ST_DEVICE_INFO &info) {
		(void)info;
	}
	//����״̬�¼�
	virtual void onOnlineStatus(uint8_t *status) {
		(void)status;
	}
	//��ѡ�����¼�
	virtual void onExitVote(uint8_t *status) {
		(void)status;
	}
	//��ѡ�����¼�
	virtual void onExitVoteMulit(const ST_OPTION_PACKET &packet) {
		(void)packet;
	}
	//���������������¼�
	virtual void onMassData(int index,const PEN_INFO &penInfo) {
		(void)index;
		(void)penInfo;
	}
	//���ش����¼�
	virtual void onGatewayError(eNebulaError error) {
		(void)error;
	}
	//�����豸����¼�
	virtual void onSetDeviceNum(int result,int customid, int classid, int deviceid) {
		(void)result;
		(void)customid;
		(void)classid;
		(void)deviceid;
	}
	//���������¼�
	virtual void onFirmwareData(int progress) {
		(void)progress;
	}
	//��������¼�
	virtual void onRawResult(int result) {
		(void)result;
	}
	//�����¼�
	virtual void onGatewayReboot() {
	}
	//����ԭʼ�����¼�
	virtual void onDataPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//���������¼�
	virtual void onOriginalPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//nodeģʽ�¼�
	virtual void onNodeMode(eNodeMode mode) {
		(void)mode;
	}
	//����rtc�¼�
	virtual void onSetRtc(int result) {
		(void)result;
	}
	//���������¼�
	virtual void onKeyPress(int result) {
		(void)result;
	}
	//ҳ����ʾ�¼�
	virtual void onShowPage(const PAGE_INFO &pageInfo) {
		(void)pageInfo;
	}
	//���߱ʼ����������¼�
	virtual void onSyncPacket(const PEN_INFO &penInfo) {
		(void)penInfo;
	}
	//���߱ʼǿ�ʼ
	virtual void onSyncBegin(int leftNum,int noteNum,const ST_RTC_INFO &rtcInfo){
		(void)leftNum;
		(void)noteNum;
		(void)rtcInfo;
	}
	//���߱ʼǽ���
	virtual void onSyncEnd(int result){
		(void)result;
	}
	//�ϱ�ҳ��
	virtual void onMassShowPage(int index,const PAGE_INFO &pageInfo){
		(void)index;
		(void)pageInfo;
	}
	//�����¼�
	virtual void onVoteAnswer(int index,int answer){
		(void)index;
		(void)answer;
	}
	//x8 mac�¼�
	virtual void onX8Mac(uint8_t *mac){
		(void)mac;
	}
	//2.4g mac�¼�
	virtual void onMassMac(int index,uint8_t *mac){
		(void)index;
		(void)mac;
	}
	//////////////////////////////dongle//////////////////////
	//Dongle״̬�¼�
	virtual void onDongleStatus(eDongleStatus status,int mode) {
		(void)status;
		(void)mode;
	}
	//Dongle�汾�¼�
	virtual void onDongleVersion(const ST_VERSION &version) {
		(void)version;
	}
	//Dongleɨ���¼�
	virtual void onDongleScanRes(const ST_BLE_DEVICE &device) {
		(void)device;
	}
	//slave�汾�¼�
	virtual void onSlaveVersion(eDeviceType type,const ST_VERSION &version) {
		(void)type;
		(void)version;
	}
	//slave״̬�¼�
	virtual void onSlaveStatus(const NODE_STATUS &status) {
		(void)status;
	}
	//���������¼�
	virtual void onSetName(int result) {
		(void)result;
	}
	//slave�����¼�
	virtual void onSlaveError(eSlaveError error) {
		(void)error;
	}
	//ģ��汾�¼�
	virtual void onModuleVersion(const ST_MODULE_VERSION &version) {
		(void)version;
	}
	//����ģ��У׼�¼�
	virtual void onAjdustMode() {
	}
	//ģ��У׼����¼�
	virtual void onAjdustResult(int result) {
		(void)result;
	}
	//ģʽ״̬
	virtual void onDeviceMode(eDeviceMode mode) {
		(void)mode;
	}

	//���ð༶SSID
	virtual void onSetClassSSID(int result,unsigned char *ssid) {
		(void)result;
		(void)ssid;
	}
	//���ð༶����
	virtual void onSetClassPwd(int result,unsigned char *pwd) {
		(void)result;
		(void)pwd;
	}
	//����ѧ��ID
	virtual void onSetStudentID(int result,unsigned char *id) {
		(void)result;
		(void)id;
	}
	//��������
	virtual void onSetPwd(int result,unsigned char *pwd) {
		(void)result;
		(void)pwd;
	}
	//��������
	virtual void onSetSecret(int result,unsigned char *secret) {
		(void)result;
		(void)secret;
	}
	//�л�ģʽ
	virtual void onSwitchMode(eDeviceMode mode) {
		(void)mode;
	}
	//�ʼ��Ż����
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
	//��ʼ�� �ص�
	virtual void ConnectInitialize(eDeviceType nDeviceType,UsbDataCallback_t pCallback = NULL, void *pContext = NULL) = 0;
	//��ʼ�� �¼�
	virtual void ConnectInitialize(eDeviceType nDeviceType,IRobotEventHandler *pEventHander = NULL) = 0;
	//�����豸���ӣ��ɹ����Զ��������ݽ���
	virtual int  ConnectOpen() = 0;
	//�ر��豸���ӣ��ɹ����Զ��ر����ݽ���
	virtual void ConnectDispose() = 0;
	//�ж��豸�Ƿ�������״̬
	virtual bool IsConnected() = 0;
	//��������
	virtual void Send(int nCmd) = 0;
	//����
	virtual bool Update(const char *fileMcu,const char *fileBle,eDeviceType type = Unknow) = 0;
	//����
	virtual void SetConfig(int nCostumNum,int nClassNum,int nDeviceNum) = 0;
	//��ȡ�����豸����
	virtual int GetDeviceCount() = 0;
	//��ȡ�����豸
	virtual DWORD GetAvailableDevice() = 0;
	virtual bool GetDeviceInfo(int index,USB_INFO &usbInfo) = 0;
	virtual bool GetDeviceInfo(int index,DEVICE_INFO &devInfo) = 0;
	//����PID��VID���豸
	virtual int Open(int nVid,int nPid,bool bAll = true) = 0;
	//���������豸
	virtual void ConnectSlave(int nID) = 0;
	//��
	virtual void Bind(unsigned char *mac) = 0;
	//������������
	virtual void SetSlaveName(const char *name) = 0;
	//�����豸����
	virtual void SetDeviceType(eDeviceType nDeviceType) = 0;
	//��������ƫ��
	virtual void SetOffset(int nOffsetX,int nOffsetY) = 0;
	//��������
	virtual void SetIsHorizontal(bool bHorizontal) = 0;
	//��ȡ�豸��
	virtual int Width() = 0;
	//��ȡ�豸��
	virtual int Height() = 0;
	//��ת�Ƕ�
	virtual void Rotate(int nAngle = 0) = 0;
	//��ʼͶƱ
	virtual void VoteMulit(bool bMulit = true) = 0;
	//���ñʿ��
	virtual void SetPenWidth(float nPenWidth = 0) = 0;
	//���û�����С
	virtual void SetCanvasSize(int nWidth,int nHeight) = 0;
	//�ʼ��Ż�
	virtual void In(const PEN_INFO &penInfo) = 0;
	//�Ƿ���ѹ��
	virtual void SetPressStatus(bool bPress) = 0;
	//�Ƿ����ʼ��Ż�
	virtual void SetOptimizeStatus(bool bOptimize) = 0;
	//����ҳ��
	virtual void SetPage(int nPage) = 0;
	//������β��ֵ�����õ�ԽС����βԽ��(0~1) Ĭ��0.4
	virtual void SetPointDelay(float delay) = 0;
	//���ô�ϸ�仯��ֵ�����õ�ԽС����ϸ�仯ԽС Ĭ��0.026
	virtual void SetPointDamping(float damping) = 0;
	//��ȡ��ǰ�豸����
	virtual eDeviceType GetDeviceType(bool bSlave = false) = 0;
	//���ð༶SSID
	virtual void SetClassSSID(unsigned char *ssid,int len) = 0;
	//���ð༶����
	virtual void SetClassPwd(unsigned char *pwd,int len) = 0;
	//����ѧ��ID
	virtual void SetStudentID(unsigned char *id,int len) = 0;
	//����MQTT����
	virtual void SetPwd(unsigned char *pwd) = 0;
	//����Secret
	virtual void SetSecret(unsigned char *sercet) = 0;
	//��������
	virtual void UpdateFont(const char *fileFont) = 0;
	//����Key
	virtual void SetKey(const char *key) = 0;
	//����bmp
	virtual void SetBmp(unsigned char *buffer,int len) = 0;
	//����ģ��
	virtual bool UpdateEmr(const char *file) = 0;
	//����mac
	virtual void SetMac(int type,unsigned char *mac,int len) = 0;
	//���ñ�����
	virtual void SetPenType(ePenType type) = 0;
	//////////////////////////////////////////////�ʼ�ʶ��ӿ�//////////////////////////////////////////////
	//����ʶ��ص�����
	virtual void SetOnResultCallback(ResultCallback_t pCallBack,void *pContext) = 0;
	//�����û���Ϣ
	virtual void SetUserInfo(const char *user_id,const char *secret, int source) = 0;
	//���ó�ʱ ����
	virtual void SetSyncTimeout(int ms = 5000) = 0;
	//��ʶ��ӿ� ����������
	virtual int OpenRecog(int maxSize = 3000,bool autoAppend = false) = 0;
	//���û���״̬
	virtual void SetCacheStatus(bool cache) = 0;
	//����ʶ��ʼ�,language,1Ӣ�� 2���� 3��ѧ��ʽ,direct,0Ϊ����,1Ϊ����
	virtual int CreateRecogNote(char *note_key,int language, int direct = 0) = 0;
	//׷�ӱʼ�
	virtual int AppendNote(void *pen_array,int array_size,const char *note_key,int draw = 0) = 0;
	virtual int AppendNote(const char *note_key,int draw = 0) = 0;
	//ʶ��ʼ�
	virtual int RecogNote(const char *user_id,const char *note_key) = 0;
	//�ر�ʶ��ӿ�
	virtual void CloseRecog() = 0;
};

//��ʼ�� �ص�
extern "C" ROBOT_API void  ConnectInitialize(eDeviceType nDeviceType, IN UsbDataCallback_t pCallback, void *pContext);
//��ʼ�� �¼�
extern "C" ROBOT_API void  ConnectInitialize2(eDeviceType nDeviceType, IN IRobotEventHandler *pEventHander);
//�����豸���ӣ��ɹ����Զ��������ݽ���
extern "C" ROBOT_API int   ConnectOpen();
//�ر��豸���ӣ��ɹ����Զ��ر����ݽ���
extern "C" ROBOT_API void  ConnectDispose();
//�ж��豸�Ƿ�������״̬
extern "C" ROBOT_API bool  IsConnected();
//��������
extern "C" ROBOT_API void  Send(int nCmd);
//����
extern "C" ROBOT_API void  Update(const char *fileMcu,const char *fileBle,eDeviceType type = Unknow);
//����
extern "C" ROBOT_API void  SetConfig(int nCostumNum,int nClassNum,int nDeviceNum);
//��ȡ�����豸����
extern "C" ROBOT_API int GetDeviceCount();
//��ȡ�����豸
extern "C" ROBOT_API bool GetDeviceInfo(int index,USB_INFO &usbInfo);
//��ȡ�����豸
extern "C" ROBOT_API bool GetDeviceInfo2(int index,DEVICE_INFO &devInfo);
//����PID��VID���豸
extern "C" ROBOT_API int  Open(int nVid,int nPid,bool bAll = true);
//���������豸
extern "C" ROBOT_API void ConnectSlave(int nID);
//������������
extern "C" ROBOT_API void SetSlaveName(const char *name);
//���û�����С
extern "C" ROBOT_API void SetCanvasSize(int nWidth,int nHeight);
//�����豸����
extern "C" ROBOT_API void SetDeviceType(eDeviceType nDeviceType);
//��������ƫ��
extern "C" ROBOT_API void SetOffset(int nOffsetX,int nOffsetY);
//��������
extern "C" ROBOT_API void SetIsHorizontal(bool bHorizontal);
//��ȡ�豸��
extern "C" ROBOT_API int Width();
//��ȡ�豸��
extern "C" ROBOT_API int Height();
//��ת�Ƕ�
extern "C" ROBOT_API void Rotate(int nAngle);
//��������
extern "C" ROBOT_API void SetPenWidth(float nPenWidth);
//��ʼͶƱ
extern "C" ROBOT_API void VoteMulit(bool bMulit);
//�ʼ��Ż�
extern "C" ROBOT_API void In(const PEN_INFO &penInfo);
//�Ƿ���ѹ��
extern "C" ROBOT_API void SetPressStatus(bool bPress);
//�Ƿ����ʼ��Ż�
extern "C" ROBOT_API void SetOptimizeStatus(bool bOptimize);
//����ҳ��
extern "C" ROBOT_API void SetPage(int nPage);
//������β��ֵ�����õ�ԽС����βԽ��(0~1) Ĭ��0.4
extern "C" ROBOT_API void SetPointDelay(float delay);
//���ô�ϸ�仯��ֵ�����õ�ԽС����ϸ�仯ԽС Ĭ��0.026
extern "C" ROBOT_API void SetPointDamping(float damping);
//���ð༶SSID
extern "C" ROBOT_API void SetClassSSID(unsigned char *ssid,int len);
//���ð༶����
extern "C" ROBOT_API void SetClassPwd(unsigned char *pwd,int len);
//����ѧ��ID
extern "C" ROBOT_API void SetStudentID(unsigned char *id,int len);
//��������
extern "C" ROBOT_API void SetPwd(unsigned char *pwd);
//����Secret
extern "C" ROBOT_API void SetSecret(unsigned char *sercet);
//��ȡ��ǰ�豸����
extern "C" ROBOT_API eDeviceType GetDeviceType(bool bSlave = false);
//����Key
extern "C" ROBOT_API void SetKey(const char *key);
//����bmp
extern "C" ROBOT_API void SetBmp(unsigned char *buffer,int len);

extern "C" 
{
	//��ȡʵ�� 
	ROBOT_API RobotPenController* GetInstance();
	//����ʵ��
	ROBOT_API void DestroyInstance();
};