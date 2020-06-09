// WBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "USBHelper.h"
#include "WBDlg.h"
#include "afxdialogex.h"
#include <algorithm>

//#define  USE_FILE
// CWBDlg 对话框
//#define USE_PATH

bool compare(const PAGE_INFO & a,const PAGE_INFO &b)
{
	if (a.note_num == b.note_num)
		return a.page_num < b.page_num;

	return a.note_num < b.note_num;
}

IMPLEMENT_DYNAMIC(CWBDlg, CDialog)

	CWBDlg::CWBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWBDlg::IDD, pParent)
	, m_bDrawing(FALSE)
	, m_nPenStatus(0)
	, m_nDevStatus(0)
	, m_bMouseDraw(FALSE)
	, m_bTrack(false)
	, m_nWidth(DEV_WIDTH)
	, m_nHeight(DEV_HEIGHT)
	, m_nState(0)
	, m_nPenWidth(1)
	, m_lastPoint(0,0)
	, m_lastWidth(0)
	, m_lastPathPoint(0,0)
	, m_nID(0)
{
	memset(&m_pageInfo,0,sizeof(PAGE_INFO));
	memset(&m_canvasPageInfo,0,sizeof(PAGE_INFO));
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
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CWBDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CWBDlg::OnBnClickedButtonRight)
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

#ifdef USE_FILE
	GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_SHOW);
#endif

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
	//return;
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

		//用path绘制
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
			PointF fPoint;
			fPoint.X = pt.x;
			fPoint.Y = pt.y;
			onbegin(fPoint);
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
			PointF fPoint;
			fPoint.X = pt.x;
			fPoint.Y = pt.y;
			onDrawing(fPoint);
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}


void CWBDlg::compressPoint(PointF& point)
{
	float fx = (float)(point.X / nCompress);
	float fy = (float)(point.Y / nCompress);
	point.X = fx;
	point.Y = fy;
}

bool CWBDlg::pointIsInvalid( int nPenStatus, CPoint& pointValue )
{
	if ((m_point == pointValue ) && (m_nPenStatus == nPenStatus))
		return false;
	m_point = pointValue;
	m_nPenStatus = nPenStatus;
	return true;
}

void CWBDlg::onbegin( const PointF& pos )
{
	m_bDrawing = true;
	m_lastPoint = pos;

	CPoint cPoint;
	cPoint.SetPoint(pos.X, pos.Y);
	m_currentItem.beginPonit = cPoint;
	m_currentItem.lstPoint.clear();
}

void CWBDlg::onDrawing( const PointF& pos , ePenMode type, float fWidth)
{
	if (!m_bDrawing)
		return;
	doDrawing(pos,type, fWidth);

	CPoint cPoint;
	cPoint.SetPoint(pos.X, pos.Y);
	m_currentItem.lstPoint.push_back(cPoint);
}

void CWBDlg::onEnd()
{
	m_bDrawing = false;
}

void CWBDlg::doDrawing( const PointF& pos , ePenMode type, float fWidth)
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

	Pen pen(Color(255, 0, 0, 0), fWidth);
	if (type == SIDE_PEN){
		pen.SetWidth(fWidth);
		pen.SetColor(Color(255, 255, 0, 0));
		graphics.DrawLine(&pen, m_lastPoint.X, m_lastPoint.Y, pos.X, pos.Y);
	}else if(type == ERASER){
		pen.SetWidth(20);
		pen.SetColor(Color(255, 240, 240, 240));
		//pen.SetColor(Color(255, 255, 0, 0));
		graphics.DrawLine(&pen, m_lastPoint.X-10, m_lastPoint.Y-10, pos.X+10, pos.Y+10);

	}else{
		graphics.DrawLine(&pen, m_lastPoint.X, m_lastPoint.Y, pos.X, pos.Y);
	}

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
	TRACE("CWBDlg::Clear()\n");
	m_currentItem.lstPoint.clear();
	m_listItems.clear();
	Invalidate();
}

void CWBDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Clear();
	m_graphicsPath.Reset();
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CWBDlg::onRecvData(const PEN_INFO& penInfo, float fWidth)
{
#ifdef USE_FILE
	if (m_canvasPageInfo == m_pageInfo)
	{}
	else
	{
		SetCanvasPage(m_pageInfo);
	}
	m_vecPenInfo.push_back(penInfo);
#endif

	processData(penInfo, fWidth);
}

void CWBDlg::processData(const PEN_INFO& penInfo, float fWidth)
{

	//TRACE("++++++++++++++++++ fwidth %f\r\n", fWidth);
	//fWidth = fWidth/nCompress;
	//TRACE("++++++++++++++++++ fwidth %f\r\n", fWidth);
	CPoint point(penInfo.nX, penInfo.nY);
	//Clear(point);
	/*CString str;
	str.Format(_T("X:%d-Y:%d-Press:%d"),penInfo.nX,penInfo.nY,penInfo.nPress);
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

	//TRACE(_T("X:%d-Y:%d-Press:%d-Status:%d\n"),penInfo.nX,penInfo.nY,penInfo.nPress,penInfo.nStatus);
	//TRACE(_T("X:%d-Y:%d-Press:%d-Status:%d\n"),point.x,point.y,penInfo.nPress,penInfo.nStatus);

	PointF fPoint;
	fPoint.X = point.x;
	fPoint.Y = point.y;

	if (penInfo.nStatus == 0x11 || penInfo.nStatus == 0x21 || penInfo.nStatus == 0x31)
	{

		// 笔接触到板子
		if (!m_bTrack)
		{
			m_bTrack = true;
#ifdef USE_PATH
			m_lastWidth = fWidth;
			m_lastpoint = point;
			m_pointsList.push_back(point.x);
			m_pointsList.push_back(point.y);
			m_pointsList.push_back(fWidth);
#endif

			compressPoint(fPoint);
			onbegin(fPoint);
		}
		else
		{

#ifdef USE_PATH
			float a = labs(m_lastpoint.x - point.x);
			float b = labs(m_lastpoint.y - point.y);
			float c = sqrt(a*a+b*b);
			//TRACE("kaifang-------->>>>:%f ====>>> %f\r\n",c, (m_lastWidth+fWidth)/2);
			if(c >= (m_lastWidth+fWidth)/2){
				//TRACE("insert-------->>>>\r\n");
				m_pointsList.push_back(point.x);
				m_pointsList.push_back(point.y);
				m_pointsList.push_back(fWidth);
				m_lastWidth = fWidth;
			}else{
				
			}
			m_lastpoint = point;
			
#endif
			compressPoint(fPoint);
			//TRACE("onDrawing--x:%d--y:%d\r\n",point.x,point.y);
			onDrawing(fPoint,(ePenMode)penInfo.nStatus, fWidth/*/nCompress*/);
			moveCursor(point);
		}
	}
	else
	{
#ifdef USE_FILE
		if (m_pageInfo.page_num > 0)
			SaveData(m_pageInfo,m_vecPenInfo);
		m_vecPenInfo.clear();
#endif
		m_bTrack = false;
		endTrack(true);

#ifdef USE_PATH
		if(m_pointsList.size() > 0)
		{
			float *fPoint = new float[m_pointsList.size()];
			for (int i = 0; i < m_pointsList.size(); i++)
			{
				fPoint[i] = m_pointsList[i];
			}

			if(m_pointsList.size() < 2){
				drawLinePath(fPoint, m_pointsList.size());
				m_pointsList.clear();
				delete fPoint;
				fPoint = NULL;
				return;
			}
			//TRACE("insert point count ===>>>>>> %d\r\n", m_pointsList.size());

			int nCount = 0;
			float *fResult = GetInstance()->ToPath(fPoint, m_pointsList.size(), &nCount);
			drawLinePath(fResult, nCount);
			m_pointsList.clear();
			GetInstance()->FreeMemory(fResult);

			delete fPoint;
			fPoint = NULL;
		}
#endif

	}

}

