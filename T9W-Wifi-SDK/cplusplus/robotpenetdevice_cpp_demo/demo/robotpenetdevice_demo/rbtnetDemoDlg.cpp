
// rbtnetDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "rbtnetDemo.h"
#include "rbtnetDemoDlg.h"
#include "afxdialogex.h"
#include "DrawDlg.h"
#include "ConfigDlg.h"
#include "StuDlg.h"
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	, m_strSSID("")
	, m_strPwd("")
	, m_strStu("")
	, m_strSource("")
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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMDblclkListConnect)
	ON_BN_CLICKED(IDC_BUTTON1, &CrbtnetDemoDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CrbtnetDemoDlg::OnBnClickedButtonConfig)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMRClickListConnect)
	ON_COMMAND(ID_SETTING_STU, &CrbtnetDemoDlg::OnSettingStu)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CrbtnetDemoDlg::OnBnClickedButtonSwitch)
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
	param.pIp = NULL;
	param.listenCount = 50;

	rbt_win_init(&param);
	initCbFunction();
	initListControl();

	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(0, _T("主观题"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(1, _T("客观题"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	m_bRun = true;
	AfxBeginThread(ThreadProc, this);

	GetLocalAddress();
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
HRESULT CrbtnetDemoDlg::rcvAccept(WPARAM wParam, LPARAM lParam)
{
	char* p = (char*)lParam;
	if (NULL == p) {
		return 0L;
	}

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(p);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1) {
		pListCtrl->SetItemText(nRowIndex, 2, _T("在线"));
	}
	else {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, A2T(p));
		pListCtrl->SetItemText(nItemTotal, 1, _T(""));
		pListCtrl->SetItemText(nItemTotal, 2, _T("在线"));
		m_device2draw[p] = new CDrawDlg();
		m_device2draw[p]->Create(IDD_DRAWDLG);
		m_device2draw[p]->ShowWindow(true);
	}
	return 0L;
}

// 收到mac地址认为上线
HRESULT CrbtnetDemoDlg::rcvMac(WPARAM wParam, LPARAM lParam)
{
	char* p = (char*)lParam;
	if (NULL == p) {
		return 0L;
	}

	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(p);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex != -1) {
		pListCtrl->SetItemText(nRowIndex, 2, _T("在线"));
	}
	else {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, A2T(p));
		pListCtrl->SetItemText(nItemTotal, 2, _T("在线"));
		m_device2draw[p] = new CDrawDlg();
		m_device2draw[p]->Create(IDD_DRAWDLG);
		m_device2draw[p]->ShowWindow(FALSE);
	}
	return 0L;
}


HRESULT CrbtnetDemoDlg::recvName(WPARAM wParam, LPARAM lParam)
{
	char* pMac = (char*)lParam;
	char* pName = (char*)wParam;
	if (NULL == pMac || NULL == pName)
	{
		return 0L;
	}
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	if (nRowIndex == -1) {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, A2T(pMac));
		pListCtrl->SetItemText(nItemTotal, 2, _T("在线"));
		m_device2draw[pMac] = new CDrawDlg();
		m_device2draw[pMac]->Create(IDD_DRAWDLG);
		m_device2draw[pMac]->ShowWindow(FALSE);
	}

	pListCtrl->SetItemText(nRowIndex, 1, A2T(pName));

	return 0L;
}

