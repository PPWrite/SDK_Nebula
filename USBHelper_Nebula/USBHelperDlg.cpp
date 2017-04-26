
// USBHelperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "USBHelper.h"
#include "USBHelperDlg.h"
#include "afxdialogex.h"
#include <GdiplusGraphics.h>
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _VERSION  _T("版本号:20170426")

//#define _GATEWAY
//#define _NODE
//#define _DONGLE
#define _P1

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

PCHAR WideStrToMultiStr (PWCHAR WideStr)
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

/*static std::wstring MultiCharToWideChar( std::string str )
{
int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
TCHAR* buffer = new TCHAR[len + 1];
MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
buffer[len] = '\0';
std::wstring return_value;
return_value.append(buffer);
delete [] buffer;
return return_value;
}//*/

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


// CUSBHelperDlg 对话框




CUSBHelperDlg::CUSBHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUSBHelperDlg::IDD, pParent)
	, m_pDlg(NULL)
	, m_nDeviceType(GATEWAY)
	, m_bRun(TRUE)
	, m_nLastStatus(-1)
	, m_nLastMode(-1)
	, m_nNoteNum(0)
	, m_pWBDlg(NULL)
{
	for (int i=0;i<2;i++)
	{
		m_hEvent[i] = CreateEvent(NULL,TRUE,FALSE,NULL);
	}
	// 初始化
	::InitializeCriticalSectionAndSpinCount(&m_sectionLock, 4000);

	memset(&m_lastInfo,0,sizeof(m_lastInfo));

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUSBHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CUSBHelperDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3_OPEN, &CUSBHelperDlg::OnBnClickedButton3Open)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_DEVICECHANGE()					//--by zlp 2016/9/27
	ON_MESSAGE(WM_CLICK, OnClick)
	ON_MESSAGE(WM_UPDATE, OnUpdate)
	ON_MESSAGE(WM_UPDATE_WINDOW, OnUpdateWindow)
	ON_BN_CLICKED(IDC_BUTTON_VOTE, &CUSBHelperDlg::OnBnClickedButtonVote)
	ON_BN_CLICKED(IDC_BUTTON_VOTE_OFF, &CUSBHelperDlg::OnBnClickedButtonVoteOff)
	ON_BN_CLICKED(IDC_BUTTON_VOTE_CLEAR, &CUSBHelperDlg::OnBnClickedButtonVoteClear)
	ON_BN_CLICKED(IDC_BUTTON3_MS, &CUSBHelperDlg::OnBnClickedButton3Ms)
	ON_BN_CLICKED(IDC_BUTTON3_MS_OFF, &CUSBHelperDlg::OnBnClickedButton3MsOff)
	ON_BN_CLICKED(IDC_BUTTON_STATUS, &CUSBHelperDlg::OnBnClickedButtonStatus)
	ON_BN_CLICKED(IDC_BUTTON_MS_CLEAR, &CUSBHelperDlg::OnBnClickedButtonMsClear)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3_SET, &CUSBHelperDlg::OnBnClickedButton3Set)
	ON_BN_CLICKED(IDC_BUTTON3_UPDATE, &CUSBHelperDlg::OnBnClickedButton3Update)
	ON_BN_CLICKED(IDC_BUTTON3_SHOW, &CUSBHelperDlg::OnBnClickedButton3Show)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CUSBHelperDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CUSBHelperDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_STOP, &CUSBHelperDlg::OnBnClickedButtonScanStop)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CUSBHelperDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_SET_NAME, &CUSBHelperDlg::OnBnClickedButtonSetName)
	ON_BN_CLICKED(IDC_BUTTON_SYNC_STOP, &CUSBHelperDlg::OnBnClickedButtonSyncStop)
	ON_BN_CLICKED(IDC_BUTTON_SYNC_START, &CUSBHelperDlg::OnBnClickedButtonSyncStart)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUSBHelperDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_SYNC_OPEN, &CUSBHelperDlg::OnBnClickedButtonSyncOpen)
END_MESSAGE_MAP()


// CUSBHelperDlg 消息处理程序

BOOL CUSBHelperDlg::OnInitDialog()
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
	//MoveWindow(0,0,1600,900)
#ifdef _GATEWAY
	this->ShowWindow(SW_MAXIMIZE);
	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LIST_SLAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCAN_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CONNECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SLAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SLAVE_VERSION)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_SLAVE_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_SYNC_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_STOP)->ShowWindow(SW_HIDE);
	
#endif
#ifdef _NODE
	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS_OFF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MS_CLEAR)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LIST_SLAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCAN_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CONNECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SLAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SLAVE_VERSION)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("开始同步"));
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("结束同步"));

	GetDlgItem(IDC_EDIT_SLAVE_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_SYNC_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_SHOW);

#endif
#ifdef _DONGLE
	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS_OFF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MS_CLEAR)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("开始同步"));
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("结束同步"));

	GetDlgItem(IDC_BUTTON_VOTE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->ShowWindow(SW_HIDE);//*/
	GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON3_SET)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CUS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CUSTOM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CLASS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CLASS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DEV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_DEV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_SYNC_START)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SYNC_STOP)->ShowWindow(SW_SHOW);
#endif

#ifdef _P1
	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LIST_SLAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCAN_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CONNECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SLAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SLAVE_VERSION)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_SLAVE_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_SYNC_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_STOP)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_STATUS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_OPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_VOTE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS_OFF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MS_CLEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_SET)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CUS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CUSTOM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CLASS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CLASS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DEV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_DEV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_UPDATE)->ShowWindow(SW_HIDE);
