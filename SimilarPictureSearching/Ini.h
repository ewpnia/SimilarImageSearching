#pragma once
#include <vector>

#define DEF_SECTION L"PPINI"
#define MAX_BUF_LEN 255
#define SUFFIX_FEATURE L".feature" // feature�ļ��ĺ�׺��
#define SUFFIX_WORD L".word" //��Ƶ�ļ���׺��
#define DIR_FEATURE L"feature" //���feature�ļ���Ŀ¼
#define DIR_SIFT "siftDraw" //���sift����ͼ��Ŀ¼
#define DIR_RESULT L"result" //Ĭ�ϵĹ���Ŀ¼
#define FILE_NAME_IMG_LIST L"imgPath.list" //������˳�򱣴�ԭʼͼƬ�ļ����б���ļ�
#define FILE_NAME_INFO L"info.ini" //һЩ��ʱ��Ϣ

class CIni
{
public:
	CIni(void);
	~CIni(void);
	CString openDir; //������ͼƬ����Ŀ¼
	CString saveDir; //��������Ŀ¼
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

	CString getIniFileName(); //��ȡ�����ļ�ȫ·��
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