#include "stdafx.h"
#include "MyFunctions.h"

extern char* CStringToCharArray(CString str)                
{
	char *ptr;
#ifdef _UNICODE
	LONG len;
	len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	ptr = new char [len+1];
	memset(ptr,0,len + 1);
	WideCharToMultiByte(CP_ACP, 0, str, -1, ptr, len + 1, NULL, NULL);
#else
	ptr = new char [str.GetAllocLength()+1];
	sprintf(ptr,_T("%s"),str);
#endif
	return ptr;
}




//计算某一目录下某一种后缀名的文件数量
//dirName是目录，filter为通配符

int FileCount(const CString &dirName,const CString &filter)
	//int FileCount(const CString &dirName)  
{
	int fileCount = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	DWORD dwError;
	CString wildcardPath = dirName + _T("\\*")+filter;
	//CString wildcardPath = dirName + _T("\\*.*");
	BOOL bMoreFiles=TRUE;
	hFind = FindFirstFile(wildcardPath,&FindFileData);

	while (hFind != INVALID_HANDLE_VALUE && bMoreFiles)
	{
		++fileCount;
		bMoreFiles = FindNextFile(hFind,&FindFileData);
	}

	dwError = GetLastError();
	FindClose(hFind);
	return fileCount;
}