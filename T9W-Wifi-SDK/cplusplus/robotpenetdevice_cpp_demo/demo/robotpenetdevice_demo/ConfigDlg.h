#pragma once


// CConfigDlg 对话框

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	int getType();
	void getWifiConfig(CString &strSSID, CString &strPwd);
	void getNetConfig(bool &bTcp, CString &strIP);
private:
	CString m_strSSID, m_strPwd, m_strIP;
	bool m_bTcp;
public:
	virtual BOOL OnInitDialog();
	bool GetLocalAddress();
	afx_msg void OnNcDestroy();
};
