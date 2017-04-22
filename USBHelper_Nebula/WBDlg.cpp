// WBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "USBHelper.h"
#include "WBDlg.h"
#include "afxdialogex.h"


// CWBDlg 对话框

IMPLEMENT_DYNAMIC(CWBDlg, CDialog)

CWBDlg::CWBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWBDlg::IDD, pParent)
	, m_bDrawing(FALSE)
	, m_nPenStatus(0)
	, m_nDevStatus(0)
	, m_bMouseDraw(FALSE)
	, m_nFlags(0)
	, m_nWidth(DEV_WIDTH)
	, m_nHeight(DEV_HEIGHT)
	, m_nState(0)
	, m_nPenWidth(1)
	, m_lastPoint(0,0)
{

}

CWBDlg::~CWBDlg()
{
}

void CWBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWBDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_NCDESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CWBDlg 消息处理程序


BOOL CWBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	readIni();
	int width = 1000;
	if (m_nState == 0 || m_nState == 180)
		width = GetSystemMetrics(SM_CXSCREEN)/2;
	else
		width = GetSystemMetrics(SM_CYSCREEN)*3/5;
	nCompress = (double)m_nWidth/width;
	int height = m_nHeight/nCompress;

	
	CRect rect;
	if (m_nState == 90 || m_nState == 270)
	{
		int rand_width = rand()%(GetSystemMetrics ( SM_CXSCREEN )- height); 
		int rand_height= rand()%(GetSystemMetrics ( SM_CYSCREEN )- width);
		rect.SetRect(rand_width,rand_height,rand_width + height,rand_height + width);
	}
	else
	{
		int rand_width = rand()%(GetSystemMetrics ( SM_CXSCREEN )- width); 
		int rand_height= rand()%(GetSystemMetrics ( SM_CYSCREEN )- height);
		rect.SetRect(rand_width,rand_height,rand_width + width,rand_height + height);
	}

	//CRect rect(rand_width,rand_height,rand_width + width,rand_height + height);
	AdjustWindowRect(rect, GetStyle(), FALSE);
	MoveWindow(rect);
	//SetWindowPos(NULL,rand_width,rand_height,width,height,SWP_HIDEWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CWBDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
#ifdef BEZIER
	CWnd* pWnd = this;
	CRect rc; // 定义一个矩形区域变量
	pWnd->GetClientRect(rc);
	int nWidth = rc.Width();
	int nHeight = rc.Height();

	CDC *pDC = pWnd->GetDC(); // 定义设备上下文
	CDC MemDC; // 定义一个内存显示设备对象
	CBitmap MemBitmap; // 定义一个位图对象

	//建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(pDC);
	//建立一个与屏幕显示兼容的位图，位图的大小可选用窗口客户区的大小
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	//将位图选入到内存显示设备中，只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	//先用背景色将位图清除干净，否则是黑色。这里用的是白色作为背景
	MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(240,240,240));

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
		delete [] pointSize;
	}

	//将内存中的图拷贝到屏幕上进行显示
	pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);

	//绘图完成后的清理
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();

	DeleteObject(pDC->m_hDC);
#else
	CDC* pdc = this->GetDC();
	Graphics graphics( pdc->m_hDC );
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
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
		delete [] pointSize;
	}

	DeleteObject(pdc->m_hDC);//*/
#endif
	//CDialog::OnPaint();
}


void CWBDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseDraw)
	{
		CPoint pt; 
		GetCursorPos(&pt); 

		CRect rect; 
		GetClientRect(&rect); 

		//然后把当前鼠标坐标转为相对于rect的坐标。 
		ScreenToClient(&pt); 

		if (rect.PtInRect(pt))  // 点是否在该矩形区域中
		{
			onbegin(pt);
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void CWBDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseDraw)
		endTrack();
	CDialog::OnLButtonUp(nFlags, point);
}


void CWBDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseDraw)
	{
		CPoint pt; 
		GetCursorPos(&pt); 

		CRect rect; 
		GetClientRect(&rect); 

		//然后把当前鼠标坐标转为相对于rect的坐标。 
		ScreenToClient(&pt); 


		if (rect.PtInRect(pt))  // 点是否在该矩形区域中
		{
			onDrawing(pt);
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}


void CWBDlg::compressPoint(CPoint& point)
{
	int nx = (point.x / nCompress);
	int ny = (point.y / nCompress);
	point.x = nx;
	point.y = ny;
}

bool CWBDlg::pointIsInvalid( int nPenStatus, CPoint& pointValue )
{
	if ((m_point == pointValue ) && (m_nPenStatus == nPenStatus))
		return false;
	m_point = pointValue;
	m_nPenStatus = nPenStatus;
	return true;
}

void CWBDlg::onbegin( const CPoint& pos )
{
	m_bDrawing = true;
	m_lastPoint = pos;
	m_currentItem.beginPonit = pos;
	m_currentItem.lstPoint.clear();
}

void CWBDlg::onDrawing( const CPoint& pos )
{
	if (!m_bDrawing)
		return;
	doDrawing(pos);
	m_currentItem.lstPoint.push_back(pos);
}

void CWBDlg::onEnd()
{
	m_bDrawing = false;
}

void CWBDlg::doDrawing( const CPoint& pos )
{
	CRect rect;
	CDC* pdc = this->GetDC();
	if (pdc == NULL)
	{
		DWORD dw = ::GetLastError();
		dw = dw;
		return;
	}

	Graphics graphics( pdc->m_hDC );
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	Pen pen(Color(255, 0, 0, 0), m_nPenWidth);

	graphics.DrawLine(&pen, m_lastPoint.x, m_lastPoint.y, pos.x, pos.y);
	m_lastPoint = pos;
	//delete pdc;
	DeleteObject(pdc->m_hDC);
}

void CWBDlg::endTrack( bool bSave /*= true*/ )
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
		float *dest_data = beziers(data,nCount,&dest_len);
		delete []data;

		m_currentItem.lstPoint.clear();

		m_currentItem.beginPonit.x = dest_data[0];
		m_currentItem.beginPonit.y = dest_data[1];
		for (int i=2;i<dest_len;i+=2)
		{
			CPoint pt(dest_data[i],dest_data[i+1]);
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

void CWBDlg::Clear()
{
	m_currentItem.lstPoint.clear();
	m_listItems.clear();
	Invalidate();
}

void CWBDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Clear();

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CWBDlg::onRecvData(PEN_INFO& penInfo)
{
	CPoint point(penInfo.nX, penInfo.nY);
	//Clear(point);
	/*CString str;
	str.Format(_T("X:%d-Y:%d-Press:%d"),penInfo.nX,penInfo.nY,penInfo.nPens);
	WriteLog(str);//*/
	if(m_nState == 90)
	{
		point.SetPoint(m_nHeight - penInfo.nY,penInfo.nX);
	}
	else if(m_nState == 180)
	{
		point.SetPoint(m_nWidth - penInfo.nX, m_nHeight - penInfo.nY);
	}
	else if(m_nState == 270)
	{
		point.SetPoint(penInfo.nY,m_nWidth - penInfo.nX);
	}
	else
		point.SetPoint(penInfo.nX, penInfo.nY);
	//TRACE("X:%d,Y:%d,Press:%d\n",penInfo.nX,penInfo.nY,penInfo.nPens);
	
	if (penInfo.nPress  == 0)// 笔离开板子
	{
		endTrack(true);
		m_nFlags = 0;
	}
	else
	{
		// 笔接触到板子
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
			moveCursor(point);
		}
	}
}

void CWBDlg::moveCursor(CPoint& pos)
{
	/*::ClientToScreen(this->GetSafeHwnd(), &pos);
	::SetCursorPos(pos.x, pos.y);//*/
}

void CWBDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rc;
	GetClientRect(rc);
	int width = rc.Width();
	int height = rc.Height();
	nCompress = (double)m_nWidth/m_nHeight;
	if (m_nState == 90 || m_nState == 270)
	{
		if ((double)height/width <  nCompress)
			nCompress =  (double)m_nWidth/height;
		else
			nCompress =  (double)m_nHeight/width;
	}
	else
	{
		if ((double)width/height <  nCompress)
			nCompress =  (double)m_nWidth/width;
		else
			nCompress =  (double)m_nHeight/height;
	}

	this->Clear();
}

