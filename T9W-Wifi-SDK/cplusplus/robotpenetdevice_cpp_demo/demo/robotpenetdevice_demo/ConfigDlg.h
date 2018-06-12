#pragma once


// CConfigDlg �Ի���

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(const CString &strSSID, const CString &strPwd, const CString &strSource,CWnd* pParent = NULL);   // ��׼���캯��
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
	void getConfig(CString &strSSID, CString &strPwd, CString &strSource);
private:
	CString m_strSSID, m_strPwd, m_strSource;
public:
	virtual BOOL OnInitDialog();
};
