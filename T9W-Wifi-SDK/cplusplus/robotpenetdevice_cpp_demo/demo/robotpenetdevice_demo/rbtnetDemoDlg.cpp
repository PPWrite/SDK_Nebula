
// rbtnetDemoDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "rbtnetDemoDlg.h"
#include "afxdialogex.h"
#include "DrawDlg.h"
#include "StuDlg.h"
#include <locale> 
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

//#define _TEST

//#define USE_OPT

#define USE_KDXF 

//#define USE_TEST_KEEPALIVE

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CrbtnetDemoDlg 对话框



CrbtnetDemoDlg::CrbtnetDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RBTNETDEMO_DIALOG, pParent)
	, m_pDlg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i = 0; i < 2; i++)
	{
		m_hEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	// 初始化
	::InitializeCriticalSectionAndSpinCount(&m_sectionLock, 4000);
}

void CrbtnetDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CrbtnetDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_STOP, &CrbtnetDemoDlg::OnBnClickedStartOrStop)
	ON_MESSAGE(WM_RCV_ACCEPT, &CrbtnetDemoDlg::rcvAccept)
	ON_MESSAGE(WM_RCV_MAC, &CrbtnetDemoDlg::rcvMac)
	ON_MESSAGE(WM_RCV_NAME, &CrbtnetDemoDlg::recvName)
	ON_MESSAGE(WM_SHOW_PAGE, &CrbtnetDemoDlg::showPage)
	ON_MESSAGE(WM_SHOW_ERROR, &CrbtnetDemoDlg::onShowError)
	ON_MESSAGE(WM_DISCONNECT, &CrbtnetDemoDlg::onDisconnect)
	ON_MESSAGE(WM_RCV_TYPE, &CrbtnetDemoDlg::rcvDeviceType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMDblclkListConnect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CrbtnetDemoDlg::OnBnClickedButtonConfig)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMRClickListConnect)
	ON_COMMAND(ID_SETTING_STU, &CrbtnetDemoDlg::OnSettingStu)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CrbtnetDemoDlg::OnBnClickedButtonSwitch)
	ON_BN_CLICKED(IDC_OPEN_MODULE, &CrbtnetDemoDlg::OnBnClickedOpenModule)
	ON_BN_CLICKED(IDC_CLOSE_MODULE, &CrbtnetDemoDlg::OnBnClickedCloseModule)
	ON_BN_CLICKED(IDC_BUTTON_START_ANSWER, &CrbtnetDemoDlg::OnBnClickedButtonStartAnswer)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ANSWER, &CrbtnetDemoDlg::OnBnClickedButtonStopAnswer)
	ON_BN_CLICKED(IDC_BUTTON_END_ANSWER, &CrbtnetDemoDlg::OnBnClickedButtonEndAnswer)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CrbtnetDemoDlg::OnBnClickedButtonSetting)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SET_FREQ, &CrbtnetDemoDlg::OnBnClickedButtonSetFreq)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CrbtnetDemoDlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CrbtnetDemoDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CrbtnetDemoDlg::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CrbtnetDemoDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CrbtnetDemoDlg::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_CVS, &CrbtnetDemoDlg::OnBnClickedButtonCvs)
	ON_BN_CLICKED(IDC_BUTTON_SET_KEEPALIVE, &CrbtnetDemoDlg::OnBnClickedButtonSetKeepalive)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMClickListConnect)
	ON_BN_CLICKED(IDC_BUTTON_DEL_NOTES, &CrbtnetDemoDlg::OnBnClickedButtonDelNotes)
END_MESSAGE_MAP()


// CrbtnetDemoDlg 消息处理程序

BOOL CrbtnetDemoDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Init_Param param;
	param.ctx = this;
	param.port = 6001;
	param.open = true;
	//param.open = false;
#ifdef USE_OPT
	param.optimize = true;
#else
	param.optimize = false;
