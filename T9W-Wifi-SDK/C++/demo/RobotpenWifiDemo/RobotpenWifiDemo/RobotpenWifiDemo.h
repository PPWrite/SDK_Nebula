
// RobotpenWifiDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRobotpenWifiDemoApp:
// �йش����ʵ�֣������ RobotpenWifiDemo.cpp
//

class CRobotpenWifiDemoApp : public CWinApp
{
public:
	CRobotpenWifiDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CRobotpenWifiDemoApp theApp;