void CWBDlg::Clear(const CPoint& pt)
{
	CPoint point = pt;
	compressPoint(point);
	CRect rc(0,0,10,10);
	if (rc.PtInRect(point))
		this->Clear();
}


void CWBDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete this;
}

void CWBDlg::readIni()
{
	m_nState = GetPrivateProfileInt(_T("General"),_T("State"),0,GetAppPath() + _T("\\USBHelper.ini"));
	m_nPenWidth = GetPrivateProfileInt(_T("General"),_T("PenWidth"),1,GetAppPath() + _T("\\USBHelper.ini"));

	m_nWidth = GetPrivateProfileInt(_T("General"),_T("Width"),0,GetAppPath() + _T("\\USBHelper.ini"));
	m_nHeight = GetPrivateProfileInt(_T("General"),_T("Height"),0,GetAppPath() + _T("\\USBHelper.ini"));
}

void CWBDlg::ResetWindow()
{
	int nCount = GetPrivateProfileInt(_T("General"),_T("ShowNum"),60,GetAppPath() + _T("\\USBHelper.ini"));
	CString str;
	this->GetWindowText(str);
	int nID = atoi(w2m(str.GetBuffer()));
	if(nID > nCount)
		return;

	CRect rc;
	GetClientRect(rc);
	int width = rc.Width();
	int height = rc.Height();
	nCompress = (double)m_nWidth/m_nHeight;
	int nRow = 0;
	int nColumn = 0;
	while(true)
	{
		width -= 5;
		if(width <= 0)
			break;
		height = width/nCompress;
		nRow = GetSystemMetrics (SM_CXSCREEN)/width;
		nColumn = GetSystemMetrics (SM_CYSCREEN)/height;
		if (nRow*nColumn > nCount)
			break;
	}

	if (m_nState == 90 || m_nState == 270)
	{
		if ((double)height/width <  nCompress)
			nCompress =  (double)m_nWidth/height;
		else
			nCompress =  (double)m_nHeight/width;
	}
	else
	{
		if ((double)width/height <  nCompress)
			nCompress =  (double)m_nWidth/width;
		else
			nCompress =  (double)m_nHeight/height;
	}

	if (nID%nRow == 0)
	{
		nColumn =  (nID-1)/nRow;
		nRow -= 1;
	}
	else
	{
		nColumn = nID/nRow;
		nRow = (nID-1)%nRow;
	}
	
	CRect rect(nRow*width,nColumn*height,nRow*width+width,nColumn*height+height);
	//AdjustWindowRect(rect, GetStyle(), FALSE);
	MoveWindow(rect);

	GetClientRect(rc);
	width = rc.Width();
	height = rc.Height();

	if (m_nState == 90 || m_nState == 270)
	{
		if ((double)height/width <  nCompress)
			nCompress =  (double)m_nWidth/height;
		else
			nCompress =  (double)m_nHeight/width;
	}
	else
	{
		if ((double)width/height <  nCompress)
			nCompress =  (double)m_nWidth/width;
		else
			nCompress =  (double)m_nHeight/height;
	}

	this->Clear();
}

PCHAR CWBDlg::w2m (PWCHAR WideStr)
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

HBRUSH CWBDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_PAGE)
	{
		pDC->SetBkColor(RGB(0,255,0));
		//HBRUSH hbr = ::CreateSolidBrush(RGB(255,0,0));    
		//return hbr;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CWBDlg::SetPage(CString strPage)
{
	CString str;
	GetDlgItem(IDC_STATIC_PAGE)->GetWindowText(str);
	if (str != strPage)
		GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(strPage);
}