#endif // USE_OPT
	param.listenCount = 128;

	rbt_win_init(&param);
	initCbFunction();
	initListControl();

	m_bRun = true;
	AfxBeginThread(ThreadProc, this);

	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(0, _T("主观题"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(1, _T("客观题"));
#ifdef USE_KDXF
	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(2, _T("投票"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(3, _T("不定选择"));
#endif
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(0, _T("判断"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(1, _T("单选"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(2, _T("多选"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(3, _T("抢答"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->SetCurSel(0);

	GetLocalAddress();

	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(0, _T("不抛点"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(1, _T("抛一个点"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(2, _T("抛两个点"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(3, _T("抛三个点"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(4, _T("抛四个点"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->SetCurSel(0);

	GetDlgItem(IDC_EDIT_NUM)->SetWindowText(_T("1"));

	m_pDlg = new CConfigDlg;
	m_pDlg->Create(IDD_CONFIGDLG);
	m_pDlg->ShowWindow(SW_HIDE);

	OnCbnSelchangeCombo2();

#ifdef _TEST
	SetTimer(0, 100, NULL);
#endif

#ifdef USE_KDXF
	GetDlgItem(IDC_STATIC_REFRESH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO_TIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CLOSE_MODULE)->ShowWindow(SW_SHOW);
	((CComboBox*)GetDlgItem(IDC_COMBO_TIME))->SetCurSel(0);
#endif // USE_KDXF

#ifdef USE_TEST_KEEPALIVE
	GetDlgItem(IDC_STATIC_KEEPALIVE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_KEEPALIVE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET_KEEPALIVE)->ShowWindow(SW_SHOW);
#endif // USE_TEST_KEEPALIVE


	GetDlgItem(IDC_EDIT_KEEPALIVE)->SetWindowText(_T("0,0,0,0"));

	((CComboBox*)GetDlgItem(IDC_COMBO_DEL_NOTES))->SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CrbtnetDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CrbtnetDemoDlg::OnPaint()
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
HCURSOR CrbtnetDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 接收到有设备连接
LRESULT CrbtnetDemoDlg::rcvAccept(WPARAM wParam, LPARAM lParam)
{
	return 0L;
}

// 收到mac地址认为上线
LRESULT CrbtnetDemoDlg::rcvMac(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = strMac;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1)
	{
		pListCtrl->SetItemText(nRowIndex, 2, _T("在线"));
	}
	else
	{
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, strMac);
		pListCtrl->SetItemText(nItemTotal, 2, _T("在线"));
		if (m_device2draw.find(strMac) != m_device2draw.end()) {
			if (m_device2draw[strMac])
			{
				m_device2draw[strMac]->DestroyWindow();
				m_device2draw[strMac] = NULL;
			}
		}

		m_device2draw[strMac] = new CDrawDlg();
		m_device2draw[strMac]->Create(IDD_DRAWDLG);
		m_device2draw[strMac]->ShowWindow(FALSE);

#ifdef USE_TEST_KEEPALIVE
		pListCtrl->SetItemText(nItemTotal, 6, _T("0"));
#endif // USE_TEST_KEEPALIVE
	}

	ShowOnlineCount();

	return 0L;
}
//收到设备类型
LRESULT CrbtnetDemoDlg::rcvDeviceType(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);


	int type = wParam;
	m_device2draw[strMac]->setDeviceType(type);

	CString strType;
	strType.Format(_T("%d"), type);

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = strMac;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1) {
		pListCtrl->SetItemText(nRowIndex, 6, strType);
	}

	return 0L;
}

LRESULT CrbtnetDemoDlg::recvName(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);

	b = (BSTR)wParam;
	CString strName(b);
	SysFreeString(b);

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = strMac;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex == -1) {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, strMac);
		pListCtrl->SetItemText(nItemTotal, 2, _T("在线"));
	}

	pListCtrl->SetItemText(nRowIndex, 1, strName);

	return 0L;
}

LRESULT CrbtnetDemoDlg::showPage(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);

	b = (BSTR)wParam;
	CString strText(b);
	SysFreeString(b);

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = strMac;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex == -1)
		return 0L;

	pListCtrl->SetItemText(nRowIndex, 5, strText);

	return 0L;
}

LRESULT CrbtnetDemoDlg::onShowError(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);

	CString strMsg;
	strMsg.Format(_T("MAC:%s,CMD:%d Error"), strMac, wParam);
	AfxMessageBox(strMsg);
	return 0L;
}

LRESULT CrbtnetDemoDlg::onDisconnect(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = strMac;

	if (strMac.IsEmpty())
		return 0;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1)
	{
		pListCtrl->SetItemText(nRowIndex, 2, _T("离线"));

#ifdef USE_TEST_KEEPALIVE
		CString str = pListCtrl->GetItemText(nRowIndex, 6);
		int nOffilneCount = _wtoi(str.GetBuffer());
		str.Format(_T("%d"), ++nOffilneCount);
		pListCtrl->SetItemText(nRowIndex, 6, str);
#endif // USE_TEST_KEEPALIVE

	}

	ShowOnlineCount();
}

// 开始启动
void CrbtnetDemoDlg::OnBnClickedStartOrStop()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(_T(""));
	CString csBtnText;
	GetDlgItemText(IDC_START_STOP, csBtnText);
	if (csBtnText == _T("开始")) {
		bool bStartRes = rbt_win_start();
		if (!bStartRes) {
			MessageBox(_T("开始失败"));
			return;
		}

		SetDlgItemText(IDC_START_STOP, _T("停止"));
	}
	else {
		rbt_win_stop();
		SetDlgItemText(IDC_START_STOP, _T("开始"));
		CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
		if (pListCtrl)
			pListCtrl->DeleteAllItems();

		for (auto it : m_device2draw)
		{
			if (it.second)
			{
				it.second->DestroyWindow();
				it.second = NULL;
			}
		}
		m_device2draw.clear();
	}
}

void CrbtnetDemoDlg::initListControl()
{
	CListCtrl* pListCtl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	DWORD dwStyle = pListCtl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	pListCtl->SetExtendedStyle(dwStyle);
	pListCtl->InsertColumn(0, _T("设备MAC地址"), LVCFMT_LEFT, 120);
	pListCtl->InsertColumn(1, _T("学号"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(2, _T("状态"), LVCFMT_LEFT, 60);
	pListCtl->InsertColumn(3, _T("选择题通知"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(4, _T("按键通知"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(5, _T("页码通知"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(6, _T("硬件号"), LVCFMT_LEFT, 50);
#ifdef USE_TEST_KEEPALIVE
	pListCtl->InsertColumn(6, _T("离线次数"), LVCFMT_LEFT, 50);
#endif
}

void CrbtnetDemoDlg::initCbFunction()
{
	rbt_win_set_accept_cb(onAccept);

	rbt_win_set_devivedisconnect_cb(onDeviceDisConnect);

	rbt_win_set_devicemac_cb(onDeviceMac);

	rbt_win_set_devicename_cb(onDeviceName);

	rbt_win_set_devicenameresult_cb(onDeviceNameResult);

	rbt_win_set_origindata_cb(onOriginData);

	rbt_win_set_devicekeypress_cb(onDeviceKeyPress);

	rbt_win_set_deviceanswerresult_cb(onDeviceAnswerResult);

	rbt_win_set_deviceshowpage_cb(onDeviceShowPage);

	rbt_win_set_error_cb(onError);

	rbt_win_set_canvasid_cb(onCanvasID);

	rbt_win_set_optimizedata_cb(onOptimizeData);

	rbt_win_set_devicetype_cb(onDeviceType);

	rbt_win_set_keyanswer_cb(onKeyAnswer);

	rbt_win_set_deletenotes_cb(onDeleteNotes);
}

void CrbtnetDemoDlg::onAccept(rbt_win_context* context, const char* pClientIpAddress)
{
	return;

	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_RCV_ACCEPT, 0, (LPARAM)pClientIpAddress);
}

void CrbtnetDemoDlg::onErrorPacket(rbt_win_context* context)
{
}

void CrbtnetDemoDlg::onOriginData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up, unsigned char *buffer, int len)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
#ifndef USE_OPT
	pThis->recvOriginData(pMac, us, ux, uy, up);
#endif // USE_OPT

}

void CrbtnetDemoDlg::onDeviceMac(rbt_win_context* context, const char* pMac)
{
	USES_CONVERSION;
	CString strMac = A2T(pMac);
	WriteLog(strMac, true);
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_RCV_MAC, 0, (LPARAM)strMac.AllocSysString());
}

void CrbtnetDemoDlg::onDeviceName(rbt_win_context* context, const char* pMac, const char* pName)
{
	USES_CONVERSION;
	CString strName = A2T(pName);
	CString strMac = A2T(pMac);
	WriteLog(strName, true);;
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_RCV_NAME, (WPARAM)strName.AllocSysString(), (LPARAM)strMac.AllocSysString());
}

void CrbtnetDemoDlg::onDeviceNameResult(rbt_win_context* context, const char* pMac, int res, const char* pName)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvNameResult(pMac, res, pName);
}

void CrbtnetDemoDlg::onDeviceDisConnect(rbt_win_context* context, const char* pMac)
{
	/*CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->deviceDisconnect(pMac);//*/
	USES_CONVERSION;
	CString strMac = A2T(pMac);

	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_DISCONNECT, NULL, (LPARAM)strMac.AllocSysString());
}

void CrbtnetDemoDlg::onDeviceKeyPress(rbt_win_context* context, const char* pMac, keyPressEnum keyValue)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvKeyPress(pMac, &keyValue);
}

void CrbtnetDemoDlg::onDeviceAnswerResult(rbt_win_context* context, const char* pMac, int resID, unsigned char* pResult, int nSize)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvDeviceAnswerResult(pMac, resID, pResult, nSize);
}

void CrbtnetDemoDlg::onDeviceShowPage(rbt_win_context* context, const char* pMac, int nNoteId, int nPageId, int nPageInfo)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvDeviceShowpage(pMac, nNoteId, nPageId);
}

void CrbtnetDemoDlg::onError(rbt_win_context* context, const char* pMac, int cmd, const char *msg)
{
	USES_CONVERSION;
	CString strMac = A2T(pMac);
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_SHOW_ERROR, cmd, (LPARAM)strMac.AllocSysString());
}

void CrbtnetDemoDlg::onCanvasID(rbt_win_context* context, const char* pMac, int type, int canvasID)
{
	TRACE("Mac:%d onCanvasID,type:%d,canvasID:%d\n", pMac, type, canvasID);
}

void CrbtnetDemoDlg::onOptimizeData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, float width, float speed)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
	pThis->recvOriginData(pMac, us, ux, uy, (width > 0) ? 1 : 0);
}

void CrbtnetDemoDlg::onDeviceType(rbt_win_context* context, const char* pMac, int type)
{
	USES_CONVERSION;
	CString strMac = A2T(pMac);
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_RCV_TYPE, type, (LPARAM)strMac.AllocSysString());
}

void CrbtnetDemoDlg::onKeyAnswer(rbt_win_context* context, const char* pMac, int key)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvKeyAnswer(pMac, key);
}

void CrbtnetDemoDlg::onDeleteNotes(rbt_win_context* context, const char* pMac, int result)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	TRACE("%s:result:%d\n", pMac, result);
	//::PostMessage(pThis->m_hWnd, WM_DEL_TYPE, result, (LPARAM)strMac.AllocSysString());
}

void CrbtnetDemoDlg::OnNMDblclkListConnect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	int nSubItem = pNMListView->iSubItem;
	CString strMac = pListCtrl->GetItemText(nItem, 0);
	USES_CONVERSION;
	if (m_device2draw.find(strMac) == m_device2draw.end()) {
		return;
	}

	m_device2draw[strMac]->SetWindowText(strMac);

	*pResult = 0;
}

UINT CrbtnetDemoDlg::ThreadProc(LPVOID lpParam)
{
	CrbtnetDemoDlg *pDlg = (CrbtnetDemoDlg*)lpParam;
	pDlg->ProcessMassData();

	return 0;
}

void CrbtnetDemoDlg::ProcessMassData()
{
	while (m_bRun)
	{
		/*if(WaitForSingleObject(m_hEvent[1],0) == WAIT_OBJECT_0 )
		break;//*/
		DWORD dwResult = WaitForMultipleObjects(2, m_hEvent, FALSE, INFINITE);

		switch (dwResult - WAIT_OBJECT_0)
		{
		case 0:
		{
			std::queue<_Mass_Data> tmpQueue;
			::EnterCriticalSection(&m_sectionLock);
			while (m_queueData.size() > 0)
			{
				tmpQueue.push(m_queueData.front());
				m_queueData.pop();
			}
			::LeaveCriticalSection(&m_sectionLock);

			while (tmpQueue.size() > 0)
			{
				_Mass_Data report = tmpQueue.front();
				tmpQueue.pop();
				CDrawDlg *pDlg = m_device2draw[report.strMac];
				if (NULL != pDlg)
					pDlg->onRecvData(report.data);
			}
			//Sleep(1);
		}
		break;
		case 1:
			m_bRun = FALSE;
			break;
		default:
			break;
		}
	}
}

void CrbtnetDemoDlg::recvOriginData(const char* pMac,
	unsigned short us,
	unsigned short ux,
	unsigned short uy,
	unsigned short up)
{
	USES_CONVERSION;
	CString strMac = A2T(pMac);
	CDrawDlg *pDlg = m_device2draw[strMac];

	CString str;
	str.Format(_T("X:%d,Y:%d,S:%d,P:%d;\n"), ux, uy, us, up);
	//OutputDebugStringW(str);//*/

	OutputDebugStringW(strMac + _T("==========================>") + str);

	if (NULL != pDlg)
		pDlg->onRecvData(us, ux, uy, up);
	return;
	//////////////////////////////////////////////////////////////
	_Mass_Data data;
	data.strMac = strMac;
	data.data.nStatus = us;
	data.data.nX = ux;
	data.data.nY = uy;
	data.data.nPress = up;

	::EnterCriticalSection(&m_sectionLock);
	m_queueData.push(data);
	::LeaveCriticalSection(&m_sectionLock);

	::SetEvent(m_hEvent[0]);
}

void CrbtnetDemoDlg::deviceDisconnect(const char* pMac)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	if (strlen(pMac) == 0) {
		return;
	}

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1) {
		pListCtrl->SetItemText(nRowIndex, 2, _T("离线"));
	}

}

