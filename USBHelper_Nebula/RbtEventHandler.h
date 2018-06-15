#pragma once

#include "../SDK/include/RobotUsbWrapper.h"

#define WM_MSGID(code) (WM_USER+0x200+code)
#define WM_EVTID(code) (code-0x200-WM_USER)

#define WM_RBTEVENT			WM_USER + 1001

class CRbtEventHandler :
	public IRobotEventHandler
{
public:
	CRbtEventHandler(void);
	~CRbtEventHandler(void);

	void SetMsgReceiver(HWND hWnd = NULL);
	HWND GetMsgReceiver() {return m_hMainWnd;};
private:
	//�豸����¼�
	virtual void onDeviceChanged(eDeviceStatus status,int pid);
	//�豸����¼�
	virtual void onDeviceChanged(eDeviceStatus status,eDeviceType type);
	//����״̬�¼�
	virtual void onGatewayStatus(eGatewayStatus status);
	//node״̬�¼�
	virtual void onNodeStatus(const NODE_STATUS &status);
	//�汾�¼�
	virtual void onDeviceInfo(const ST_DEVICE_INFO &info);
	//����״̬�¼�
	virtual void onOnlineStatus(uint8_t *status);
	//��ѡ�����¼�
	virtual void onExitVote(uint8_t *status);
	//��ѡ�����¼�
	virtual void onExitVoteMulit(const ST_OPTION_PACKET &packet);
	//���������������¼�
	virtual void onMassData(int index,const PEN_INFO &penInfo);
	//���ش����¼�
	virtual void onGatewayError(eNebulaError error);
	//�����豸����¼�
	virtual void onSetDeviceNum(int result,int customid, int classid, int deviceid);
	//���������¼�
	virtual void onFirmwareData(int progress);
	//��������¼�
	virtual void onRawResult(int result);
	//�����¼�
	virtual void onGatewayReboot();
	//���������¼�
	virtual void onOriginalPacket(const PEN_INFO &penInfo);
	//nodeģʽ�¼�
	virtual void onNodeMode(eNodeMode mode);
	//����rtc�¼�
	virtual void onSetRtc(int result);
	//���������¼�
	virtual void onKeyPress(int result);
	//ҳ����ʾ�¼�
	virtual void onShowPage(int count, int current);
	//���߱ʼ����������¼�
	virtual void onSyncPacket(const PEN_INFO &penInfo);
	//���߱ʼǿ�ʼ
	virtual void onSyncBegin(int noteNum,const ST_RTC_INFO &rtcInfo);
	//���߱ʼǽ���
	virtual void onSyncEnd(int result);
	//�ϱ�ҳ��
	virtual void onMassShowPage(int index,int pageNo);
	//�����¼�
	virtual void onVoteAnswer(int index,int answer);
	//////////////////////////////dongle//////////////////////
	//Dongle״̬�¼�
	virtual void onDongleStatus(eDongleStatus status,int mode);
	//Dongle�汾�¼�
	virtual void onDongleVersion(const ST_VERSION &version);
	//Dongleɨ���¼�
	virtual void onDongleScanRes(const ST_BLE_DEVICE &device);
	//slave�汾�¼�
	virtual void onSlaveVersion(eDeviceType type,const ST_VERSION &version);
	//slave״̬�¼�
	virtual void onSlaveStatus(const NODE_STATUS &status);
	//���������¼�
	virtual void onSetName(int result);
	//slave�����¼�
	virtual void onSlaveError(eSlaveError error);

	//�ʼ��Ż����
	virtual void onOut(float x,float y,float width,int press,int status);

private:
	HWND		m_hMainWnd;
};

