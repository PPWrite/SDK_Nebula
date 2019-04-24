#pragma once

#include <list>
// CDrawDlg �Ի���

enum ePenType {
	PEN = 0x11,
	SIDE_PEN = 0x21,
	ERASER = 0x31,
};

class CDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawDlg)

public:
	CDrawDlg(int deviceType = 42, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawDlg();

	void onRecvData(const PEN_INFO& penInfo);
	void onRecvData(unsigned short us, unsigned short ux, unsigned short uy, unsigned short up);
	void Clear();
	void Clear(const CPoint& pt);

	void setDeviceType(int type) { m_nDeviceType = type; }
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

protected:
	void onbegin(const CPoint& pos);
	void onDrawing(const CPoint& pos, ePenType type = PEN);
	void onEnd();
	void doDrawing(const CPoint& pos, ePenType type = PEN);
	void endTrack(bool bSave = true);
	void compressPoint(CPoint& point);
	bool pointIsInvalid(int nPenStatus, CPoint& pointValue);
	void PostNcDestroy();

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

	PAGE_INFO m_pageInfo;
	PAGE_INFO m_canvasPageInfo;
	int m_nWidth;
	int m_nHeight;
	int m_nState;
	int m_nID;
	int m_nDeviceType;
public:
	CString m_strValue = _T("");
	virtual BOOL OnInitDialog();
};
