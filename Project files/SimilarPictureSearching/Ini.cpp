#include "StdAfx.h"
#include "Ini.h"


CIni::CIni(void) :
fileName("PPini.txt")
	, openDir(_T(""))
	, saveDir(_T(""))

{
	CFileFind finder;
	if(!finder.FindFile(fileName))
	{
		CFile file;
		file.Open(fileName, CFile::modeCreate);
		fileName = file.GetFilePath();
		file.Close();
	}
	else
	{
		finder.FindNextFile();
		fileName = finder.GetFilePath();
		openDir = getString(L"openDir");
		saveDir = getString(L"saveDir");
	}
}


CIni::~CIni(void)
{
	writeString(L"openDir", openDir);
	writeString(L"saveDir", saveDir);
}

CString CIni::getIniFileName()
{
	return fileName;
}

BOOL CIni::writeString(LPCTSTR key, LPCTSTR val, LPCTSTR section)
{
	return WritePrivateProfileString(section, key, val, fileName);
}

CString CIni::getString(LPCTSTR key, LPCTSTR section)
{
	WCHAR temp[MAX_BUF_LEN];
	DWORD k = GetPrivateProfileString(section, key, NULL, temp, MAX_BUF_LEN, fileName);
	return CString(temp);
}


CString CIni::getSiftDirPath(void)
{
	return saveDir + _T("\\") + DIR_SIFT;
}


CString CIni::getFeatureDirPath(void)
{
	return saveDir + _T("\\") + DIR_FEATURE;
}

CString CIni::getImgListFilePath(void)
{
	return saveDir + _T("\\") + FILE_NAME_IMG_LIST;
}

CString CIni::getInfoFilePath(void)
{
	return saveDir + _T("\\") + FILE_NAME_INFO;
}

CString CIni::getsourcePictureFeaturePath(void)
{
	char* temp = (LPSTR)(LPCTSTR)sourcePicture.GetBuffer();
	CString name = (LPCTSTR)strrchr(temp, 92);
	return saveDir + L"\\target" ;
}

CString CIni::getsourcePicturefilePath(void)
{
	CString temp = sourcePicture;
	int dotpos = temp.ReverseFind(L'.');
	temp.Delete(dotpos, temp.GetLength() - dotpos);
	int slashpos = temp.ReverseFind(L'\\');
	temp.Delete(0, slashpos);
	temp.Append(SUFFIX_FEATURE);
	return saveDir + "\\target" + temp ;
}



CString CIni::convertToFeatureSuffix(CString fileName)
{
	CString featureFileName = fileName;
	int dotpos = featureFileName.ReverseFind('.');
	featureFileName.Delete(dotpos, featureFileName.GetLength() - dotpos);
	featureFileName.Append(SUFFIX_FEATURE);
	return featureFileName;
}


CString CIni::removeSuffix(CString fileName)
{
	int pos = fileName.ReverseFind('.');
	CString newFileName(fileName);
	newFileName.Delete(pos, fileName.GetLength() - pos);
	return newFileName;
}


CString CIni::getFileNameFromPath(CString fullFileName)
{
	int pos = fullFileName.ReverseFind('\\');
	CString newFileName(fullFileName);
	newFileName.Delete(0, pos + 1);
	return newFileName;
}