// 开始启动
void CrbtnetDemoDlg::OnBnClickedStartOrStop()
{
	// TODO: 在此添加控件通知处理程序代码
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
	pListCtl->InsertColumn(5, _T("页码通知"), LVCFMT_LEFT, 150);
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

	rbt_win_set_deviceshowpage_cb(onDeviceShowPage);//*/

	/*rbt_win_set_accept_cb([](rbt_win_context* ctx, const char* pIp) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		return;
		::PostMessage(pThis->m_hWnd, WM_RCV_ACCEPT, 0, (LPARAM)pIp);
	});

	rbt_win_set_devivedisconnect_cb([](rbt_win_context* ctx, const char* pmac) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		pThis->deviceDisconnect(pmac);
	});

	rbt_win_set_devicemac_cb([](rbt_win_context* ctx, const char* pMac) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		::PostMessage(pThis->m_hWnd, WM_RCV_MAC, 0, (LPARAM)pMac);
	});

	rbt_win_set_devicename_cb([](rbt_win_context* ctx, const char* pMac, const char* pName) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		pThis->recvName(pMac, pName);
	});

	rbt_win_set_devicenameresult_cb([](rbt_win_context* ctx, const char* pMac, int res, const char* pName) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		pThis->recvNameResult(pMac, res, pName);
	});

	rbt_win_set_origindata_cb([](rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		pThis->recvOriginData(pMac, us, ux, uy, up);
	});

	rbt_win_set_devicekeypress_cb([](rbt_win_context* ctx, const char* pMac, keyPressEnum value) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
		pThis->recvKeyPress(pMac, &value);
	});

	rbt_win_set_deviceanswerresult_cb([](rbt_win_context* context, const char* pMac, unsigned char* pResult, int nSize) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
		pThis->recvDeviceAnswerResult(pMac, pResult, nSize);
	});

	rbt_win_set_deviceshowpage_cb([](rbt_win_context* context, const char* pMac, int nNoteId, int nPageId) {
		CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
		pThis->recvDeviceShowpage(pMac, nNoteId, nPageId);
	});//*/
}

void CrbtnetDemoDlg::onAccept(rbt_win_context* context, const char* pClientIpAddress)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	return;
	::PostMessage(pThis->m_hWnd, WM_RCV_ACCEPT, 0, (LPARAM)pClientIpAddress);
}
void CrbtnetDemoDlg::onErrorPacket(rbt_win_context* context)
{

}
void CrbtnetDemoDlg::onOriginData(rbt_win_context* ctx, const char* pMac, ushort us, ushort ux, ushort uy, ushort up)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(ctx);
	pThis->recvOriginData(pMac, us, ux, uy, up);
}
void CrbtnetDemoDlg::onDeviceMac(rbt_win_context* context, const char* pMac)
{
	USES_CONVERSION;
	WriteLog(A2T(pMac),true);;
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_RCV_MAC, 0, (LPARAM)pMac);
}
void CrbtnetDemoDlg::onDeviceName(rbt_win_context* context, const char* pMac, const char* pName)
{
	USES_CONVERSION;
	WriteLog(A2T(pName), true);;
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	::PostMessage(pThis->m_hWnd, WM_RCV_NAME, (WPARAM)pName, (LPARAM)pMac);
}
void CrbtnetDemoDlg::onDeviceNameResult(rbt_win_context* context, const char* pMac, int res, const char* pName)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvNameResult(pMac, res, pName);
}
void CrbtnetDemoDlg::onDeviceDisConnect(rbt_win_context* context, const char* pMac)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->deviceDisconnect(pMac);
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
void CrbtnetDemoDlg::onDeviceShowPage(rbt_win_context* context, const char* pMac, int nNoteId, int nPageId)
{
	CrbtnetDemoDlg *pThis = reinterpret_cast<CrbtnetDemoDlg*>(context);
	pThis->recvDeviceShowpage(pMac, nNoteId, nPageId);
}

void CrbtnetDemoDlg::OnNMDblclkListConnect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	int nSubItem = pNMListView->iSubItem;
	CString sText = pListCtrl->GetItemText(nItem, 0);
	USES_CONVERSION;
	std::string strMac = T2A(sText);
	if (m_device2draw.find(strMac) == m_device2draw.end()) {
		return;
	}

	m_device2draw[strMac]->SetWindowText(sText);
	m_device2draw[strMac]->ShowWindow(true);

	*pResult = 0;
}