#endif
	InitListCtrl();

	resetUI();
	//AfxBeginThread(ThreadProc,this);
	m_pDlg = new CUpdateDlg;
	m_pDlg->Create(IDD_UPDATEDLG);

	GetDlgItem(IDC_STATIC_SV)->SetWindowText(_VERSION);

	AddList();

	AfxBeginThread(ThreadProc,this);

	GetInstance()->ConnectInitialize(GATEWAY,false,getUsbData,this);

#ifdef _NODE
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();

	m_pWBDlg = new CWBDlg;
	m_pWBDlg->Create(IDD_WBDLG);
	m_pWBDlg->ShowWindow(SW_HIDE);
	m_pWBDlg->SetWindowText(_T("离线笔记"));
	m_pWBDlg->SetPage(_T(""));
#else
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
#endif

#ifdef _P1
	m_list[0]->SetPage(_T(""));
#endif

	/*GetInstance()->SetFilterWidth(2);
	GetInstance()->SetCanvasSize(960,669);//*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUSBHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if (nID == SC_MINIMIZE)
		{
			if (m_pDlg->IsWindowVisible())
				return;
		}
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUSBHelperDlg::OnPaint()
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
HCURSOR CUSBHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUSBHelperDlg::InitListCtrl()
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_USB_DEVICE));
	if (NULL == pListView)
		return;

	pListView->InsertColumn(0, _T("设备名称"), LVCFMT_LEFT, 180);
	pListView->InsertColumn(1, _T("VID"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(2, _T("PID"), LVCFMT_LEFT, 80);
	pListView->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );//设置扩展

	pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;

	pListView->InsertColumn(0, _T("Num"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(1, _T("名称"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(2, _T("Mac地址"), LVCFMT_LEFT, 180);
	pListView->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );//设置扩展
}

void CUSBHelperDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();//*/
}

void CUSBHelperDlg::AddList()
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_USB_DEVICE));
	if (NULL == pListView)
		return;

	pListView->DeleteAllItems();

	/*DWORD dwAddress = GetInstance()->GetAvailableDevice();
	std::vector<USB_INFO>* pVecUsbInfo = (std::vector<USB_INFO>*)dwAddress;
	if (pVecUsbInfo == NULL)
	{
		return;
	}
	std::vector<USB_INFO>& vecUsbInfo  = *pVecUsbInfo;//*/
	/*std::vector<USB_INFO> vecUsbInfo;
	GetInstance()->GetAvailableDevice(vecUsbInfo);//*/
	/*for (int i=0;i<vecUsbInfo.size();i++)
	{
		int nIndex = pListView->GetItemCount();
		pListView->InsertItem(i,MultiCharToWideChar(vecUsbInfo[i].szDevName).c_str());
		CString str;
		str.Format(_T("%d"),vecUsbInfo[i].nVendorNum);
		pListView->SetItemText(nIndex,1,str);
		str.Format(_T("%d"),vecUsbInfo[i].nProductNum);
		pListView->SetItemText(nIndex,2,str);
	}//*/

	int nCount = GetInstance()->GetAvailableDeviceCount();
	for (int i=0;i<nCount;i++)
	{
		USB_INFO usbInfo;
		if (GetInstance()->GetAvailableDevice(i,usbInfo))
		{
			int nIndex = pListView->GetItemCount();
			pListView->InsertItem(i,MultiCharToWideChar(usbInfo.szDevName).c_str());
			CString str;
			str.Format(_T("%d"),usbInfo.nVendorNum);
			pListView->SetItemText(nIndex,1,str);
			str.Format(_T("%d"),usbInfo.nProductNum);
			pListView->SetItemText(nIndex,2,str);
		}
	}

	if (pListView->GetItemCount() > 0)
	{
		pListView->SetItemState(0,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
	}
}
// 打开设备
void CUSBHelperDlg::OnBnClickedButton3Open()
{
	// TODO: 在此添加控件通知处理程序代码

	CString csBtnTitle;
	GetDlgItemText(IDC_BUTTON3_OPEN,csBtnTitle);
	if (csBtnTitle.Compare(_T("关闭设备")) == 0)
	{
		GetInstance()->ConnectDispose();
		resetDevice();
		return;
	}

	POSITION pos = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetFirstSelectedItemPosition();
	if (pos == nullptr)
	{
		/*int nRes = GetInstance()->Open(0x0ED1,0x781E);
		ASSERT(nRes == 0);
		if(nRes == 0)
		GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowText(_T("关闭设备"));
		return;//*/
		MessageBox(_T("请先选中设备!"), _T("提示"), IDOK);
		return;
	}

	int nItem = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetNextSelectedItem(pos);
	CString strVid = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetItemText(nItem, 1);
	CString strPid = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetItemText(nItem, 2);

	int nVid = atoi(WideStrToMultiStr(strVid.GetBuffer()));
	int nPid = atoi(WideStrToMultiStr(strPid.GetBuffer()));

	if (nPid == GATEWAY_PID)
	{
		GetInstance()->ConnectInitialize(GATEWAY,false,getUsbData,this);
		m_nDeviceType = GATEWAY;
	}
	else if (nPid == T8A_PID || nPid == T9A_PID )
	{
		GetInstance()->ConnectInitialize(NODE,false,getUsbData,this);
		m_nDeviceType = NODE;
	}
	else if (nPid == DONGLE_PID)
	{
		GetInstance()->ConnectInitialize(DONGLE,false,getUsbData,this);
		m_nDeviceType = DONGLE;
	}
	else if (nPid == P1_PID)
	{
		GetInstance()->ConnectInitialize(P1,false,getUsbData,this);
		m_nDeviceType = P1;
	}

	int nRes = GetInstance()->ConnectOpen();
	ASSERT(nRes == 0);
	if(nRes == 0)
		GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowText(_T("关闭设备"));

	/*GetDlgItem(IDC_BUTTON_VOTE)->EnableWindow(!m_bNode);
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->EnableWindow(!m_bNode);//*/
	bool bShow = (m_nDeviceType == GATEWAY) ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON3_MS)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON3_MS_OFF)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON_MS_CLEAR)->EnableWindow(bShow);

	GetDlgItem(IDC_STATIC_DEV)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_DEV)->ShowWindow(!bShow);

	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(!bShow);
	GetDlgItem(IDC_STATIC_MODE)->ShowWindow(!bShow);
	//GetDlgItem(IDC_COMBO1)->ShowWindow(bShow);

	if(m_nDeviceType == GATEWAY)
	{
		GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("发起投票"));
		GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("结束投票"));
	}
	else if(m_nDeviceType == NODE)
	{
		GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("开始同步"));
		GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("结束同步"));
	}
	else
	{
		GetDlgItem(IDC_BUTTON3_SET)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_VOTE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_VOTE_OFF)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_CUS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CLASS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DEV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_CUSTOM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CLASS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DEV)->ShowWindow(SW_HIDE);
	}

	if (m_nDeviceType != GATEWAY)
		OnBnClickedButtonStatus();
}

