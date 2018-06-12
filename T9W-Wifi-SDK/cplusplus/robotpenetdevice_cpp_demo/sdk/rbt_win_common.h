#ifndef _RBT_WIN_COMMOM_H_
#define _RBT_WIN_COMMOM_H_

typedef void rbt_win_context;
typedef unsigned short ushort;

enum sendCmdID
{
	startAnswer,
	endAnsewer,
};

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

typedef void CALLBACK onAccept(rbt_win_context* context, const char* pClientIpAddress );
typedef void CALLBACK onErrorPacket(rbt_win_context* context);
typedef void CALLBACK onOriginData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up);
typedef void CALLBACK onDeviceMac(rbt_win_context* context, const char* pMac);
typedef void CALLBACK onDeviceName(rbt_win_context* context, const char* pMac, const char* pName);
typedef void CALLBACK onDeviceNameResult(rbt_win_context* context, const char* pMac,int res,const char* pName);
typedef void CALLBACK onDeviceDisConnect(rbt_win_context* context, const char* pMac);
typedef void CALLBACK onDeviceKeyPress(rbt_win_context* context, const char* pMac, keyPressEnum keyValue);
typedef void CALLBACK onDeviceAnswerResult(rbt_win_context* context, const char* pMac, int resID, unsigned char* pResult, int nSize);
typedef void CALLBACK onDeviceShowPage(rbt_win_context* context, const char* pMac, int nNoteId, int nPageId);
typedef void CALLBACK onError(rbt_win_context* context, const char* pmac, int cmd, const char *msg);

void rbt_win_set_accept_cb( onAccept* arg);
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

typedef struct _Init_Param
{
	char* pIp;
	int port;
	int listenCount;
	rbt_win_context* ctx;
}Init_Param;

#endif
