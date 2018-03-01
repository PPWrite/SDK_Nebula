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
// ��ȡӦ�ó���·��
extern CString GetAppPath(void);
extern CString GetDataFloder();

// д��־
// lpszText �� [in] ��־����
extern void WriteLog(LPCTSTR lpszText);

// �ݹ�����Ŀ¼
extern void CreateAllDirectories(CString strDir);

// �ж��Ǹ�Ŀ¼�пռ�
// lpszDirs - [in]  ��Ҫ�жϵ�Ŀ¼,��Ӣ�Ķ��ŷָ���Ŀ¼,����"D:\123,D:\456,E:\123",����ʹ�þ���·��,��֧��UNC·��
// ullSize  - [in]  ��Ҫ�Ŀռ��С
// strDir   - [out] ���������ĵ�һ��Ŀ¼
// ����ֵ   - �ҵ��ռ乻�õ�Ŀ¼����true,���򷵻�false
// ˵��     - ˳�����lpszDirs�ַ����е�Ŀ¼���ڷ����Ŀռ�,���ҵ�һ������������Ŀ¼
extern bool HasDirEnoughSpace(LPCTSTR lpszDirs, ULONGLONG ullSize, CString &strDir);

// ��һ���ַ��ָ��ַ���
// sFields �� [in] ��Ҫ�ָ���ַ���
// sList �� [in/out] ����ָ���������
// strSplit �� [in]�ָ��
extern void SplitFields(CString sFields,CStringList & sList, CString strSplit);
extern void SplitFields(CString sFields, CStringArray& sArray, CString strSplit);

extern PCHAR w2m (PWCHAR WideStr);
extern std::wstring m2w( std::string str );
