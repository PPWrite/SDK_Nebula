// DrawDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "rbtnetDemo.h"
#include "DrawDlg.h"
#include "afxdialogex.h"
#include <algorithm>

// CDrawDlg �Ի���

//#define USE_CURSOR

IMPLEMENT_DYNAMIC(CDrawDlg, CDialog)

CDrawDlg::CDrawDlg(int deviceType, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DRAWDLG, pParent)
	, m_bTrack(false)
	, m_bDrawing(false)
	, m_nPenStatus(0)
	, m_bMouseDraw(false)
	, m_lastPoint(0, 0)
	, m_nDeviceType(deviceType)
{
	m_nPenWidth = 2;

	m_nWidth = GetPrivateProfileInt(_T("General"), _T("Width"), 22600, GetAppPath() + _T("\\robotpenetdevice_demo.ini"));
	m_nHeight = GetPrivateProfileInt(_T("General"), _T("Height"), 16650, GetAppPath() + _T("\\robotpenetdevice_demo.ini"));
	m_nState = GetPrivateProfileInt(_T("General"), _T("State"), 270, GetAppPath() + _T("\\robotpenetdevice_demo.ini"));
}

CDrawDlg::~CDrawDlg()
{
	m_listItems.clear();
}

void CDrawDlg::onRecvData(const PEN_INFO& penInfo)
{
	CPoint point(penInfo.nX, penInfo.nY);

	//Clear(point);
	/*CString str;
	str.Format(_T("X:%d-Y:%d-Press:%d"),penInfo.nX,penInfo.nY,penInfo.nPress);
	WriteLog(str);//*/
	if (m_nState == 90)
	{
		point.SetPoint(m_nHeight - penInfo.nY, penInfo.nX);
	}
	else if (m_nState == 180)
	{
		point.SetPoint(m_nWidth - penInfo.nX, m_nHeight - penInfo.nY);
	}
	else if (m_nState == 270)
	{
		point.SetPoint(penInfo.nY, m_nWidth - penInfo.nX);
	}
	else
		point.SetPoint(penInfo.nX, penInfo.nY);
	//TRACE("X:%d,Y:%d,Press:%d\n",penInfo.nX,penInfo.nY, penInfo.nPress);

	if (penInfo.nStatus == 0x11)
	{
		// �ʽӴ�������
		if (!m_bTrack)
		{
			m_bTrack = true;
			compressPoint(point);
			onbegin(point);
		}
		else
		{
			compressPoint(point);
			onDrawing(point);
		}
	}
	else
	{
		if (m_bTrack)
		{
#ifdef USE_FILE
			if (m_pageInfo.page_num > 0)
				SaveData(m_pageInfo, m_vecPenInfo);
			m_vecPenInfo.clear();
#endif
			m_bTrack = false;
			endTrack(true);
		}
	}
}

void CDrawDlg::onRecvData(unsigned short us, unsigned short ux, unsigned short uy, unsigned short up)
{
	CPoint point(ux, uy);
	//Clear(point);
	/*CString str;
	str.Format(_T("X:%d-Y:%d-Press:%d-Status:%d"), ux, uy, up, us);
	WriteLog(str);//*/
	int state = m_nState;
	if (60 == m_nDeviceType)
		state += 180;
	if (state == 90)
	{
		point.SetPoint(m_nHeight - uy, ux);
	}
	else if (state == 180)
	{
		point.SetPoint(m_nWidth - ux, m_nHeight - uy);
	}
	else if (state == 270)
	{
		point.SetPoint(uy, m_nWidth - ux);
	}
	else
		point.SetPoint(ux, uy);
	/*CString str;
	str.Format(_T("X:%d,Y:%d,Press:%d,Status:%d\n"), ux, uy, up, us);
	OutputDebugString(str);//*/

	/*TRACE("%d\n", us);
	switch (us)
	{
	case 0:
		m_nFlags = 0;
		endTrack(true);
		break;
	case 16:
	case 17:
	{
		if (m_nFlags == 0)
		{
			m_nFlags = 1;
			compressPoint(point);
			onbegin(point);
	}
		else
		{
			compressPoint(point);
			onDrawing(point);
		}
}
	break;
	default:
		break;
	}
	return;//*/

	if (us == 0x11 || us == 0x21 || us == 0x31)
	{
		// �ʽӴ�������
		if (!m_bTrack)
		{
			m_bTrack = true;
			compressPoint(point);
			onbegin(point);
		}
		else
		{
			compressPoint(point);
			onDrawing(point, (ePenType)us);
		}

#ifdef USE_CURSOR
		ClientToScreen(&point);
		::SetCursorPos(point.x, point.y);
#endif // USE_CURSOR
	}
	else
	{
#ifdef USE_CURSOR
		if (us == 0x10 || us == 0x20)
		{
			compressPoint(point);
			ClientToScreen(&point);
			::SetCursorPos(point.x, point.y);
		}
#endif // USE_CURSOR
		if (m_bTrack)
		{
			m_bTrack = false;
			endTrack(true);
		}

	}

	/*if (up == 0 && m_nFlags == 1)// ���뿪����
	{
		endTrack(true);
		m_nFlags = 0;
	}
	else
	{
		// �ʽӴ�������
		if (m_nFlags == 0)
		{
			m_nFlags = 1;
			compressPoint(point);
			onbegin(point);
		}
		else
		{
			compressPoint(point);
			onDrawing(point);
		}
	}//*/
}

