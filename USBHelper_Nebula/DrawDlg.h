#pragma once
#include "WBDlg.h"

#define COUNT 40
#define SPACE 5

 #define WM_CLICK WM_USER + 100
// CDrawDlg �Ի���

class CDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawDlg)

public:
	CDrawDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawDlg();

// �Ի�������
	enum { IDD = IDD_DRAWDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnClick(WPARAM wParam, LPARAM lParam);

protected:
	DWORD m_Sum[COUNT];
	int m_nIndex;
	CString m_strText;
	CWBDlg	*m_pWBDlg;
	CString m_strVote;
	bool	m_bOn;
	CFont	m_font;

public:
	void AddData(PEN_INFO& penInfo, float fWidth = 2);
	void SetOnLine(bool bOn = false);
	void SetText(CString str = _T(""));
	void SetVote(CString strVote = _T(""));
	void SetPage(const PAGE_INFO &pageInfo);
	void SetID(int nID);
	CString GetText(){return m_strText;}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
	void HideWinodow();
	void ResetUI(bool bClear = false);

	void ResetWindow();
	void Clear();
};
