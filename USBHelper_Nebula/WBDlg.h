#pragma once

// CWBDlg 对话框
#define DEV_WIDTH	14335
#define DEV_HEIGHT	8191

class CWBDlg : public CDialog
{
	DECLARE_DYNAMIC(CWBDlg)

public:
	CWBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWBDlg();

// 对话框数据
	enum { IDD = IDD_WBDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	bool m_bDrawing;
	std::list<sCanvasPointItem> m_listItems;
	sCanvasPointItem m_currentItem;
	CPoint m_lastPoint;
	int m_nPenStatus;
	CPoint m_point;
	int m_nDevStatus;
	double nCompress;
	bool m_bMouseDraw;
	bool m_bTrack;
	int	m_nPenWidth;
protected:
	void onbegin(const CPoint& pos);
	void onDrawing(const CPoint& pos);
	void onEnd();
	void doDrawing(const CPoint& pos);
	void endTrack(bool bSave = true);

	void compressPoint(CPoint& point);
	bool pointIsInvalid( int nPenStatus, CPoint& pointValue );
public:
	void onRecvData(const PEN_INFO& penInfo);
	void processData(const PEN_INFO& penInfo);
	void moveCursor(CPoint& pos);
	void Clear();
	void Clear(const CPoint& pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcDestroy();
	void readIni();
	void ResetWindow();
	PCHAR w2m(PWCHAR WideStr);
	void SetPage(const PAGE_INFO &pageInfo);
	void SetCanvasPage(const PAGE_INFO &pageInfo);
	void SetID(int nID);
	std::vector<PEN_INFO> m_vecPenInfo;
	void ReadData();
	void SaveData(const PAGE_INFO &pageInfo,const std::vector<PEN_INFO> &vecPenInfo);
	std::vector<PAGE_INFO> m_vecPageNum;
	void SetText(const CString &str);
private:
	PAGE_INFO m_pageInfo;
	PAGE_INFO m_canvasPageInfo;
	int m_nWidth;
	int m_nHeight;
	int m_nState;
	int m_nID;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
};
