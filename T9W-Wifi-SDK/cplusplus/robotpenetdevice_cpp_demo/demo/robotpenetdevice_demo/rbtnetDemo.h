
// rbtnetDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CrbtnetDemoApp: 
// �йش����ʵ�֣������ rbtnetDemo.cpp
//

class CrbtnetDemoApp : public CWinApp
{
public:
	CrbtnetDemoApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code
// ʵ��

	DECLARE_MESSAGE_MAP()

	// ʵ��
private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

extern CrbtnetDemoApp theApp;