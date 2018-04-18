
// rbtnetDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "rbtnetDemo.h"
#include "rbtnetDemoDlg.h"
#include "afxdialogex.h"
#include "DrawDlg.h"
#include "ConfigDlg.h"
#include "StuDlg.h"
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //��Ҫ���Iphlpapi.lib��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMDblclkListConnect)
	ON_BN_CLICKED(IDC_BUTTON1, &CrbtnetDemoDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CrbtnetDemoDlg::OnBnClickedButtonConfig)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONNECT, &CrbtnetDemoDlg::OnNMRClickListConnect)
	ON_COMMAND(ID_SETTING_STU, &CrbtnetDemoDlg::OnSettingStu)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CrbtnetDemoDlg::OnBnClickedButtonSwitch)
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
	param.pIp = NULL;
	param.listenCount = 50;

	rbt_win_init(&param);
	initCbFunction();
	initListControl();

	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(0, _T("������"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(1, _T("�͹���"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	m_bRun = true;
	AfxBeginThread(ThreadProc, this);

	GetLocalAddress();
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
		pListCtrl->SetItemText(nRowIndex, 2, _T("����"));
	}
	else {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, A2T(p));
		pListCtrl->SetItemText(nItemTotal, 1, _T(""));
		pListCtrl->SetItemText(nItemTotal, 2, _T("����"));
		m_device2draw[p] = new CDrawDlg();
		m_device2draw[p]->Create(IDD_DRAWDLG);
		m_device2draw[p]->ShowWindow(true);
	}
	return 0L;
}

// �յ�mac��ַ��Ϊ����
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
		pListCtrl->SetItemText(nRowIndex, 2, _T("����"));
	}
	else {
		int nItemTotal = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nItemTotal, A2T(p));
		pListCtrl->SetItemText(nItemTotal, 2, _T("����"));
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
		pListCtrl->SetItemText(nItemTotal, 2, _T("����"));
		m_device2draw[pMac] = new CDrawDlg();
		m_device2draw[pMac]->Create(IDD_DRAWDLG);
		m_device2draw[pMac]->ShowWindow(FALSE);
	}

	pListCtrl->SetItemText(nRowIndex, 1, A2T(pName));

	return 0L;
}

// ��ʼ����
void CrbtnetDemoDlg::OnBnClickedStartOrStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

// ��ʼ������߽�������
void CrbtnetDemoDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	static int iTest = 0; 
	++iTest;

	CString csBtnText;
	GetDlgItemText(IDC_BUTTON1, csBtnText);
	if (csBtnText == _T("��ʼ����")) {
		int totalTopic = 3;
		char pTopicType[3] = { 1,2,3 };
		bool bSendRes = false;
		//0Ϊ������,1Ϊ�͹���
		if (index == 1)
			bSendRes = rbt_win_send_startanswer(index, totalTopic, pTopicType);
		else
			bSendRes = rbt_win_send_startanswer(index, 0, NULL);

		if (!bSendRes) {
			MessageBox(_T("��������ʧ��"));
			return;
		}
		SetDlgItemText(IDC_BUTTON1, _T("ֹͣ����"));
	} else {
		bool bSendRes = rbt_win_send_stopanswer();
		if (!bSendRes) {
			MessageBox(_T("��������ʧ��"));
			return;
		}
		SetDlgItemText(IDC_BUTTON1, _T("��ʼ����"));
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

void CrbtnetDemoDlg::recvDeviceAnswerResult(const char* pMac, int resID, unsigned char* pResult, int nSize)
{
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	USES_CONVERSION;
	info.psz = A2T(pMac);

	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONNECT);
	int nRowIndex = pListCtrl->FindItem(&info);
	CString csValue;
	csValue.Format(_T("%d��"), resID);
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
			csValue.Format(_T("%s��ȷ"), csValue);
			break;
		case 0x13:
			csValue.Format(_T("%s����"), csValue);
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
	csValue.Format(_T("��ҳ��:%d ��ǰҳ:%d"), nNoteId, nPageId);
	pListCtrl->SetItemText(nRowIndex, 5, csValue);
}

void CrbtnetDemoDlg::recvNameResult(const char* pMac, int res, const char* pName)
{
	if (res == 0)
	{
		::PostMessage(m_hWnd, WM_RCV_NAME, (WPARAM)pName, (LPARAM)pMac);
		AfxMessageBox(_T("���óɹ�"));
	}
	else
	{
		AfxMessageBox(_T("����ʧ��"));
	}
}

void CrbtnetDemoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CrbtnetDemoDlg::OnSettingStu()
{
	// TODO: �ڴ���������������
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
			AfxMessageBox(_T("0-6 bytes��"));
			return;
		}
		USES_CONVERSION;
		rbt_win_config_stu(T2A(strMac), T2A(strStu));
	}
}


void CrbtnetDemoDlg::OnBnClickedButtonSwitch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
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
		delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
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
	//�ͷ��ڴ�ռ�
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}
}
