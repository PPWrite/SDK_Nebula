#ifndef _RBT_WIN_COMMOM_H_
#define _RBT_WIN_COMMOM_H_

typedef void rbt_win_context;
typedef unsigned short ushort;

//��������
enum keyPressEnum
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

enum eBatteryStatus
{
	BATTERY_LOW_POWER = 0,//�͵�
	BATTERY_FIVE = 5,	//5%����
	BATTERY_TWENTY = 20,//20%����
	BATTERY_FORTY = 40,//40%����
	BATTERY_SIXTY = 60,//60%����
	BATTERY_EIGHTY = 80,//80%����
	BATTERY_ONEHUNDREDTY = 100,//100%����
	BATTERY_CHARGING = 254, //�����
	BATTERY_COMPLETE = 255, //������
};

//��������
enum DeviceCmd
{
	CMD_DEVICE_INFO, //��ȡ�豸��Ϣ
	CMD_DEVICE_HARD_INFO //��ȡӲ����Ϣ
};

//ҳ�봫������20��ֵ
typedef struct st_page_sensor
{
	uint16_t sensor1;
	uint16_t sensor2;
	uint16_t sensor3;
	uint16_t sensor4;
	uint16_t sensor5;
	uint16_t sensor6;
	uint16_t sensor7;
	uint16_t sensor8;
	uint16_t sensor9;
	uint16_t sensor10;
	uint16_t sensor11;
	uint16_t sensor12;
	uint16_t sensor13;
	uint16_t sensor14;
	uint16_t sensor15;
	uint16_t sensor16;
	uint16_t sensor17;
	uint16_t sensor18;
	uint16_t sensor19;
	uint16_t sensor20;
}ST_PAGE_SENSOR;

//�豸���߻ص�
typedef void __stdcall onAccept(rbt_win_context* context, const char* pClientIpAddress);
//������ص�
typedef void __stdcall onErrorPacket(rbt_win_context* context);
//�ʼ����ݻص�
typedef void __stdcall onOriginData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up, unsigned char *buffer, int len);
//��������ʼ����ݻص�
typedef void __stdcall onOriginDataEx(rbt_win_context* ctx, const char* pMac, int currentPage, ushort us, ushort ux, ushort uy, ushort up, unsigned char *buffer, int len);
//�ʼ����ݻص�
typedef void __stdcall onOriginDataE3(rbt_win_context* ctx, const char* pMac, ushort us, int ux, int uy, ushort up, ushort ua, unsigned char *buffer, int len);
//Mac��ַ�ص�
typedef void __stdcall onDeviceMac(rbt_win_context* context, const char* pMac);
//�豸���ƻص�
typedef void __stdcall onDeviceName(rbt_win_context* context, const char* pMac, const char* pName);
//�����豸���ƻص�
typedef void __stdcall onDeviceNameResult(rbt_win_context* context, const char* pMac, int res, const char* pName);
//�豸�Ͽ��ص�
typedef void __stdcall onDeviceDisConnect(rbt_win_context* context, const char* pMac);
//�����ص�
typedef void __stdcall onDeviceKeyPress(rbt_win_context* context, const char* pMac, keyPressEnum keyValue);
//�𰸻ص�
typedef void __stdcall onDeviceAnswerResult(rbt_win_context* context, const char* pMac, int resID, unsigned char* pResult, int nSize);
//ҳ����ʾ�ص�
typedef void __stdcall onDeviceShowPage(rbt_win_context* context, const char* pMac, int nNoteId, int nPageId, int nPageInfo);
//����ص�
typedef void __stdcall onError(rbt_win_context* context, const char* pmac, int cmd, const char *msg);
//����ID�ص�
typedef void __stdcall onCanvasID(rbt_win_context* context, const char* pmac, int type, int canvasID);
//�Ż��ʼǻص�
typedef void __stdcall onOptimizeData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, float width, float speed);
//���������Ż��ʼǻص�
typedef void __stdcall onOptimizeDataEx(rbt_win_context* ctx, const char* pMac, int currentPage, ushort us, ushort ux, ushort uy, float width, float speed);
//�豸���ͻص�
typedef void __stdcall onDeviceType(rbt_win_context* context, const char* pMac, int type);
//C5W�����ص�
typedef void __stdcall onKeyAnswer(rbt_win_context* context, const char* pMac, int key);
//�豸��Ϣ�ص�
typedef void __stdcall onDeviceInfo(rbt_win_context *ctx, const char* pMac, const char *version, const char* deviceMac, ushort hardNum);
//�豸Ӳ����Ϣ�ص�
typedef void __stdcall onHardInfo(rbt_win_context *ctx, const char* pMac, int xRange, int yRange, int LPI, int pageNum);
//�豸������Ϣ�ص�
typedef void __stdcall onDeviceBattery(rbt_win_context *ctx, const char* pMac, eBatteryStatus battery);
//�豸ɾ�����߱ʼǻص�
typedef void __stdcall onDeleteNotes(rbt_win_context *ctx, const char* pMac, int result);
//�豸�����ϱ��豸��ip��ַ
typedef void __stdcall onDeviceIp(rbt_win_context *ctx, const char* pMac, const char *ip);
//X10�ϱ�ɨ����Ϣ(x����,y����,��ת�Ƕ�)
typedef void __stdcall onOidPageInfo(rbt_win_context *ctx, const char* pMac, float fX, float fY, int nAngle);
//���,��д,��������Ŀ�л���Ŀ�ϱ������
typedef void __stdcall onCurrentWritingNum(rbt_win_context *ctx, const char* pMac, int nNum);
//��ģ��ص�
typedef void __stdcall onOpenModule(rbt_win_context* ctx, const char* pMac, bool isOpen);
//FB������Ϣ�ص�
typedef void __stdcall onFBSetMessage(rbt_win_context* ctx, const char* pMac, bool ret);
//����WAV�ļ��ص�
typedef void __stdcall onDownloadWAVFile(rbt_win_context* ctx, const char* pMac, int ret, const char *outpath);
//�ϴ�wav�ļ��ص�
typedef void __stdcall onUploadWAVFile(rbt_win_context* ctx, const char* pMac, int ret);
//ҳ�봫����20��ֵ�ϱ��ص�
typedef void __stdcall onPageSensor(rbt_win_context* ctx, const char* pMac, ST_PAGE_SENSOR pageSensor);