void CUSBHelperDlg::OnDestroy()		//--by zlp 2016/9/26
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	resetDevice();

	for(int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		pDlg = NULL;
	}//*/

	DestroyInstance();

	Sleep(100);
}

void CUSBHelperDlg::resetDevice()
{
	GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowTextW(_T("打开设备"));

	for (int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		if (NULL != pDlg)
		{
			pDlg->SetOnLine();
			pDlg->ResetUI();
		}
	}

	GetDlgItem(IDC_EDIT_CUSTOM)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_CLASS)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_DEV)->SetWindowText(_T(""));

	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowTextW(_T(""));

	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T(""));

	GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_STATIC_VERSION_SLAVE)->SetWindowTextW(_T(""));

	GetDlgItem(IDC_STATIC_NOTE)->SetWindowTextW(_T(""));

	GetDlgItem(IDC_EDIT_SLAVE_NAME)->SetWindowTextW(_T(""));

	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;
	pListView->DeleteAllItems();

	m_nLastStatus = -1;
	m_nLastMode = -1;
	memset(&m_lastInfo,0,sizeof(m_lastInfo));

	AddList();
}

UINT CUSBHelperDlg::ThreadProc(LPVOID lpParam)
{
	CUSBHelperDlg *pDlg = (CUSBHelperDlg*)lpParam;
	pDlg->ProcessMassData();

	return 0;
}

void CUSBHelperDlg::ProcessMassData()
{
	while(m_bRun)
	{
		/*if(WaitForSingleObject(m_hEvent[1],0) == WAIT_OBJECT_0 )
		break;//*/
		DWORD dwResult = WaitForMultipleObjects(2,m_hEvent,FALSE,INFINITE);

		switch(dwResult - WAIT_OBJECT_0)
		{
		case 0:
			{
				std::queue<ROBOT_REPORT> tmpQueue;
				::EnterCriticalSection(&m_sectionLock);
				while(m_queueData.size() > 0)
				{
					tmpQueue.push(m_queueData.front());
					m_queueData.pop();
				}
				::LeaveCriticalSection(&m_sectionLock);

				while(tmpQueue.size() > 0)
				{
					ROBOT_REPORT report = tmpQueue.front();
					tmpQueue.pop();

					if (m_nDeviceType == DONGLE)
						this->parseDongleReport(report);
					else
						this->parseRobotReport(report);
				}
			}
			break;
		case 1:
			m_bRun = FALSE;
			break;
		default:
			break;
		}
	}
	TRACE("==========================ProcessMassData Exit=========================\n");
}

LRESULT CUSBHelperDlg::OnClick(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)wParam;
	CString s(b);
	//SysFreeString(b);
	AfxMessageBox(s);
	return 0;
}

void CUSBHelperDlg::OnBnClickedButtonVote()
{
	// TODO: 在此添加控件通知处理程序代码
	/*ROBOT_REPORT report = {0};
	report.cmd_id = ROBOT_PAGE_NO;
	report.reserved = 0;
	uint16_t r = rand()%999;
	memcpy(&report.payload,&r,sizeof(uint16_t));
	parseRobotReport(report);
	return;//*/

	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	if (m_nDeviceType == GATEWAY)
	{
		if (nIndex == 0)
			GetInstance()->Send(VoteBegin);
		else
			GetInstance()->VoteMulit();
	}
	else
	{
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetPos(0);
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetStep(1);

		m_pWBDlg->Clear();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
		for(int i=0;i<MAX_NOTE;i++)
		{
			vecPenInfo[i].clear();
		}
		GetInstance()->Send(SyncBegin);
	}
}

void CUSBHelperDlg::OnBnClickedButtonVoteOff()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nDeviceType == GATEWAY)
		GetInstance()->Send(VoteEnd);
	else
		GetInstance()->Send(SyncEnd);
}

void CUSBHelperDlg::OnBnClickedButtonVoteClear()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		if (NULL != pDlg)
			pDlg->SetVote();
	}
}

void CUSBHelperDlg::OnBnClickedButton3Ms()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(WriteBegin);
}

void CUSBHelperDlg::OnBnClickedButton3MsOff()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(WriteEnd);
}

void CUSBHelperDlg::OnBnClickedButtonStatus()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(GetConfig);
}

