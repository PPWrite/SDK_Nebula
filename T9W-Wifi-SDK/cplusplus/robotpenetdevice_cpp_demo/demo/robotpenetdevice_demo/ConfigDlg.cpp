// ConfigDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(const CString &strSSID, const CString &strPwd, const CString &strStu, const CString &strSource, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CONFIGDLG, pParent)
	, m_strSSID(strSSID)
	, m_strPwd(strPwd)
	, m_strStu(strStu)
	, m_strSource(strSource)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConfigDlg 消息处理程序


void CConfigDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_strSSID);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_strPwd);
	GetDlgItem(IDC_EDIT3)->GetWindowText(m_strStu);
	GetDlgItem(IDC_EDIT4)->GetWindowText(m_strSource);
	CDialog::OnOK();
}

void CConfigDlg::getConfig(CString &strSSID, CString &strPwd, CString &strStu, CString &strSource)
{
	strSSID = m_strSSID;
	strPwd = m_strPwd;
	strStu = m_strStu;
	strSource = m_strSource;
}


BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_strSSID);
	GetDlgItem(IDC_EDIT2)->SetWindowText(m_strPwd);
	GetDlgItem(IDC_EDIT3)->SetWindowText(m_strStu);
	GetDlgItem(IDC_EDIT4)->SetWindowText(m_strSource);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
