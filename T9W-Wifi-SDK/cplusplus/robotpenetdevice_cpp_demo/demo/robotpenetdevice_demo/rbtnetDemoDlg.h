
// rbtnetDemoDlg.h : 头文件
//

#pragma once
#include <map>
#include <queue>
#include "rbt_win.h"
#include "ConfigDlg.h"

class CDrawDlg;

#define WM_RCV_ACCEPT (WM_USER + 100)
#define WM_RCV_MAC (WM_USER + 101)
#define WM_RCV_NAME (WM_USER + 102)
#define WM_SHOW_PAGE (WM_USER + 103)
#define WM_SHOW_ERROR (WM_USER + 104)
#define WM_DISCONNECT (WM_USER + 105)
#define WM_RCV_TYPE (WM_USER + 106)
#define WM_DEL_TYPE (WM_USER + 107)

struct _Mass_Data
{
	CString strMac;
	PEN_INFO data;
};
// CrbtnetDemoDlg 对话框
class CrbtnetDemoDlg : public CDialogEx
{
// 构造
public:
	CrbtnetDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RBTNETDEMO_DIALOG };
#endif

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

	afx_msg LRESULT rcvAccept(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT rcvMac(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT rcvDeviceType(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT recvName(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT showPage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onShowError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onDisconnect(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartOrStop();
	afx_msg void OnNMDblclkListConnect(NMHDR *pNMHDR, LRESULT *pResult);

	static UINT ThreadProc(LPVOID lpParam);
	void ProcessMassData();
	void recvOriginData(const char* pMac, unsigned short us,
		unsigned short ux,
		unsigned short uy,
		unsigned short up);
	void deviceDisconnect(const char* pMac);
	void recvKeyPress(const char* pMac, void* keyValue);
	void recvDeviceAnswerResult(const char* pMac, int resID, unsigned char* pResult, int nSize);
	void recvDeviceShowpage(const char* pMac, int nNoteId, int nPageId);
	void recvNameResult(const char* pMac, int res, const char* pName);
	void recvKeyAnswer(const char* pMac, int key);
private:
	void initListControl();
	void initCbFunction();

private:
	std::map<CString, CDrawDlg*> m_device2draw;
	CRITICAL_SECTION m_sectionLock;
	std::queue<_Mass_Data> m_queueData;
	bool m_bRun;
	HANDLE m_hEvent[2];
	CConfigDlg *m_pDlg;
public:
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnNMRClickListConnect(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSettingStu();
	afx_msg void OnBnClickedButtonSwitch();

	static void CALLBACK onAccept(rbt_win_context* context, const char* pClientIpAddress);
	static void CALLBACK onErrorPacket(rbt_win_context* context);
	static void CALLBACK onOriginData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up, unsigned char *buffer, int len);
	static void CALLBACK onDeviceMac(rbt_win_context* context, const char* pMac);
	static void CALLBACK onDeviceName(rbt_win_context* context, const char* pMac, const char* pName);
	static void CALLBACK onDeviceNameResult(rbt_win_context* context, const char* pMac, int res, const char* pName);
	static void CALLBACK onDeviceDisConnect(rbt_win_context* context, const char* pMac);
	static void CALLBACK onDeviceKeyPress(rbt_win_context* context, const char* pMac, keyPressEnum keyValue);
	static void CALLBACK onDeviceAnswerResult(rbt_win_context* context, const char* pMac, int resID, unsigned char* pResult, int nSize);
	static void CALLBACK onDeviceShowPage(rbt_win_context* context, const char* pMac, int nNoteId, int nPageId, int nPageInfo);
	static void CALLBACK onError(rbt_win_context* context, const char* pMac, int cmd, const char *msg);
	static void CALLBACK onCanvasID(rbt_win_context* context, const char* pMac, int type, int canvasID);
	static void CALLBACK onOptimizeData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, float width, float speed);
	static void CALLBACK onDeviceType(rbt_win_context* context, const char* pMac, int type);
	static void CALLBACK onKeyAnswer(rbt_win_context* context, const char* pMac, int key);
	static void CALLBACK onDeleteNotes(rbt_win_context* context, const char* pMac, int result);

	bool GetLocalAddress();
	afx_msg void OnBnClickedOpenModule();
	afx_msg void OnBnClickedCloseModule();
	afx_msg void OnBnClickedButtonStartAnswer();
	afx_msg void OnBnClickedButtonStopAnswer();
	afx_msg void OnBnClickedButtonEndAnswer();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSetFreq();
	afx_msg void OnBnClickedButtonClear();

	CString GetAnswerResult(int resID, unsigned char* pResult, int nSize);
	afx_msg void OnCbnSelchangeCombo2();

	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonExport();

	void SetItemName(const CString &strMac,const CString &strName);

	void ShowOnlineCount();
	afx_msg void OnBnClickedButtonPoint();
	afx_msg void OnBnClickedButtonCvs();
	afx_msg void OnBnClickedButtonSetKeepalive();
	afx_msg void OnNMClickListConnect(NMHDR *pNMHDR, LRESULT *pResult);

	int m_nCurrentSubject = 0;
	CString getValue(int key);
	CString Asc(CString strData);
	void rcvMac(const char* pMac);
	afx_msg void OnBnClickedButtonDelNotes();
};
