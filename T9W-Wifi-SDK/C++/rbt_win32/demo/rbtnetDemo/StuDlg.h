#pragma once


// CStuDlg 对话框

class CStuDlg : public CDialog
{
	DECLARE_DYNAMIC(CStuDlg)

public:
	CStuDlg(const CString &strStu,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStuDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString getStu() { return m_strStu; }
private:
	CString m_strStu;
};
