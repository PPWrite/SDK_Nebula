
// USBHelperDlg.cpp : ʵ���ļ�
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

#define _VERSION  _T("�汾��:20180329")

#define RESET_NODE 0x2a
#define RESET_ALL  0x29

#define _GATEWAY
//#define _NODE
//#define _DONGLE
//#define _P1
//#define _WIFI

//#define _CY

//#define TEST_COUNT
//#define TEST_T7E

//#define USE_POWER
//#define USE_OPTIMIZE

static std::vector<PEN_INFO> vecPenInfo[MAX_NOTE];

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CUSBHelperDlg �Ի���




CUSBHelperDlg::CUSBHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUSBHelperDlg::IDD, pParent)
	, m_pDlg(NULL)
	, m_nDeviceType(Gateway)
	, m_bRun(TRUE)
	, m_nLastStatus(-1)
	, m_nLastMode(-1)
	, m_nNoteNum(0)
	, m_pWBDlg(NULL)
	, m_nIndexCount(0)
	, m_nSlaveType(0)
	, m_nCurNoteNum(0)
	, m_bMouse(false)
	, m_bConnect(FALSE)
{
	for (int i=0;i<2;i++)
	{
		m_hEvent[i] = CreateEvent(NULL,TRUE,FALSE,NULL);
	}
	// ��ʼ��
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
	ON_BN_CLICKED(IDC_BUTTON3_RESET, &CUSBHelperDlg::OnBnClickedButton3Reset)
	ON_BN_CLICKED(IDC_BUTTON_ADJUST, &CUSBHelperDlg::OnBnClickedButtonAdjust)
#ifdef USE_POWER
	ON_WM_POWERBROADCAST()
#endif
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GET_ID, &CUSBHelperDlg::OnBnClickedButtonGetId)
	ON_BN_CLICKED(IDC_BUTTON3_RESET2, &CUSBHelperDlg::OnBnClickedButton3Reset2)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CUSBHelperDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_SET2, &CUSBHelperDlg::OnBnClickedButtonSet2)
	ON_BN_CLICKED(IDC_BUTTON_SET3, &CUSBHelperDlg::OnBnClickedButtonSet3)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CUSBHelperDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUSBHelperDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SET4, &CUSBHelperDlg::OnBnClickedButtonSet4)
	ON_BN_CLICKED(IDC_BUTTON_SET5, &CUSBHelperDlg::OnBnClickedButtonSet5)
END_MESSAGE_MAP()


// CUSBHelperDlg ��Ϣ�������

BOOL CUSBHelperDlg::OnInitDialog()
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
	GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_OPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GET_ID)->ShowWindow(SW_HIDE);
	SetWindowText(_T("GATEWAY"));

	DeleteDir(GetDataFloder());
	CreateAllDirectories(GetDataFloder());
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

	GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("��ʼͬ��"));
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("����ͬ��"));

	GetDlgItem(IDC_EDIT_SLAVE_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_SYNC_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON3_RESET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SYNC_OPEN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_SHOW);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GET_ID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_RESET2)->ShowWindow(SW_SHOW);
	SetWindowText(_T("NODE"));
#endif

#ifdef _WIFI
	GetDlgItem(IDC_STATIC_SSID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_STUID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_SSID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_CPWD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_SID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET3)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_LOCAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_LOCAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_REMOTE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_REMOTE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_UPDATE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_MQTT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_MQTT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET4)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_SECRET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_SECRET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET5)->ShowWindow(SW_SHOW);
#endif
	
#ifdef _DONGLE
	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_MS_OFF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MS_CLEAR)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("��ʼͬ��"));
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("����ͬ��"));

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
	GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_OPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_SHOW);
	SetWindowText(_T("DONGLE"));

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
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_GET_ID)->ShowWindow(SW_HIDE);

	SetWindowText(_T("P1"));
#endif

