
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

#define _VERSION  _T("版本号:1.1.6.6")

#define RESET_NODE 0x2a
#define RESET_ALL  0x29

//#define _GATEWAY
#define _NODE
//#define _DONGLE
//#define _P1
//#define _WIFI

//#define _CY

//#define TEST_COUNT
//#define TEST_T7E

//#define USE_POWER
//#define USE_OPTIMIZE

const char *szSubjectArray[] = { "未选","语文","数学","英语","物理","化学","生物","历史","地理","政治","自然","科一" ,"科二","科三","科四","科五","科六","科七","科八","科九","科十"};

#define B2S(b) (((b[0] & 0xff) << 8) | (b[1] & 0xff)) 

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
	, m_DeviceMode(DEVICE_MOUSE)
	, m_bActive(false)
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
	ON_BN_CLICKED(IDC_BUTTON_SET6, &CUSBHelperDlg::OnBnClickedButtonSet6)
	ON_CBN_SELCHANGE(IDC_COMBO_PEN, &CUSBHelperDlg::OnCbnSelchangeComboPen)
	ON_BN_CLICKED(IDC_BUTTON_SER_PEN, &CUSBHelperDlg::OnBnClickedButtonSerPen)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SLAVE, &CUSBHelperDlg::OnLvnItemchangedListSlave)
	ON_BN_CLICKED(IDC_ADJUST_VALUE, &CUSBHelperDlg::OnBnClickedAdjustValue)
	ON_EN_CHANGE(IDC_EDIT_REMOTE, &CUSBHelperDlg::OnEnChangeEditRemote)
	ON_BN_CLICKED(IDC_BUTTON_SET_ADJUST_VALUE, &CUSBHelperDlg::OnBnClickedButtonSetAdjustValue)
	ON_EN_CHANGE(IDC_EDIT4, &CUSBHelperDlg::OnEnChangeEdit4)
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
	GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_OPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GET_ID)->ShowWindow(SW_HIDE);
	SetWindowText(_T("GATEWAY"));

	DeleteDir(GetDataFloder());
	CreateAllDirectories(GetDataFloder());
#endif