void CUSBHelperDlg::resetUI()
{
	int left = 10;
	int top = 10;
	CRect rect;
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_USB_DEVICE));
	pListView->GetClientRect(rect);
	pListView->MoveWindow(left,top,rect.Width(),rect.Height());

	/*top += rect.Height() + left;
	CButton *pButton = static_cast<CButton*>(GetDlgItem(IDC_BUTTON3_OPEN));
	pButton->GetClientRect(rect);
	pButton->MoveWindow(left,top,rect.Width(),rect.Height());//*/

	CreateChart(rect.Width() + 2*left);
}

void CUSBHelperDlg::CreateChart(int nHStart)
{
	// TODO: 在此添加控件通知处理程序代码
	//int nHStart = 450;
	int nVStart = 10;
	int nItemSize = 200;
	int nSpaceMax = nItemSize + 10;
	int nRow = 0;
	int nColumn = 0;
	CRect rect;
	this->GetClientRect(&rect);
#ifdef _GATEWAY
	int nMaxNum = GetPrivateProfileInt(_T("General"),_T("MaxNum"),60,GetAppPath() + _T("\\USBHelper.ini"));
#else
	int nMaxNum = 1; 
#endif
	while(true)
	{
		nItemSize -= 5;
		if(nItemSize <= 0)
			break;
		nSpaceMax = nItemSize + 10;
		nRow = (rect.Width() - nHStart)/nSpaceMax;
		nColumn = (rect.Height() - nVStart)/nSpaceMax;
		if (nRow*nColumn > nMaxNum)
			break;
	}

	for (int j=0;j<nColumn;j++)	
	{
		for (int i=0;i<nRow;i++)
		{
			if (m_list.size() == nMaxNum)
				break;
			CDrawDlg *pDlg = new CDrawDlg;
			m_list.push_back(pDlg);
			CString str;
			str.Format(_T("%d"),m_list.size());
#ifdef _GATEWAY
			pDlg->SetText(str);
#else
			pDlg->SetText(_T("双击显示画布"));
#endif
			//pDlg->SetVote(str);
			pDlg->Create(IDD_DRAWDLG,this);
			pDlg->MoveWindow(nHStart + i*nSpaceMax,nVStart + j*nSpaceMax,nItemSize,nItemSize); 
			pDlg->ShowWindow(SW_SHOWNORMAL);
		}
	}
}

void CUSBHelperDlg::OnBnClickedButtonMsClear()
{
	// TODO: 在此添加控件通知处理程序代码

	for(int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		if (NULL != pDlg)
		{
			pDlg->ResetUI(true);
		}
	}
}

void CUSBHelperDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	GetDlgItem(IDC_BUTTON3_OPEN)->GetWindowText(str);
	if (str == _T("关闭设备"))
		OnBnClickedButton3Open();
	m_bRun = FALSE;

	SetEvent(m_hEvent[1]);

	CDialogEx::OnClose();
}

void CUSBHelperDlg::OnBnClickedButton3Set()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCustom;
	GetDlgItem(IDC_EDIT_CUSTOM)->GetWindowText(strCustom);
	CString strClass;
	GetDlgItem(IDC_EDIT_CLASS)->GetWindowText(strClass);
	CString strDevice;
	GetDlgItem(IDC_EDIT_DEV)->GetWindowText(strDevice);
	BOOL bNode = (m_nDeviceType == NODE) ? TRUE : FALSE;
	CSettingDlg dlg(strCustom,strClass,strDevice,bNode);
	if (IDOK == dlg.DoModal())
	{
		dlg.GetSettingInfo(strCustom,strClass,strDevice);

		int nCustrom = atoi(WideStrToMultiStr(strCustom.GetBuffer()));
		int nClass = atoi(WideStrToMultiStr(strClass.GetBuffer()));
		int nDevice = atoi(WideStrToMultiStr(strDevice.GetBuffer()));
		GetInstance()->SetConfig(nCustrom,nClass,nDevice);
	}
}

void CUSBHelperDlg::OnBnClickedButton3Update()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL != m_pDlg)
	{
		if(m_pDlg->IsWindowVisible())
			return;
		CString str;
		GetDlgItem(IDC_STATIC_VERSION)->GetWindowText(str);
		m_pDlg->ResetUI();
		m_pDlg->SetUpgradeType(m_nDeviceType);
		if (m_nDeviceType == DONGLE)
		{
			CString strSlave;
			GetDlgItem(IDC_STATIC_VERSION_SLAVE)->GetWindowText(strSlave);
			str += _T("_");
			str += strSlave;
		}
		m_pDlg->SetVersion(str);
		m_pDlg->CenterWindow(this);
		m_pDlg->ShowWindow(SW_SHOWDEFAULT);
	}
}

LRESULT CUSBHelperDlg::OnUpdate(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case START_UPADTE_GATEWAY:
		GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),"");
		break;
	case START_UPADTE_NODE:
		GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),WideStrToMultiStr(m_strFileBle.GetBuffer()));
		break;
	case START_UPADTE_DONGLE:
		{
			m_nDongleUpdateType = wParam;
			if (m_nDongleUpdateType == 1)
				GetInstance()->Update(WideStrToMultiStr(m_strFileBle.GetBuffer()),(const char*)wParam);
			else
				GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),(const char*)wParam);
		}
		break;
	case STOP_UPDATE_GATEWAY:
	case STOP_UPDATE_NODE:
	case STOP_UPDATE_DONGLE:
		GetInstance()->Send(UpdateStop);
		break;
	case SET_VERSION:
		{
			BSTR b = (BSTR)wParam;
			CString str(b);
			m_version = CString2Version(str);
		}
		break;
	case SET_MCU:
		{
			BSTR b = (BSTR)wParam;
			CString str(b);
			m_strFileMcu = str;
		}
		break;
	case SET_BLE:
		{
			BSTR b = (BSTR)wParam;
			CString str(b);
			m_strFileBle = str;
		}
		break;
	default:
		break;
	}

	return 0;
}