#ifdef _CY
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(_T("��"));
#endif

	InitListCtrl();

	resetUI();
	//AfxBeginThread(ThreadProc,this);
	m_pDlg = new CUpdateDlg;
	m_pDlg->Create(IDD_UPDATEDLG);

	GetDlgItem(IDC_STATIC_SV)->SetWindowText(_VERSION);

	AddList();

	AfxBeginThread(ThreadProc,this);

	GetInstance()->ConnectInitialize(Gateway,getUsbData,this);//*/

	//GetInstance()->ConnectInitialize(Gateway,this);

	//#ifdef _NODE

	m_pWBDlg = new CWBDlg;
	m_pWBDlg->Create(IDD_WBDLG);
	m_pWBDlg->ShowWindow(SW_HIDE);
	m_pWBDlg->SetWindowText(_T("���߱ʼ�"));
	//#else
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);//*/
	//#endif

	/*GetInstance()->SetPenWidth(2);
	GetInstance()->SetCanvasSize(960,669);//*/

	//==========================�Ż��ʼ�����======================
	/*GetInstance()->SetPenWidth(1.2);
#ifdef USE_OPTIMIZE
	GetInstance()->SetPenWidth(2);
	GetInstance()->SetPressStatus(false);
	GetInstance()->SetOptimizeStatus(true);
#endif*/

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUSBHelperDlg::OnPaint()
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
HCURSOR CUSBHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUSBHelperDlg::InitListCtrl()
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_USB_DEVICE));
	if (NULL == pListView)
		return;

	pListView->InsertColumn(0, _T("�豸����"), LVCFMT_LEFT, 180);
	pListView->InsertColumn(1, _T("VID"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(2, _T("PID"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(3, _T(""), LVCFMT_LEFT, 10);
	pListView->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );//������չ

	pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;

	pListView->InsertColumn(0, _T("Num"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(1, _T("����"), LVCFMT_LEFT, 80);
	pListView->InsertColumn(2, _T("Mac��ַ"), LVCFMT_LEFT, 180);
	pListView->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );//������չ
}

void CUSBHelperDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	int nCount = GetInstance()->GetDeviceCount();
	for (int i=0;i<nCount;i++)
	{
		USB_INFO usbInfo = {0};
		if (GetInstance()->GetDeviceInfo(i,usbInfo))
		{
			DEVICE_INFO deviceInfo = {0};
			GetInstance()->GetDeviceInfo(i,deviceInfo);

			int nIndex = pListView->GetItemCount();
			pListView->InsertItem(nIndex,MultiCharToWideChar(usbInfo.szDevName).c_str());
			CString str;
			str.Format(_T("%d"),usbInfo.nVendorNum);
			pListView->SetItemText(nIndex,1,str);
			str.Format(_T("%d"),usbInfo.nProductNum);
			pListView->SetItemText(nIndex,2,str);
			pListView->SetItemData(nIndex,deviceInfo.type);
			pListView->SetItemText(nIndex,3,MultiCharToWideChar(usbInfo.szDevPath).c_str());
		}
	}

	if (pListView->GetItemCount() > 0)
	{
		pListView->SetItemState(0,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
	}

#ifdef TEST_T7E
	openT7E();
#endif
}

void CUSBHelperDlg::openT7E()
{
	CListCtrl *pListView = (CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE);
	int nCount = pListView->GetItemCount();
	for (int i=0;i<nCount;i++)
	{
		CString strName = pListView->GetItemText(i, 0);
		if (strName == "T7E BOOT")
		{
			pListView->SetItemState(i,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
			OnBnClickedButton3Open();

			if (m_nDeviceType == T7E_TS || m_nDeviceType == T7E || m_nDeviceType == T7E_HFHH || m_nDeviceType == P1_CX_M3)
			{
				SetTimer(1,1000,NULL);
			}

			return;
		}
	}
}

// ���豸
void CUSBHelperDlg::OnBnClickedButton3Open()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString csBtnTitle;
	GetDlgItemText(IDC_BUTTON3_OPEN,csBtnTitle);
	if (csBtnTitle.Compare(_T("�ر��豸")) == 0)
	{
#ifndef _CY
		if (Dongle == m_nDeviceType)
		{
			GetInstance()->Send(DongleDisconnect);
			Sleep(300);
		}
#endif
		/*else if (X8 == m_nDeviceType)
		{
		GetInstance()->Send(ExitUsb);
		Sleep(100);
		}//*/
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
		GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowText(_T("�ر��豸"));
		return;//*/
		MessageBox(_T("����ѡ���豸!"), _T("��ʾ"), IDOK);
		return;
	}

	int nItem = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetNextSelectedItem(pos);
	CString strVid = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetItemText(nItem, 1);
	CString strPid = ((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetItemText(nItem, 2);

	int nVid = atoi(WideStrToMultiStr(strVid.GetBuffer()));
	int nPid = atoi(WideStrToMultiStr(strPid.GetBuffer()));

	m_nDeviceType = (eDeviceType)((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetItemData(nItem);

	GetInstance()->ConnectInitialize(m_nDeviceType,getUsbData,this);

	int nRes = GetInstance()->ConnectOpen();
	ASSERT(nRes == 0);
	if(nRes == 0)
		GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowText(_T("�ر��豸"));

	if (nRes != 0)
	{
		CString str;
		str.Format(_T("��ʧ��,������:%d"),nRes);
		AfxMessageBox(str);
	}

	/*GetDlgItem(IDC_BUTTON_VOTE)->EnableWindow(!m_bNode);
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->EnableWindow(!m_bNode);//*/
	bool bShow = (m_nDeviceType == Gateway) ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON3_MS)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON3_MS_OFF)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON_MS_CLEAR)->EnableWindow(bShow);

	GetDlgItem(IDC_STATIC_DEV)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_DEV)->ShowWindow(!bShow);

	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(!bShow);
	GetDlgItem(IDC_STATIC_MODE)->ShowWindow(!bShow);
	//GetDlgItem(IDC_COMBO1)->ShowWindow(bShow);

	if(m_nDeviceType == Gateway)
	{
		GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("����ͶƱ"));
		GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("����ͶƱ"));
	}
	else if(m_nDeviceType == T8A || m_nDeviceType == T9A || m_nDeviceType == T9_J0  || m_nDeviceType == J0_A4_P 
		|| m_nDeviceType == T9E || m_nDeviceType == J0_T9 || m_nDeviceType == T8B ||m_nDeviceType == T9B_YD
		|| m_nDeviceType == T8C || m_nDeviceType == T9W || m_nDeviceType == T9W_TY)
	{
		GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("��ʼͬ��"));
		GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("����ͬ��"));
	}
	else if (m_nDeviceType == X8 || m_nDeviceType == T7PL || m_nDeviceType == X8E_A5 || m_nDeviceType == T7E || m_nDeviceType == P1_CX_M3)
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

		GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_SHOW);
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

	if(m_nDeviceType == T7PL || m_nDeviceType == T7E)
	{
		GetDlgItem(IDC_BUTTON3_SHOW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON3_SHOW)->SetWindowText(_T("�л�"));
		Sleep(100);
		GetInstance()->Send(SearchMode);
	}

	if (m_nDeviceType == Gateway)
	{
		GetInstance()->Send(GetMassMac);
	}
	else
	{
		//OnBnClickedButtonStatus();
		SetTimer(0,500,NULL);
	}

	/*if (m_nDeviceType == X8)
	GetInstance()->Send(GetMac);*/

}

