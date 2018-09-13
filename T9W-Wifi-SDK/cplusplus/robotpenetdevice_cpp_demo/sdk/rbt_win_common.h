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
};

//�豸���߻ص�
typedef void __stdcall onAccept(rbt_win_context* context, const char* pClientIpAddress);
//������ص�
typedef void __stdcall onErrorPacket(rbt_win_context* context);
//�ʼ����ݻص�
typedef void __stdcall onOriginData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up, unsigned char *buffer, int len);
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
//��������ص�
typedef void __stdcall onClearCanvas(rbt_win_context* context, const char* pmac);
//�Ż��ʼǻص�
typedef void __stdcall onOptimizeData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, float width, float speed);

void rbt_win_set_accept_cb(onAccept* arg);
void rbt_win_set_errorpacket_cb(onErrorPacket* arg);
void rbt_win_set_origindata_cb(onOriginData* arg);
void rbt_win_set_devicemac_cb(onDeviceMac* arg);
void rbt_win_set_devicename_cb(onDeviceName* arg);
void rbt_win_set_devicenameresult_cb(onDeviceNameResult* arg);
void rbt_win_set_devicekeypress_cb(onDeviceKeyPress* arg);
void rbt_win_set_devivedisconnect_cb(onDeviceDisConnect* arg);
void rbt_win_set_deviceshowpage_cb(onDeviceShowPage* arg);
void rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult* arg);
void rbt_win_set_error_cb(onError *arg);
void rbt_win_set_clearcanvas_cb(onClearCanvas *arg);
void rbt_win_set_optimizedata_cb(onOptimizeData *arg);

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
