#pragma once


// CStuDlg �Ի���

class CStuDlg : public CDialog
{
	DECLARE_DYNAMIC(CStuDlg)

public:
	CStuDlg(const CString &strStu,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStuDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString getStu() { return m_strStu; }
private:
	CString m_strStu;
};