void CUSBHelperDlg::OnDestroy()		//--by zlp 2016/9/26
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	resetDevice();

	for(int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		pDlg = NULL;
	}//*/

	DestroyInstance();

	//Sleep(100);
}

void CUSBHelperDlg::resetDevice()
{
	GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowTextW(_T("���豸"));

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

	GetDlgItem(IDC_STATIC_NOTE2)->SetWindowTextW(_T(""));


	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;
	for (int i=0;i<pListView->GetItemCount();i++)
	{
		unsigned char *pMac = (unsigned char*)pListView->GetItemData(i);
		if (pMac)
		{
			delete pMac;
			pMac = NULL;
		}
	}//*/
	pListView->DeleteAllItems();

	m_nLastStatus = -1;
	m_nLastMode = -1;
	memset(&m_lastInfo,0,sizeof(m_lastInfo));

	while(m_queueData.size() > 0)
	{
		m_queueData.pop();
	}
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

					if (m_nDeviceType == Dongle)
						this->parseDongleReport(report);
					else
						this->parseRobotReport(report);
				}
				Sleep(1);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*ROBOT_REPORT report = {0};
	report.cmd_id = ROBOT_PAGE_NO;
	report.reserved = 0;
	uint16_t r = rand()%999;
	memcpy(&report.payload,&r,sizeof(uint16_t));
	parseRobotReport(report);
	return;//*/

	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	if (m_nDeviceType == Gateway)
	{
		if (nIndex == 0)
		{
			GetInstance()->Send(VoteBegin);
		}
		else if (nIndex == 1)
		{
			GetInstance()->VoteMulit();
		}
		else
		{
			GetInstance()->Send(VoteAnswer);
		}
	}
	else
	{
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetPos(0);
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetStep(1);

		m_pWBDlg->Clear();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
		for(int i=0;i<MAX_NOTE;i++)
		{
			//vecPenInfo[i].clear();
		}
		GetInstance()->Send(SyncBegin);
	}
}

void CUSBHelperDlg::OnBnClickedButtonVoteOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_nDeviceType == Gateway)
		GetInstance()->Send(VoteEnd);
	else
		GetInstance()->Send(SyncEnd);
}

void CUSBHelperDlg::OnBnClickedButtonVoteClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		if (NULL != pDlg)
			pDlg->SetVote();
	}
}

void CUSBHelperDlg::OnBnClickedButton3Ms()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(WriteBegin);
}

void CUSBHelperDlg::OnBnClickedButton3MsOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(WriteEnd);
}

void CUSBHelperDlg::OnBnClickedButtonStatus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*GetInstance()->Send(VotePoll);
	return;/*/

	/*CString str;
	str.Format(_T("w:%d-h:%d"),GetInstance()->Width(),GetInstance()->Height());
	AfxMessageBox(str);//*/

#ifdef _CY
	GetInstance()->Send(DongleVersion);
#else
	GetInstance()->Send(GetConfig);
#endif
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			//pDlg->SetVote(str);
			pDlg->Create(IDD_DRAWDLG,this);
			pDlg->MoveWindow(nHStart + i*nSpaceMax,nVStart + j*nSpaceMax,nItemSize,nItemSize); 
#ifdef _GATEWAY
			pDlg->SetText(str);
			pDlg->SetID(m_list.size());
#else
			pDlg->SetText(_T("˫����ʾ����"));
#endif
			pDlg->ShowWindow(SW_SHOWNORMAL);
		}
	}
}

void CUSBHelperDlg::OnBnClickedButtonMsClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	for(int i=0;i<m_list.size();i++)
	{
		CDrawDlg *pDlg = m_list[i];
		if (NULL != pDlg)
		{
			pDlg->ResetUI(true);
		}
	}

#ifdef TEST_COUNT
	m_nIndexCount = 0;
	CString str;
	str.Format(_T("%d"),m_nIndexCount);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);
#endif
}

void CUSBHelperDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	GetDlgItem(IDC_BUTTON3_OPEN)->GetWindowText(str);
	if (str == _T("�ر��豸"))
		OnBnClickedButton3Open();
	m_bRun = FALSE;

	SetEvent(m_hEvent[1]);

	CDialogEx::OnClose();
}

