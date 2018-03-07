
// RobotpenWifiDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotpenWifiDemo.h"
#include "RobotpenWifiDemoDlg.h"
#include "afxdialogex.h"
#include "WBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRobotpenWifiDemoDlg �Ի���




CRobotpenWifiDemoDlg::CRobotpenWifiDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRobotpenWifiDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRobotpenWifiDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRobotpenWifiDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CRobotpenWifiDemoDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_START, &CRobotpenWifiDemoDlg::OnBnClickedButtonStart)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRobotpenWifiDemoDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CRobotpenWifiDemoDlg ��Ϣ�������

BOOL CRobotpenWifiDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_pDlg = new CWBDlg;
	m_pDlg->Create(IDD_WBDLG,this);
	CRect rect;
	m_pDlg->GetClientRect(rect);
	m_pDlg->MoveWindow(230,20,rect.Width(),rect.Height());
	m_pDlg->ShowWindow(SW_SHOW);

	InitListCtrl();

	Init_Options opts = {mqtt_onConnectResult,mqtt_onPushJob,mqtt_onStartdAnswer,mqtt_onStopAnswer,mqtt_onFinishedAnswer,this};
	returnCode code = handle.init(&opts);
	if (eOk != code)
	{
		CString str;
		str.Format(_T("Init failed,ErrorCode:%s"),GetErrorMsg(code));
		AfxMessageBox(str);
	}

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRobotpenWifiDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRobotpenWifiDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRobotpenWifiDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRobotpenWifiDemoDlg::mqtt_onConnectResult(void* context, MqttConnect_Data* response)
{
	TRACE(_T("mqtt_onConnectResult\n"));
}

void CRobotpenWifiDemoDlg::mqtt_onPushJob(void* conect, std::string& strNoteKey, std::string& strTarget)
{
	TRACE(_T("mqtt_onPushJob\n"));
	CRobotpenWifiDemoDlg *pDlg = (CRobotpenWifiDemoDlg*)conect;
	if (pDlg)
	{
		pDlg->AddTarget(m2w(strTarget).c_str(),m2w(strNoteKey).c_str());
	}
}

void CRobotpenWifiDemoDlg::mqtt_onStartdAnswer(void* context)
{
	TRACE(_T("mqtt_onStartdAnswer\n"));
}

void CRobotpenWifiDemoDlg::mqtt_onStopAnswer(void* context)
{
	TRACE(_T("mqtt_onStopAnswer\n"));
}

void CRobotpenWifiDemoDlg::mqtt_onFinishedAnswer()
{
	TRACE(_T("mqtt_onFinishedAnswer\n"));
}

void CRobotpenWifiDemoDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST1));
	if (NULL == pListView)
		return;

	pListView->DeleteAllItems();

	returnCode code = handle.loginMqttServer();
	if (eOk != code)
	{
		CString str;
		str.Format(_T("loginMqttServer failed,ErrorCode:%s"),GetErrorMsg(code));
		AfxMessageBox(str);
		return;
	}

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

void CRobotpenWifiDemoDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	handle.disconnectMqttServer();
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}

void CRobotpenWifiDemoDlg::InitListCtrl()
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST1));
	if (NULL == pListView)
		return;

	pListView->InsertColumn(0, _T("Target"), LVCFMT_LEFT, 180);
	pListView->InsertColumn(1, _T("NoteKey"), LVCFMT_LEFT, 0);
	pListView->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );//������չ

}

void CRobotpenWifiDemoDlg::AddTarget(const CString &strTarget,const CString &strNoteKey)
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST1));
	if (NULL == pListView)
		return;

	int nIndex = pListView->GetItemCount();
	pListView->InsertItem(nIndex,strTarget);
	pListView->SetItemText(nIndex,1,strNoteKey);
}

void CRobotpenWifiDemoDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowItem();

	*pResult = 0;
}

void CRobotpenWifiDemoDlg::ShowItem()
{
	if (m_pDlg)
		m_pDlg->Clear();
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST1));
	if (NULL == pListView)
		return;
	POSITION pos = pListView->GetFirstSelectedItemPosition();
	if (pos == nullptr)
		return;

	int nItem = pListView->GetNextSelectedItem(pos);
	CString strTarget = pListView->GetItemText(nItem, 0);
	CString strNoteKey = pListView->GetItemText(nItem, 1);
	Trails_Data *trails = NULL;
	returnCode code = handle.getServerTrails(w2m(strNoteKey.GetBuffer(0)),&trails);
	if(eOk == code)
	{
		while(trails != NULL)
		{
			PEN_INFO info = {trails->ns,trails->nx,trails->ny,trails->np};
			if (m_pDlg)
				m_pDlg->onRecvData(info);

			trails = trails->next;
		}
	}
	else
	{
		CString str;
		str.Format(_T("getServerTrails failed,ErrorCode:%s"),GetErrorMsg(code));
		AfxMessageBox(str);
	}
}

CString CRobotpenWifiDemoDlg::GetErrorMsg(returnCode code)
{
	CString str(_T(""));
	switch(code)
	{
	case eOk:					str = _T("eOk");					break;
	case eFail:					str = _T("eFail");					break;
	case eActiveFail:			str = _T("eActiveFail");			break;
	case eLoginMqttServerFail:	str = _T("eLoginMqttServerFail");	break;
	case eParameterError:		str = _T("eParameterError");		break;
	case eHttpRequestError:		str = _T("eHttpRequestError");		break;
	case eParseError:			str = _T("eParseError");			break;
	case eTrailsParseError:		str = _T("eTrailsParseError");		break;
	case eMqttConnectError:		str = _T("eMqttConnectError");		break;
	default:	break;
	}

	return str;
}