void CWBDlg::drawLinePath(float *points, unsigned int count)
{
	float ratioY = nCompress;
	if(points == NULL)
		return;

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

	//GraphicsPath newpath;


	//GraphicsPath newpath1;
	//newpath1.AddLine(100,100,200,100);
	//newpath.AddPath(&newpath1, true);

	//GraphicsPath newpath2;
	//newpath2.AddLine(200,100,200,200);
	//newpath.AddPath(&newpath2, true);

	//GraphicsPath newpath3;
	//newpath3.AddLine(100,100,100,100);
	//newpath.AddPath(&newpath3, true);


	//graphics.FillPath(new SolidBrush(Gdiplus::Color::Black), &newpath);
	//DeleteObject(pdc->m_hDC);

	//return;

	//Point *newpoints = new Point[count/3];

	int nIndex = 0;

	for(int i = 0; i < count; i+=3){
		/*if(i == 0)
		{
			Point firstP(points[i]/ratioY, points[i+1]/ratioY);
			m_lastPathPoint = firstP;
			continue;
		}else if (points[i+2] > 0)
		 {
		 if(points[i+5] > 0){
		 Point *p2 = new Point[4];
		 Point point0(m_lastPathPoint);
		 Point point1(points[i]/ratioY, points[i+1]/ratioY);
		 Point point2(points[i+3]/ratioY, points[i+4]/ratioY);
		 Point point3(points[i+6]/ratioY, points[i+7]/ratioY);
		 p2[0] = point0;
		 p2[1] = point1;
		 p2[2] = point2;
		 p2[3] = point3;
		 m_lastPathPoint = point3;
		 m_graphicsPath.AddCurve(p2, 4);
		 i += 6;
		 }else {
		 Point *p3 = new Point[3];
		 Point point0(m_lastPathPoint);
		 Point point1(points[i]/ratioY, points[i+1]/ratioY);
		 Point point2(points[i+3]/ratioY, points[i+4]/ratioY);
		 p3[0] = point0;
		 p3[1] = point1;
		 p3[2] = point2;

		 m_lastPathPoint = point2;
		 m_graphicsPath.AddBeziers(p3, 3);
		 i += 3;
		 }

		 }else {
		 Point *p1 = new Point[2];
		 Point point(points[i]/ratioY,  points[i+1]/ratioY);
		 p1[0] = m_lastPathPoint;
		 p1[1] = point;
		 m_lastPathPoint = point;
		 m_graphicsPath.AddLines(p1, 2);
		 }*/

		PointF point((float)points[i]/ratioY,  (float)points[i+1]/ratioY);
		
		//newpoints[nIndex] = point;
		//nIndex++;
		if(i > 0){
			GraphicsPath newPath;
			newPath.AddLine(m_lastPathPoint, point);
			newPath.SetFillMode(Gdiplus::FillModeWinding);
			
			m_graphicsPath.AddPath(&newPath, true);
			//m_graphicsPath.AddEllipse(point.X, point.Y, points[i+2], points[i+2]);
			//TRACE("point ===>>> last %f ,%f; current:%f, %f current index %d\r\n", m_lastPathPoint.X, m_lastPathPoint.Y, point.X, point.Y, i);

		}


		//Point point1(point.X,  point.Y);
		m_lastPathPoint = point;

	}
	m_graphicsPath.CloseFigure();
			//GraphicsPath newPath;
			//newPath.AddClosedCurve(newpoints, count/3);
			//m_graphicsPath.AddPath(&newPath, false);
	//m_graphicsPath.add
	//m_graphicsPath.AddLines(newpoints, count/3);
	this->Clear();
	//graphics.DrawPath(new Pen(Gdiplus::Color::Black), &m_graphicsPath);
	m_graphicsPath.SetFillMode(Gdiplus::FillModeWinding);
	graphics.FillPath(new SolidBrush(Gdiplus::Color::Black), &m_graphicsPath);
	DeleteObject(pdc->m_hDC);
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
	m_graphicsPath.Reset();
}

