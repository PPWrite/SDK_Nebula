#pragma once

#include "include/RobotUsbWrapper.h"

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
	//设备插拔事件
	virtual void onDeviceChanged(eDeviceStatus status,const char *szName,int pid);
	//网关状态事件
	virtual void onGatewayStatus(eGatewayStatus status);
	//node状态事件
	virtual void onNodeStatus(const NODE_STATUS &status);
	//版本事件
	virtual void onDeviceInfo(const ST_DEVICE_INFO &info);
	//在线状态事件
	virtual void onOnlineStatus(uint8_t *status);
	//单选结束事件
	virtual void onExitVote(uint8_t *status);
	//多选结束事件
	virtual void onExitVoteMulit(const ST_OPTION_PACKET &packet);
	//大数据坐标数据事件
	virtual void onMassData(int index,const PEN_INFO &penInfo);
	//网关错误事件
	virtual void onGatewayError(eNebulaError error);
	//设置设备结果事件
	virtual void onSetDeviceNum(int result,int customid, int classid, int deviceid);
	//升级进度事件
	virtual void onFirmwareData(int progress);
	//升级结果事件
	virtual void onRawResult(int result);
	//重启事件
	virtual void onGatewayReboot();
	//坐标数据事件
	virtual void onOriginalPacket(const PEN_INFO &penInfo);
	//node模式事件
	virtual void onNodeMode(eNodeMode mode);
	//设置rtc事件
	virtual void onSetRtc(int result);
	//按键按下事件
	virtual void onKeyPress(int result);
	//页面显示事件
	virtual void onShowPage(int count, int current);
	//离线笔记坐标数据事件
	virtual void onSyncPacket(const PEN_INFO &penInfo);
	//离线笔记开始
	virtual void onSyncBegin();
	//离线笔记结束
	virtual void onSyncEnd();
	//上报页码
	virtual void onPageNo(int pageNo);
	//抢答事件
	virtual void onVoteAnswer(int index,int answer);
	//////////////////////////////dongle//////////////////////
	//Dongle状态事件
	virtual void onDongleStatus(eDongleStatus status);
	//Dongle版本事件
	virtual void onDongleVersion(const ST_VERSION &version);
	//Dongle扫描事件
	virtual void onDongleScanRes(const ST_BLE_DEVICE &device);
	//slave版本事件
	virtual void onSlaveVersion(eDeviceType type,const ST_VERSION &version);
	//slave状态事件
	virtual void onSlaveStatus(eSlaveStatus status);
	//设置名称事件
	virtual void onSetName(int result);
	//slave错误事件
	virtual void onSlaveError(eSlaveError error);

	//笔记优化输出
	virtual void onOut(float x,float y,float width,int press,int status);

private:
	HWND		m_hMainWnd;
};