#ifdef _NODE
	//GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->ShowWindow(SW_HIDE);
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
	//GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->SetWindowText(_T("删除笔记"));
	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->SetWindowText(_T("查询硬件"));

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
	GetDlgItem(IDC_ADJUST_VALUE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET_ADJUST_VALUE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ADJUST_VALUE1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
	
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

	GetDlgItem(IDC_STATIC_MAC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_MAC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ADJUST_VALUE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
#endif

#ifdef _DONGLE
	GetDlgItem(IDC_STATIC_MODE_NAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->SetWindowText(_T("删除笔记"));
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
	GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SYNC_OPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_SHOW);
	SetWindowText(_T("DONGLE"));
	GetDlgItem(IDC_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ADJUST_VALUE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);

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
	GetDlgItem(IDC_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ADJUST_VALUE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);

	SetWindowText(_T("P1"));
#endif

#ifdef _CY
	GetDlgItem(IDC_BUTTON_ADJUST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(_T("绑定"));
	GetDlgItem(IDC_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET_ADJUST_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ADJUST_VALUE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
#endif

	GetInstance()->SetKey("robotpen");

	((CComboBox*)GetDlgItem(IDC_COMBO_PEN))->InsertString(0,_T("M2"));
	((CComboBox*)GetDlgItem(IDC_COMBO_PEN))->InsertString(1,_T("M3K"));
	((CComboBox*)GetDlgItem(IDC_COMBO_PEN))->InsertString(2,_T("M3"));
	((CComboBox*)GetDlgItem(IDC_COMBO_PEN))->SetCurSel(0);

	GetDlgItem(IDC_BUTTON3_RESET2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3_RESET)->ShowWindow(SW_SHOW);

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
	m_pWBDlg->SetWindowText(_T("离线笔记"));
	//#else
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);//*/
	//#endif

	/*GetInstance()->SetPenWidth(2);
	GetInstance()->SetCanvasSize(960,669);//*/

	//==========================优化笔记设置======================
#ifdef USE_OPTIMIZE
	//开启压感
	GetInstance()->SetPressStatus(true);
	//开启笔记优化
	float fWidth = 2.0f;
	GetInstance()->SetOptimizeStatus(true);
	GetInstance()->SetPenWidth(fWidth);
	GetInstance()->SetPointDelay(0.28f);
	GetInstance()->SetPointDamping(0.026f);
	GetInstance()->SetEndWidth(fWidth*0.5f);

	//设置拖尾长度
	//GetInstance()->SetPointDelay(0.4);
#endif

	//GetInstance()->Rotate(360);

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
	pListView->InsertColumn(3, _T(""), LVCFMT_LEFT, 10);
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

			if (m_nDeviceType == T7E_TS || m_nDeviceType == T7E || m_nDeviceType == T7E_HFHH || m_nDeviceType == P1_CX_M3 
				|| m_nDeviceType == S1_DE || m_nDeviceType == J7E)
			{
				SetTimer(1,1000,NULL);
			}

			return;
		}
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
#ifndef _CY
		if (Dongle == m_nDeviceType)
		{
			GetInstance()->Send(DongleDisconnect);
			Sleep(300);
		}
		else if (T8B_D2 == m_nDeviceType || T8S == m_nDeviceType || T8S_LQ == m_nDeviceType)
		{
			GetInstance()->SetDeviceMode(DEVICE_MOUSE);
			Sleep(300);
		}
#endif
		/*else if (X8 == m_nDeviceType)
		{
		GetInstance()->Send(ExitUsb);
		Sleep(100);
		}//*/
		if(T8S != m_nDeviceType/* && T8Y != m_nDeviceType*/){
			GetInstance()->ConnectDispose();
		}
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

	m_nDeviceType = (eDeviceType)((CListCtrl*)GetDlgItem(IDC_LIST_USB_DEVICE))->GetItemData(nItem);

	GetInstance()->ConnectInitialize(m_nDeviceType,getUsbData,this);

	int nRes = GetInstance()->ConnectOpen();
	ASSERT(nRes == 0);
	if(nRes == 0)
		GetDlgItem(IDC_BUTTON3_OPEN)->SetWindowText(_T("关闭设备"));

	if (nRes != 0)
	{
		CString str;
		str.Format(_T("打开失败,错误码:%d"),nRes);
		AfxMessageBox(str);
	}

	if(T8Y == m_nDeviceType)
	{
		GetInstance()->Send(EnterUsb);
	}

	/*GetDlgItem(IDC_BUTTON_VOTE)->EnableWindow(!m_bNode);
	GetDlgItem(IDC_BUTTON_VOTE_OFF)->EnableWindow(!m_bNode);//*/
	bool bShow = (m_nDeviceType == Gateway) ? TRUE : FALSE;
	//GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->EnableWindow(bShow);
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
		GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("发起投票"));
		GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("结束投票"));
	}
	else if(m_nDeviceType == T8A || m_nDeviceType == T9A || m_nDeviceType == T9_J0  || m_nDeviceType == J0_A4_P 
		|| m_nDeviceType == T9E || m_nDeviceType == J0_T9 || m_nDeviceType == T8B ||m_nDeviceType == T9B_YD
		|| m_nDeviceType == T8C || m_nDeviceType == T9W || m_nDeviceType == T9W_TY || T9B_YD2 == m_nDeviceType
		|| T9W_QX == m_nDeviceType || T9W_YJ == m_nDeviceType || T9W_WX == m_nDeviceType || m_nDeviceType == T8B_DH2
		|| T9W_B_KZ == m_nDeviceType || C5 == m_nDeviceType || T9B == m_nDeviceType || T9B_ZXB == m_nDeviceType
		|| T8B_D2 == m_nDeviceType || T8S_LQ == m_nDeviceType || m_nDeviceType == X9 || m_nDeviceType == T9W_H || m_nDeviceType == T10)
	{
		GetDlgItem(IDC_BUTTON_VOTE)->SetWindowText(_T("开始同步"));
		GetDlgItem(IDC_BUTTON_VOTE_OFF)->SetWindowText(_T("结束同步"));
	}
	else if (m_nDeviceType == X8 || m_nDeviceType == T7PL || m_nDeviceType == X8E_A5 
		|| m_nDeviceType == T7E || m_nDeviceType == P1_CX_M3 || m_nDeviceType == S1_DE
		|| m_nDeviceType == J7E || m_nDeviceType == K7_HW || m_nDeviceType == K8 || m_nDeviceType == K8_ZM
		|| m_nDeviceType == T7PL_CL || m_nDeviceType == T7PL_XDF || m_nDeviceType == K8_HF || m_nDeviceType == K8)
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

	if(m_nDeviceType == T7PL || m_nDeviceType == T7E || m_nDeviceType == S1_DE 
		|| m_nDeviceType == J7E || m_nDeviceType == K7_HW || m_nDeviceType == T7PL_CL 
		|| m_nDeviceType == T8B_D2 || m_nDeviceType == T8S_LQ || m_nDeviceType == J7B_ZY
		|| m_nDeviceType == T7PL_XDF || m_nDeviceType == K8_HF  || m_nDeviceType == K8_ZM || m_nDeviceType == T8S|| m_nDeviceType == K8 || m_nDeviceType == J7M || m_nDeviceType == X10_B || m_nDeviceType == T8Y)
	{
		GetDlgItem(IDC_BUTTON3_SHOW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON3_SHOW)->SetWindowText(_T("切换"));
		Sleep(100);
		GetInstance()->Send(SearchMode);
	}

	if(K8 ==  m_nDeviceType || K8_HF ==  m_nDeviceType || m_nDeviceType == K8_ZM || m_nDeviceType == T8S || m_nDeviceType == X10_B)
	{
		GetDlgItem(IDC_BUTTON_VOTE_CLEAR)->SetWindowText(_T("K8切换生效"));

		Sleep(200);

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

	//GetInstance()->Rotate(180);

	//GetInstance()->SetPaperType(eA4);

	/*if (m_nDeviceType == X8 || m_nDeviceType == T7B_HF || m_nDeviceType == J7B_ZY)
	GetInstance()->Send(GetMac);//*/

}