void CUSBHelperDlg::OnBnClickedButton3Set()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strCustom;
	GetDlgItem(IDC_EDIT_CUSTOM)->GetWindowText(strCustom);
	CString strClass;
	GetDlgItem(IDC_EDIT_CLASS)->GetWindowText(strClass);
	CString strDevice;
	GetDlgItem(IDC_EDIT_DEV)->GetWindowText(strDevice);
	BOOL bGateway = (m_nDeviceType == Gateway) ? TRUE : FALSE;
	CSettingDlg dlg(strCustom,strClass,strDevice,bGateway);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL != m_pDlg)
	{
		if(m_pDlg->IsWindowVisible())
			return;
		CString str;
		GetDlgItem(IDC_STATIC_VERSION)->GetWindowText(str);
		m_pDlg->ResetUI();
		m_pDlg->SetUpgradeType(m_nDeviceType);
		if (m_nDeviceType == Dongle && m_bConnect)
		{
			CString strSlave;
			GetDlgItem(IDC_STATIC_VERSION_SLAVE)->GetWindowText(strSlave);
			m_pDlg->SetVersion(strSlave);
		}
		else
			m_pDlg->SetVersion(str);
#ifdef TEST_T7E
		m_pDlg->AutoSetPath();
#endif
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
			switch(m_nDongleUpdateType)
			{
			case DONGLE_BLE:
				{
					if (!m_bConnect)
						GetInstance()->Update("",WideStrToMultiStr(m_strFileBle.GetBuffer()),Dongle);
				}
				break;
			case DONGLE_MCU:
				{
					if (!m_bConnect)
						GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),"",Dongle);
				}
				break;
			case SLAVE_MCU:
				{

					if (m_bConnect)
						GetInstance()->Update("",WideStrToMultiStr(m_strFileBle.GetBuffer()),(eDeviceType)m_nSlaveType);
				}
				break;
			case MODULE_MCU:
				GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),"",(eDeviceType)m_nSlaveType);
				break;
			default:
				break;
			}
		}
		break;
	case STOP_UPDATE_GATEWAY:
	case STOP_UPDATE_NODE:
	case STOP_UPDATE_DONGLE:
	case STOP_UPDATE_MODULE:
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
	case ROBOT_RAW_RESULT://У����
	case ROBOT_GATEWAY_REBOOT:
		{
			if (m_pDlg->IsWindowVisible())
			{
				m_pDlg->ShowWindow(SW_HIDE);
				if (wParam == 0)
					AfxMessageBox(_T("�����ɹ���"));
				else
					AfxMessageBox(_T("����ʧ�ܣ�"));
				if (m_nDongleUpdateType == SLAVE_MCU)
				{
					GetInstance()->Send(UpdateStop);
				}
				else if (m_nDongleUpdateType == DONGLE_BLE)
				{
					GetInstance()->Send(DongleVersion);
				}
				else if (m_nDeviceType == T7PL)
				{
					resetDevice();
					AddList();
				}
			}
		}
		break;
	case ROBOT_SET_PASSWORD:
	case ROBOT_SET_CLASS_SSID:
	case ROBOT_SET_CLASS_PWD:
	case ROBOT_SET_STUDENT_ID:
	case ROBOT_UPDATE_WIFI:
	case ROBOT_SET_SECRET:
		{
			if (wParam == 0)
				AfxMessageBox(_T("���óɹ���"));
			else
				AfxMessageBox(_T("����ʧ�ܣ�"));

		}
		break;
	case ROBOT_SET_DEVICE_NUM:
		{
			if (wParam == 0)
				AfxMessageBox(_T("���óɹ���"));
			else
				AfxMessageBox(_T("����ʧ�ܣ�"));
			resetDevice();
			AddList();

		}
		break;
	case ROBOT_DEVICE_CHANGE:
		{
			if (wParam == 0)
				AddList();
			else
			{
				resetDevice();
				AddList();
			}
		}
		break;
	case ROBOT_SET_NAME:
		AfxMessageBox(_T("���óɹ���"));
		break;
	case ROBOT_MODULE_ADJUST_RESULT:
		{
			CString str;
			switch(wParam)
			{
			case ADJUST_SUCCESSED:
				str = _T("У׼�ɹ�");
				break;
			case ADJUST_FAILED:
				str = _T("У׼ʧ��");
				break;
			case ADJUST_TIMEOUT:
				str = _T("У׼��ʱ");
				break;
			default:
				break;
			}

			AfxMessageBox(str);
		}
		break;
	default:
		break;
	}

	return 0;
}

