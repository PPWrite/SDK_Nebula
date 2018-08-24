// ConfigDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg 对话框

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


// CConfigDlg 消息处理程序


void CConfigDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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

	// TODO:  在此添加额外的初始化
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
				  // 异常: OCX 属性页应返回 FALSE
}

bool CConfigDlg::GetLocalAddress()
{
	CComboBox *pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_IP));
	if (pComboBox == NULL)
		return false;
	pComboBox->ResetContent();
	std::string strAddress;
	int nCardNo = 1;
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = NULL;
	PIP_ADAPTER_INFO pIpAdapterInfoEx = NULL;
	pIpAdapterInfo = new IP_ADAPTER_INFO();
	pIpAdapterInfoEx = pIpAdapterInfo;

	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//记录网卡数量
	int netCardNum = 0;
	//记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		if (NULL != pIpAdapterInfo) {
			delete pIpAdapterInfo;
			pIpAdapterInfo = NULL;
			pIpAdapterInfoEx = NULL;
		}

		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		pIpAdapterInfoEx = pIpAdapterInfo;
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}

	if (ERROR_SUCCESS == nRel)
	{
		USES_CONVERSION;
		//输出网卡信息
		//可能有多网卡,因此通过循环去判断
		while (pIpAdapterInfo)
		{
			//可能网卡有多IP,因此通过循环去判断
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
			strAddress = pIpAddrString->IpAddress.String;
			// 需要注意的是有时可能获取的IP地址是0.0.0.0，这时需要过滤掉
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

	// TODO: 在此处添加消息处理程序代码
	delete this;
}