// 开始答题或者结束答题
void CrbtnetDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	static int iTest = 0; 
	++iTest;

	CString csBtnText;
	GetDlgItemText(IDC_BUTTON1, csBtnText);
	if (csBtnText == _T("开始答题")) {
		int totalTopic = 3;
		char pTopicType[3] = { 1,2,3 };
		bool bSendRes = false;
		//0为主观题,1为客观题
		if (index == 1)
			bSendRes = rbt_win_send_startanswer(index, totalTopic, pTopicType);
		else
			bSendRes = rbt_win_send_startanswer(index, 0, NULL);

		if (!bSendRes) {
			MessageBox(_T("开启答题失败"));
			return;
		}
		SetDlgItemText(IDC_BUTTON1, _T("停止答题"));
	} else {
		bool bSendRes = rbt_win_send_stopanswer();
		if (!bSendRes) {
			MessageBox(_T("结束答题失败"));
			return;
		}
		SetDlgItemText(IDC_BUTTON1, _T("开始答题"));
	}
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
				CDrawDlg *pDlg = m_device2draw[report.pMac];
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
	CDrawDlg *pDlg = m_device2draw[pMac];
	if (NULL != pDlg)
		pDlg->onRecvData(us, ux, uy, up);
	return;

	_Mass_Data data;
	data.pMac = pMac;
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

void CrbtnetDemoDlg::recvDeviceAnswerResult(const char* pMac, int resID, unsigned char* pResult, int nSize)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	CString csValue;
	csValue.Format(_T("%d："), resID);
	if (nRowIndex < 0)
		return;

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
		default:
			break;
		}
	}
	pListCtrl->SetItemText(nRowIndex, 3, csValue);
}

void CrbtnetDemoDlg::recvDeviceShowpage(const char* pMac, int nNoteId, int nPageId)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
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
	if (res == 0)
	{
		::PostMessage(m_hWnd, WM_RCV_NAME, (WPARAM)pName, (LPARAM)pMac);
		AfxMessageBox(_T("设置成功"));
	}
	else
	{
		AfxMessageBox(_T("设置失败"));
	}
}

void CrbtnetDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bRun = FALSE;

	SetEvent(m_hEvent[1]);
	Sleep(100);

	::DeleteCriticalSection(&m_sectionLock);
	rbt_win_stop();
	rbt_win_uninit();
	CDialogEx::OnClose();
}


void CrbtnetDemoDlg::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CConfigDlg dlg(m_strSSID, m_strPwd, m_strStu, m_strSource);
	if (dlg.DoModal() == IDOK)
	{
		dlg.getConfig(m_strSSID, m_strPwd, m_strStu, m_strSource);
		USES_CONVERSION;
		rbt_win_config_wifi(T2A(m_strSSID), T2A(m_strPwd), T2A(m_strStu), T2A(m_strSource));
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


void CrbtnetDemoDlg::OnSettingStu()
{
	// TODO: 在此添加命令处理程序代码
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	int nItem = pListCtrl->GetNextSelectedItem(pos);

	CString strMac = pListCtrl->GetItemText(nItem, 0);
	CString strStu = pListCtrl->GetItemText(nItem, 1);
	CStuDlg dlg(strStu);
	if (dlg.DoModal() == IDOK)
	{
		strStu = dlg.getStu();
		if (strStu.GetLength() > 6)
		{
			AfxMessageBox(_T("0-6 bytes！"));
			return;
		}
		USES_CONVERSION;
		rbt_win_config_stu(T2A(strMac), T2A(strStu));
	}
}


void CrbtnetDemoDlg::OnBnClickedButtonSwitch()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strIP;
	GetDlgItem(IDC_COMBO_IP)->GetWindowText(strIP);
	USES_CONVERSION;
	rbt_win_config_net("", T2A(strIP), 6001, false, true, "");
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
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
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
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
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
				USES_CONVERSION;
				pComboBox->AddString(A2W(strAddress.c_str()));
			}
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
		if (pComboBox->GetCount() > 0)
		{
			pComboBox->SetCurSel(0);
		}
	}
	//释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}
}