void CrbtnetDemoDlg::recvKeyPress(const char* pMac, void* keyValue)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1) {
		CString csValue;
		keyPressEnum keyPressValue = *(keyPressEnum*)(keyValue);
		switch (keyPressValue)
		{
		case K_A:
			csValue.Format(_T("按下A"));
			break;
		case K_B:
			csValue.Format(_T("按下B"));
			break;
		case K_C:
			csValue.Format(_T("按下C"));
			break;
		case K_D:
			csValue.Format(_T("按下D"));
			break;
		case K_E:
			csValue.Format(_T("按下E"));
			break;
		case K_F:
			csValue.Format(_T("按下F"));
			break;
		case K_SUCC:
			csValue.Format(_T("按下正确"));
			break;
		case K_ERROR:
			csValue.Format(_T("按下错误"));
			break;
		case K_CACLE:
			csValue.Format(_T("按下取消"));
			break;
		case K_SURE:
			csValue.Format(_T("按下确认"));
			break;
		default:
			break;
		}
		pListCtrl->SetItemText(nRowIndex, 4, csValue);
	}
}
//resID 第几题，pResult 答案，nSize 长度
CString CrbtnetDemoDlg::GetAnswerResult(int resID, unsigned char* pResult, int nSize)
{
	CString csValue(_T(""));
	csValue.Format(_T("%d："), resID);

	for (int i = 0; i < nSize; ++i)
	{
		int nResult = (int)*(pResult + i);
		switch (nResult)
		{
		case 0x06:
			csValue.Format(_T("%sA"), csValue);
			break;
		case 0x07:
			csValue.Format(_T("%sB"), csValue);
			break;
		case 0x08:
			csValue.Format(_T("%sC"), csValue);
			break;
		case 0x09:
			csValue.Format(_T("%sD"), csValue);
			break;
		case 0x10:
			csValue.Format(_T("%sE"), csValue);
			break;
		case 0x11:
			csValue.Format(_T("%sF"), csValue);
			break;
		case 0x12:
			csValue.Format(_T("%s正确"), csValue);
			break;
		case 0x13:
			csValue.Format(_T("%s错误"), csValue);
			break;
		case 0x14:
			break;
		case 0x15:
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->GetCurSel() == 3)
				csValue.Format(_T("参与抢答"));
		}
		break;
		default:
			break;
		}
	}

	return csValue;
}

