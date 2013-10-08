#pragma once
#include <vector>

#define DEF_SECTION L"PPINI"
#define MAX_BUF_LEN 255
#define SUFFIX_FEATURE L".feature" // feature文件的后缀名
#define SUFFIX_WORD L".word" //词频文件后缀名
#define DIR_FEATURE L"feature" //存放feature文件的目录
#define DIR_SIFT "siftDraw" //存放sift特征图的目录
#define DIR_RESULT L"result" //默认的工作目录
#define FILE_NAME_IMG_LIST L"imgPath.list" //按查找顺序保存原始图片文件名列表的文件
#define FILE_NAME_INFO L"info.ini" //一些临时信息

class CIni
{
public:
	CIni(void);
	~CIni(void);
	CString openDir; //待处理图片所在目录
	CString saveDir; //结果保存根目录
	CString sourcePicture;
	bool drawFeatures;

private:
	CString fileName;
	BOOL writeString(LPCTSTR key, LPCTSTR val, LPCTSTR section = (LPCTSTR)DEF_SECTION);
	CString getString(LPCTSTR key, LPCTSTR section = (LPCTSTR)DEF_SECTION);

public:

	int SAselected;
	std::vector<CString> MatchPictureList;
	int PastTime;
	int IsPopUp;
	int SIFTEditNum;
	int NoMatch;
	int ImageSum;

	CString getIniFileName(); //获取配置文件全路径
	CString getSiftDirPath(void);
	CString getFeatureDirPath(void);
	CString getImgListFilePath(void);
	CString getInfoFilePath(void);
	CString getsourcePictureFeaturePath(void);
	CString getsourcePicturefilePath(void);
	CString convertToFeatureSuffix(CString fileName);
	static CString removeSuffix(CString fileName);
	static CString getFileNameFromPath(CString fullFileName);
	
};