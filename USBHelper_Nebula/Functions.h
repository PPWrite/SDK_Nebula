#pragma once
#if DBG

#define ALLOC(dwBytes) MyAlloc(__FILE__, __LINE__, (dwBytes))

#define REALLOC(hMem, dwBytes) MyReAlloc((hMem), (dwBytes))

#define FREE(hMem)  MyFree((hMem))

#define CHECKFORLEAKS() MyCheckForLeaks()

#else

#define ALLOC(dwBytes) GlobalAlloc(GPTR,(dwBytes))

#define REALLOC(hMem, dwBytes) GlobalReAlloc((hMem), (dwBytes), (GMEM_MOVEABLE|GMEM_ZEROINIT))

#define FREE(hMem)  GlobalFree((hMem))

#define CHECKFORLEAKS()

#endif
// 获取应用程序路径
extern CString GetAppPath(void);

// 写日志
// lpszText － [in] 日志内容
extern void WriteLog(LPCTSTR lpszText);

// 递归生成目录
extern void CreateAllDirectories(CString strDir);

// 判断那个目录有空间
// lpszDirs - [in]  需要判断的目录,用英文逗号分割多个目录,例如"D:\123,D:\456,E:\123",必须使用绝对路径,不支持UNC路径
// ullSize  - [in]  需要的空间大小
// strDir   - [out] 满足条件的第一个目录
// 返回值   - 找到空间够用的目录返回true,否则返回false
// 说明     - 顺序查找lpszDirs字符串中的目录所在分区的空间,查找第一个满足条件的目录
extern bool HasDirEnoughSpace(LPCTSTR lpszDirs, ULONGLONG ullSize, CString &strDir);

// 用一个字符分割字符串
// sFields － [in] 需要分割的字符串
// sList － [in/out] 保存分割结果的链表
// strSplit － [in]分割符
extern void SplitFields(CString sFields,CStringList & sList, CString strSplit);
extern void SplitFields(CString sFields, CStringArray& sArray, CString strSplit);