LRESULT CUSBHelperDlg::OnUpdateWindow(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case ROBOT_DONGLE_RAW_RESULT://校验结果
	case ROBOT_GATEWAY_REBOOT:
		{
			if (m_pDlg->IsWindowVisible())
			{
				m_pDlg->ShowWindow(SW_HIDE);
				if (wParam == 0)
					AfxMessageBox(_T("升级成功！"));
				else
					AfxMessageBox(_T("升级失败！"));
				if (m_nDongleUpdateType == SLAVE_MCU)
				{
					GetInstance()->Send(UpdateStop);
				}
				else if (m_nDongleUpdateType == DONGLE_BLE)
				{
				}
				else
					resetDevice();
			}
		}
		break;
	case ROBOT_SET_DEVICE_NUM:
		{
			if (wParam == 0)
				AfxMessageBox(_T("设置成功！"));
			else
				AfxMessageBox(_T("设置失败！"));
			resetDevice();
		}
		break;
	case ROBOT_DEVICE_CHANGE:
		{
			if (wParam == 0)
				AddList();
			else
				resetDevice();
		}
		break;
	case ROBOT_SET_NAME:
		AfxMessageBox(_T("设置成功！"));
		break;
	default:
		break;
	}

	return 0;
}

void CUSBHelperDlg::OnBnClickedButton3Show()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = GetPrivateProfileInt(_T("General"),_T("ShowNum"),60,GetAppPath() + _T("\\USBHelper.ini"));
	if(nCount > m_list.size())
		return;
	for(int i=0;i<nCount;i++)
	{
		CDrawDlg *pDlg = m_list[i];
		if (NULL != pDlg)
		{
			pDlg->ResetWindow();
		}
	}
}

ST_VERSION CUSBHelperDlg::CString2Version(CString strVersion)
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

///////////////////////////////////////////////
BOOL CUSBHelperDlg::IsItemExist(CString strName)
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_USB_DEVICE));
	for(int i=0;i<pListView->GetItemCount();i++)
	{
		if (pListView->GetItemText(i,0) == strName)
			return TRUE;
	}
	return FALSE;
}

void CUSBHelperDlg::getUsbData(const unsigned char *pData,int len,void *pContext)
{
	CUSBHelperDlg *pDlg = (CUSBHelperDlg*)pContext;

	pDlg->setUsbData(pData);
}

