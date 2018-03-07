
// RobotpenWifiDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RobotpenWifiDemo.h"
#include "RobotpenWifiDemoDlg.h"
#include "afxdialogex.h"
#include "WBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRobotpenWifiDemoDlg 对话框




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


// CRobotpenWifiDemoDlg 消息处理程序

BOOL CRobotpenWifiDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRobotpenWifiDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	pListView->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );//设置扩展

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
	// TODO: 在此添加控件通知处理程序代码
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
