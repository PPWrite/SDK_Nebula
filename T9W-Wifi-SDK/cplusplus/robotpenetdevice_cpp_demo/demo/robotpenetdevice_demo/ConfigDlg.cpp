// ConfigDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg �Ի���

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CONFIGDLG, pParent)
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
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// CConfigDlg ��Ϣ�������


void CConfigDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_strSSID);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_strPwd);
	GetDlgItem(IDC_COMBO_IP)->GetWindowText(m_strIP);

	m_bTcp = (((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel() == 0);

	CDialog::OnOK();
}

void CConfigDlg::getWifiConfig(CString &strSSID, CString &strPwd)
{
	strSSID = m_strSSID;
	strPwd = m_strPwd;
}

void CConfigDlg::getNetConfig(bool &bTcp, CString &strIP)
{
	bTcp = m_bTcp;
	strIP = m_strIP;
}


BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_strSSID);
	GetDlgItem(IDC_EDIT2)->SetWindowText(m_strPwd);
	GetDlgItem(IDC_EDIT4)->SetWindowText(m_strIP);

	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(0, _T("TCP"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(1, _T("MQTT"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(0);

	GetLocalAddress();

	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);

	GetDlgItem(IDC_EDIT1)->GetWindowText(m_strSSID);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_strPwd);
	GetDlgItem(IDC_COMBO_IP)->GetWindowText(m_strIP);

	m_bTcp = (((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel() == 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

bool CConfigDlg::GetLocalAddress()
{
	CComboBox *pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_IP));
	if (pComboBox == NULL)
		return false;
	pComboBox->ResetContent();
	std::string strAddress;
	int nCardNo = 1;
	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = NULL;
	PIP_ADAPTER_INFO pIpAdapterInfoEx = NULL;
	pIpAdapterInfo = new IP_ADAPTER_INFO();
	pIpAdapterInfoEx = pIpAdapterInfo;

	//�õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//��¼��������
	int netCardNum = 0;
	//��¼ÿ�������ϵ�IP��ַ����
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//�ͷ�ԭ�����ڴ�ռ�
		if (NULL != pIpAdapterInfo) {
			delete pIpAdapterInfo;
			pIpAdapterInfo = NULL;
			pIpAdapterInfoEx = NULL;
		}

		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		pIpAdapterInfoEx = pIpAdapterInfo;
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}

	if (ERROR_SUCCESS == nRel)
	{
		USES_CONVERSION;
		//���������Ϣ
		//�����ж�����,���ͨ��ѭ��ȥ�ж�
		while (pIpAdapterInfo)
		{
			//���������ж�IP,���ͨ��ѭ��ȥ�ж�
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
			strAddress = pIpAddrString->IpAddress.String;
			// ��Ҫע�������ʱ���ܻ�ȡ��IP��ַ��0.0.0.0����ʱ��Ҫ���˵�
			if (std::string("0.0.0.0") != strAddress)
			{
				pComboBox->AddString(A2W(strAddress.c_str()));
			}
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}

		if (pComboBox->GetCount() > 0)
		{
			pComboBox->SetCurSel(0);
		}
	}

	if (pIpAdapterInfoEx != NULL)
	{
		delete pIpAdapterInfoEx;
		pIpAdapterInfoEx = NULL;
	}
}

int CConfigDlg::getType()
{
	
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2))
	{
		return 3;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
	{
		return 1;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2))
	{
		return 2;
	}

	return 0;
}


void CConfigDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �ڴ˴������Ϣ����������
	delete this;
}