void CUSBHelperDlg::setUsbData(const unsigned char *pData)
{
	ROBOT_REPORT report = {0};
	memcpy(&report,pData,sizeof(ROBOT_REPORT));

	::EnterCriticalSection(&m_sectionLock);
	m_queueData.push(report);
	::LeaveCriticalSection(&m_sectionLock);
	SetEvent(m_hEvent[0]);
}
//解析nebula命令
void CUSBHelperDlg::parseRobotReport(const ROBOT_REPORT &report)
{
	switch(report.cmd_id)
	{
	case ROBOT_GATEWAY_STATUS://获取状态
		{
			ROBOT_STATUS status = {0};
			memcpy(&status,report.payload,sizeof(ROBOT_STATUS));

			if (m_nLastStatus == status.device_status)
			{
				break;
			}
			else
				m_nLastStatus = status.device_status;

			if (report.reserved == 0)
			{
				switch(status.device_status)
				{
				case NEBULA_STATUS_STANDBY:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("STANDBY"));
					break;
				case NEBULA_STATUS_VOTE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("VOTE"));
					break;
				case NEBULA_STATUS_MASSDATA:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("MASSDATA"));
					break;
				case NEBULA_STATUS_END:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("END"));
					break;
				case NEBULA_STATUS_CONFIG:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("CONFIG"));
					break;
				case NEBULA_STATUS_DFU:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DFU"));
					break;
				case NEBULA_STATUS_MULTI_VOTE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("MULTI_VOTE"));
					break;
				default:
					{
						CString str;
						str.Format(_T("UNKNOW:%d"),status.device_status);
						GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
					}
					break;
				}
			}
			else
			{
				switch(status.device_status)
				{
				case DEVICE_POWER_OFF:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_POWER_OFF"));
					break;
				case DEVICE_STANDBY:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_STANDBY"));
					break;
				case DEVICE_INIT_BTN:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_INIT_BTN"));
					break;
				case DEVICE_OFFLINE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_OFFLINE"));
					break;
				case DEVICE_ACTIVE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_ACTIVE"));
					break;
				case DEVICE_LOW_POWER_ACTIVE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_LOW_POWER_ACTIVE"));
					break;
				case DEVICE_OTA_MODE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_OTA_MODE"));
					break;
				case DEVICE_OTA_WAIT_SWITCH:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_OTA_WAIT_SWITCH"));
					break;
				case DEVICE_DFU_MODE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_DFU_MODE"));
					break;
				case DEVICE_TRYING_POWER_OFF:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_TRYING_POWER_OFF"));
					break;
				case DEVICE_FINISHED_PRODUCT_TEST:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_FINISHED_PRODUCT_TEST"));
					break;
				case DEVICE_SYNC_MODE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DEVICE_SYNC_MODE"));
					break;
				default:
					break;
				}
				CString str;
				str.Format(_T("离线笔记:%d条"),status.note_num);
				GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(str);

				((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetRange(0,status.note_num);
			}

		}
		break;			
	case ROBOT_EXIT_VOTE://退出投票模式
		{
			for (int i=0;i<m_list.size();i++)
			{
				CString str;
				str.Format(_T("%c"),report.payload[i]);
				CDrawDlg *pDlg = m_list[i];
				if (NULL != pDlg)
					pDlg->SetVote(str);
			}
		}
		break;	
	case ROBOT_EXIT_VOTE_MULIT:
		{
			ST_OPTION_PACKET packet = {0};
			memcpy(&packet,report.payload,sizeof(packet));
			CString strOption(_T(""));
			CString str;
			for (int i=0;i<sizeof(packet.option);i++)
			{
				if (packet.option[i] != 0)
				{
					str.Format(_T("%c"),packet.option[i]);
					strOption += str;
				}
			}

			CDrawDlg *pDlg = m_list[packet.id];
			if (NULL != pDlg)
				pDlg->SetVote(strOption);
		}
		break;
		case ROBOT_BIG_DATA_REPORT://大数据上报
			{
				PEN_INFO penInfo = {0};
				memcpy(&penInfo,report.payload,sizeof(PEN_INFO));
				CDrawDlg *pDlg = m_list[report.reserved];
				if (pDlg)
					pDlg->AddData(penInfo);
			}
			break;
		case  ROBOT_PAGE_NO:
			{
				uint16_t nPage;
				memcpy(&nPage,report.payload,sizeof(nPage));

				CString str;
				str.Format(_T("第%d页"),nPage);
				CDrawDlg *pDlg = m_list[report.reserved];
				if (NULL != pDlg)
					pDlg->SetPage(str);
			}
			break;
		case ROBOT_GATEWAY_ERROR://错误
			{
				switch(report.payload[0])
				{
				case ERROR_NONE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_NONE"));
					break;
				case ERROR_FLOW_NUM:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_FLOW_NUM"));
					break;
				case ERROR_FW_LEN:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_FW_LEN"));
					break;
				case ERROR_FW_CHECKSUM:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_FW_CHECKSUM"));
					break;
				case ERROR_STATUS:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_STATUS"));
					break;
				case ERROR_VERSION:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_VERSION"));
					break;
				case ERROR_NAME_CONTENT:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_NAME_CONTENT"));
					break;
				case ERROR_NO_NOTE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("ERROR_NO_NOTE"));
					break;
				default:
					break;
				}
			}
			break;			
		case ROBOT_SET_DEVICE_NUM://设置设备网络号
			{
				this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
				if (report.payload[0] == 0)
				{
					CString str;
					str.Format(_T("%d"),report.payload[1]);
					GetDlgItem(IDC_EDIT_CUSTOM)->SetWindowText(str);
					str.Format(_T("%d"),report.payload[2]);
					GetDlgItem(IDC_EDIT_CLASS)->SetWindowText(str);
					str.Format(_T("%d"),report.payload[3]);
					GetDlgItem(IDC_EDIT_DEV)->SetWindowText(str);
				}
			}
			break;			
		case ROBOT_FIRMWARE_DATA://进度
			m_pDlg->PostMessage(WM_PROCESS,report.payload[0],report.cmd_id);
			break;			
		case ROBOT_RAW_RESULT://校验结果
			this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
			break;			
		case ROBOT_GATEWAY_REBOOT:	//设备重启	
			this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
			break;			
		case ROBOT_GATEWAY_VERSION://设备版本号
			{
				ST_DEVICE_INFO info = {0};
				memcpy(&info,report.payload,sizeof(ST_DEVICE_INFO));

				if (m_lastInfo.custom_num == info.custom_num
					&& m_lastInfo.class_num == info.class_num
					&& m_lastInfo.device_num == info.device_num
					&& m_lastInfo.version.version == info.version.version
					&& m_lastInfo.version.version2 == info.version.version2
					&& m_lastInfo.version.version3 == info.version.version3
					&& m_lastInfo.version.version4 == info.version.version4)
				{
					break;
				}
				else
					memcpy(&m_lastInfo,&info,sizeof(m_lastInfo));

				CString str;
				str.Format(_T("%d.%d.%d.%d"),info.version.version4,info.version.version3,info.version.version2,info.version.version);
				GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);

				str.Format(_T("%d"),info.custom_num);
				GetDlgItem(IDC_EDIT_CUSTOM)->SetWindowText(str);
				str.Format(_T("%d"),info.class_num);
				GetDlgItem(IDC_EDIT_CLASS)->SetWindowText(str);
				str.Format(_T("%d"),info.device_num);
				GetDlgItem(IDC_EDIT_DEV)->SetWindowText(str);
			}
			break;			
		case ROBOT_ONLINE_STATUS://在线状态
			{
				for (int i=0;i<m_list.size();i++)
				{
					CDrawDlg *pDlg = m_list[i];
					if (NULL != pDlg)
						pDlg->SetOnLine(report.payload[i]);
				}
			}
			break;				
		case ROBOT_DEVICE_CHANGE://设备改变
			this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
			break;	
		case ROBOT_NODE_MODE:
			{
				int nStatus = report.payload[0];
				if (m_nLastMode == nStatus)
					break;
				else
					m_nLastMode = nStatus;
				CString str;
				switch(nStatus)
				{
				case 0:
					{
						str = _T("BLE");
						GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_HIDE);
					}
					break;
				case 1:
					{
						str = _T("2.4G");
						GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_HIDE);
					}
					break;
				case 2:
					{
						str = _T("USB");
						GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_SHOW);
					}
					break;
				default:
					str = _T("Unknow");
					break;
				}
				GetDlgItem(IDC_STATIC_MODE)->SetWindowText(str);
			}
			break;
		case ROBOT_USB_PACKET://USB坐标
			{
				PEN_INFO penInfo = {0};
				memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

				penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

				//TRACE(_T("X:%d-Y:%d-Press:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress);

				m_list[0]->AddData(penInfo);
			}
			break;
		case ROBOT_KEY_PRESS://按键按下
			{
				int nStatus = report.payload[0];
				switch(nStatus)
				{
				case CLICK:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("CLICK"));
					break;
				case DBCLICK:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DBCLICK"));
					break;
				case PAGEUP:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUP"));
					break;
				case PAGEDOWN:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWN"));
					break;
				case CREATEPAGE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("CREATEPAGE"));
					break;
				default:
					break;
				}
			}
			break;
		case ROBOT_SHOW_PAGE://显示页码	
			{
				int nCurrentPage = report.payload[0];
				int nPageCount = report.payload[1];
				CString str;
				str.Format(_T("第%d页,共%d页"),nCurrentPage,nPageCount);
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
			}
			break;
		case ROBOT_SYNC_TRANS_BEGIN:
			{
				ST_NOTE_PLUS_HEADER_INFO info = {0};
				memcpy(&info,report.payload,sizeof(ST_NOTE_PLUS_HEADER_INFO));

				int nCount = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();
				CString str,strID;
				strID.Format(_T("%d"),info.note_number);

				bool bExist = false;
				for (int i=0;i<nCount;i++)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(i,str);
					if (str == strID)
					{
						bExist = true;
						break;
					}
				}
				if (!bExist)
					((CComboBox*)GetDlgItem(IDC_COMBO1))->InsertString(nCount,strID);

				((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->StepIt();

				str.Format(_T("离线笔记:%d条"),report.reserved);
				GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(str);
			}
			break;
		case ROBOT_SYNC_TRANS_END:
			{
				GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(_T("同步结束"));
				if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
					((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
			}
			break;
		case ROBOT_ORIGINAL_PACKET:
			{
				PEN_INFO penInfo = {0};
				memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

				//penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

				//TRACE(_T("X:%d-Y:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nStatus);
				//T9A
				if (report.reserved < MAX_NOTE)
				{
					vecPenInfo[report.reserved].push_back(penInfo);
				}

				m_list[0]->AddData(penInfo);
			}
			break;
		default:						
			break;
	}
}
//解析dongle命令
void CUSBHelperDlg::parseDongleReport(const ROBOT_REPORT &report)
{
	switch(report.cmd_id)
	{
	case ROBOT_DONGLE_STATUS://获取状态
		{
			int nStatus = report.payload[0];
			int nMode = report.payload[1];
			if (nMode == 1)
			{
				switch(nStatus)
				{
				case BLE_STANDBY:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_STANDBY"));
					break;
				case BLE_SCANNING:			//正在扫描	
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_SCANNING"));
					break;	
				case BLE_CONNECTING:		//连接中
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_CONNECTING"));
					break;	
				case BLE_CONNECTED:			//连接成功
					{
						GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_CONNECTED"));
						POSITION pos = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetFirstSelectedItemPosition();
						if (pos == nullptr)
							return;
						int nItem = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetNextSelectedItem(pos);
						CString strName = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetItemText(nItem, 1);

						GetDlgItem(IDC_EDIT_SLAVE_NAME)->SetWindowText(strName);
					}
					break;
				case BLE_ACTIVE_DISCONNECT://正在断开链接
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_ACTIVE_DISCONNECT"));
					break;
				case BLE_RECONNECTING:		//重新连接
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_RECONNECTING"));
					break;
				case BLE_LINK_BREAKOUT:		//蓝牙正在升级中
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_LINK_BREAKOUT"));
					break;
				case BLE_DFU_START:			//蓝牙dfu模式
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_DFU_START"));
					break;
				default:
					{
						CString str;
						str.Format(_T("UNKNOW:%d"),nStatus);
						GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
					}
					break;
				}
			}
			else if (nMode == 2)
			{
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("DONGLE_DFU"));
			}
		}
		break;
	case ROBOT_DONGLE_VERSION:
		{
			ST_VERSION version = {0};
			memcpy(&version,report.payload,sizeof(version));

			CString str;
			str.Format(_T("%d.%d.%d.%d"),version.version2,version.version,
				version.version4,version.version3);
			GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);
		}
		break;
	case ROBOT_DONGLE_SCAN_RES:
		{
			ST_BLE_DEVICE device = {0};
			memcpy(&device,report.payload,sizeof(device));

			const unsigned char* pDevName  = device.device_name;

			unsigned char szMac[25] = {0};
			sprintf((char*)szMac,"%02X:%02X:%02X:%02X:%02X:%02X",device.addr[0],device.addr[1],device.addr[2],device.addr[3],device.addr[4],device.addr[5]);

			std::string strName = (char*)pDevName;
			std::string strMac = (char*)szMac;
			AddSlaveList(device.num,MultiCharToWideChar(strName).c_str(),MultiCharToWideChar(strMac).c_str());
		}
		break;
	case ROBOT_DONGLE_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

			TRACE(_T("X:%d-Y:%d-Press:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress);

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_SLAVE_STATUS:
		{
			ROBOT_STATUS status = {0};
			memcpy(&status,report.payload,sizeof(ROBOT_STATUS));
			switch(status.device_status)
			{
			case DEVICE_POWER_OFF:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_POWER_OFF"));
				break;
			case DEVICE_STANDBY:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_STANDBY"));
				break;
			case DEVICE_INIT_BTN:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_INIT_BTN"));
				break;
			case DEVICE_OFFLINE:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_OFFLINE"));
				break;
			case DEVICE_ACTIVE:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_ACTIVE"));
				break;
			case DEVICE_LOW_POWER_ACTIVE:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_LOW_POWER_ACTIVE"));
				break;
			case DEVICE_OTA_MODE:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_OTA_MODE"));
				break;
			case DEVICE_OTA_WAIT_SWITCH:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_OTA_WAIT_SWITCH"));
				break;
			case DEVICE_TRYING_POWER_OFF:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_TRYING_POWER_OFF"));
				break;
			case DEVICE_FINISHED_PRODUCT_TEST:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_FINISHED_PRODUCT_TEST"));
				break;
			case DEVICE_SYNC_MODE:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("DEVICE_SYNC_MODE"));
				break;
			default:							break;
			}

			CString str;
			str.Format(_T("离线笔记:%d条"),status.note_num);
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
		}
		break;
	case ROBOT_SLAVE_SYNC_BEGIN:
		{
			CString str;
			str.Format(_T("离线笔记:%d条"),report.reserved);
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
		}
		break;
	case ROBOT_SLAVE_SYNC_END:
		{
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(_T("同步结束"));
		}
		break;
	case ROBOT_SLAVE_VERSION:
		{
			ST_VERSION version = {0};
			memcpy(&version,report.payload+2,sizeof(version));
			CString str;
			str.Format(_T("%d.%d.%d.%d"),version.version4,version.version3,version.version2,version.version);
			GetDlgItem(IDC_STATIC_VERSION_SLAVE)->SetWindowText(str);
		}
		break;
	case ROBOT_SLAVE_ERROR:
		{
			int nError = report.payload[0];
			switch(nError)
			{
			case ERROR_SLAVE_NONE:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("ERROR_SLAVE_NONE"));
				break;
			case ERROR_OTA_FLOW_NUM:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("ERROR_OTA_FLOW_NUM"));
				break;
			case ERROR_OTA_LEN:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("ERROR_OTA_LEN"));
				break;
			case ERROR_OTA_CHECKSUM:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("ERROR_OTA_CHECKSUM"));
				break;
			case ERROR_OTA_STATUS:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("ERROR_OTA_STATUS"));
				break;
			case ERROR_OTA_VERSION:
				GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T("ERROR_OTA_VERSION"));
				break;
			default:
				{
					CString str;
					str.Format(_T("UNKNOW:%d"),nError);
					GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(str);
				}
				break;
			}
		}
		break;
	case ROBOT_DONGLE_FIRMWARE_DATA:
		m_pDlg->PostMessage(WM_PROCESS,report.payload[0],report.cmd_id);
		break;			
	case ROBOT_DONGLE_RAW_RESULT://校验结果
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_DEVICE_CHANGE://设备改变
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_ORIGINAL_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			//penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

			//TRACE(_T("X:%d-Y:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nStatus);

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_SET_NAME:
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	default:
		break;
	}
}