void CUSBHelperDlg::OnDestroy()		//--by zlp 2016/9/26
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	//resetDevice();

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

	mapSyncInfo.clear();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	m_pWBDlg->Clear();
	mapRtc.clear();

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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_nDeviceType == Gateway)
		GetInstance()->Send(VoteEnd);
	else
		GetInstance()->Send(SyncEnd);
}

void CUSBHelperDlg::OnBnClickedButtonVoteClear()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nDeviceType == Gateway)
	{
		for (int i=0;i<m_list.size();i++)
		{
			CDrawDlg *pDlg = m_list[i];
			if (NULL != pDlg)
				pDlg->SetVote();
		}
	}
	else if(K8 == m_nDeviceType || K8_HF == m_nDeviceType || m_nDeviceType == K8_ZM || m_nDeviceType == X10_B)
	{
		m_bActive = !m_bActive;
		GetInstance()->SetButtonActive(m_bActive);
	}
	else if(T9W_H == m_nDeviceType || C5 == m_nDeviceType || T10 == m_nDeviceType)
	{
		GetInstance()->Send(eRbtType::GetProperty);
	}
	else
	{
		GetInstance()->Send(DeleteSync);
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
			//pDlg->SetVote(str);
			pDlg->Create(IDD_DRAWDLG,this);
			pDlg->MoveWindow(nHStart + i*nSpaceMax,nVStart + j*nSpaceMax,nItemSize,nItemSize); 
#ifdef _GATEWAY
			pDlg->SetText(str);
			pDlg->SetID(m_list.size());
#else
			pDlg->SetText(_T("双击显示画布"));
#endif
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

#ifdef TEST_COUNT
	m_nIndexCount = 0;
	CString str;
	str.Format(_T("%d"),m_nIndexCount);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);
