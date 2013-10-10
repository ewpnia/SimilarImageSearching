// SiftDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SimilarPictureSearching.h"
#include "SiftDialog.h"
#include "afxdialogex.h"

#include <highgui.h>
#include "..\sift\sift.h"
#include "..\sift\imgfeatures.h"
#include "..\sift\utils.h"

#include "KDTmatch.h"
#include "MyFunctions.h"
#include <time.h>





// SiftDialog 对话框

IMPLEMENT_DYNAMIC(SiftDialog, CDialogEx)

SiftDialog::SiftDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(SiftDialog::IDD, pParent)
{

}

SiftDialog::~SiftDialog()
{
}


void SiftDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OnEnChangePathSave, m_pathSave);
	DDX_Text(pDX, IDC_OnEnChangePathSource, m_pathSource);
	DDX_Control(pDX, IDC_SIFTPROGRESS, m_pro);
}


BEGIN_MESSAGE_MAP(SiftDialog, CDialogEx)
	ON_EN_CHANGE(IDC_OnEnChangePathSource, &SiftDialog::OnEnChangeOnenchangepathtarget)
	ON_EN_CHANGE(IDC_OnEnChangePathSave, &SiftDialog::OnEnChangeOnenchangepathsave)
	ON_BN_CLICKED(IDOK, &SiftDialog::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL SiftDialog::OnInitDialog(void)
{
	CDialogEx::OnInitDialog();
	m_pro.SetRange(0,10000);
	m_progessMax = 10000;

	return 0;
}



// SiftDialog 消息处理程序


void SiftDialog::OnEnChangeOnenchangepathtarget()
{
	ini.sourcePicture = m_pathSource;
}


void SiftDialog::OnEnChangeOnenchangepathsave()
{
	ini.saveDir = m_pathSave;
}


void SiftDialog::OnBnClickedOk()
{
	//用clock()来计时  毫秒  
	clock_t  clockBegin, clockEnd;  
	clockBegin = clock();  

	CFileFind finder;
	CString &openDir = ini.openDir;
	CString &saveDir = ini.saveDir;
	CString &sourcePicture = ini.sourcePicture;
	CString siftDrawDir;
	CString featureDir;
	CString sourceFeature;
	CString fileName;

	UpdateData();
	openDir = m_pathOpen;
	saveDir = m_pathSave;
	sourcePicture = m_pathSource;
	siftDrawDir = ini.getSiftDirPath();
	featureDir = ini.getFeatureDirPath();
	BOOL haveNext = finder.FindFile(openDir + "\\*.*");
	sourceFeature = ini.getsourcePictureFeaturePath();

	//检查文件夹路径
	if(haveNext)
	{
		if ( openDir == saveDir )
		{
			MessageBox(L"请不要把结果保存目录放在目标图像文件夹下！");
			return;
		}
		if(PathIsDirectory(sourcePicture))
		{
			MessageBox(L"目标图片路径不正确！");
			return;
		}
		if(!PathIsDirectory(sourceFeature) && !CreateDirectory(sourceFeature, NULL))
		{
			MessageBox(L"目标图片特征保存目录创建失败！");
			return; 
		}
		if(!PathIsDirectory(openDir))
		{
			MessageBox(L"相似图片目录路径不正确！");
			return;
		}
		if(!PathIsDirectory(saveDir) && !CreateDirectory(saveDir, NULL))
		{
			MessageBox(L"结果保存文件夹创建失败！");
			return;
		}
		if (ini.drawFeatures == TRUE)
		{
			if(!PathIsDirectory(siftDrawDir) && !CreateDirectory(siftDrawDir, NULL))
			{
				MessageBox(L"图片特征绘制文件夹创建失败！");
				return; 
			}
		}
		
		if(!PathIsDirectory(featureDir) && !CreateDirectory(featureDir, NULL))
		{
			MessageBox(L"特征文件夹创建失败！");
			return; 
		}

	}
	else
	{
		MessageBox(L"相似图片目录下没有发现图片文件！");
	}
	
	m_pro.ShowWindow(SW_SHOW);
	m_progessStep = m_progessMax / ( FileCount( openDir, L".jpg" ) );
	m_pro.SetStep(m_progessStep);
	/**************************************************************************************************************/
	/*对源图片的Sift特征进行提取*/
	/**************************************************************************************************************/
	
	CStdioFile sourcePicturefile;
	CString sourcePicturefilePathName = ini.getsourcePicturefilePath();

	sourcePicturefile.Open(sourcePicturefilePathName, CStdioFile::modeCreate | CStdioFile::modeWrite);
	IplImage* Sourceimg;
	struct feature* Sourcefeatures;
	int sourceN = 0;
	
	/*
	const wchar_t* wstr = ( LPCTSTR )sourcePicture;     //unicode，否则错
	char str[ 100 ] = { 0 };
	wcstombs( str, wstr, wcslen( wstr ) );
	*/
	//img = cvLoadImage( str, 1);
	
	Sourceimg = cvLoadImage( CStringToCharArray(sourcePicture), 1);
	if(!Sourceimg)
	{
		return;
	}
	//sourceN = _sift_features(Sourceimg, &Sourcefeatures, SIFT_INTVLS/*3*/, SIFT_SIGMA/*1.6*/, SIFT_CONTR_THR/*0.04*/,
	//	SIFT_CURV_THR/*10*/, SIFT_IMG_DBL/*1*/, SIFT_DESCR_WIDTH/*4*/, SIFT_DESCR_HIST_BINS/*8*/); //SIFTfeature提取
	sourceN = sift_features(Sourceimg, &Sourcefeatures);

	//char* tempName = (LPSTR)sourcePicturefilePathName.GetBuffer();
	char* tempName = CStringToCharArray(sourcePicturefilePathName);
	sourcePicturefile.Close();
	export_features(tempName, Sourcefeatures, sourceN); //将features导出为文件
	m_pro.StepIt();


	/*************************************************************************************************************/
	/*对相似图片目录中的图片进行特征提取*/
	/*************************************************************************************************************/
	
	CStdioFile file;
	file.Open(ini.getImgListFilePath(), CStdioFile::modeCreate | CStdioFile::modeWrite);
	int featureSum = 0;
	IplImage* Targetimg;
	//struct feature* Targetfeatures;

	while(haveNext) 
	{ 
		haveNext = finder.FindNextFile(); 
		if(finder.IsDirectory()) 
			continue;

		fileName = finder.GetFileName();
		file.WriteString(fileName + "\n");

		CString tempOpenDir = openDir;
		CString tempSiftDrawDir = siftDrawDir;
		CString tempFeatureDir = featureDir;
		
		//相关文件的路径
		tempOpenDir.Append(L"\\");
		tempOpenDir.Append(fileName);
		//char * img_file_name =(LPSTR)tempOpenDir.GetBuffer();
		char * img_file_name = CStringToCharArray(tempOpenDir);

		tempSiftDrawDir.Append(L"\\");
		tempSiftDrawDir.Append(fileName);
		//char * out_img_name =tempSiftDrawDir.GetBuffer();
		char * out_img_name = CStringToCharArray(tempSiftDrawDir);

		tempFeatureDir.Append(L"\\");
		tempFeatureDir.Append(ini.convertToFeatureSuffix(fileName));
		//char * out_file_name =(LPSTR)tempFeatureDir.GetBuffer();
		char * out_file_name = CStringToCharArray(tempFeatureDir);

		struct feature* Targetfeatures;
		int targetN = 0;

		//CString info("Sift ");
		//info.Append(fileName);
		Targetimg = cvLoadImage(img_file_name, 1);

		if(!Targetimg)
		{
			return;
		}
		//targetN = _sift_features(Targetimg, &Targetfeatures, SIFT_INTVLS/*3*/, SIFT_SIGMA/*1.6*/, SIFT_CONTR_THR/*0.04*/,
		//	SIFT_CURV_THR/*10*/, SIFT_IMG_DBL/*1*/, SIFT_DESCR_WIDTH/*4*/, SIFT_DESCR_HIST_BINS/*8*/); //SIFTfeature提取
		targetN = sift_features(Targetimg, &Targetfeatures);
		
		featureSum += targetN;
		if( out_file_name != NULL )
			export_features(out_file_name, Targetfeatures, targetN); //将features导出为文件

		if( (ini.drawFeatures == TRUE) && (out_img_name != NULL) )
		{
			draw_features(Targetimg, Targetfeatures, targetN); //在img图片上标记出features
			cvSaveImage(out_img_name, Targetimg, NULL); //将标记后的图片保存
		}

		int IsMatch;
		if (ini.SAselected == TRUE)
		{
			IsMatch = KDTmatch( Sourceimg, Targetimg, sourceN, targetN, Sourcefeatures, Targetfeatures, ini.IsPopUp, ini.SIFTEditNum );
		}

		if (IsMatch)
		{
			ini.MatchPictureList.push_back(tempOpenDir);
			//MessageBox(tempOpenDir);
		}
		else
		{
			ini.NoMatch = 1;
		}

		m_pro.StepIt();
		img_file_name = NULL;
		out_img_name = NULL;
		out_file_name = NULL;
	}
	file.Close();

	CString temp;
	temp.Format(L"%d", featureSum);
	file.Open(ini.getInfoFilePath(), CStdioFile::modeCreate | CStdioFile::modeWrite);
	file.Close();
	WritePrivateProfileString(L"temp", L"featureSum", temp, ini.getInfoFilePath());

	ini.ImageSum = ( FileCount( openDir, L".jpg" ) );

	clockEnd = clock(); 
	int intms = clockEnd - clockBegin;
	ini.PastTime = intms;
	//CString ms;
	//ms.Format(_T("%d"), intms);
	//MessageBox(ms);

	cvReleaseImage( &Sourceimg );
	free( Sourcefeatures );
	tempName = NULL;
	
	//EndDialog(IDCANCEL);
	CDialogEx::OnOK();
	MessageBox(L"SIFT相似图像匹配已完成！");
}