void CDrawDlg::Clear()
{
	m_bTrack = 0;
	m_currentItem.lstPoint.clear();
	m_listItems.clear();
	Invalidate();
	WriteLog(_T("CDrawDlg::Clear()"));
}

void CDrawDlg::Clear(const CPoint& pt)
{

}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CDrawDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
#ifdef BEZIER
	CWnd* pWnd = this;
	CRect rc; // ����һ�������������
	pWnd->GetClientRect(rc);
	int nWidth = rc.Width();
	int nHeight = rc.Height();

	CDC *pDC = pWnd->GetDC(); // �����豸������
	CDC MemDC; // ����һ���ڴ���ʾ�豸����
	CBitmap MemBitmap; // ����һ��λͼ����

					   //��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(pDC);
	//����һ������Ļ��ʾ���ݵ�λͼ��λͼ�Ĵ�С��ѡ�ô��ڿͻ����Ĵ�С
	MemBitmap.CreateCompatibleBitmap(pDC, nWidth, nHeight);
	//��λͼѡ�뵽�ڴ���ʾ�豸�У�ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	//���ñ���ɫ��λͼ����ɾ��������Ǻ�ɫ�������õ��ǰ�ɫ��Ϊ����
	MemDC.FillSolidRect(0, 0, nWidth, nHeight, RGB(240, 240, 240));

	Graphics graphics(MemDC.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	Pen pen(Color(255, 0, 0, 0), m_nPenWidth);

	for (std::list<sCanvasPointItem>::iterator it = m_listItems.begin();
		it != m_listItems.end(); ++it)
	{
		if (it->lstPoint.size() == 0)
		{
			continue;
		}
		int nSize = it->lstPoint.size() + 1;
		Point* pointSize = new Point[nSize];
		//PointF tmpPoint = item.beginPoint;
		//onbegin(ref tmpPoint);
		pointSize[0].X = it->beginPonit.x;
		pointSize[0].Y = it->beginPonit.y;
		int nCount = 0;
		for (std::list<CPoint>::iterator its = it->lstPoint.begin(); its != it->lstPoint.end(); ++its)
		{
			pointSize[nCount + 1].X = its->x;
			pointSize[nCount + 1].Y = its->y;
			++nCount;
		}

		graphics.DrawLines(&pen, pointSize, nSize);
		delete[] pointSize;
	}

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	pDC->BitBlt(0, 0, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);

	//��ͼ��ɺ������
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();

	DeleteObject(pDC->m_hDC);
#else
	CDC* pdc = this->GetDC();
	Graphics graphics(pdc->m_hDC);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	Pen pen(Color(255, 0, 0, 0), m_nPenWidth);

	/*for (std::list<sCanvasPointItem>::iterator it = m_listItems.begin();
		it != m_listItems.end(); ++it)
	{
		if (it->lstPoint.size() == 0)
		{
			continue;
		}
		int nSize = it->lstPoint.size() + 1;
		Point* pointSize = new Point[nSize];
		//PointF tmpPoint = item.beginPoint;
		//onbegin(ref tmpPoint);
		pointSize[0].X = it->beginPonit.x;
		pointSize[0].Y = it->beginPonit.y;
		int nCount = 0;
		for (std::list<CPoint>::iterator its = it->lstPoint.begin(); its != it->lstPoint.end(); ++its)
		{
			pointSize[nCount + 1].X = its->x;
			pointSize[nCount + 1].Y = its->y;
			++nCount;
		}

		graphics.DrawLines(&pen, pointSize, nSize);
		delete[] pointSize;
	}
	*/

	std::for_each(m_listItems.begin(), m_listItems.end(), [&graphics, &pen](const sCanvasPointItem& va) {
		if (va.lstPoint.size() == 0) {
			return;
		}
		int nSize = va.lstPoint.size() + 1;
		Point* pointSize = new Point[nSize];
		//PointF tmpPoint = item.beginPoint;
		//onbegin(ref tmpPoint);
		pointSize[0].X = va.beginPonit.x;
		pointSize[0].Y = va.beginPonit.y;
		int nCount = 0;
		for (std::list<CPoint>::const_iterator its = va.lstPoint.cbegin(); its != va.lstPoint.cend(); ++its)
		{
			pointSize[nCount + 1].X = its->x;
			pointSize[nCount + 1].Y = its->y;
			++nCount;
		}

		graphics.DrawLines(&pen, pointSize, nSize);
		delete[] pointSize;
	});

	DeleteObject(pdc->m_hDC);//*/
#endif
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDrawDlg ��Ϣ�������

void CDrawDlg::onbegin(const CPoint& pos)
{
	m_bDrawing = true;
	m_lastPoint = pos;
	m_currentItem.beginPonit = pos;
	m_currentItem.lstPoint.clear();
}

void CDrawDlg::onDrawing(const CPoint& pos, ePenType type)
{
	if (!m_bDrawing)
		return;
	doDrawing(pos, type);
	m_currentItem.lstPoint.push_back(pos);
}

void CDrawDlg::onEnd()
{
	m_bDrawing = false;
}

void CDrawDlg::doDrawing(const CPoint& pos, ePenType type)
{
	CRect rect;
	CDC* pdc = this->GetDC();
	if (pdc == NULL)
	{
		DWORD dw = ::GetLastError();
		dw = dw;
		return;
	}

	Graphics graphics(pdc->m_hDC);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	Pen pen(Color(255, 0, 0, 0), m_nPenWidth);
	if (type == SIDE_PEN)
		pen.SetColor(Color(255, 255, 0, 0));
	else if(type == ERASER)
		pen.SetColor(Color(255, 240, 240, 240));

	graphics.DrawLine(&pen, m_lastPoint.x, m_lastPoint.y, pos.x, pos.y);
	m_lastPoint = pos;
	//delete pdc;
	DeleteObject(pdc->m_hDC);
}

void CDrawDlg::endTrack(bool bSave /*= true*/)
{
	onEnd();
	if (m_currentItem.lstPoint.size() > 0)
	{
		/////////////////////////////////////////////////////
#ifdef BEZIER
		int nCount = (m_currentItem.lstPoint.size() + 1) * 2;
		float *data = new float[nCount];
		data[0] = m_currentItem.beginPonit.x;
		data[1] = m_currentItem.beginPonit.y;
		int nIndex = 2;
		for (std::list<CPoint>::iterator its = m_currentItem.lstPoint.begin(); its != m_currentItem.lstPoint.end(); ++its)
		{
			data[nIndex++] = its->x;
			data[nIndex++] = its->y;
		}
		size_t dest_len;
		float *dest_data = beziers(data, nCount, &dest_len);
		delete[]data;

		m_currentItem.lstPoint.clear();

		m_currentItem.beginPonit.x = dest_data[0];
		m_currentItem.beginPonit.y = dest_data[1];
		for (int i = 2; i < dest_len; i += 2)
		{
			CPoint pt(dest_data[i], dest_data[i + 1]);
			m_currentItem.lstPoint.push_back(pt);
		}
		free(dest_data);
#endif
		//////////////////////////////////////////////////
		m_listItems.push_back(m_currentItem);

		m_currentItem.lstPoint.clear();
#ifdef BEZIER
		Invalidate();
#endif
	}
}

void CDrawDlg::compressPoint(CPoint& point)
{
	int nx = (point.x / nCompress);
	int ny = (point.y / nCompress);
	point.x = nx;
	point.y = ny;
}

bool CDrawDlg::pointIsInvalid(int nPenStatus, CPoint& pointValue)
{
	if ((m_point == pointValue) && (m_nPenStatus == nPenStatus))
		return false;
	m_point = pointValue;
	m_nPenStatus = nPenStatus;
	return true;
}


void CDrawDlg::PostNcDestroy()
{
	delete this;
	CDialog::PostNcDestroy();
}

void CDrawDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Clear();
	CDialog::OnLButtonDblClk(nFlags, point);
}


void CDrawDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(rc);
	int width = rc.Width();
	int height = rc.Height();
	nCompress = (double)m_nWidth / m_nHeight;
	if (m_nState == 90 || m_nState == 270)
	{
		if ((double)height / width < nCompress)
			nCompress = (double)m_nWidth / height;
		else
			nCompress = (double)m_nHeight / width;
	}
	else
	{
		if ((double)width / height < nCompress)
			nCompress = (double)m_nWidth / width;
		else
			nCompress = (double)m_nHeight / height;
	}

	this->Clear();
}


BOOL CDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int width = 1000;
	if (m_nState == 0 || m_nState == 180)
		width = GetSystemMetrics(SM_CXSCREEN) / 2;
	else
		width = GetSystemMetrics(SM_CYSCREEN) * 3 / 5;
	nCompress = (double)m_nWidth / width;
	int height = m_nHeight / nCompress;


	CRect rect;
	if (m_nState == 90 || m_nState == 270)
	{
		int rand_width = rand() % (GetSystemMetrics(SM_CXSCREEN) - height);
		int rand_height = rand() % (GetSystemMetrics(SM_CYSCREEN) - width);
		rect.SetRect(rand_width, rand_height, rand_width + height, rand_height + width);
	}
	else
	{
		int rand_width = rand() % (GetSystemMetrics(SM_CXSCREEN) - width);
		int rand_height = rand() % (GetSystemMetrics(SM_CYSCREEN) - height);
		rect.SetRect(rand_width, rand_height, rand_width + width, rand_height + height);
	}

	//CRect rect(rand_width,rand_height,rand_width + width,rand_height + height);
	AdjustWindowRect(rect, GetStyle(), FALSE);
	MoveWindow(rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
