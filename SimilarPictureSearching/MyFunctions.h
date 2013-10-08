/***************************************************/
/*****************一些常用函数**********************/
/***************************************************/

//在Unicode下把CString对象转换成char * 对象
extern char* CStringToCharArray(CString str);

//计算某一目录下某一种后缀名的文件数量
//dirName是目录，filter为通配符
extern int FileCount(const CString &dirName,const CString &filter);