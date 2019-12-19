// DrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USBHelper.h"
#include "DrawDlg.h"
#include "afxdialogex.h"


// CDrawDlg �Ի���

IMPLEMENT_DYNAMIC(CDrawDlg, CDialog)

CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawDlg::IDD, pParent)
	, m_nIndex(0)
	, m_strText("")
	, m_pWBDlg(NULL)
	, m_strVote("")
	, m_bOn(false)
{
	memset(m_Sum,0,COUNT);
}

CDrawDlg::~CDrawDlg()
{
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrawDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_CLICK, OnClick)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// CDrawDlg ��Ϣ�������


void CDrawDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	int bottom = 18;

	CDC dcMem;									//�����ڴ��豸
	CRect rect;
	GetClientRect(&rect);						//��ȡ���������
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	dcMem.CreateCompatibleDC(&dc);				//�����豸������
	dcMem.SelectObject(&bmp);					//��λͼѡ���ڴ��豸
	dcMem.FillSolidRect(rect,RGB(0,0,0));		//��䴰��

	CPen pen; 
	pen.CreatePen(PS_SOLID,1,RGB(0,120,0));
	dcMem.SelectObject(&pen);
	/////////////////////////////////////////
	int nCount = (COUNT > m_nIndex) ? m_nIndex : COUNT;
	dcMem.MoveTo(rect.Width(),m_Sum[0]);
	for(int i=0;i<nCount;i++)
	{
		dcMem.LineTo(rect.Width()-(i*5),m_Sum[i]);
		dcMem.MoveTo(rect.Width()-(i*5),m_Sum[i]);
	}
	dcMem.LineTo(rect.Width() - ((nCount-1)*5),m_Sum[nCount-1]);
	//Text
	dcMem.SetBkMode(TRANSPARENT);				
	dcMem.SetTextColor(RGB(255,255,255));		
	CRect rc = CRect(0,rect.Height()/2-bottom,rect.Width(),rect.Height());
	CFont *font = dcMem.SelectObject(&m_font);
	dcMem.DrawText(m_strVote,rc,1);
	dcMem.SelectObject(font);
	rc = CRect(0,rect.Height()-bottom,rect.Width()-bottom,rect.Height());
	dcMem.DrawText(m_strText,rc,1);

	//Ellipse
	CBrush brush;
	if(m_bOn)
		brush.CreateSolidBrush(RGB(0,255,0));
	else
		brush.CreateSolidBrush(RGB(255,0,0));
	dcMem.SelectObject(&brush);
	CRect rc2 = CRect(rect.Width()-bottom,rect.Height()-bottom,rect.Width(),rect.Height());
	dcMem.Ellipse(rc2);
	/////////////////////////////////////////
	//���ڴ��豸�е�ͼ����ʾ���������
	dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	bmp.DeleteObject();
	dcMem.DeleteDC();
}


BOOL CDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//SetTimer(0,rand()%500+500,NULL);
	//SetTimer(0,1,NULL);

	m_font.CreateFont(
		36,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));                 // lpszFacename

	m_pWBDlg = new CWBDlg;
	m_pWBDlg->Create(IDD_WBDLG);
	m_pWBDlg->ShowWindow(SW_HIDE);//*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDrawDlg::AddData(PEN_INFO& penInfo,  float fWidth)
{
	m_pWBDlg->onRecvData(penInfo, fWidth);

	for(int i=COUNT-1;i>0;i--)
	{
		m_Sum[i] = m_Sum[i-1];
	}
	CRect rect;
	this->GetClientRect(rect);
	m_Sum[0] = (penInfo.nX+penInfo.nY)%rect.Height();
	m_nIndex++;

	this->Invalidate(FALSE);	
}

void CDrawDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);
	int height = rect.Height();	
	PEN_INFO penInfo = {0};
	penInfo.nX = rand()%DEV_WIDTH;
	penInfo.nY = rand()%DEV_HEIGHT;

	if(m_nIndex%20 == 0)
		penInfo.nPress = 0;
	else
		penInfo.nPress = 111;
	//if (m_strText == _T("1"))
		AddData(penInfo);//*/
	/*if (m_nIndex == 100)
		KillTimer(0);//*/
	CDialog::OnTimer(nIDEvent);
}


void CDrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//this->SendMessage(WM_CLICK,(WPARAM)m_strText.GetBuffer());
	//this->GetParent()->SendMessage(WM_CLICK,(WPARAM)m_strText.GetBuffer());
	CDialog::OnLButtonDown(nFlags, point);
}

LRESULT CDrawDlg::OnClick(WPARAM wParam, LPARAM lParam)
{
	BSTR b = (BSTR)wParam;
	CString str(b);
	if(NULL != m_pWBDlg)
	{
		m_pWBDlg->SetWindowText(str);
		m_pWBDlg->ShowWindow(SW_SHOW);
	}
	//AfxMessageBox(s);
	return 0;
}


void CDrawDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//m_pWBDlg->SendMessage(WM_CLOSE,NULL,NULL);

	m_font.DeleteObject();

	if(NULL != m_pWBDlg)
	{
		m_pWBDlg = NULL;
	}
}

void CDrawDlg::SetOnLine(bool bOn)
{
	m_bOn = bOn;
	this->Invalidate(FALSE);	
}

void CDrawDlg::SetText(CString str ) 
{
	m_strText = str;
}
void CDrawDlg::SetVote(CString strVote) 
{	
	m_strVote = strVote;
	this->Invalidate(FALSE);
}

void CDrawDlg::SetPage(const PAGE_INFO &pageInfo)
{
	m_pWBDlg->SetPage(pageInfo);
}

void CDrawDlg::SetID(int nID)
{
	m_pWBDlg->SetID(nID);
}

void CDrawDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if (m_bOn)
		this->SendMessage(WM_CLICK,(WPARAM)m_strText.GetBuffer());

	CDialog::OnLButtonDblClk(nFlags, point);
}


void CDrawDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �ڴ˴������Ϣ����������
	delete this;
}

void CDrawDlg::ResetUI(bool bClear)
{
	if(bClear)
		m_pWBDlg->Clear();
	for (int i=0;i<COUNT;i++)
	{
		m_Sum[i] = 0;
	}

	/*CString str;
	str.Format(_T("DeviceID:%s-Count:%d"),m_strText,m_nIndex);
	WriteLog(str);//*/

	m_nIndex = 0;
	this->Invalidate(FALSE);
}

void CDrawDlg::HideWinodow()
{
	m_pWBDlg->ShowWindow(SW_HIDE);
}

void CDrawDlg::ResetWindow()
{
	if(NULL != m_pWBDlg)
	{
		m_pWBDlg->SetWindowText(m_strText);
		m_pWBDlg->ResetWindow();
		m_pWBDlg->ShowWindow(SW_SHOW);
	}
}

void CDrawDlg::Clear()
{
	if(NULL != m_pWBDlg)
		m_pWBDlg->Clear();
}
