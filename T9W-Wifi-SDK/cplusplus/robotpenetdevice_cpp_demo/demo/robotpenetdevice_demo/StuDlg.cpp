// StuDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "StuDlg.h"
#include "afxdialogex.h"


// CStuDlg �Ի���

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


// CStuDlg ��Ϣ�������


void CStuDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_STU)->GetWindowText(m_strStu);

	CDialog::OnOK();
}


BOOL CStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT_STU)->SetWindowText(m_strStu);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