void CWBDlg::Clear(const CPoint& pt)
{
	CPoint point = pt;
	PointF fPoint;
	fPoint.X = pt.x;
	fPoint.Y = pt.y;
	compressPoint(fPoint);
	CRect rc(0,0,10,10);
	point.SetPoint(fPoint.X, fPoint.Y);
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

void CWBDlg::SetPage(const PAGE_INFO &pageInfo)
{
	if (pageInfo.note_num == 0 && pageInfo.page_num == 0)
		return ;

	if(m_pageInfo.note_num == pageInfo.note_num && m_pageInfo.page_num == pageInfo.page_num)
		return;
	memcpy(&m_pageInfo,&pageInfo,sizeof(PAGE_INFO));

#ifdef USE_FILE
	bool bFound = false;
	for (int i=0;i<m_vecPageNum.size();i++)
	{
		if (pageInfo == m_vecPageNum[i])
		{
			bFound = true;
		}
	}
	if (!bFound)
	{
		m_vecPageNum.push_back(pageInfo);
		sort(m_vecPageNum.begin(),m_vecPageNum.end(),compare);
	}

	SetCanvasPage(pageInfo);
#else
	CString str;
	str.Format(_T("第%d本,第%d页"),pageInfo.note_num,pageInfo.page_num);

	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(str);
#endif
}

void CWBDlg::SetCanvasPage(const PAGE_INFO &pageInfo)
{
	memcpy(&m_canvasPageInfo,&pageInfo,sizeof(PAGE_INFO));

	CString str;
	str.Format(_T("第%d本,第%d页,共%d页"),m_canvasPageInfo.note_num,m_canvasPageInfo.page_num,m_vecPageNum.size());

	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(str);

	Clear();
	ReadData();
}

void CWBDlg::SetID(int nID)
{
	m_nID = nID;
}


void CWBDlg::ReadData()
{
	CString strFileName;
	strFileName.Format(_T("%s\\%d.bat"),GetDataFloder(),m_nID);
	try
	{
		CFileFind find;
		CFile file;
		if(find.FindFile(strFileName))
		{
			file.Open(strFileName, CFile::modeRead);
			if(file !=INVALID_HANDLE_VALUE)
			{
				PAGE_PEN_INFO pagePenInfo = {0};
				while (true)
				{
					int nRead = file.Read(&pagePenInfo,sizeof(PAGE_PEN_INFO));
					if(nRead < sizeof(PAGE_PEN_INFO))
						break;
					if (m_canvasPageInfo == pagePenInfo.pageInfo)
					{
						processData(pagePenInfo.penInfo);
					}
				}
			}

		}
		find.Close();
	}
	catch (...)
	{
	}
}

void CWBDlg::SaveData(const PAGE_INFO &pageInfo,const std::vector<PEN_INFO> &vecPenInfo)
{
	CString strFileName;
	strFileName.Format(_T("%s\\%d.bat"),GetDataFloder(),m_nID);
	try
	{
		CFileFind find;
		CFile file;
		if(find.FindFile(strFileName))
		{
			file.Open(strFileName, CFile::modeWrite);
			if(file !=INVALID_HANDLE_VALUE)
				file.SeekToEnd();
		}
		else
		{
			file.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
		}
		find.Close();

		if(file !=INVALID_HANDLE_VALUE)
		{
			PAGE_PEN_INFO pagePenInfo = {0};
			for(int i=0;i<vecPenInfo.size();i++)
			{
				memcpy(&pagePenInfo.pageInfo,&pageInfo,sizeof(PAGE_INFO));
				memcpy(&pagePenInfo.penInfo,&vecPenInfo[i],sizeof(PEN_INFO));
				file.Write(&pagePenInfo,sizeof(PAGE_PEN_INFO));
				/*file.Write(&nPageNum,sizeof(uint8_t));
				file.Write(&vecPenInfo[i],sizeof(PEN_INFO));*/
			}

			file.Close();
		}
	}
	catch (...)
	{
	}
}

void CWBDlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = m_vecPageNum.size();
	for (int i=0;i<nCount;i++)
	{
		if (m_vecPageNum[i] == m_canvasPageInfo)
		{
			if (i > 0)
			{
				SetCanvasPage(m_vecPageNum[i-1]);
				return;
			}
		}
	}
}

void CWBDlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = m_vecPageNum.size();
	for (int i=0;i<nCount;i++)
	{
		if (m_vecPageNum[i] == m_canvasPageInfo)
		{
			if (i < (nCount-1))
			{
				SetCanvasPage(m_vecPageNum[i+1]);
				return;
			}
		}
	}
}

void CWBDlg::SetText(const CString &str)
{
	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(str);
}
