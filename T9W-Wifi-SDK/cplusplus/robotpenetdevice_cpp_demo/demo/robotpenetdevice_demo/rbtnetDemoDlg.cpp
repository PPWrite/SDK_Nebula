
// rbtnetDemoDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "rbtnetDemoDlg.h"
#include "afxdialogex.h"
#include "DrawDlg.h"
#include "StuDlg.h"
#include <locale> 
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //��Ҫ���Iphlpapi.lib��

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

//#define _TEST

//#define USE_OPT

#define USE_KDXF //�ƴ�Ѷ��

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CrbtnetDemoDlg �Ի���



CrbtnetDemoDlg::CrbtnetDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RBTNETDEMO_DIALOG, pParent)
	, m_pDlg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i = 0; i < 2; i++)
	{
		m_hEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	// ��ʼ��
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
END_MESSAGE_MAP()


// CrbtnetDemoDlg ��Ϣ�������

BOOL CrbtnetDemoDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Init_Param param;
	param.ctx = this;
	param.port = 6001;
	param.open = true;
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

	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(0, _T("������"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(1, _T("�͹���"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(0, _T("�ж�"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(1, _T("��ѡ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(2, _T("��ѡ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->InsertString(3, _T("����"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->SetCurSel(0);

	GetLocalAddress();

	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(0, _T("���׵�"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(1, _T("��һ����"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(2, _T("��������"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(3, _T("��������"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->InsertString(4, _T("���ĸ���"));
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
	GetDlgItem(IDC_COMBO_TIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CLOSE_MODULE)->ShowWindow(SW_SHOW);
	((CComboBox*)GetDlgItem(IDC_COMBO_TIME))->SetCurSel(0);
#endif // USE_KDXF


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CrbtnetDemoDlg::OnPaint()
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
HCURSOR CrbtnetDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���յ����豸����
HRESULT CrbtnetDemoDlg::rcvAccept(WPARAM wParam, LPARAM lParam)
{
	return 0L;
}

// �յ�mac��ַ��Ϊ����
HRESULT CrbtnetDemoDlg::rcvMac(WPARAM wParam, LPARAM lParam)
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
	if (nRowIndex != -1) {
		pListCtrl->SetItemText(nRowIndex, 2, _T("����"));
	}
	else {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, strMac);
		pListCtrl->SetItemText(nItemTotal, 2, _T("����"));
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
	}

	ShowOnlineCount();
	
	return 0L;
}


HRESULT CrbtnetDemoDlg::recvName(WPARAM wParam, LPARAM lParam)
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
		pListCtrl->SetItemText(nItemTotal, 2, _T("����"));
	}

	pListCtrl->SetItemText(nRowIndex, 1, strName);

	return 0L;
}

HRESULT CrbtnetDemoDlg::showPage(WPARAM wParam, LPARAM lParam)
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

HRESULT CrbtnetDemoDlg::onShowError(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)lParam;
	CString strMac(b);
	SysFreeString(b);

	CString strMsg;
	strMsg.Format(_T("MAC:%s,CMD:%d Error"), strMac, wParam);
	AfxMessageBox(strMsg);
	return 0L;
}

HRESULT CrbtnetDemoDlg::onDisconnect(WPARAM wParam, LPARAM lParam)
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
	if (nRowIndex != -1) {
		pListCtrl->SetItemText(nRowIndex, 2, _T("����"));
	}

	ShowOnlineCount();

}


// ��ʼ����
void CrbtnetDemoDlg::OnBnClickedStartOrStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(_T(""));
	CString csBtnText;
	GetDlgItemText(IDC_START_STOP, csBtnText);
	if (csBtnText == _T("��ʼ")) {
		bool bStartRes = rbt_win_start();
		if (!bStartRes) {
			MessageBox(_T("��ʼʧ��"));
			return;
		}

		SetDlgItemText(IDC_START_STOP, _T("ֹͣ"));
	}
	else {
		rbt_win_stop();
		SetDlgItemText(IDC_START_STOP, _T("��ʼ"));
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
	pListCtl->InsertColumn(0, _T("�豸MAC��ַ"), LVCFMT_LEFT, 120);
	pListCtl->InsertColumn(1, _T("ѧ��"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(2, _T("״̬"), LVCFMT_LEFT, 60);
	pListCtl->InsertColumn(3, _T("ѡ����֪ͨ"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(4, _T("����֪ͨ"), LVCFMT_LEFT, 100);
	pListCtl->InsertColumn(5, _T("ҳ��֪ͨ"), LVCFMT_LEFT, 150);
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
	pThis->recvOriginData(pMac, us, ux, uy, width);
}

void CrbtnetDemoDlg::OnNMDblclkListConnect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_device2draw[strMac]->ShowWindow(true);

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
		pListCtrl->SetItemText(nRowIndex, 2, _T("����"));
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
			csValue.Format(_T("����A"));
			break;
		case K_B:
			csValue.Format(_T("����B"));
			break;
		case K_C:
			csValue.Format(_T("����C"));
			break;
		case K_D:
			csValue.Format(_T("����D"));
			break;
		case K_E:
			csValue.Format(_T("����E"));
			break;
		case K_F:
			csValue.Format(_T("����F"));
			break;
		case K_SUCC:
			csValue.Format(_T("������ȷ"));
			break;
		case K_ERROR:
			csValue.Format(_T("���´���"));
			break;
		case K_CACLE:
			csValue.Format(_T("����ȡ��"));
			break;
		case K_SURE:
			csValue.Format(_T("����ȷ��"));
			break;
		default:
			break;
		}
		pListCtrl->SetItemText(nRowIndex, 4, csValue);
	}
}
//resID �ڼ��⣬pResult �𰸣�nSize ����
CString CrbtnetDemoDlg::GetAnswerResult(int resID, unsigned char* pResult, int nSize)
{
	CString csValue(_T(""));
	csValue.Format(_T("%d��"), resID);

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
			csValue.Format(_T("%s��ȷ"), csValue);
			break;
		case 0x13:
			csValue.Format(_T("%s����"), csValue);
			break;
		case 0x14:
			break;
		case 0x15:
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->GetCurSel() == 3)
				csValue.Format(_T("��������"));
		}
		break;
		default:
			break;
		}
	}

	return csValue;
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
			//8 �ֽ� {�����ͣ����ȣ�0��1��2��3��4��5��6}
			uint8_t buf[8] = { 0 };
			memcpy(buf, pResult + i * 8, 8);
			CString str = GetAnswerResult(i + 1/*buf[0]*/, buf + 2, buf[1]);
			csValue += str;
		}
	}
	else
	{
		csValue = GetAnswerResult(resID, pResult, nSize);
	}


	pListCtrl->SetItemText(nRowIndex, 3, csValue);
}

void CrbtnetDemoDlg::recvDeviceShowpage(const char* pMac, int nNoteId, int nPageId)
{
	TRACE("recvDeviceShowpage\n");
	USES_CONVERSION;
	CString strMac = A2T(pMac);
	CString strText;
	strText.Format(_T("��ҳ��:%d ��ǰҳ:%d"), nNoteId, nPageId);
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
	csValue.Format(_T("��ҳ��:%d ��ǰҳ:%d"), nNoteId, nPageId);
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
		AfxMessageBox(_T("���óɹ�"));
	}
	else
	{
		AfxMessageBox(_T("����ʧ��"));
	}
#endif
}

void CrbtnetDemoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bRun = FALSE;

	SetEvent(m_hEvent[1]);
	Sleep(10);
	rbt_win_stop();
	Sleep(500);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pDlg)
	{
		m_pDlg->ShowWindow(SW_SHOW);
		m_pDlg->CenterWindow();
	}

}


void CrbtnetDemoDlg::OnNMRClickListConnect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//��������
void CrbtnetDemoDlg::OnSettingStu()
{
	// TODO: �ڴ���������������
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
		if (strName.GetLength() > 6)
		{
			AfxMessageBox(_T("0-6 bytes��"));
			return;
		}
		USES_CONVERSION;
		//rbt_win_config_stu(T2A(strMac), T2A(strStu));
		SetItemName(strMac, strName);
		rbt_win_config_bmp_stu(T2A(strMac), T2A(strMac), T2A(strName));
	}
}


void CrbtnetDemoDlg::OnBnClickedButtonSwitch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = NULL;
	PIP_ADAPTER_INFO pIpAdapterInfoEx = NULL;
	pIpAdapterInfo = new IP_ADAPTER_INFO();
	pIpAdapterInfoEx = pIpAdapterInfo;

	//�õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//��¼��������
	int netCardNum = 0;
	//��¼ÿ�������ϵ�IP��ַ����
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//�ͷ�ԭ�����ڴ�ռ�
		if (NULL != pIpAdapterInfo) {
			delete pIpAdapterInfo;
			pIpAdapterInfo = NULL;
			pIpAdapterInfoEx = NULL;
		}

		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		pIpAdapterInfoEx = pIpAdapterInfo;
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}

	if (ERROR_SUCCESS == nRel)
	{
		USES_CONVERSION;
		//���������Ϣ
		//�����ж�����,���ͨ��ѭ��ȥ�ж�
		while (pIpAdapterInfo)
		{
			//���������ж�IP,���ͨ��ѭ��ȥ�ж�
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
			strAddress = pIpAddrString->IpAddress.String;
			// ��Ҫע�������ʱ���ܻ�ȡ��IP��ַ��0.0.0.0����ʱ��Ҫ���˵�
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

//��ģ��
void CrbtnetDemoDlg::OnBnClickedOpenModule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//rbt_win_start();
	CString str;
	GetDlgItem(IDC_OPEN_MODULE)->GetWindowText(str);
	if (_T("�ر�ģ��") == str)
	{
		rbt_win_open_module(false);
		GetDlgItem(IDC_OPEN_MODULE)->SetWindowText(_T("��ģ��"));
	}
	else
	{
		rbt_win_open_module(true);
		GetDlgItem(IDC_OPEN_MODULE)->SetWindowText(_T("�ر�ģ��"));
	}
	
}

//�ر�ģ��
void CrbtnetDemoDlg::OnBnClickedCloseModule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

//��ʼ����
void CrbtnetDemoDlg::OnBnClickedButtonStartAnswer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nCount = pListCtrl->GetItemCount();
	for (size_t i = 0; i < nCount; i++)
	{
		pListCtrl->SetItemText(i, 5, _T(""));
	}//*/

	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();

	int subject = ((CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT))->GetCurSel();

	CString strNum;
	GetDlgItem(IDC_EDIT_NUM)->GetWindowText(strNum);
	USES_CONVERSION;
	int totalTopic = atoi(T2A(strNum)); //��Ŀ����
	char pTopicType[128] = { 0 };
	for (size_t i = 0; i < totalTopic; i++)
	{
		pTopicType[i] = subject + 1; //��Ŀ���� 1�ж� 2��ѡ 3��ѡ 4����
	}
	bool bSendRes = false;
	//0Ϊ������,1Ϊ�͹���
	if (index == 1)
		bSendRes = rbt_win_send_startanswer(index, totalTopic, pTopicType);
	else
		bSendRes = rbt_win_send_startanswer(index, 0, NULL);

	if (!bSendRes)
		AfxMessageBox(_T("��ʼ����ʧ��!"));
}

//ֹͣ����
void CrbtnetDemoDlg::OnBnClickedButtonStopAnswer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	rbt_win_send_stopanswer();
}

//��������
void CrbtnetDemoDlg::OnBnClickedButtonEndAnswer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	rbt_win_send_endanswer();
}


void CrbtnetDemoDlg::OnBnClickedButtonSetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT_TIME)->GetWindowText(str);
	USES_CONVERSION;
	int nTime = atoi(T2A(str));
	rbt_win_config_sleep(nTime);
}


void CrbtnetDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->GetCurSel();
	rbt_win_config_freq(nIndex);
}


void CrbtnetDemoDlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::map<CString, CDrawDlg*>::iterator iter;
	for (iter = m_device2draw.begin(); iter != m_device2draw.end(); iter++)
	{
		iter->second->Clear();
	}
}


void CrbtnetDemoDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	GetDlgItem(IDC_COMBO_SUBJECT)->ShowWindow(index ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EDIT_NUM)->ShowWindow(index ? SW_SHOW : SW_HIDE);
}

void CrbtnetDemoDlg::OnBnClickedButtonImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�ı��ļ�(*.csv)|*.csv|�����ļ�(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("csv"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");//�趨   
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
			free(old_locale);//��ԭ�����趨
			file.Close();
		}
	}
}


void CrbtnetDemoDlg::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�ı��ļ�(*.csv)|*.csv|�����ļ�(*.*)|*.*||");
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
		if (pListCtrl->GetItemText(i, 2) == _T("����"))
			nSum++;
	}

	CString strCount;
	strCount.Format(_T("����/������%d/%d"), nSum, nCount);
	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(strCount);
}

void CrbtnetDemoDlg::OnBnClickedButtonPoint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_BUTTON_POINT)->GetWindowText(str);
	if (str == _T("��������"))
	{
		GetDlgItem(IDC_BUTTON_POINT)->SetWindowText(_T("�ر�������"));
		rbt_win_open_suspension(true);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_POINT)->SetWindowText(_T("��������"));
		rbt_win_open_suspension(false);
	}
}


void CrbtnetDemoDlg::OnBnClickedButtonCvs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	rbt_win_get_canvas_id();
}
