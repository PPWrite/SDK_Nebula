#include "StdAfx.h"
#include "Functions.h"

PCHAR w2m (PWCHAR WideStr)
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


static std::wstring m2w( std::string str )
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	std::wstring return_value;
	return_value.append(buffer);
	delete [] buffer;
	return return_value;
}


CString GetAppPath(void)
{
    TCHAR exeFullPath[MAX_PATH]; 
    if(GetModuleFileName(NULL,exeFullPath,MAX_PATH) == 0)
		return _T("");
    CString sPath;
    sPath.Format(_T("%s"),exeFullPath);
    int iPath=sPath.ReverseFind('\\');
    return sPath.Left(iPath);
}

CCriticalSection g_csWriteLog;
void WriteLog(LPCTSTR lpszText)
{
	if(lpszText == NULL)// || strlen(lpszText) == 0)
		return;

	CSingleLock lock(&g_csWriteLog);
	lock.Lock();

	if(lpszText == NULL)
		return;

    TCHAR exeFullPath[MAX_PATH]; 
    if(GetModuleFileName(NULL,exeFullPath,MAX_PATH) == 0)
		return;

	CString strExePath;
	strExePath.Format(_T("%s"), exeFullPath);
	int nFind = strExePath.ReverseFind('.');
	CString strLogPath = strExePath.Left(nFind + 1) + _T("log");

	CFile file;
	try
	{
		
		CString strText;
		CTime time = CTime::GetCurrentTime();
		//strText.Format(_T("%04d-%02d-%02d %02d:%02d:%02d\r\n%s\r\n"),time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(),lpszText);
		strText.Format(_T("%s\r\n"),lpszText);

		CFileFind find;
		if(find.FindFile(strLogPath))
		{
			file.Open(strLogPath, CFile::modeWrite);
			if(file.GetLength() < 10*1024*1024)
				file.SeekToEnd();
			else
				file.SetLength(0);
		}
		else
		{
			file.Open(strLogPath, CFile::modeCreate | CFile::modeWrite);
		}
		find.Close();
		file.Write(w2m(strText.GetBuffer()), strText.GetLength());
		strText.ReleaseBuffer();
	}
	catch(...)
	{
	}
}

// 递归生成目录
void CreateAllDirectories(CString strDir)
{
	if (strDir.Right(1)==L"\\") 
		strDir=strDir.Left(strDir.GetLength()-1);
	
	if (GetFileAttributes(strDir)!=-1)
		return;

	int nFound=strDir.ReverseFind(L'\\');
	CreateAllDirectories(strDir.Left(nFound));
	
	CreateDirectory(strDir,NULL);
}

// 判断那个目录有空间
bool HasDirEnoughSpace(LPCTSTR lpszDirs, ULONGLONG ullSize, CString &strDir)
{
	strDir = _T("");
	CString strDirs = lpszDirs;
	CString strTestDir = _T("");
	CString strDisk = _T("");
	int nFind = -1;
	ULARGE_INTEGER available;
	available.QuadPart = 0;
	do
	{
		// 提取一个测试目录
		nFind = strDirs.Find(',');
		if(nFind > -1)
		{
			strTestDir = strDirs.Left(nFind);
			strDirs = strDirs.Right(strDirs.GetLength() - nFind - 1);
		}
		else
			strTestDir = strDirs;

		// 提取目录所在的分区
		if(strTestDir.GetLength() >= 2 && strTestDir.Mid(1,1) == L":")
			strDisk = strTestDir.Left(2);
		else
			strDisk = _T("");

		// 读取分区的剩余空间
		if(!GetDiskFreeSpaceEx(strDisk,	&available, NULL, NULL))
			available.QuadPart = 0;

		// 判断空间是否够用
		if(available.QuadPart >= ullSize)
		{
			strDir = strTestDir;
			break;
		}
	}while(nFind > -1);

	// 返回判断结果
	if(strDir.GetLength() == 0)
		return false;
	else
		return true;
}

// 用一个字符分割字符串
void SplitFields(CString sFields,CStringList & sList, CString strSplit)
{	
	int j=0;
	CString str;
	for(int k=0 ;k<sFields.GetLength();k++)
	{
		CString s=sFields.Mid(k,1);
		if(s!=strSplit)
			str+=sFields.Mid(k,1);
		else
		{
			CString sNew=str;
			str.Empty();
			sList.AddTail(sNew);
		}
	}
	CString sNew=str;
	str.Empty();
	sList.AddTail(sNew);
}

void SplitFields(CString sFields, CStringArray& sArray, CString strSplit)
{
	sArray.RemoveAll();
	int pos = 0;
	int pre_pos = 0;
	while( -1 != pos )
	{
		pre_pos = pos;
		pos = sFields.Find(strSplit, pos+1);
		CString str;
		if(pos > 0)
			str = sFields.Mid(pre_pos,(pos-pre_pos));
		else
			str = sFields.Mid(pre_pos,(sFields.GetLength()-pre_pos));
		str.Replace(strSplit,NULL);
		sArray.Add(str);
	}
}