void CUSBHelperDlg::OnBnClickedButton3Show()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_nDeviceType == T7PL || m_nDeviceType == T7E)
	{
		GetInstance()->Send(SwitchMode);
		Sleep(100);
	}
	else
	{
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
//����nebula����
void CUSBHelperDlg::parseRobotReport(const ROBOT_REPORT &report)
{
	/*CString strHex("");
	for(int i=0;i<60;i++)
	{
	CString str;
	str.Format(_T("%02x "),report.payload[i]);
	strHex += str;
	}
	strHex += "\r\n";
	WriteLog(strHex);//*/
	switch(report.cmd_id)
	{
	case ROBOT_GATEWAY_STATUS://��ȡ״̬
		{
			NODE_STATUS status = {0};
			memcpy(&status,report.payload,sizeof(NODE_STATUS));

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
			case NEBULA_STATUS_VOTE_ANSWER:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("VOTE_ANSWER"));
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
		break;
	case ROBOT_NODE_STATUS:
		{
			NODE_STATUS status = {0};
			memcpy(&status,report.payload,sizeof(NODE_STATUS));

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
			str.Format(_T("���߱ʼ�:%d��"),status.note_num);
			GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(str);

			((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetRange(0,status.note_num);
		}
		break;
	case ROBOT_EXIT_VOTE://�˳�ͶƱģʽ
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
	case ROBOT_MASS_DATA://�������ϱ�
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));
			CDrawDlg *pDlg = m_list[report.reserved];
#ifdef TEST_COUNT
			m_nIndexCount++;
			CString str;
			str.Format(_T("%d"),m_nIndexCount);
			GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);
#endif
			if (pDlg)
				pDlg->AddData(penInfo);
		}
		break;
	case ROBOT_MASS_MAC:
		{
			CString str;
			str.Format(_T("index:%d "),report.reserved+1);
			TRACE(str);
			str.Format(_T("%02X%02X%02X%02X%02X%02X"),report.payload[0],report.payload[1],report.payload[2],report.payload[3],report.payload[4],report.payload[5]);
			TRACE(str);
			TRACE("\r\n");
		}
		break;
	case  ROBOT_SHOW_PAGE:
		{
			PAGE_INFO pageInfo = {0};
			memcpy(&pageInfo,report.payload,sizeof(pageInfo));

			if (report.reserved >= m_list.size())
			{
				CDrawDlg *pDlg = m_list[0];
				if (NULL != pDlg)
					pDlg->SetPage(pageInfo);
			}
			else
			{
				CDrawDlg *pDlg = m_list[report.reserved];
				if (NULL != pDlg)
					pDlg->SetPage(pageInfo);
			}
		}
		break;
	case ROBOT_GATEWAY_ERROR://����
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
	case ROBOT_SET_DEVICE_NUM://�����豸�����
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
	case ROBOT_FIRMWARE_DATA://����
		m_pDlg->PostMessage(WM_PROCESS,report.payload[0],report.cmd_id);
		break;			
	case ROBOT_RAW_RESULT://У����
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;			
	case ROBOT_GATEWAY_REBOOT:	//�豸����	
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;			
	case ROBOT_GATEWAY_VERSION://�豸�汾��
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
#ifdef _WIFI
			str.Format(_T("%02X%02X%02X%02X%02X%02X"),info.mac[0],info.mac[1],info.mac[2],info.mac[3],info.mac[4],info.mac[5]);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
#endif
		}
		break;			
	case ROBOT_ONLINE_STATUS://����״̬
		{
			for (int i=0;i<m_list.size();i++)
			{
				CDrawDlg *pDlg = m_list[i];
				if (NULL != pDlg)
					pDlg->SetOnLine(report.payload[i]);
			}
		}
		break;				
	case ROBOT_DEVICE_CHANGE://�豸�ı�
		{
			/*CString str;
			str.Format(_T("ROBOT_DEVICE_CHANGE:%d"),report.reserved);
			WriteLog(str);//*/

			this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		}

		break;	
	case ROBOT_NODE_MODE:
		{
			int nStatus = report.payload[0];
			if (m_nLastMode == nStatus)
				break;
			else
				m_nLastMode = nStatus;

			/*if (X8 ==report.reserved)
			{
			if (nStatus != NODE_USB)
			{
			GetInstance()->Send(EnterUsb);
			}
			}//*/

			CString str;
			switch(nStatus)
			{
			case 0:
				{
					str = _T("BLE");
					//GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_HIDE);
				}
				break;
			case 1:
				{
					str = _T("2.4G");
					//GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_HIDE);
				}
				break;
			case 2:
				{
					str = _T("USB");
					//GetDlgItem(IDC_STATIC_NOTE2)->ShowWindow(SW_SHOW);
				}
				break;
			default:
				str = _T("Unknow");
				break;
			}
			GetDlgItem(IDC_STATIC_MODE)->SetWindowText(str);
		}
		break;
	case ROBOT_ORIGINAL_PACKET://USB����
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

			TRACE(_T("X:%d-Y:%d-Press:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress);
			if (m_nDeviceType == T7B_HF || m_nDeviceType == T7E)
			{
				switch(penInfo.nStatus)
				{
				case PEN_LEAVE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PEN_LEAVE"));
					break;
				case PEN_WRITE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PEN_WRITE"));
					break;
				case PEN_SUSPEND:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PEN_SUSPEND"));
					break;
				case PEN_SIDE_SUSPEND:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PEN_SIDE_SUSPEND"));
					break;
				case PEN_SIDE_WRITE:
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PEN_SIDE_WRITE"));
					break;
				default:
					break;
				}
			}

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_KEY_PRESS://��������
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
	case ROBOT_SYNC_TRANS_BEGIN:
		{
			ST_NOTE_HEADER_INFO info = {0};
			memcpy(&info,report.payload,sizeof(ST_NOTE_HEADER_INFO));

			m_nCurNoteNum = info.note_number;

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

			str.Format(_T("���߱ʼ�:%d��"),report.reserved);
			GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(str);
		}
		break;
	case ROBOT_SYNC_TRANS_END:
		{
			GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(_T("ͬ������"));
			if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
				((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

			OnCbnSelchangeCombo1();

			OnBnClickedButtonVoteOff();
		}
		break;
	case ROBOT_SYNC_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			//penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

			//TRACE(_T("X:%d-Y:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nStatus);
			//T9A
			if (m_nCurNoteNum < MAX_NOTE)
			{
				//vecPenInfo[m_nCurNoteNum].push_back(penInfo);
			}

			//m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_VOTE_ANSWER:
		{
			int index = report.payload[0];
			int answer = report.payload[1];
			CString str;
			str.Format(_T("%c"),answer);
			CDrawDlg *pDlg = m_list[index];
			if (NULL != pDlg)
				pDlg->SetVote(str);
		}
		break;
	case ROBOT_ENTER_ADJUST_MODE:
		GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("����У׼ģʽ"));
		break;
	case ROBOT_MODULE_ADJUST_RESULT:
		{
			this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
			/*CString str;
			int result = report.payload[0];
			switch(result)
			{
			case ADJUST_SUCCESSED:
			str = _T("У׼�ɹ�");
			break;
			case ADJUST_FAILED:
			str = _T("У׼ʧ��");
			break;
			case ADJUST_TIMEOUT:
			str = _T("У׼��ʱ");
			break;
			default:
			break;
			}
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);//*/
		}
		break;
	case ROBOT_OPTIMIZE_PACKET:
		{
			PEN_INFOF penInfof = {0};
			memcpy(&penInfof,report.payload,sizeof(PEN_INFOF));
			TRACE(_T("Robot X:%d-Y:%d-Status:%d-Width:%f\n"),penInfof.nX,penInfof.nY,penInfof.nStatus,penInfof.fWidth);

			PEN_INFO penInfo = {0};
			penInfo.nX = penInfof.nX;
			penInfo.nY = penInfof.nY;
			penInfo.nStatus = penInfof.nStatus;
			if (penInfof.fWidth > 0)
				penInfo.nPress = 1;
			else
				penInfo.nPress = 0;

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_SEARCH_MODE:
		{
			uint8_t mode = report.payload[0];
			if (mode)
				GetDlgItem(IDC_STATIC_SCANTIP2)->SetWindowText(_T("Hand"));
			else
				GetDlgItem(IDC_STATIC_SCANTIP2)->SetWindowText(_T("Mouse"));

			GetInstance()->Send(GetNodeInfo);
		}
		break;
	case ROBOT_SET_PASSWORD:
	case ROBOT_SET_CLASS_SSID:
	case ROBOT_SET_CLASS_PWD:
	case ROBOT_SET_STUDENT_ID:
	case ROBOT_UPDATE_WIFI:
	case ROBOT_SET_SECRET:
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_UPDATE_SEARCH:
		{
			int len = report.payload[0];
			int len2 = report.payload[1];
			char sz_ver[60] = {0};
			char sz_ver2[60] = {0};
			memcpy(sz_ver,report.payload+2,len);
			memcpy(sz_ver2,report.payload+2+len,len2);

			CString strVer(sz_ver);
			CString strVer2(sz_ver2);
			GetDlgItem(IDC_EDIT_LOCAL)->SetWindowText(strVer);
			GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(strVer2);
		}
		break;
	default:						
		break;
	}
}
//����dongle����
void CUSBHelperDlg::parseDongleReport(const ROBOT_REPORT &report)
{
	switch(report.cmd_id)
	{
	case ROBOT_DONGLE_STATUS://��ȡ״̬
		{
			int nStatus = report.payload[0];
			int nMode = report.payload[1];
			if (nMode == 1)
			{
				switch(nStatus)
				{
				case BLE_STANDBY:
					{
						GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_STANDBY"));
						GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(_T(""));
						GetDlgItem(IDC_STATIC_VERSION_SLAVE)->SetWindowText(_T(""));
						GetDlgItem(IDC_EDIT_SLAVE_NAME)->SetWindowText(_T(""));
						GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(_T(""));
						GetDlgItem(IDC_BUTTON_SCAN)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
						m_bConnect = FALSE;
					}
					break;
				case BLE_SCANNING:			//����ɨ��	
					GetDlgItem(IDC_BUTTON_SCAN)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_SCANNING"));
					break;	
				case BLE_CONNECTING:		//������
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_CONNECTING"));
					break;	
				case BLE_CONNECTED:			//���ӳɹ�
					{
						GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_CONNECTED"));
						POSITION pos = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetFirstSelectedItemPosition();
						if (pos == nullptr)
							return;
						int nItem = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetNextSelectedItem(pos);
						CString strName = ((CListCtrl*)GetDlgItem(IDC_LIST_SLAVE))->GetItemText(nItem, 1);

						GetDlgItem(IDC_EDIT_SLAVE_NAME)->SetWindowText(strName);

						GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);

						m_bConnect = TRUE;
					}
					break;
				case BLE_ACTIVE_DISCONNECT://���ڶϿ�����
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_ACTIVE_DISCONNECT"));
					break;
				case BLE_RECONNECTING:		//��������
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_RECONNECTING"));
					break;
				case BLE_LINK_BREAKOUT:		//��������������
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("BLE_LINK_BREAKOUT"));
					break;
				case BLE_DFU_START:			//����dfuģʽ
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
			str.Format(_T("%d.%d.%d.%d"),version.version,version.version2,
				version.version3,version.version4);
			GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);
		}
		break;
	case ROBOT_DONGLE_SCAN_RES:
		{
			ST_BLE_DEVICE device = {0};
			memcpy(&device,report.payload,sizeof(device));

			/*const unsigned char* pDevName  = device.device_name;

			unsigned char szMac[25] = {0};
			sprintf((char*)szMac,"%02X:%02X:%02X:%02X:%02X:%02X",device.addr[0],device.addr[1],device.addr[2],device.addr[3],device.addr[4],device.addr[5]);

			std::string strName = (char*)pDevName;
			std::string strMac = (char*)szMac;
			AddSlaveList(device.num,MultiCharToWideChar(strName).c_str(),MultiCharToWideChar(strMac).c_str());//*/
			AddSlaveList(device.num,device.device_name,device.addr);
		}
		break;
	case ROBOT_ORIGINAL_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			penInfo.nPress = (penInfo.nStatus == 0x11) ? 1 : 0;

			TRACE(_T("X:%d-Y:%d-Press:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress);

			/*CString str;
			str.Format(_T("ѹ�У�%d"),penInfo.nPress);
			GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);//*/

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_SLAVE_STATUS:
		{
			NODE_STATUS status = {0};
			memcpy(&status,report.payload,sizeof(NODE_STATUS));
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
			str.Format(_T("���߱ʼ�:%d��"),status.note_num);
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
		}
		break;
	case ROBOT_SYNC_TRANS_BEGIN:
		{
			CString str;
			str.Format(_T("���߱ʼ�:%d��"),report.reserved);
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
		}
		break;
	case ROBOT_SYNC_TRANS_END:
		{
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(_T("ͬ������"));
		}
		break;
	case ROBOT_SLAVE_VERSION:
		{
			memcpy(&m_nSlaveType,&report.payload,2);

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
	case ROBOT_FIRMWARE_DATA:
		m_pDlg->PostMessage(WM_PROCESS,report.payload[0],report.cmd_id);
		break;			
	case ROBOT_RAW_RESULT://У����
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_DEVICE_CHANGE://�豸�ı�
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_SYNC_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			//TRACE(_T("X:%d-Y:%d-Press:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress);

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_SET_NAME:
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_KEY_PRESS://��������
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
	case ROBOT_SHOW_PAGE://��ʾҳ��	
		{
			PAGE_INFO pageInfo = {0};
			memcpy(&pageInfo,report.payload,sizeof(pageInfo));

			CDrawDlg *pDlg = m_list[0];
			if (NULL != pDlg)
				pDlg->SetPage(pageInfo);
		}
		break;
	case ROBOT_ENTER_ADJUST_MODE:
		GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("����У׼ģʽ"));
		break;
	case ROBOT_MODULE_ADJUST_RESULT:
		{
			CString str;
			int result = report.payload[0];
			switch(result)
			{
			case ADJUST_SUCCESSED:
				str = _T("У׼�ɹ�");
				break;
			case ADJUST_FAILED:
				str = _T("У׼ʧ��");
				break;
			case ADJUST_TIMEOUT:
				str = _T("У׼��ʱ");
				break;
			default:
				break;
			}
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
		}
		break;
	case ROBOT_OPTIMIZE_PACKET:
		{
			PEN_INFOF penInfof = {0};
			memcpy(&penInfof,report.payload,sizeof(PEN_INFOF));
			TRACE(_T("DONGLE X:%d-Y:%d-Status:%d-Width:%f\n"),penInfof.nX,penInfof.nY,penInfof.nStatus,penInfof.fWidth);

			PEN_INFO penInfo = {0};
			penInfo.nX = penInfof.nX;
			penInfo.nY = penInfof.nY;
			penInfo.nStatus = penInfof.nStatus;
			if (penInfof.nStatus == 17)
				penInfo.nPress = 1;
			else
				penInfo.nPress = 0;

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_DONGLE_BIND:
		{
			CListCtrl *pListView = (CListCtrl*)GetDlgItem(IDC_LIST_SLAVE);
			POSITION pos = pListView->GetFirstSelectedItemPosition();
			int nItem = pListView->GetNextSelectedItem(pos);
			CString strNum = pListView->GetItemText(nItem, 0);
			int nNum = atoi(WideStrToMultiStr(strNum.GetBuffer()));
			GetInstance()->ConnectSlave(nNum);
		}
		break;
	case ROBOT_GET_DEVICE_ID:
		{
			__int64 id;
			memcpy(&id,report.payload,5);
			CString str;
			str.Format(_T("%I64d"),id);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
		}
		break;
	case ROBOT_VIRTUAL_KEY_PRESS:
		{
			uint8_t nKey = report.payload[0];
			CString str;
			str.Format(_T("%d"),nKey);
			GetDlgItem(IDC_STATIC_SLAVE_STATUS)->SetWindowText(str);
		}
		break;
	default:
		break;
	}
}

void CUSBHelperDlg::OnBnClickedButtonScan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));
	if (NULL == pListView)
		return;
	for (int i=0;i<pListView->GetItemCount();i++)
	{
		unsigned char *pMac = (unsigned char*)pListView->GetItemData(i);
		if (pMac)
		{
			delete pMac;
			pMac = NULL;
		}
	}//*/
	pListView->DeleteAllItems();

	GetInstance()->Send(DongleScanStart);
}

void CUSBHelperDlg::OnBnClickedButtonScanStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(DongleScanStop);
}