void CUSBHelperDlg::OnBnClickedButtonScan()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;
	pListView->DeleteAllItems();

	GetInstance()->Send(DongleScanStart);
}

void CUSBHelperDlg::OnBnClickedButtonScanStop()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(DongleScanStop);
}

void CUSBHelperDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetFirstSelectedItemPosition();
	if (pos == nullptr)
	{
		MessageBox(_T("请先选中设备!"), _T("提示"), IDOK);
		return;
	}

	int nItem = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetNextSelectedItem(pos);
	CString strNum = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetItemText(nItem, 0);

	int nNum = atoi(WideStrToMultiStr(strNum.GetBuffer()));

	GetInstance()->ConnectSlave(nNum);
}

void CUSBHelperDlg::OnBnClickedButtonDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(DongleDisconnect);
}

void CUSBHelperDlg::AddSlaveList(int nNum,const CString &strName,const CString &strMac)
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;
	int nIndex = pListView->GetItemCount();

	for (int i=0;i<nIndex;i++)
	{
		CString strNum = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetItemText(nIndex, 0);
		int num = atoi(WideStrToMultiStr(strNum.GetBuffer()));
		if (num == nNum)
		{
			return;
		}
	}

	CString strID;
	strID.Format(_T("%d"),nNum);
	pListView->InsertItem(nIndex,strID);
	pListView->SetItemText(nIndex,1,strName);
	pListView->SetItemText(nIndex,2,strMac);
}

void CUSBHelperDlg::OnBnClickedButtonSetName()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_SLAVE_NAME)->GetWindowText(str);

	GetInstance()->SetSlaveName(WideCharToMultichar(str.GetBuffer()).c_str());
}

void CUSBHelperDlg::OnBnClickedButtonSyncStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(SyncBegin);
}

void CUSBHelperDlg::OnBnClickedButtonSyncStop()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(SyncEnd);
}

void CUSBHelperDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
#ifdef _NODE
	CString str;
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	if (nIndex < 0)
		return;
	m_pWBDlg->Clear();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nIndex,str);
	int nNoteNum = atoi(WideCharToMultichar(str.GetBuffer()).c_str());
	for(int j=0;j<vecPenInfo[nNoteNum].size();j++)
	{
		m_pWBDlg->onRecvData(vecPenInfo[nNoteNum][j]);
	}
#endif
}


void CUSBHelperDlg::OnBnClickedButtonSyncOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pWBDlg->ShowWindow(SW_SHOW);
}
