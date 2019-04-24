// UpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USBHelper.h"
#include "UpdateDlg.h"
#include "afxdialogex.h"


// CUpdateDlg �Ի���

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


// CUpdateDlg ��Ϣ�������



void CUpdateDlg::OnBnClickedButton4Update()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel();
	if (nIndex == 5)
	{
		CString str;
		GetDlgItem(IDC_EDIT_MCU)->GetWindowText(str);
		this->GetParent()->SendMessage(WM_UPDATE,(WPARAM)str.GetBuffer(),SET_FONT);
		return;
	}

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

		if(m_nDeviceType == Gateway)
			this->GetParent()->SendMessage(WM_UPDATE,NULL,START_UPADTE_GATEWAY);
		else if(m_nDeviceType == Dongle)
		{
			int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel();
			this->GetParent()->SendMessage(WM_UPDATE,nIndex,START_UPADTE_DONGLE);
		}
		else
			this->GetParent()->SendMessage(WM_UPDATE,NULL,START_UPADTE_NODE);

	}
	else
	{
		AfxMessageBox(_T("�̼��汾���ͣ�"));
	}
}

void CUpdateDlg::OnBnClickedButtonBrower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = _T("Bin Files(*.bin)|*.bin|All Files(*.*)|*.*||");  
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,NULL);  

	if(dlg.DoModal() == IDOK)  
	{
		CString strFileName = dlg.GetFileName();
		int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel();
		if (nIndex == 5)
		{
			GetDlgItem(IDC_EDIT_MCU)->SetWindowText(dlg.GetPathName());
			return;
		}

		if(strFileName.MakeLower().Find(_T("mcu")) < 0)
		{
			AfxMessageBox(_T("�̼����Ͳ�ƥ�䣡"));
			return;
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
				AfxMessageBox(_T("�ļ���ʽ��ƥ�䣡"));
		}
		else
		{
			AfxMessageBox(_T("�ļ���ʽ��ƥ�䣡"));
		}
	}  
}

void CUpdateDlg::OnBnClickedButtonBrower2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = _T("Bin Files(*.bin)|*.bin|All Files(*.*)|*.*||");  
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,NULL);  

	if(dlg.DoModal() == IDOK)  
	{  
		CString strFileName = dlg.GetFileName();

		if(strFileName.MakeLower().Find(_T("ble")) < 0)
		{
			AfxMessageBox(_T("�̼����Ͳ�ƥ�䣡"));
			return;
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
			else if(sArrayVersion.GetCount() == 4)
			{
				m_version.version = atoi(WideCharToMultichar(sArrayVersion[0].GetBuffer()).c_str());
				m_version.version2 = atoi(WideCharToMultichar(sArrayVersion[1].GetBuffer()).c_str());
				m_version.version3 = atoi(WideCharToMultichar(sArrayVersion[2].GetBuffer()).c_str());
				m_version.version4 = atoi(WideCharToMultichar(sArrayVersion[3].GetBuffer()).c_str());

				CString str;
				str.Format(_T("%d.%d.%d.%d"),m_version.version,m_version.version2,m_version.version3,m_version.version4);
				GetDlgItem(IDC_EDIT_VERSION2)->SetWindowText(str);
			}
			else
				AfxMessageBox(_T("�ļ���ʽ��ƥ�䣡"));
		}
		else
		{
			AfxMessageBox(_T("�ļ���ʽ��ƥ�䣡"));
		}
	}  
}

void CUpdateDlg::SetVersion(const CString &strVersion)
{
	m_strVersion = strVersion;
	GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(strVersion);
	m_version = CString2Version(strVersion);
}

void CUpdateDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �ڴ˴������Ϣ����������
	delete this;
}

