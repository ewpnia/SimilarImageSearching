================================================================================
MICROSOFT �������: SimilarPictureSearching ��Ŀ����
===============================================================================

Ӧ�ó�������Ϊ����������� SimilarPictureSearching Ӧ�ó��򡣴�Ӧ�ó��򲻽���ʾ Microsoft ������Ļ���ʹ�÷�����������Ϊ����дӦ�ó������㡣

���ļ���Ҫ������� SimilarPictureSearching Ӧ�ó����ÿ���ļ������ݡ�

SimilarPictureSearching.vcxproj
����ʹ��Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
���������ɸ��ļ��� Visual C++ �İ汾��Ϣ���Լ��й�ʹ��Ӧ�ó�����ѡ���ƽ̨�����ú���Ŀ���ܵ���Ϣ��

SimilarPictureSearching.vcxproj.filters
    ����ʹ�á�Ӧ�ó����򵼡����ɵ� VC++ ��Ŀɸѡ���ļ���
    �������й���Ŀ�ļ���ɸѡ��֮��Ĺ�����Ϣ���� IDE �У�ͨ�����ֹ��������ض��ڵ����Է�����ʽ��ʾ����������չ�����ļ������磬��.cpp���ļ��롰Դ�ļ���ɸѡ��������

SimilarPictureSearching.h
����Ӧ�ó������Ҫͷ�ļ���������������Ŀ�ض���ͷ�ļ�(���� Resource.h)�������� CSimilarPictureSearchingApp Ӧ�ó����ࡣ

SimilarPictureSearching.cpp
���ǰ���Ӧ�ó����� CSimilarPictureSearchingApp ����ҪӦ�ó���Դ�ļ���

SimilarPictureSearching.rc
���ǳ���ʹ�õ����� Microsoft Windows ��Դ���б������� RES ��Ŀ¼�д洢��ͼ�ꡢλͼ�͹�ꡣ���ļ�����ֱ���� Microsoft Visual C++ �н��б༭����Ŀ��Դλ�� 2052 �С�

res\SimilarPictureSearching.ico
��������Ӧ�ó���ͼ���ͼ���ļ�����ͼ���������Ҫ��Դ�ļ� SimilarPictureSearching.rc �С�

res\SimilarPictureSearching.rc2
���ļ��������� Microsoft Visual C++ �н��б༭����Դ����Ӧ�ý���������Դ�༭���༭��������Դ���ڴ��ļ��С�

/////////////////////////////////////////////////////////////////////////////

��������ܴ���:
��Ŀ������׼ MFC ���档

MainFrm.h, MainFrm.cpp
��Щ�ļ���������� CMainFrame������������
CMDIFrameWnd ���������� MDI ��ܹ��ܡ�

/////////////////////////////////////////////////////////////////////////////

�����ӿ�ܴ���:

ChildFrm.h��ChildFrm.cpp
��Щ�ļ����岢ʵ�� CChildFrame �࣬����֧�� MDI Ӧ�ó����е��Ӵ��ڡ�

/////////////////////////////////////////////////////////////////////////////

Ӧ�ó����򵼴���һ���ĵ����ͺ�һ����ͼ:

SimilarPictureSearchingDoc.h��SimilarPictureSearchingDoc.cpp - �ĵ�
��Щ�ļ����� CSimilarPictureSearchingDoc �ࡣ�༭��Щ�ļ�������������ĵ����ݲ���ʵ���ļ�����ͼ���(ͨ�� CSimilarPictureSearchingDoc::Serialize)��

SimilarPictureSearchingView.h��SimilarPictureSearchingView.cpp - �ĵ�����ͼ
��Щ�ļ����� CSimilarPictureSearchingView �ࡣ
CSimilarPictureSearchingView �������ڲ鿴 CSimilarPictureSearchingDoc ����

res\SimilarPictureSearchingDoc.ico
����ͼ���ļ��������� CSimilarPictureSearchingDoc ��� MDI �Ӵ��ڵ�ͼ�ꡣ��ͼ���������Ҫ��Դ�ļ� SimilarPictureSearching.rc �С�




/////////////////////////////////////////////////////////////////////////////

��������:

ActiveX �ؼ�
Ӧ�ó��������ʹ�� ActiveX �ؼ���֧�֡�

��ӡ����ӡԤ��֧��
Ӧ�ó�������ͨ���� MFC ����� CView ���еĳ�Ա���������������ڴ����ӡ����ӡ���úʹ�ӡԤ������Ĵ��롣

/////////////////////////////////////////////////////////////////////////////

������׼�ļ�:

StdAfx.h��StdAfx.cpp
��Щ�ļ�����������Ϊ SimilarPictureSearching.pch ��Ԥ����ͷ (PCH) �ļ�����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
���Ǳ�׼ͷ�ļ����������µ���Դ ID��
Microsoft Visual C++ ��ȡ�����´��ļ���

SimilarPictureSearching.manifest
	Ӧ�ó����嵥�ļ��� Windows XP ��������Ӧ�ó���
	���ض��汾���г��򼯵������ԡ����س���ʹ�ô�
	��Ϣ�ӳ��򼯻�������ʵ��ĳ��򼯻�
	��Ӧ�ó������˽����Ϣ��Ӧ�ó����嵥����Ϊ�����·ַ�����Ϊ
	��Ӧ�ó����ִ���ļ���װ����ͬ�ļ����е��ⲿ .manifest �ļ�������
	Ҳ��������Դ����ʽ�����ڸÿ�ִ���ļ��С� 
/////////////////////////////////////////////////////////////////////////////

����ע��:

Ӧ�ó�����ʹ�á�TODO:��ָʾӦ��ӻ��Զ����Դ���벿�֡�

���Ӧ�ó����ڹ���� DLL ��ʹ�� MFC������Ҫ���·�����Щ MFC DLL�����Ӧ�ó������õ����������ϵͳ�ĵ�ǰ�������ò�ͬ������Ҫ���·�����Ӧ�ı��ػ���Դ MFC100XXX.DLL���й�����������ĸ�����Ϣ����μ� MSDN �ĵ����й� Redistributing Visual C++ applications (���·��� Visual C++ Ӧ�ó���)���½ڡ�

/////////////////////////////////////////////////////////////////////////////
