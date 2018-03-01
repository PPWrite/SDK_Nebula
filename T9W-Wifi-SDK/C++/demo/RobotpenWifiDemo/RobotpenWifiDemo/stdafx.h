
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include <list>
#include <vector>
#include <Dbt.h>
#include <stdint.h>
#include "Functions.h"
#include "gdiplus.h"
using namespace Gdiplus;

struct sCanvasPointItem
{
	CPoint beginPonit;
	std::list<CPoint> lstPoint;
};

// 笔数据信息
typedef struct pen_info
{
	uint8_t nStatus;		// 笔状态
	uint16_t nX;			// 笔x轴坐标
	uint16_t nY;			// 笔y轴坐标
	uint16_t nPress;		// 笔压力
	bool operator==(pen_info &penInfo) const
	{
		if (penInfo.nX == this->nX
			&& penInfo.nY == this->nY
			&& penInfo.nPress == this->nPress
			&& penInfo.nStatus == this->nStatus)
		{
			return true;
		}
		return false;
	}
}PEN_INFO;  

//页码信息
typedef struct page_info
{
	uint8_t page_num : 8;
	uint8_t note_num : 6;
	bool operator==(page_info &pageInfo) const
	{
		if (pageInfo.page_num == this->page_num
			&& pageInfo.note_num == this->note_num)
		{
			return true;
		}
		return false;
	}
}PAGE_INFO;

#include "mqtthandle.h"
#pragma comment(lib,"robotpen.lib")





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


