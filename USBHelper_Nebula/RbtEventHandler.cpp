#include "StdAfx.h"
#include "RbtEventHandler.h"


CRbtEventHandler::CRbtEventHandler(void)
{
}

CRbtEventHandler::~CRbtEventHandler(void)
{
}

void CRbtEventHandler::SetMsgReceiver(HWND hWnd)
{
	m_hMainWnd = hWnd;
}

//设备插拔事件
void CRbtEventHandler::onDeviceChanged(eDeviceStatus status,int pid)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_DEVICE_CHANGE), (WPARAM)status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_DEVICE_CHANGE, (LPARAM)&status);
	}
}
//设备插拔事件
void CRbtEventHandler::onDeviceChanged(eDeviceStatus status,eDeviceType type)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_DEVICE_CHANGE), (WPARAM)status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_DEVICE_CHANGE, (LPARAM)&status);
	}
}

//网关状态事件
void CRbtEventHandler::onGatewayStatus(eGatewayStatus status)	
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_GATEWAY_STATUS), (WPARAM)&status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_GATEWAY_STATUS, (LPARAM)&status);
	}
}
//node状态事件
void CRbtEventHandler::onNodeStatus(const NODE_STATUS &status)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_NODE_STATUS), (WPARAM)&status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_NODE_STATUS, (LPARAM)&status);
	}
}
//版本事件
void CRbtEventHandler::onDeviceInfo(const ST_DEVICE_INFO &info)	
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_GATEWAY_VERSION), (WPARAM)&info, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_GATEWAY_VERSION, (LPARAM)&info);
	}
}
//在线状态事件
void CRbtEventHandler::onOnlineStatus(uint8_t *status)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_ONLINE_STATUS), (WPARAM)status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_ONLINE_STATUS, (LPARAM)&status);
	}
}
//单选结束事件
void CRbtEventHandler::onExitVote(uint8_t *status)	
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_EXIT_VOTE), (WPARAM)status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_EXIT_VOTE, (LPARAM)&status);
	}
}
//多选结束事件
void CRbtEventHandler::onExitVoteMulit(const ST_OPTION_PACKET &packet)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_EXIT_VOTE_MULIT), (WPARAM)&packet, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_EXIT_VOTE_MULIT, (LPARAM)&packet);
	}
}
//大数据坐标数据事件
void CRbtEventHandler::onMassData(int index,const PEN_INFO &penInfo)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_MASS_DATA), (WPARAM)&index, (LPARAM)&penInfo);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_MASS_DATA, (LPARAM)&penInfo);
	}
}
//网关错误事件
void CRbtEventHandler::onGatewayError(eNebulaError error)	
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_GATEWAY_ERROR), (WPARAM)&error, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_GATEWAY_ERROR, (LPARAM)&error);
	}
}
//设置设备结果事件
void CRbtEventHandler::onSetDeviceNum(int result,int customid, int classid, int deviceid)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SET_DEVICE_NUM), (WPARAM)status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SET_DEVICE_NUM, (LPARAM)&result);
	}
}
//升级进度事件
void CRbtEventHandler::onFirmwareData(int progress)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_FIRMWARE_DATA), (WPARAM)&progress, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_FIRMWARE_DATA, (LPARAM)&progress);
	}
}
//升级结果事件
void CRbtEventHandler::onRawResult(int result)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_RAW_RESULT), (WPARAM)&result, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_RAW_RESULT, (LPARAM)&result);
	}
}
//重启事件
void CRbtEventHandler::onGatewayReboot()
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_GATEWAY_REBOOT), 0, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_GATEWAY_REBOOT, 0);
	}
}
//坐标数据事件
void CRbtEventHandler::onOriginalPacket(const PEN_INFO &penInfo)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_ORIGINAL_PACKET), (WPARAM)status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_ORIGINAL_PACKET, 0);
	}
}
//node模式事件
void CRbtEventHandler::onNodeMode(eNodeMode mode)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_NODE_MODE), (WPARAM)&mode, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_ORIGINAL_PACKET, (LPARAM)&mode);
	}
}
//设置rtc事件
void CRbtEventHandler::onSetRtc(int result)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SET_RTC), (WPARAM)&result, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SET_RTC, (LPARAM)&result);
	}
}
//按键按下事件
void CRbtEventHandler::onKeyPress(int result)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_KEY_PRESS), (WPARAM)&result, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_KEY_PRESS, (LPARAM)&result);
	}
}
//页面显示事件
void CRbtEventHandler::onShowPage(int count, int current)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SHOW_PAGE), (WPARAM)&count,(LPARAM)&current);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SHOW_PAGE, (LPARAM)&count);
	}
}
//离线笔记坐标数据事件
void CRbtEventHandler::onSyncPacket(const PEN_INFO &penInfo)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SYNC_PACKET), (WPARAM)&penInfo, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SYNC_PACKET, (LPARAM)&penInfo);
	}
}
//离线笔记开始
void CRbtEventHandler::onSyncBegin(int noteNum,const ST_RTC_INFO &rtcInfo)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SYNC_TRANS_BEGIN), 0, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SYNC_TRANS_BEGIN, 0);
	}
}
//离线笔记结束
void CRbtEventHandler::onSyncEnd(int result)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SYNC_TRANS_END), 0, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SYNC_TRANS_END, 0);
	}
}
//上报页码
void CRbtEventHandler::onMassShowPage(int index,int pageNo)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_PAGE_NO), (WPARAM)&pageNo, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SHOW_PAGE, 0);
	}
}
//抢答事件
void CRbtEventHandler::onVoteAnswer(int index,int answer)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_VOTE_ANSWER), 0, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_VOTE_ANSWER, 0);
	}
}
//////////////////////////////dongle//////////////////////
//Dongle状态事件
void CRbtEventHandler::onDongleStatus(eDongleStatus status,int mode)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_DONGLE_STATUS), (WPARAM)&status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_DONGLE_STATUS, 0);
	}
}
//Dongle版本事件
void CRbtEventHandler::onDongleVersion(const ST_VERSION &version)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_DONGLE_VERSION), (WPARAM)&version, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_DONGLE_VERSION, 0);
	}
}
//Dongle扫描事件
void CRbtEventHandler::onDongleScanRes(const ST_BLE_DEVICE &device)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_DONGLE_SCAN_RES), (WPARAM)&device, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_DONGLE_SCAN_RES, 0);
	}
}
//slave版本事件
void CRbtEventHandler::onSlaveVersion(eDeviceType type,const ST_VERSION &version)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SLAVE_VERSION), 0, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SLAVE_VERSION, 0);
	}
}
//slave状态事件
void CRbtEventHandler::onSlaveStatus(const NODE_STATUS &status)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SLAVE_STATUS), (WPARAM)&status, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SLAVE_STATUS, 0);
	}
}
//设置名称事件
void CRbtEventHandler::onSetName(int result)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SET_NAME), (WPARAM)&result, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SET_NAME, 0);
	}
}
//slave错误事件
void CRbtEventHandler::onSlaveError(eSlaveError error)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_SLAVE_ERROR), (WPARAM)&error, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_SLAVE_ERROR, 0);
	}
}

//笔记优化输出
void CRbtEventHandler::onOut(float x,float y,float width,int press,int status)
{
	if(m_hMainWnd != NULL)
	{
		//::PostMessage(m_hMainWnd, WM_MSGID(ROBOT_OPTIMIZE_PACKET), 0, 0);
		::PostMessage(m_hMainWnd, WM_RBTEVENT, ROBOT_OPTIMIZE_PACKET, 0);
	}
}