#endif
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
	// TODO: 在此添加控件通知处理程序代码
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
		if(m_nDeviceType == T8Y)
		{
			if(m_strFileBle.IsEmpty())
			{
				if(!m_strFileMcu.IsEmpty())
				{
					GetInstance()->UpdateMcu(WideStrToMultiStr(m_strFileMcu.GetBuffer()));
				}
			}else{
				GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),WideStrToMultiStr(m_strFileBle.GetBuffer()));
			}
		}else{
			GetInstance()->Update(WideStrToMultiStr(m_strFileMcu.GetBuffer()),WideStrToMultiStr(m_strFileBle.GetBuffer()));	
		}
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
	case SET_FONT:
		{
			BSTR b = (BSTR)wParam;
			CString str(b);
			GetInstance()->UpdateFont(WideStrToMultiStr(str.GetBuffer()));
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
	case ROBOT_RAW_RESULT://校验结果
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
					GetInstance()->Send(DongleVersion);
				}
				else if (m_nDeviceType == T7PL 
					|| m_nDeviceType == K7_HW 
					|| m_nDeviceType == K8 
					|| m_nDeviceType == T7PL_CL
					|| m_nDeviceType == T7PL_XDF
					|| m_nDeviceType == K8_HF)
				{
					resetDevice();
					AddList();
				}
			}
		}
		break;
	case ROBOT_SET_CLASS_SSID:
	case ROBOT_SET_CLASS_PWD:
	case ROBOT_SET_STUDENT_ID:
	case ROBOT_UPDATE_WIFI:
	case ROBOT_SET_SECRET:
		{
			if (wParam == 0)
				AfxMessageBox(_T("设置成功！"));
			else
				AfxMessageBox(_T("设置失败！"));

		}
		break;
	case ROBOT_SET_DEVICE_NUM:
		{
			if (wParam == 0)
				AfxMessageBox(_T("设置成功！"));
			else
				AfxMessageBox(_T("设置失败！"));
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
		AfxMessageBox(_T("设置成功！"));
		break;
	case ROBOT_MODULE_ADJUST_RESULT:
		{
			CString str;
			switch(wParam)
			{
			case ADJUST_SUCCESSED:
				str = _T("校准成功");
				break;
			case ADJUST_FAILED:
				str = _T("校准失败");
				break;
			case ADJUST_TIMEOUT:
				str = _T("校准超时");
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
	// TODO: 在此添加控件通知处理程序代码
	if(m_nDeviceType == T7PL || m_nDeviceType == T7E || m_nDeviceType == S1_DE
		|| m_nDeviceType == J7E || m_nDeviceType == K7_HW || m_nDeviceType == K8
		|| m_nDeviceType == T7PL_CL || m_nDeviceType == T7PL_XDF)
	{
		GetInstance()->Send(SwitchMode);
		//GetInstance()->SetDeviceMode(DEVICE_HAND);
		Sleep(100);
	}
	else if (m_nDeviceType == T8B_D2 || m_nDeviceType == T8S_LQ || m_nDeviceType == J7B_ZY || m_nDeviceType == K8_HF|| m_nDeviceType == K8_ZM || m_nDeviceType == T8S || m_nDeviceType == J7M || m_nDeviceType == X10_B || m_nDeviceType == T8Y)
	{
		if (DEVICE_MOUSE == m_DeviceMode)
			m_DeviceMode = DEVICE_HAND;
		else
			m_DeviceMode = DEVICE_MOUSE;
		GetInstance()->SetDeviceMode(m_DeviceMode);
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
//解析nebula命令
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
	case ROBOT_GATEWAY_STATUS://获取状态
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
			unsigned char szByte[2] = {0};
			szByte[0] = status.note_num_h;
			szByte[1] = status.note_num;
			int noteNum = B2S(szByte);
			str.Format(_T("离线笔记:%d条"),noteNum);
			GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(str);

			((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetRange(0,status.note_num);
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
	case ROBOT_MASS_DATA://大数据上报
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
			int pageTotalID = 0;
			memcpy(&pageTotalID,&pageInfo,sizeof(pageInfo));
			TRACE("ROBOT_SHOW_PAGE:%d,note_num:%d,page_num:%d",pageTotalID,pageInfo.note_num,pageInfo.page_num);

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
	case  ROBOT_SHOW_OID_PAGE:
		{
			OID_PAGE_INFO pageInfo;
			memcpy(&pageInfo,report.payload,sizeof(pageInfo));
			TRACE("ROBOT_SHOW_OID_PAGE: x: %f, y: %f, angle:%d\r\n",pageInfo.fX,pageInfo.fY, pageInfo.fAngle);
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
			str.Format(_T("%d.%d.%d.%d 硬件号:%d"),info.version.version4,info.version.version3,info.version.version2,info.version.version,info.hardware_num);
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
#ifdef _NODE
			//查询硬件信息
			GetInstance()->Send(31);
#endif // _NODE
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
		{
			/*CString str;
			str.Format(_T("ROBOT_DEVICE_CHANGE:%d"),report.reserved);
			WriteLog(str);//*/

			TRACE("==============%d ,,,,,%d\r\n", report.reserved, report.payload[0]);

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
	case ROBOT_ORIGINAL_PACKET://USB坐标
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			//TRACE(_T("ROBOT_ORIGINAL_PACKET X:%d-Y:%d-Press:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress,penInfo.nStatus);
			if (T7B_HF		==	m_nDeviceType
				|| T7E		==	m_nDeviceType
				|| S1_DE	==	m_nDeviceType
				|| J7E		==	m_nDeviceType
				|| J7B_HF	==	m_nDeviceType
				|| J7B_ZY	==	m_nDeviceType
				|| T8S      ==	m_nDeviceType
				|| T8B_D2 == m_nDeviceType
				|| T8S_LQ == m_nDeviceType
				|| J7M == m_nDeviceType
				|| T8Y == m_nDeviceType
				)
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
			}//*/

			/*CString str;
			str.Format(_T("Press:%d"),penInfo.nPress);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);*/
			CString str;
			str.Format(_T("Press:%d"),penInfo.nPress);
			GetDlgItem(IDC_EDIT4)->SetWindowText(str);

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
			case PAGEUPCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUPCLICK"));
				break;
			case PAGEUPDBCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUPDBCLICK"));
				break;
			case PAGEUPPRESS:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUPPRESS"));
				break;
			case PAGEDOWNCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWNCLICK"));
				break;
			case PAGEDOWNDBCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWNDBCLICK"));
				break;
			case PAGEDOWNPRESS:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWNPRESS"));
				break;
			case KEY_A:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_A"));
				break;
			case KEY_B:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_B"));
				break;
			case KEY_C:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_C"));
				break;
			case KEY_D:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_D"));
				break;
			case KEY_E:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_E"));
				break;
			case KEY_F:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_F"));
				break;
			case KEY_UP:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_UP"));
				break;
			case KEY_DOWN:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_DOWN"));
				break;
			case KEY_YES:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_YES"));
				break;
			case KEY_NO:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_NO"));
				break;
			case KEY_CANCEL:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_CANCEL"));
				break;
			case KEY_OK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("KEY_OK"));
				break;
			case SELF1CLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("SELF1CLICK"));
				break;
			case SELF1DBCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("SELF1DBCLICK"));
				break;
			case SELF1PRESS:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("SELF1PRESS"));
				break;
			case SELF2CLICK:
				{
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("SELF2CLICK"));
					Send(SwitchMode);
				}
				break;
			case SELF2DBCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("SELF2DBCLICK"));
				break;
			case SELF2PRESS:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("SELF2PRESS"));
				break;
			default:
				{
					CString str;
					str.Format(_T("Press:%d"),nStatus);
					GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
				}
				break;
			}
		}
		break;
	case ROBOT_SYNC_TRANS_BEGIN:
		{
			CString strID;
			if (T9B == m_nDeviceType || T9B_ZXB == m_nDeviceType)
			{
				ST_T9_NOTE_HEADER_INFO info = {0};
				memcpy(&info,report.payload,sizeof(ST_T9_NOTE_HEADER_INFO));

				memcpy(&m_nCurNoteNum,&info.note_number,sizeof(info.note_number));

				strID.Format(_T("%d"),info.note_number);
			}
			else if (T9W_B_KZ == m_nDeviceType)
			{
				ST_KZ_NOTE_HEADER_INFO info = {0};
				memcpy(&info,report.payload,sizeof(ST_KZ_NOTE_HEADER_INFO));

				m_nCurNoteNum = ((info.note_current_subject << 8) | info.note_current_topic);

				strID.Format(_T("%d"),m_nCurNoteNum);

				RTC_INFO rtc = {0};
				rtc.useTimes = info.note_use_times;
				memcpy(&rtc.rtc,&info.rtc,sizeof(ST_RTC_INFO));

				TRACE(_T("note_current_subject:%d,note_current_topic:%d,useTimes:%d>>>>>>>%d:%d:%d:%d:%d\n"),info.note_current_subject,info.note_current_topic,info.note_use_times
					,rtc.rtc.note_time_year,rtc.rtc.note_time_month,rtc.rtc.note_time_day,rtc.rtc.note_time_hour,rtc.rtc.note_time_min);

				mapRtc[m_nCurNoteNum].vecRtcInfo.push_back(rtc);
			}else if( J7B == report.reserved || J7M == report.reserved)
			{
				ST_ELITE_HEADER_INFO info = {0};
				memcpy(&info,report.payload,sizeof(ST_ELITE_HEADER_INFO));
				memcpy(&m_nCurNoteNum,&info.note_number,sizeof(info.note_number));
				strID.Format(_T("%d"),info.note_number);
			}
			else
			{
				ST_NOTE_HEADER_INFO info = {0};
				memcpy(&info,report.payload,sizeof(ST_NOTE_HEADER_INFO));

				m_nCurNoteNum = info.note_number;

				strID.Format(_T("%d"),info.note_number);
			}


			bool bExist = false;
			int nCount = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();
			for (int i=0;i<nCount;i++)
			{
				CString strTemp;
				((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(i,strTemp);
				if (strTemp == strID)
				{
					bExist = true;
					break;
				}
			}
			if (!bExist)
				((CComboBox*)GetDlgItem(IDC_COMBO1))->InsertString(nCount,strID);

			((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->StepIt();

			CString str;
			str.Format(_T("离线笔记:%d条"),report.reserved);
			GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(str);
		}
		break;
	case ROBOT_SYNC_TRANS_END:
		{
			GetDlgItem(IDC_STATIC_NOTE2)->SetWindowText(_T("同步结束"));
			if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
				((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

			OnCbnSelchangeCombo1();
		}
		break;
	case ROBOT_SYNC_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			//TRACE(_T("X:%d-Y:%d-Press:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress,penInfo.nStatus);

			//T9A
			mapSyncInfo[m_nCurNoteNum].vecPenInfo.push_back(penInfo);

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
		{
			//GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("进入校准模式"));
			CString str;
			str.Format(_T("ret:%d,L;%d,H:%d\n"),report.payload[0],report.payload[1],report.payload[2]);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
		}
		break;
	case ROBOT_MODULE_ADJUST_RESULT:
		{
			this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
			/*CString str;
			int result = report.payload[0];
			switch(result)
			{
			case ADJUST_SUCCESSED:
			str = _T("校准成功");
			break;
			case ADJUST_FAILED:
			str = _T("校准失败");
			break;
			case ADJUST_TIMEOUT:
			str = _T("校准超时");
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
			TRACE(_T("OPTIMIZE X:%d-Y:%d-Status:%d-Width:%.2f-Speed:%.2f\n"),penInfof.nX,penInfof.nY,penInfof.nStatus,penInfof.fWidth,penInfof.fSpeed);

			PEN_INFO penInfo = {0};
			penInfo.nX = penInfof.nX;
			penInfo.nY = penInfof.nY;
			penInfo.nStatus = penInfof.nStatus;
			if (penInfof.fWidth > 0)
				penInfo.nPress = 1;
			else
				penInfo.nPress = 0;

			m_list[0]->AddData(penInfo, penInfof.fWidth);
		}
		break;
	case ROBOT_SEARCH_MODE:
		{
			uint8_t mode = report.payload[0];
			m_DeviceMode = (eDeviceMode)mode;

			if (mode)
				GetDlgItem(IDC_STATIC_SCANTIP2)->SetWindowText(_T("Hand"));
			else
				GetDlgItem(IDC_STATIC_SCANTIP2)->SetWindowText(_T("Mouse"));

			//GetInstance()->Send(GetNodeInfo);
		}
		break;
	case ROBOT_SET_CLASS_SSID:
	case ROBOT_SET_CLASS_PWD:
	case ROBOT_SET_STUDENT_ID:
	case ROBOT_UPDATE_WIFI:
	case ROBOT_SET_SECRET:
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_UPDATE_SEARCH:
		{
			if (report.reserved == 1)
			{
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("UPDATE_SEARCH Error"));
			}
			else
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

		}
		break;
	case ROBOT_LOG_OUTPUT:
		{
			int len = report.reserved;
			char buffer[MAX_PATH] =  {0};
			memcpy(buffer,report.payload,len);
			USES_CONVERSION;
			CString str = A2W(buffer);
			TRACE(str);
			WriteLog(str);
		}
		break;
	case ROBOT_SWITCH_MODE:
		{
			uint8_t mode = report.payload[0];
			if (mode)
				GetDlgItem(IDC_STATIC_SCANTIP2)->SetWindowText(_T("Hand"));
			else
				GetDlgItem(IDC_STATIC_SCANTIP2)->SetWindowText(_T("Mouse"));
		}
		break;
	case ROBOT_PEN_TYPE:
		{
			uint8_t type = report.payload[0];
			((CComboBox*)GetDlgItem(IDC_COMBO_PEN))->SetCurSel(type-1);			
		}
		break;
	case ROBOT_SEARCH_STORAGE:
		{
			STORAGE_INFO storageInfo = {0};
			memcpy(&storageInfo,report.payload,sizeof(STORAGE_INFO));
			CString str;
			str.Format(_T("total:%d,free:%d"),storageInfo.total,storageInfo.free);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
		}
		break;
	case ROBOT_GET_PROPERTY:
		{
			HARD_INFO hardInfo = {0};
			memcpy(&hardInfo,report.payload,sizeof(HARD_INFO));
			CString str;
			str.Format(_T("XR:%d,YR%d,LPI:%d,PageNum:%d"),hardInfo.x_range,hardInfo.y_range,hardInfo.lpi,hardInfo.page_num);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
			AfxMessageBox(str);
		}
		break;
	case ROBOT_GET_ADJUST_VALUE:
		{
			int nValue = report.payload[0];
			TRACE(_T("ROBOT_GET_ADJUST_VALUE %d\n"),nValue);
			CString str;
			str.Format(_T("当前设备校准相位值:%d"),report.payload[0]);
			AfxMessageBox(str);
		}
		break;
	case ROBOT_SET_ADJUST_VALUE:
		{
			CString str;
			str.Format(_T("设置后的设备校准相位值:%d"),report.payload[0]);
			AfxMessageBox(str);
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
				case BLE_SCANNING:			//正在扫描	
					GetDlgItem(IDC_BUTTON_SCAN)->EnableWindow(FALSE);
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

						GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);

						m_bConnect = TRUE;
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

			//TRACE(_T("X:%d-Y:%d-Press:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress,penInfo.nStatus);

			/*CString str;
			str.Format(_T("压感：%d"),penInfo.nPress);
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
			str.Format(_T("离线笔记:%d条"),status.note_num);
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
		}
		break;
	case ROBOT_SYNC_TRANS_BEGIN:
		{
			CString str;
			str.Format(_T("离线笔记:%d条"),report.reserved);
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
		}
		break;
	case ROBOT_SYNC_TRANS_END:
		{
			GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(_T("同步结束"));
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
	case ROBOT_RAW_RESULT://校验结果
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_DEVICE_CHANGE://设备改变
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
		break;
	case ROBOT_SYNC_PACKET:
		{
			PEN_INFO penInfo = {0};
			memcpy(&penInfo,report.payload,sizeof(PEN_INFO));

			//TRACE(_T("X:%d-Y:%d-Press:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress,penInfo.nStatus);

			m_list[0]->AddData(penInfo);
		}
		break;
	case ROBOT_SET_NAME:
		this->PostMessage(WM_UPDATE_WINDOW,report.payload[0],report.cmd_id);
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
			case PAGEUPCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUPCLICK"));
				break;
			case PAGEUPDBCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUPDBCLICK"));
				break;
			case PAGEUPPRESS:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEUPPRESS"));
				break;
			case PAGEDOWNCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWNCLICK"));
				break;
			case PAGEDOWNDBCLICK:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWNDBCLICK"));
				break;
			case PAGEDOWNPRESS:
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("PAGEDOWNPRESS"));
				break;
			default:
				CString str;
				str.Format(_T("Press:%d"),nStatus);
				GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
				break;
			}
		}
		break;
	case ROBOT_SHOW_PAGE://显示页码	
		{
			PAGE_INFO pageInfo = {0};
			memcpy(&pageInfo,report.payload,sizeof(pageInfo));

			CDrawDlg *pDlg = m_list[0];
			if (NULL != pDlg)
				pDlg->SetPage(pageInfo);
		}
		break;
	case ROBOT_ENTER_ADJUST_MODE:
		GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(_T("进入校准模式"));
		break;
	case ROBOT_MODULE_ADJUST_RESULT:
		{
			CString str;
			int result = report.payload[0];
			switch(result)
			{
			case ADJUST_SUCCESSED:
				str = _T("校准成功");
				break;
			case ADJUST_FAILED:
				str = _T("校准失败");
				break;
			case ADJUST_TIMEOUT:
				str = _T("校准超时");
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
			TRACE(_T("OPTIMIZE X:%d-Y:%d-Status:%d-Width:%.2f-Speed:%.2f\n"),penInfof.nX,penInfof.nY,penInfof.nStatus,penInfof.fWidth,penInfof.fSpeed);

			PEN_INFO penInfo = { 0 };
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
	case ROBOT_SEARCH_STORAGE:
		{
			STORAGE_INFO storageInfo = {0};
			memcpy(&storageInfo,report.payload,sizeof(STORAGE_INFO));
			CString str;
			str.Format(_T("total:%d,free:%d"),storageInfo.total,storageInfo.free);
			GetDlgItem(IDC_STATIC_SCANTIP)->SetWindowText(str);
		}
		break;
	case ROBOT_DATA_PACKET:
		{
			//TRACE("ROBOT_DATA_PACKET\n");
		}
		break;
	case ROBOT_PAPER_TYPE:
		{
			TRACE("ROBOT_DATA_PACKET ===== >> %d\n", report.payload[0]);
		}
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
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(DongleScanStop);
}

void CUSBHelperDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl *pListView = (CListCtrl*)GetDlgItem(IDC_LIST_SLAVE);
	POSITION pos = pListView->GetFirstSelectedItemPosition();
	if (pos == nullptr)
	{
		MessageBox(_T("请先选中设备!"), _T("提示"), IDOK);
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
	// TODO: 在此添加控件通知处理程序代码
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
	if (T9W_B_KZ == m_nDeviceType)
	{
		PAGE_INFO pageInfo = {0};
		memcpy(&pageInfo,&nNoteNum,sizeof(pageInfo));
		CString strText;
		strText.Format(_T("subject:%s,topic:%d"),GetSubject(pageInfo.note_num),pageInfo.page_num);
		m_pWBDlg->SetText(strText);
		int nRow = mapRtc[nNoteNum].vecRtcInfo.size();
		for (int i=0;i<nRow;i++)
		{
			CString strText;
			const ST_RTC_INFO &rtc = mapRtc[nNoteNum].vecRtcInfo[i].rtc;
			int useTimes = mapRtc[nNoteNum].vecRtcInfo[i].useTimes;

			strText.Format(_T("note_current_subject:%d,note_current_topic:%d,useTimes:%d>>>>>>>%d:%d:%d:%d:%d\n"),pageInfo.note_num,pageInfo.page_num,useTimes
				,rtc.note_time_year,rtc.note_time_month,rtc.note_time_day,rtc.note_time_hour,rtc.note_time_min);

			OutputDebugStringW(strText.GetBuffer());
		}
	}

	for(int j=0;j<mapSyncInfo[nNoteNum].vecPenInfo.size();j++)
	{
		m_pWBDlg->onRecvData(mapSyncInfo[nNoteNum].vecPenInfo[j]);
	}
#endif
}

void CUSBHelperDlg::OnBnClickedButtonSyncOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	//if (DEVICE_MOUSE == m_DeviceMode)
	//	m_DeviceMode = DEVICE_HAND;
	//else
	//	m_DeviceMode = DEVICE_MOUSE;
	//GetInstance()->SetDeviceMode(m_DeviceMode);
	//return;
	CRect dlgRect;
	m_pWBDlg->GetWindowRect(dlgRect);
	m_pWBDlg->MoveWindow(50, 100, dlgRect.Width(), dlgRect.Height());
	m_pWBDlg->ShowWindow(SW_SHOW);
}

void CUSBHelperDlg::OnBnClickedButton3Reset()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(SearchStorage);
	//GetInstance()->Send(RESET_NODE);
	//GetInstance()->SetPage(255);
}


void CUSBHelperDlg::OnBnClickedButtonAdjust()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(AdjustMode);
	//GetInstance()->SetButtonActive(true);
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
		if(finder.IsReadOnly())//清除只读属性
		{    
			SetFileAttributes(strdel,GetFileAttributes(strdel)&(~FILE_ATTRIBUTE_READONLY));
		}
		DeleteFile(strdel); //删除文件
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
	// TODO: 在此添加专用代码和/或调用基类

	//屏蔽ESC关闭窗体/
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE ) return TRUE;
	//屏蔽回车关闭窗体,但会导致回车在窗体上失效.
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN && pMsg->wParam) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUSBHelperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(GetDeviceID);
}


void CUSBHelperDlg::OnBnClickedButton3Reset2()
{
	// TODO: 在此添加控件通知处理程序代码
	//恢复出厂设置
	GetInstance()->Send(RESET_ALL);
}


void CUSBHelperDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_SSID)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetClassSSID((unsigned char*)buffer,strlen(buffer));
}


void CUSBHelperDlg::OnBnClickedButtonSet2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_CPWD)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetClassPwd((unsigned char*)buffer,strlen(buffer));
}


void CUSBHelperDlg::OnBnClickedButtonSet3()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(UpdateSearch);
}


void CUSBHelperDlg::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(UpdateWifi);
}


void CUSBHelperDlg::OnBnClickedButtonSet4()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//GetInstance()->SetPwd(buffer);
}


void CUSBHelperDlg::OnBnClickedButtonSet5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_SECRET)->GetWindowText(str);
	char *buffer = WideStrToMultiStr(str.GetBuffer());
	GetInstance()->SetSecret((unsigned char*)buffer);
}

void CUSBHelperDlg::OnBnClickedButtonSet6()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char buffer[20] = {0};
	CString str;
	GetDlgItem(IDC_EDIT_MAC)->GetWindowText(str);
	int len = str.GetLength();
	int index = 0;
	for (int i=0;i<len;i+=2)
	{
		CString strNum = str.Mid(i,2);
		buffer[index++] = strtoul(WideStrToMultiStr(strNum.GetBuffer()),NULL,16);
	}
	GetInstance()->SetMac(m_nDeviceType,buffer,index);
}


void CUSBHelperDlg::OnCbnSelchangeComboPen()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_PEN))->GetCurSel() + 1;
	GetInstance()->SetPenType((ePenType)nIndex);
}


void CUSBHelperDlg::OnBnClickedButtonSerPen()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(GetPenType);
}

CString CUSBHelperDlg::GetSubject(int subject)
{
	CString str = MultiCharToWideChar(szSubjectArray[subject]).c_str();

	return str;
}


void CUSBHelperDlg::OnLvnItemchangedListSlave(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUSBHelperDlg::OnBnClickedAdjustValue()
{
	// TODO: 在此添加控件通知处理程序代码
	GetInstance()->Send(GetAdjustValue);
}


void CUSBHelperDlg::OnEnChangeEditRemote()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CUSBHelperDlg::OnBnClickedButtonSetAdjustValue()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_ADJUST_VALUE1)->GetWindowText(str);
	int nValue = atoi(WideStrToMultiStr(str.GetBuffer()));
	GetInstance()->SetAdujustValue(nValue);
}


void CUSBHelperDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