void CUSBHelperDlg::OnBnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListCtrl *pListView = (CListCtrl*)GetDlgItem(IDC_LIST_SLAVE);
	POSITION pos = pListView->GetFirstSelectedItemPosition();
	if (pos == nullptr)
	{
		MessageBox(_T("����ѡ���豸!"), _T("��ʾ"), IDOK);
		return;
	}

	int nItem = pListView->GetNextSelectedItem(pos);
	CString strNum = pListView->GetItemText(nItem, 0);
#ifdef _CY
	unsigned char *pMac = (unsigned char*)pListView->GetItemData(nItem);
	GetInstance()->Bind(pMac);
#else
	int nNum = atoi(WideStrToMultiStr(strNum.GetBuffer()));
	GetInstance()->ConnectSlave(nNum);
#endif
}

void CUSBHelperDlg::OnBnClickedButtonDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(DongleDisconnect);
}

void CUSBHelperDlg::AddSlaveList(int nNum,unsigned char *name,unsigned char *mac)
{
	char szMac[25] = {0};
	sprintf((char*)szMac,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

	std::string strName = (char*)name;
	std::string strMac = (char*)szMac;

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

	CString strName_ = MultiCharToWideChar(strName).c_str();
	CString strMac_ = MultiCharToWideChar(strMac).c_str();

	if (SalveExist(strName_,strMac_))
		return;

	CString strID;
	strID.Format(_T("%d"),nNum);
	pListView->InsertItem(nIndex,strID);
	pListView->SetItemText(nIndex,1,strName_);
	pListView->SetItemText(nIndex,2,strMac_);

	unsigned char *pMac = new unsigned char[6];
	memcpy(pMac,mac,6);
	pListView->SetItemData(nIndex,(DWORD)pMac);
}

bool CUSBHelperDlg::SalveExist(CString name,CString mac)
{
	CListCtrl* pListView = static_cast<CListCtrl*>(GetDlgItem(IDC_LIST_SLAVE));

	for (int i=0;i<pListView->GetItemCount();i++)
	{
		CString strName = pListView->GetItemText(i,1);
		CString strMac = pListView->GetItemText(i,2);
		if (name == strName && mac == strMac)
			return true;
	}

	return false;
}

void CUSBHelperDlg::OnBnClickedButtonSetName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT_SLAVE_NAME)->GetWindowText(str);

	GetInstance()->SetSlaveName(WideCharToMultichar(str.GetBuffer()).c_str());
}