LRESULT CUpdateDlg::OnProcess(WPARAM wParam, LPARAM lParam)
{
	CString str(_T(""));

	switch(lParam)
	{
		break;
	case ROBOT_FIRMWARE_DATA:
		{
			((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetPos(wParam);
			str.Format(_T("���ȣ�%d%%"),wParam);
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetRange(0,100);

	CComboBox *pCombobox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	if (NULL == pCombobox)
		return FALSE;
	pCombobox->InsertString(0,_T("BLE"));
	pCombobox->InsertString(1,_T("MCU"));
	pCombobox->InsertString(2,_T("SLAVE"));
	pCombobox->InsertString(3,_T("ģ��"));
	pCombobox->InsertString(4,_T("All"));
	pCombobox->InsertString(5,_T("�ֿ�"));
	pCombobox->SetCurSel(1);

	OnCbnSelchangeComboType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CUpdateDlg::OnBnClickedButton4Stop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_nDeviceType == Gateway)
		this->GetParent()->SendMessage(WM_UPDATE,NULL,STOP_UPDATE_GATEWAY);
	else if (m_nDeviceType == Dongle)
		this->GetParent()->SendMessage(WM_UPDATE,NULL,STOP_UPDATE_DONGLE);
	else
		this->GetParent()->SendMessage(WM_UPDATE,NULL,STOP_UPDATE_NODE);

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
	bool bNode = (m_nDeviceType == T8A || m_nDeviceType == T9A || m_nDeviceType == X8 || m_nDeviceType == T8B ||m_nDeviceType == T9B_YD 
		|| m_nDeviceType == X8E_A5 || m_nDeviceType == T8C || m_nDeviceType == T9W || m_nDeviceType == T9W_TY || T9B_YD2 == m_nDeviceType
		|| T9W_QX == m_nDeviceType || T9W_YJ == m_nDeviceType || T9W_WX == m_nDeviceType || m_nDeviceType == T8B_DH2 || T9W_B_KZ == m_nDeviceType
		|| C5 == m_nDeviceType || T9B == m_nDeviceType || T9B_ZXB == m_nDeviceType || T8B_D2 == m_nDeviceType || m_nDeviceType == X9 
		|| m_nDeviceType == T9W_H || m_nDeviceType == T10) ? TRUE : FALSE;
	GetDlgItem(IDC_STATIC_BLE)->ShowWindow(bNode);
	GetDlgItem(IDC_EDIT_BT)->ShowWindow(bNode);
	GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(bNode);

	if (Dongle == m_nDeviceType)
	{
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_TYPE)->ShowWindow(TRUE);
		//GetDlgItem(IDC_COMBO_TYPE)->ShowWindow(FALSE);
	}
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel();

	if (nIndex == 0 || nIndex == 2) //ble or slave
	{
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MCU)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_BROWER)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(SW_SHOW);
	}
	else if (nIndex == 4)
	{
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MCU)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_BROWER)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_BLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(SW_SHOW);
	}
	else if (nIndex == 1 || nIndex == 3) //mcu or ģ��
	{
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MCU)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_BROWER)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_BLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_BROWER2)->ShowWindow(SW_HIDE);
	}
	else  if (nIndex == 5)
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VERSION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VERSION2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MCU)->ShowWindow(SW_HIDE);

	}

	if (nIndex == 3)
	{
		GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(_T("0.0.0.0"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(m_strVersion);
	}
}

void CUpdateDlg::AutoSetPath()
{
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(1);
	OnCbnSelchangeComboType();

	CString strFilePath;
	GetPrivateProfileString(_T("General"),_T("Path"),_T(""),strFilePath.GetBuffer(MAX_PATH),MAX_PATH,GetAppPath() + _T("\\USBHelper.ini"));

	CString strFileName = strFilePath;
	CFileFind ff;
	BOOL find = ff.FindFile(strFilePath);
	if (find)
	{
		ff.FindNextFile();
		strFileName = ff.GetFileName();
	}


	if(strFileName.MakeLower().Find(_T("mcu")) < 0)
	{
		AfxMessageBox(_T("�̼����Ͳ�ƥ�䣡"));
		return;
	}

	GetDlgItem(IDC_EDIT_MCU)->SetWindowText(strFilePath);
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
			AfxMessageBox(_T("�ļ���ʽ��ƥ�䣡"));
	}
	else
	{
		AfxMessageBox(_T("�ļ���ʽ��ƥ�䣡"));
	}
}