void CrbtnetDemoDlg::recvKeyAnswer(const char* pMac, int key)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex < 0)
		return;

	switch (m_nCurrentSubject)
	{
	case 0: //判断
	{
		if (key == 0x12 || key == 0x13)
			pListCtrl->SetItemText(nRowIndex, 3, getValue(key));
	}
	break;
	case 1: //单选
	{
		if (key == 0x06 || key == 0x07 || key == 0x08 || key == 0x09)
			pListCtrl->SetItemText(nRowIndex, 3, getValue(key));
	}
	break;
	case 2: //多选
	{
		CString strAnswer = pListCtrl->GetItemText(nRowIndex, 3);
		if (key == 0x06 || key == 0x07 || key == 0x08 || key == 0x09 || key == 0x10 || key == 0x11)
		{
			CString csValue = getValue(key);
			if (strAnswer.Find(csValue) >= 0)
			{
				strAnswer.Replace(csValue, _T(""));
			}
			else
				strAnswer += csValue;

			pListCtrl->SetItemText(nRowIndex, 3, Asc(strAnswer));
		}
	}
	break;
	case 3: //抢答
	{
		if (key == 0x15)
			pListCtrl->SetItemText(nRowIndex, 3, _T("参与抢答"));
	}
	break;
	default:
		break;
	}
}

