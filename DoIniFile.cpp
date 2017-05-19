// DoIniFile.cpp: implementation of the DoIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "getposter.h"
#include "DoIniFile.h"
#include <fstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DoIniFile::DoIniFile()
{
	CString strIniPathName;
	//		TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	//	(strrchr(strIniPathName.GetBuffer(MAX_PATH),'\\'))[1] = 0;   
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	//strcat(szPath,strIniFileName.GetBuffer(MAX_PATH));
	//strIniPathName=szPath;
	strIniPathName=strIniPathName +INIFILE;
	
	CFileFind cFile;
	if(!cFile.FindFile(strIniPathName))
		MakeIniFile(strIniPathName);
}

DoIniFile::~DoIniFile()
{

}

void DoIniFile::MakeIniFile(CString const& strIniPathName)
{
//	CString strIniPathName;
	//		TCHAR szPath[MAX_PATH];
//	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
 	//(strrchr(strIniPathName.GetBuffer(MAX_PATH),'\\'))[1] = 0;   
//	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	//strcat(szPath,strIniFileName.GetBuffer(MAX_PATH));
	//strIniPathName=szPath;
//	strIniPathName=strIniPathName +strIniFileName;
	
	CFileFind cFile;
	if(cFile.FindFile(strIniPathName))
		if(AfxMessageBox("初始化档案存在！是否覆盖？",MB_OK|MB_OKCANCEL)==IDCANCEL)
			return;
		
		ofstream _outFile(strIniPathName,ios::out);
		_outFile.close();
		
		CString strData;
		CString arrayData[7]={"1024=200","1018=audio","1011=C:\\ffmpeg.exe","1019=image","1013=Poster","1012=Thumbnail","1017=video"};
		for(int i=0;i<7;i++)
		{
			strData+=arrayData[i];
			strData+='\0';
		}
		::WritePrivateProfileSection(_T("Output"),strData.GetBuffer(strData.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength()));
}

BOOL DoIniFile::WriteString(CString const& strSection, CString const& strKey, CString const& strAdd, CString const& strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;

    return ::WritePrivateProfileString(strSection.GetBuffer(strSection.GetLength()),strKey.GetBuffer(strKey.GetLength()),strAdd.GetBuffer(strAdd.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength())); 
}

DWORD DoIniFile::ReadString(const CString &strSection, const CString &strKey, const CString &strRead, const CString &strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;
	
    return ::GetPrivateProfileString(strSection.GetBuffer(strSection.GetLength()), strKey.GetBuffer(strKey.GetLength()),NULL,strRead.GetBuffer(MAX_PATH),MAX_PATH,strIniPathName.GetBuffer(strIniPathName.GetLength()));  
}