void CUSBHelperDlg::OnBnClickedButtonSyncStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(SyncBegin);
}

void CUSBHelperDlg::OnBnClickedButtonSyncStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(SyncEnd);
}

void CUSBHelperDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#ifdef _NODE
	CString str;
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	if (nIndex < 0)
		return;
	m_pWBDlg->Clear();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nIndex,str);
	int nNoteNum = atoi(WideCharToMultichar(str.GetBuffer()).c_str());
	if (nNoteNum < MAX_NOTE)
	{
		for(int j=0;j<vecPenInfo[nNoteNum].size();j++)
		{
			m_pWBDlg->onRecvData(vecPenInfo[nNoteNum][j]);
		}
	}
#endif
}

void CUSBHelperDlg::OnBnClickedButtonSyncOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pWBDlg->ShowWindow(SW_SHOW);
}

void CUSBHelperDlg::OnBnClickedButton3Reset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(RESET_NODE);
	//GetInstance()->SetPage(255);
}


void CUSBHelperDlg::OnBnClickedButtonAdjust()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(AdjustMode);
}

void CUSBHelperDlg::DeleteDir(CString str)
{
	CFileFind finder;
	CString strdel,strdir;
	strdir = str + _T("\\*");
	BOOL b_found=finder.FindFile(strdir,0); 
	while(b_found) 
	{
		b_found=finder.FindNextFile(); 
		strdel=finder.GetFileName(); 
		strdel=str+ "\\" + strdel;
		if(finder.IsReadOnly())//���ֻ������
		{    
			SetFileAttributes(strdel,GetFileAttributes(strdel)&(~FILE_ATTRIBUTE_READONLY));
		}
		DeleteFile(strdel); //ɾ���ļ�
	}
	finder.Close();
}