CString CrbtnetDemoDlg::getValue(int key)
{
	CString csValue;
	switch (key)
	{
	case 0x06:
		csValue.Format(_T("A"), csValue);
		break;
	case 0x07:
		csValue.Format(_T("B"), csValue);
		break;
	case 0x08:
		csValue.Format(_T("C"), csValue);
		break;
	case 0x09:
		csValue.Format(_T("D"), csValue);
		break;
	case 0x10:
		csValue.Format(_T("E"), csValue);
		break;
	case 0x11:
		csValue.Format(_T("F"), csValue);
		break;
	case 0x12:
		csValue.Format(_T("正确"), csValue);
		break;
	case 0x13:
		csValue.Format(_T("错误"), csValue);
		break;
	case 0x14:
		break;
	case 0x15:
		break;
	default:
		break;
	}

	return csValue;
}
//字符串内排序
CString CrbtnetDemoDlg::Asc(CString strData)
{
	std::list<TCHAR> l;
	CString strAsc = strData;
	CString strIt;
	strAsc.MakeUpper();
	int count = strAsc.GetLength();
	for (int i = 0; i<count; i++)
	{
		TCHAR iChar = strAsc.GetAt(i);
		l.push_back(iChar);
	}
	l.sort();
	std::list<TCHAR>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		strIt += *it;
	}
	return strIt;
}

void CrbtnetDemoDlg::recvDeviceAnswerResult(const char* pMac, int resID, unsigned char* pResult, int nSize)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex < 0)
		return;

	CString csValue(_T(""));

	if (0x6e == resID)
	{
		int nCount = nSize / 8;
		for (size_t i = 0; i < nCount; i++)
		{
			//8 字节 {题类型，长度，0，1，2，3，4，5，6}
			uint8_t buf[8] = { 0 };
			memcpy(buf, pResult + i * 8, 8);
			CString str = GetAnswerResult(i + 1/*buf[0]*/, buf + 2, buf[1]);
			csValue += str;
		}

		m_device2draw[info.psz]->m_strValue += _T("#");
		m_device2draw[info.psz]->m_strValue += csValue;

		pListCtrl->SetItemText(nRowIndex, 3, csValue);
		/*CString strText = info.psz;
		strText += _T("=====>");
		strText += csValue;
		strText += _T("\n");
		OutputDebugStringW(strText);//*/

	}
	else
	{
		csValue = GetAnswerResult(resID, pResult, nSize);
		pListCtrl->SetItemText(nRowIndex, 3, csValue);
	}

}

