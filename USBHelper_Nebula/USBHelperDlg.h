
// USBHelperDlg.h : 头文件
//

#pragma once
#include <vector>
#include <map>
#include "DrawDlg.h"
#include <queue>
#include "UpdateDlg.h"
#include "RbtEventHandler.h"

using namespace std;

//#define MAX_NOTE 256
#define MAX_NOTE 65536

typedef struct sync_info
{
	std::vector<PEN_INFO> vecPenInfo;
}SYNC_INFO;

typedef struct rtc_info
{
	ST_RTC_INFO rtc;
	int useTimes;
}RTC_INFO;

typedef struct rtc_note_info
{
	std::vector<RTC_INFO> vecRtcInfo;
}RTC_NOTE_INFO;

typedef struct device_mac
{
	unsigned char mac[6];
}DEVICE_MAC;

// CUSBHelperDlg 对话框
class CUSBHelperDlg : public CDialogEx , CRbtEventHandler
{
	// 构造
public:
	CUSBHelperDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_USBHELPER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3Open();

	afx_msg void OnDestroy();
	void resetDevice();			//--by zlp 2016/9/26
public:
	afx_msg LRESULT OnClick(WPARAM wParam, LPARAM lParam);
	void CreateChart(int nHStart);
public:
	afx_msg void OnBnClickedButtonVote();
	afx_msg void OnBnClickedButtonVoteOff();
	afx_msg void OnBnClickedButtonVoteClear();	
	afx_msg void OnBnClickedButton3Ms();
	afx_msg void OnBnClickedButton3MsOff();
	afx_msg void OnBnClickedButtonStatus();
	void resetUI();
	afx_msg void OnBnClickedButtonMsClear();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3Set();
private:
	std::vector<CDrawDlg*> m_list;
	CUpdateDlg *m_pDlg;
	eDeviceType m_nDeviceType;
private:
	CRITICAL_SECTION m_sectionLock;
	std::queue<ROBOT_REPORT> m_queueData;
	bool m_bRun;
	HANDLE m_hEvent[2];
private:
	CString m_strFileMcu;
	CString m_strFileBle;
	ST_VERSION m_version;
private:
	ST_DEVICE_INFO m_lastInfo;
	int m_nLastStatus;
	int m_nLastMode;
	int m_nNoteNum;
	//dongle升级类型
	int m_nDongleUpdateType;
	int m_nSlaveType;
	bool m_bMouse;

	eDeviceMode m_DeviceMode;
	bool m_bActive;
public:
	afx_msg void OnBnClickedButton3Update();
	afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateWindow(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton3Show();
	ST_VERSION CString2Version(CString strVersion);
	BOOL IsItemExist(CString strName);
	void InitListCtrl();
	void AddList();
	void GetTime();
	void AddSlaveList(int nNum,unsigned char *name,unsigned char *mac);
	void openT7E();
	bool SalveExist(CString name,CString mac);
protected:
	static UINT ThreadProc(LPVOID lpParam);
	void ProcessMassData();
	static void CALLBACK getUsbData(const unsigned char *pData,int len,void *pContext);
	void setUsbData(const unsigned char *pData);
	void parseRobotReport(const ROBOT_REPORT &report);
	void parseDongleReport(const ROBOT_REPORT &report);
public:
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonScanStop();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonSetName();
	afx_msg void OnBnClickedButtonSyncStop();
	afx_msg void OnBnClickedButtonSyncStart();
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonSyncOpen();
	CWBDlg *m_pWBDlg;
	afx_msg void OnBnClickedButton3Reset();

	//afx_msg LRESULT OnRobotEvent(WPARAM wParam, LPARAM lParam);

	int m_nIndexCount;
	afx_msg void OnBnClickedButtonAdjust();
	static void DeleteDir(CString str);

	int m_nCurNoteNum;
	afx_msg UINT OnPowerBroadcast(UINT nPowerEvent, UINT nEventData);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	std::vector<DEVICE_MAC> m_vecMac;
	afx_msg void OnBnClickedButtonGetId();
	afx_msg void OnBnClickedButton3Reset2();

	BOOL m_bConnect;
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonSet2();
	afx_msg void OnBnClickedButtonSet3();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonSet4();
	afx_msg void OnBnClickedButtonSet5();
	afx_msg void OnBnClickedButtonSet6();
	afx_msg void OnCbnSelchangeComboPen();
	afx_msg void OnBnClickedButtonSerPen();
	std::map<int,RTC_NOTE_INFO> mapRtc;
	std::map<int,SYNC_INFO> mapSyncInfo;
	static CString GetSubject(int subject);
};
