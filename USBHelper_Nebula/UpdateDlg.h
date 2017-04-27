#pragma once


// CUpdateDlg 对话框
#define WM_UPDATE			WM_USER + 101
#define WM_PROCESS			WM_USER + 102
#define WM_UPDATE_WINDOW	WM_USER + 103

enum
{
	START_UPADTE_GATEWAY = 0,
	START_UPADTE_NODE,
	START_UPADTE_DONGLE,
	STOP_UPDATE_GATEWAY,
	STOP_UPDATE_NODE,
	STOP_UPDATE_DONGLE,
	SET_VERSION,
	SET_MCU,
	SET_BLE,
};

class CUpdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateDlg();

// 对话框数据
	enum { IDD = IDD_UPDATEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4Update();
	afx_msg void OnBnClickedButtonBrower();
	afx_msg void OnBnClickedButtonBrower2();

	void SetVersion(const CString &strVersion);
	afx_msg void OnNcDestroy();

	afx_msg LRESULT OnProcess(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton4Stop();
	PCHAR WideStrToMultiStr (PWCHAR WideStr);
	ST_VERSION CString2Version(CString strVersion);
	bool IsNeedUpdate(const ST_VERSION &versionWeb,const ST_VERSION &versionDev);
	void SetUpgradeType(int nDeviceType);
	void ResetUI();
	ST_VERSION m_version;
private:
	int m_nDeviceType;
	CString m_strDongleVersion;
public:
	afx_msg void OnCbnSelchangeComboType();
};
