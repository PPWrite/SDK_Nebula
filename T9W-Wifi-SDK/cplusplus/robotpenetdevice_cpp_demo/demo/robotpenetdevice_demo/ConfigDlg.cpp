// ConfigDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg �Ի���

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


// CConfigDlg ��Ϣ�������


void CConfigDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_strSSID);
	GetDlgItem(IDC_EDIT2)->SetWindowText(m_strPwd);
	GetDlgItem(IDC_EDIT3)->SetWindowText(m_strStu);
	GetDlgItem(IDC_EDIT4)->SetWindowText(m_strSource);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