void CrbtnetDemoDlg::recvDeviceShowpage(const char* pMac, int nNoteId, int nPageId)
{
	TRACE("recvDeviceShowpage\n");
	USES_CONVERSION;
	CString strMac = A2T(pMac);
	CString strText;
	strText.Format(_T("总页数:%d 当前页:%d\n"), nNoteId, nPageId);
	OutputDebugStringW(strMac + _T("==========================>") + strText);
	PostMessage(WM_SHOW_PAGE, (WPARAM)strText.AllocSysString(), (LPARAM)strMac.AllocSysString());
	return;

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	//USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex == -1) {
		return;
	}
	CString csValue;
	csValue.Format(_T("总页数:%d 当前页:%d"), nNoteId, nPageId);
	pListCtrl->SetItemText(nRowIndex, 5, csValue);
}

void CrbtnetDemoDlg::recvNameResult(const char* pMac, int res, const char* pName)
{
#ifdef _TEST
	if (res != 0)
	{
		USES_CONVERSION;
		CString strMac = A2T(pMac);
		SetItemName(strMac, _T(""));
	}
#else
	if (res == 0)
	{
		USES_CONVERSION;
		CString strName = A2T(pName);
		CString strMac = A2T(pMac);
		WriteLog(strName, true);;
		::PostMessage(m_hWnd, WM_RCV_NAME, (WPARAM)strName.AllocSysString(), (LPARAM)strMac.AllocSysString());
		AfxMessageBox(_T("设置成功"));
	}
	else
	{
		AfxMessageBox(_T("设置失败"));
	}
#endif
}

void CrbtnetDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bRun = FALSE;

	SetEvent(m_hEvent[1]);
	Sleep(10);
	rbt_win_stop();
	Sleep(1000);
	rbt_win_uninit();

	for (int i = 0; i < 2; i++)
	{
		CloseHandle(m_hEvent[i]);
		m_hEvent[i] = nullptr;
	}

	for (auto it : m_device2draw)
	{
		it.second->DestroyWindow();
		it.second = NULL;
	}
	m_device2draw.clear();
	::DeleteCriticalSection(&m_sectionLock);
	CDialogEx::OnClose();
}

void CrbtnetDemoDlg::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pDlg)
	{
		m_pDlg->ShowWindow(SW_SHOW);
		m_pDlg->CenterWindow();
	}

}

void CrbtnetDemoDlg::OnNMRClickListConnect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CMenu* popup = menu.GetSubMenu(0);
		if (popup != NULL)
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	*pResult = 0;
}

//配网设置
void CrbtnetDemoDlg::OnSettingStu()
{
	// TODO: 在此添加命令处理程序代码
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	int nItem = pListCtrl->GetNextSelectedItem(pos);

	CString strMac = pListCtrl->GetItemText(nItem, 0);
	CString strName = pListCtrl->GetItemText(nItem, 1);
	CStuDlg dlg(strName);
	if (dlg.DoModal() == IDOK)
	{
		strName = dlg.getStu();
		USES_CONVERSION;
		int len = strlen(W2A(strName.GetBuffer()));
		if (len > 10)
		{
			AfxMessageBox(_T("0-10 bytes！"));
			return;
		}
		//rbt_win_config_stu(T2A(strMac), T2A(strStu));
		SetItemName(strMac, strName);
		if (len > 6)
		{
			CString str = _T("");
			for (int i = 2; i < strName.GetLength(); i++)
			{
				USES_CONVERSION;
				if (strlen(W2A(strName.Left(i).GetBuffer())) > 6)
					break;
				str = strName.Left(i);
			}
			rbt_win_config_bmp_stu_more(T2A(strMac), T2A(strMac), T2A(str));
		}
		else
		{
			rbt_win_config_bmp_stu(T2A(strMac), T2A(strMac), T2A(strName));
		}
		//rbt_win_config_bmp_stu2(T2A(strMac), T2A(strName));
	}
	}

void CrbtnetDemoDlg::OnBnClickedButtonSwitch()
{
	// TODO: 在此添加控件通知处理程序代码
#ifdef _TEST
	SetTimer(0, 100, NULL);
#else
	int type = m_pDlg->getType();
	CString strSSID, strPwd, strIP;
	bool bTcp;
	switch (type)
	{
	case 1:
	{
		m_pDlg->getWifiConfig(strSSID, strPwd);
		if (strSSID.IsEmpty())
			break;
		USES_CONVERSION;
		rbt_win_config_wifi(T2A(strSSID), T2A(strPwd), "");
	}
	break;
	case 2:
	{
		m_pDlg->getNetConfig(bTcp, strIP);
		USES_CONVERSION;
		rbt_win_config_net(T2A(strIP), 6001, !bTcp, bTcp, "");
	}
	break;
	case 3:
	{
		m_pDlg->getWifiConfig(strSSID, strPwd);
		m_pDlg->getNetConfig(bTcp, strIP);
		if (strSSID.IsEmpty())
			break;
		USES_CONVERSION;
		rbt_win_config_wifi_net(T2A(strSSID), T2A(strPwd), T2A(strIP), 6001, !bTcp, bTcp, "");
	}
	break;
	default:
		break;
	}
#endif
}

bool CrbtnetDemoDlg::GetLocalAddress()
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