UINT CUSBHelperDlg::OnPowerBroadcast(UINT nPowerEvent, UINT nEventData)
{
	//OnBnClickedButtonStatus();
	OnBnClickedButton3Open();

	return CDialogEx::OnPowerBroadcast(nPowerEvent, nEventData);
}


BOOL CUSBHelperDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	//����ESC�رմ���/
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE ) return TRUE;
	//���λس��رմ���,���ᵼ�»س��ڴ�����ʧЧ.
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN && pMsg->wParam) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUSBHelperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 0:
		{
			/*CString str;
			GetDlgItem(IDC_STATIC_VERSION)->GetWindowText(str);
			if (!str.IsEmpty())
			{
				KillTimer(0);
				break;
			}//*/
			KillTimer(0);
			OnBnClickedButtonStatus();
		}
		break;
	case 1:
		{
			KillTimer(1);
			this->SendMessage(WM_UPDATE,1,START_UPADTE_DONGLE);
		}
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUSBHelperDlg::OnBnClickedButtonGetId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(GetDeviceID);
}


void CUSBHelperDlg::OnBnClickedButton3Reset2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(RESET_ALL);
}


void CUSBHelperDlg::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT_SSID)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetClassSSID((unsigned char*)buffer,strlen(buffer));
}


void CUSBHelperDlg::OnBnClickedButtonSet2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT_CPWD)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetClassPwd((unsigned char*)buffer,strlen(buffer));
}


void CUSBHelperDlg::OnBnClickedButtonSet3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*unsigned char buffer[6] = {0};
	CString str;
	GetDlgItem(IDC_EDIT_SID)->GetWindowText(str);
	int len = str.GetLength();
	int index = 0;
	for (int i=0;i<len;i+=2)
	{
		CString strNum = str.Mid(i,2);
		buffer[index++] = strtoul(WideStrToMultiStr(strNum.GetBuffer()),NULL,16);
	}//*/
	CString str;
	GetDlgItem(IDC_EDIT_SID)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetStudentID((unsigned char*)buffer,strlen(buffer));
}


void CUSBHelperDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(UpdateSearch);
}


void CUSBHelperDlg::OnBnClickedButtonUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetInstance()->Send(UpdateWifi);
}


void CUSBHelperDlg::OnBnClickedButtonSet4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char buffer[20] = {0};
	CString str;
	GetDlgItem(IDC_EDIT_MQTT)->GetWindowText(str);
	int len = str.GetLength();
	int index = 0;
	for (int i=0;i<len;i+=2)
	{
		CString strNum = str.Mid(i,2);
		buffer[index++] = strtoul(WideStrToMultiStr(strNum.GetBuffer()),NULL,16);
	}
	GetInstance()->SetPwd(buffer);
}


void CUSBHelperDlg::OnBnClickedButtonSet5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT_SECRET)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetSecret((unsigned char*)buffer);
}
