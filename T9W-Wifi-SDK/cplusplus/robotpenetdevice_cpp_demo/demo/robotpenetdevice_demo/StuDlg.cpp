// StuDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "StuDlg.h"
#include "afxdialogex.h"


// CStuDlg 对话框

IMPLEMENT_DYNAMIC(CStuDlg, CDialog)

CStuDlg::CStuDlg(const CString &strStu, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_STUDLG, pParent)
	, m_strStu(strStu)
{

}

CStuDlg::~CStuDlg()
{
}

void CStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStuDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CStuDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStuDlg 消息处理程序


void CStuDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_STU)->GetWindowText(m_strStu);

	CDialog::OnOK();
}


BOOL CStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT_STU)->SetWindowText(m_strStu);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