//打开模组
void CrbtnetDemoDlg::OnBnClickedOpenModule()
{
	// TODO: 在此添加控件通知处理程序代码
	//rbt_win_start();
	CString str;
	GetDlgItem(IDC_OPEN_MODULE)->GetWindowText(str);
	if (_T("关闭模组") == str)
	{
		rbt_win_open_module(false);

		GetDlgItem(IDC_OPEN_MODULE)->SetWindowText(_T("打开模组"));
	}
	else
	{
		/*#ifdef USE_TEST_KEEPALIVE
				for (int i = 0; i < 2; i++)
				{
					rbt_win_open_module(true);
				}
		#endif // USE_TEST_KEEPALIVE//*/
		rbt_win_open_module(true);
		GetDlgItem(IDC_OPEN_MODULE)->SetWindowText(_T("关闭模组"));
	}

}

//关闭模组
void CrbtnetDemoDlg::OnBnClickedCloseModule()
{
	// TODO: 在此添加控件通知处理程序代码

	/*rbt_win_stop();

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	if (pListCtrl)
		pListCtrl->DeleteAllItems();

	for (auto it : m_device2draw)
	{
		it.second->DestroyWindow();
		it.second = NULL;
	}
	m_device2draw.clear();//*/

	CString str;
	GetDlgItem(IDC_COMBO_TIME)->GetWindowText(str);
	rbt_win_set_screen_freq(_wtoi(str.GetBuffer()));
}

//开始答题
void CrbtnetDemoDlg::OnBnClickedButtonStartAnswer()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nCount = pListCtrl->GetItemCount();
	for (size_t i = 0; i < nCount; i++)
	{
		pListCtrl->SetItemText(i, 5, _T(""));
	}//*/

	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();

	int subject = ((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->GetCurSel();
	m_nCurrentSubject = subject;

	CString strNum;
	GetDlgItem(IDC_EDIT_NUM)->GetWindowText(strNum);
	USES_CONVERSION;
	int totalTopic = atoi(T2A(strNum)); //题目总数
	char pTopicType[128] = { 0 };
	for (size_t i = 0; i < totalTopic; i++)
	{
		pTopicType[i] = subject + 1; //题目类型 1判断 2单选 3多选 4抢答
	}
	bool bSendRes = false;
	//0为主观题,1为客观题
	if (index == 0)
		bSendRes = rbt_win_send_startanswer(index, 0, NULL);
	else
		bSendRes = rbt_win_send_startanswer(index, totalTopic, pTopicType);

	if (!bSendRes)
		AfxMessageBox(_T("开始答题失败!"));

	/*#ifdef USE_TEST_KEEPALIVE
		rbt_win_send_stopanswer();
		rbt_win_send_endanswer();
	#endif // USE_TEST_KEEPALIVE//*/
}

//停止答题
void CrbtnetDemoDlg::OnBnClickedButtonStopAnswer()
{
	// TODO: 在此添加控件通知处理程序代码

	rbt_win_send_stopanswer();

}

//结束答题
void CrbtnetDemoDlg::OnBnClickedButtonEndAnswer()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);

	for (size_t i = 0; i < pListCtrl->GetItemCount(); i++)
	{
		CString strMac = pListCtrl->GetItemText(i, 0);

		m_device2draw[strMac]->m_strValue = _T("");
	}

	rbt_win_send_endanswer();
}

void CrbtnetDemoDlg::OnBnClickedButtonSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_TIME)->GetWindowText(str);
	USES_CONVERSION;
	int nTime = atoi(T2A(str));
	rbt_win_config_sleep(nTime);
}

void CrbtnetDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int type = m_pDlg->getType();
	CString strSSID, strPwd, strIP;
	bool bTcp;
	switch (type)
	{
	case 1:
	{
		m_pDlg->getWifiConfig(strSSID, strPwd);
		if (strSSID.IsEmpty())
			break;
		USES_CONVERSION;
		rbt_win_config_wifi(T2A(strSSID), T2A(strPwd), "");
	}
	break;
	case 2:
	{
		m_pDlg->getNetConfig(bTcp, strIP);
		USES_CONVERSION;
		rbt_win_config_net(T2A(strIP), 6001, !bTcp, bTcp, "");
	}
	break;
	case 3:
	{
		m_pDlg->getWifiConfig(strSSID, strPwd);
		m_pDlg->getNetConfig(bTcp, strIP);
		if (strSSID.IsEmpty())
			break;
		USES_CONVERSION;
		rbt_win_config_wifi_net(T2A(strSSID), T2A(strPwd), T2A(strIP), 6001, !bTcp, bTcp, "");
	}
	break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CrbtnetDemoDlg::OnBnClickedButtonSetFreq()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->GetCurSel();
	rbt_win_config_freq(nIndex);
}

void CrbtnetDemoDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	std::map<CString, CDrawDlg*>::iterator iter;
	for (iter = m_device2draw.begin(); iter != m_device2draw.end(); iter++)
	{
		iter->second->Clear();
	}
}

void CrbtnetDemoDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	GetDlgItem(IDC_COMBO_SUBJECT)->ShowWindow((index == 1) ? SW_SHOW : SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->SetCurSel(2);
	GetDlgItem(IDC_EDIT_NUM)->ShowWindow(index ? SW_SHOW : SW_HIDE);
}

void CrbtnetDemoDlg::OnBnClickedButtonImport()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.csv)|*.csv|所有文件(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("csv"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");//设定   
		CStdioFile file;
		if (file.Open(dlg.GetPathName(), CFile::modeRead))
		{
			CString str;
			while (file.ReadString(str))
			{
				str = str.Trim(_T(" "));
				CStringArray sArray;
				SplitFields(str, sArray, _T(","));
				if (sArray.GetCount() > 1)
				{
					SetItemName(sArray[0], sArray[1]);
					USES_CONVERSION;
					rbt_win_config_bmp_stu(T2A(sArray[0]), T2A(sArray[0]), T2A(sArray[1]));
				}
			}
			setlocale(LC_CTYPE, old_locale);
			free(old_locale);//还原区域设定
			file.Close();
		}
	}
}

void CrbtnetDemoDlg::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.csv)|*.csv|所有文件(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("csv"), _T(""), 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CStdioFile file;
		if (file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
		{
			CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);

			int nCount = pListCtrl->GetItemCount();

			for (size_t i = 0; i < nCount; i++)
			{
				CString strMac = pListCtrl->GetItemText(i, 0);
				CString str = strMac + "\n";
				file.WriteString(str);
			}

			file.Close();
		}
	}
}

void CrbtnetDemoDlg::SetItemName(const CString &strMac, const CString &strName)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = strMac;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex < 0)
		return;

	pListCtrl->SetItemText(nRowIndex, 1, strName);
}

void CrbtnetDemoDlg::ShowOnlineCount()
{
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);

	int nCount = pListCtrl->GetItemCount();
	int nSum = 0;
	for (size_t i = 0; i < nCount; i++)
	{
		if (pListCtrl->GetItemText(i, 2) == _T("在线"))
			nSum++;
	}

	CString strCount;
	strCount.Format(_T("在线/总数：%d/%d"), nSum, nCount);
	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(strCount);
}

void CrbtnetDemoDlg::OnBnClickedButtonPoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_BUTTON_POINT)->GetWindowText(str);
	if (str == _T("打开悬浮点"))
	{
		GetDlgItem(IDC_BUTTON_POINT)->SetWindowText(_T("关闭悬浮点"));
		rbt_win_open_suspension(true);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_POINT)->SetWindowText(_T("打开悬浮点"));
		rbt_win_open_suspension(false);
	}
}

void CrbtnetDemoDlg::OnBnClickedButtonCvs()
{
	// TODO: 在此添加控件通知处理程序代码
	rbt_win_get_canvas_id();
}

/*void onResult(const char *sessionID, const char *stuID, const char * arrayFile, const char* questions, int pageID, int ret)
{
	printf((ret == 0) ? "successed\n" : "failed\n");
	printf("sessionID:%s,stuID:%s,arrayFile:%s,questions:%s,pageID:%d,ret:%d\n", sessionID, stuID, arrayFile, questions, pageID, ret);
}//*/

void CrbtnetDemoDlg::OnBnClickedButtonSetKeepalive()
{
	// TODO: 在此添加控件通知处理程序代码
	/*rbt_create_image("sessionid", "stuid", 22, 720, 1280, 29700, 21000, "[1,2]", "[0.0,0.2,0.6,0.8,1.0]", "D:/a.txt", "", "D:/test", "", onResult, "D:/test.jpg");

	return;//*/

	CString str;
	GetDlgItem(IDC_EDIT_KEEPALIVE)->GetWindowText(str);
	if (str.IsEmpty())
		return;
	CStringArray arrayStr;
	SplitFields(str, arrayStr, _T(","));
	if (arrayStr.GetCount() == 4)
	{
		int value = _wtoi(arrayStr.GetAt(0));
		int value2 = _wtoi(arrayStr.GetAt(1));
		int value3 = _wtoi(arrayStr.GetAt(2));
		int value4 = _wtoi(arrayStr.GetAt(3));
		rbt_win_set_keepalive(value, value2, value3, value4);

	}
}

void CrbtnetDemoDlg::OnNMClickListConnect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nIndex = pListCtrl->GetNextItem(-1, LVIS_SELECTED);
	if (nIndex < 0)
	{
		return;
	}

	CString strMac = pListCtrl->GetItemText(nIndex, 0);
	OutputDebugStringW(strMac);
	OutputDebugStringW(_T("\r\n"));

	CString str = m_device2draw[strMac]->m_strValue;

	CStringArray sArray;
	SplitFields(str, sArray, _T("#"));

	for (size_t i = 0; i < sArray.GetCount(); i++)
	{
		CString strAnswer = sArray[i] + _T("\n");
		OutputDebugStringW(strAnswer);
	}

}

void CrbtnetDemoDlg::OnBnClickedButtonDelNotes()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO_DEL_NOTES))->GetCurSel();
	
	rbt_win_del_notes(index);
}
