#pragma once


// CSettingDlg 对话框

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(const CString &strCustom,const CString &strClass,const CString &strDevice,BOOL bNode = false,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CString m_strCustom;
	CString m_strClass;
	CString m_strDevice;
	BOOL m_bNode;
public:
	afx_msg void OnBnClickedOk();
	void GetSettingInfo(CString &strCustom,CString &strClass,CString &strDevice);
};
