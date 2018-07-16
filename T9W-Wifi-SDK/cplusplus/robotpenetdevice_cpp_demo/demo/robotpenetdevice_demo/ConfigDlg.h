#pragma once


// CConfigDlg �Ի���

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
