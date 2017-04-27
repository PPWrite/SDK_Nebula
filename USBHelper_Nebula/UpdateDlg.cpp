// UpdateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "USBHelper.h"
#include "UpdateDlg.h"
#include "afxdialogex.h"


// CUpdateDlg 对话框

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialog)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
	, m_nDeviceType(FALSE)
{

}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON4_UPDATE, &CUpdateDlg::OnBnClickedButton4Update)
	ON_BN_CLICKED(IDC_BUTTON_BROWER, &CUpdateDlg::OnBnClickedButtonBrower)
	ON_BN_CLICKED(IDC_BUTTON_BROWER2, &CUpdateDlg::OnBnClickedButtonBrower2)
	ON_WM_NCDESTROY()
	ON_MESSAGE(WM_PROCESS, OnProcess)
	ON_BN_CLICKED(IDC_BUTTON4_STOP, &CUpdateDlg::OnBnClickedButton4Stop)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CUpdateDlg::OnCbnSelchangeComboType)
END_MESSAGE_MAP()


// CUpdateDlg 消息处理程序


void CUpdateDlg::OnBnClickedButton4Update()
{
	// TODO: 在此添加控件通知处理程序代码

	ST_VERSION versionDev,versionFile;
	CString str;
	GetDlgItem(IDC_EDIT_VERSION)->GetWindowText(str);
	versionDev = CString2Version(str);
	GetDlgItem(IDC_EDIT_VERSION2)->GetWindowText(str);
	versionFile = CString2Version(str);
	this->GetParent()->SendMessage(WM_UPDATE,(WPARAM)str.GetBuffer(),SET_VERSION);
	if (IsNeedUpdate(versionFile,versionDev))
	{
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetPos(0);
		GetDlgItem(IDC_EDIT_MCU)->GetWindowText(str);
		this->GetParent()->SendMessage(WM_UPDATE,(WPARAM)str.GetBuffer(),SET_MCU);
		GetDlgItem(IDC_EDIT_BT)->GetWindowText(str);
		this->GetParent()->SendMessage(WM_UPDATE,(WPARAM)str.GetBuffer(),SET_BLE);

		if(m_nDeviceType == NODE)
			this->GetParent()->SendMessage(WM_UPDATE,NULL,START_UPADTE_NODE);
		else if(m_nDeviceType == GATEWAY)
			this->GetParent()->SendMessage(WM_UPDATE,NULL,START_UPADTE_GATEWAY);
		else
		{
			int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel();
			this->GetParent()->SendMessage(WM_UPDATE,nIndex,START_UPADTE_DONGLE);
		}
	}
}

void CUpdateDlg::OnBnClickedButtonBrower()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilter = _T("Bin Files(*.bin)|*.bin|All Files(*.*)|*.*||");  
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,NULL);  

	if(dlg.DoModal() == IDOK)  
	{
		CString strFileName = dlg.GetFileName();
		if (m_nDeviceType == NODE)
		{
			if(strFileName.MakeLower().Find(_T("mcu")) < 0)
			{
				AfxMessageBox(_T("固件类型不匹配！"));
				return;
			}
		}

		GetDlgItem(IDC_EDIT_MCU)->SetWindowText(dlg.GetPathName());
		CStringArray sArray;
		SplitFields(strFileName.Left(strFileName.GetLength()-4),sArray,_T("_"));

		if(sArray.GetCount() == 3)
		{
			CStringArray sArrayVersion;
			SplitFields(sArray[2],sArrayVersion,_T("."));

			if(sArrayVersion.GetCount() == 2)
			{
				m_version.version = atoi(WideCharToMultichar(sArrayVersion[0].GetBuffer()).c_str());
				m_version.version2 = atoi(WideCharToMultichar(sArrayVersion[1].GetBuffer()).c_str());

				CString str;
				str.Format(_T("%d.%d.%d.%d"),m_version.version,m_version.version2,m_version.version3,m_version.version4);
				GetDlgItem(IDC_EDIT_VERSION2)->SetWindowText(str);
			}
			else if(sArrayVersion.GetCount() == 4)
			{
				CString str;
				str.Format(_T("%s.%s.%s.%s"),sArrayVersion[0],sArrayVersion[1],sArrayVersion[2],sArrayVersion[3]);
				GetDlgItem(IDC_EDIT_VERSION2)->SetWindowText(str);
			}
			else
				AfxMessageBox(_T("文件格式不匹配！"));
		}
		else
		{
			AfxMessageBox(_T("文件格式不匹配！"));
		}
	}  
}

void CUpdateDlg::OnBnClickedButtonBrower2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilter = _T("Bin Files(*.bin)|*.bin|All Files(*.*)|*.*||");  
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,NULL);  

	if(dlg.DoModal() == IDOK)  
	{  
		CString strFileName = dlg.GetFileName();
		if (m_nDeviceType == NODE)
		{
			if(strFileName.MakeLower().Find(_T("ble")) < 0)
			{
				AfxMessageBox(_T("固件类型不匹配！"));
				return;
			}
		}

		GetDlgItem(IDC_EDIT_BT)->SetWindowText(dlg.GetPathName());
		CStringArray sArray;
		SplitFields(strFileName.Left(strFileName.GetLength()-4),sArray,_T("_"));

		if(sArray.GetCount() == 3)
		{
			CStringArray sArrayVersion;
			SplitFields(sArray[2],sArrayVersion,_T("."));

			if(sArrayVersion.GetCount() == 2)
			{
				m_version.version3 = atoi(WideCharToMultichar(sArrayVersion[0].GetBuffer()).c_str());
				m_version.version4 = atoi(WideCharToMultichar(sArrayVersion[1].GetBuffer()).c_str());

				CString str;
				str.Format(_T("%d.%d.%d.%d"),m_version.version,m_version.version2,m_version.version3,m_version.version4);
				GetDlgItem(IDC_EDIT_VERSION2)->SetWindowText(str);
			}
			else
				AfxMessageBox(_T("文件格式不匹配！"));
		}
		else
		{
			AfxMessageBox(_T("文件格式不匹配！"));
		}
	}  
}