void rbt_win_set_accept_cb(onAccept* arg);
void rbt_win_set_errorpacket_cb(onErrorPacket* arg);
void rbt_win_set_origindata_cb(onOriginData* arg);
void rbt_win_set_origindata_ex_cb(onOriginDataEx* arg);
void rbt_win_set_origindata_e3_cb(onOriginDataE3* arg);
void rbt_win_set_devicemac_cb(onDeviceMac* arg);
void rbt_win_set_devicename_cb(onDeviceName* arg);
void rbt_win_set_devicenameresult_cb(onDeviceNameResult* arg);
void rbt_win_set_devicekeypress_cb(onDeviceKeyPress* arg);
void rbt_win_set_devivedisconnect_cb(onDeviceDisConnect* arg);
void rbt_win_set_deviceshowpage_cb(onDeviceShowPage* arg);
void rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult* arg);
void rbt_win_set_error_cb(onError *arg);
void rbt_win_set_canvasid_cb(onCanvasID *arg);
void rbt_win_set_optimizedata_cb(onOptimizeData *arg);
void rbt_win_set_optimizedata_ex_cb(onOptimizeDataEx *arg);
void rbt_win_set_devicetype_cb(onDeviceType *arg);
void rbt_win_set_keyanswer_cb(onKeyAnswer *arg);
void rbt_win_set_deviceinfo_cb(onDeviceInfo *arg);
void rbt_win_set_hardinfo_cb(onHardInfo *arg);
void rbt_win_set_devicebattery_cb(onDeviceBattery *arg);
void rbt_win_set_deletenotes_cb(onDeleteNotes *arg);
void rbt_win_set_deviceip_cb(onDeviceIp *arg);
void rbt_win_set_oidpageinfo_cb(onOidPageInfo *arg);
void rbt_wib_set_currentwritingnum_cb(onCurrentWritingNum *arg);
void rbt_win_set_openmodule_cb(onOpenModule *arg);
void rbt_win_set_fbmsgresult_cb(onFBSetMessage *arg);
void rbt_win_set_downloadwavfile_cb(onDownloadWAVFile *arg);
void rbt_win_set_uploadwavfile_cb(onUploadWAVFile *arg);
void rbt_win_set_page_sensor_cb(onPageSensor *arg);

#pragma pack(1)
typedef struct _Init_Param
{
	char ip[32]; //����ip��Ĭ��Ϊ��
	int port;	//�����˿ڣ�6001
	int listenCount; //��������� Ĭ��60
	bool open;  //�Ƿ��ģ�飬 Ĭ�ϴ�
	bool optimize;	//�Ƿ�����Ż��ʼǣ�Ĭ�Ϲر�
	rbt_win_context* ctx; //������ָ��
	_Init_Param() :ip(""), port(6001), listenCount(60), open(true), optimize(false), ctx(nullptr) {}
}Init_Param;
#pragma pack()

#endif