void CUpdateDlg::SetVersion(const CString &strVersion)
{
	if (m_nDeviceType == DONGLE)
	{
		m_strDongleVersion = strVersion;
		OnCbnSelchangeComboType();
	}
	else
	{
		GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(strVersion);
		m_version = CString2Version(strVersion);
	}
}


void CUpdateDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete this;
}

LRESULT CUpdateDlg::OnProcess(WPARAM wParam, LPARAM lParam)
{
	CString str(_T(""));

	switch(lParam)
	{
		break;
	case ROBOT_DONGLE_FIRMWARE_DATA:
	case ROBOT_FIRMWARE_DATA:
		{
			((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetPos(wParam);
			str.Format(_T("进度：%d%%"),wParam);
		}
		break;
	default:
		break;
	}
	GetDlgItem(IDC_STATIC_UPDATE_INFO)->SetWindowText(str);

	return 0;
}

BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetRange(0,100);

	CComboBox *pCombobox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	if (NULL == pCombobox)
		return FALSE;
	pCombobox->InsertString(0,_T("BLE"));
	pCombobox->InsertString(1,_T("MCU"));
	pCombobox->InsertString(2,_T("SLAVE"));
	pCombobox->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUpdateDlg::OnBnClickedButton4Stop()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nDeviceType == NODE)
		this->GetParent()->SendMessage(WM_UPDATE,NULL,STOP_UPDATE_NODE);
	else if(m_nDeviceType == GATEWAY)
		this->GetParent()->SendMessage(WM_UPDATE,NULL,STOP_UPDATE_GATEWAY);
	else
		this->GetParent()->SendMessage(WM_UPDATE,NULL,STOP_UPDATE_DONGLE);

}

PCHAR CUpdateDlg::WideStrToMultiStr (PWCHAR WideStr)
{
	ULONG nBytes;
	PCHAR MultiStr;

	// Get the length of the converted string
	//
	nBytes = WideCharToMultiByte(
		CP_ACP,
		0,
		WideStr,
		-1,
		NULL,
		0,
		NULL,
		NULL);

	if (nBytes == 0)
	{
		return NULL;
	}

	// Allocate space to hold the converted string
	//
	MultiStr = (PCHAR)ALLOC(nBytes);

	if (MultiStr == NULL)
	{
		return NULL;
	}

	// Convert the string
	//
	nBytes = WideCharToMultiByte(
		CP_ACP,
		0,
		WideStr,
		-1,
		MultiStr,
		nBytes,
		NULL,
		NULL);

	if (nBytes == 0)
	{
		FREE(MultiStr);
		return NULL;
	}

	return MultiStr;
}

ST_VERSION CUpdateDlg::CString2Version(CString strVersion)
{
	ST_VERSION version = {0};
	CStringArray sArray;
	SplitFields(strVersion,sArray,_T("."));

	if(sArray.GetCount() == 4)
	{
		version.version = atoi(WideStrToMultiStr(sArray[0].GetBuffer()));
		version.version2 = atoi(WideStrToMultiStr(sArray[1].GetBuffer()));
		version.version3 = atoi(WideStrToMultiStr(sArray[2].GetBuffer()));
		version.version4 = atoi(WideStrToMultiStr(sArray[3].GetBuffer()));
	}
	return version;
}

bool CUpdateDlg::IsNeedUpdate(const ST_VERSION &versionWeb,const ST_VERSION &versionDev)
{
	if( versionWeb.version*10 + versionWeb.version2 > versionDev.version*10 + versionDev.version2)
		return true;
	if( versionWeb.version*10 + versionWeb.version2 == versionDev.version*10 + versionDev.version2)
	{
		if( versionWeb.version3*10 + versionWeb.version4 > versionDev.version3*10 + versionDev.version4)
			return true;
	}

	return false;
}

void CUpdateDlg::SetUpgradeType(int nDeviceType)
{
	m_nDeviceType = nDeviceType;
	bool bNode = (m_nDeviceType == NODE) ? TRUE : FALSE;
	GetDlgItem(IDC_STATIC_BLE)->ShowWindow(bNode);
	GetDlgItem(IDC_EDIT_BT)->ShowWindow(bNode);
	GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(bNode);

	if (m_nDeviceType == DONGLE)
	{
		GetDlgItem(IDC_COMBO_TYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(FALSE);
	}
	else
		GetDlgItem(IDC_COMBO_TYPE)->ShowWindow(FALSE);
}

void CUpdateDlg::ResetUI()
{
	GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_VERSION2)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_MCU)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_BT)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_UPDATE_INFO)->SetWindowText(_T(""));
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetPos(0);

	memset(&m_version,0,sizeof(m_version));
}

void CUpdateDlg::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel();

	CStringArray sArray;
	SplitFields(m_strDongleVersion,sArray,_T("_"));
	if (sArray.GetCount() != 2)
	{
		GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(_T(""));;
		return;
	}

	CString strVersion = _T("");
	if (nIndex == 0 || nIndex == 1)
		strVersion = sArray[0];
	else
		strVersion = sArray[1];

	GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(strVersion);
	m_version = CString2Version(strVersion);
	if (nIndex == 1 )
	{
		GetDlgItem(IDC_EDIT_MCU)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_BROWER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BLE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_BT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MCU)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_BROWER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BLE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_BT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(SW_HIDE);
	}
}
