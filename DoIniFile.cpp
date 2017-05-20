// DoIniFile.cpp: implementation of the DoIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "getposter.h"
#include "DoIniFile.h"
//#include <VECTOR>
#include <fstream>
//using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoIniFile::CDoIniFile()
{
	CString strIniPathName;
	//		TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	//	(strrchr(strIniPathName.GetBuffer(MAX_PATH),'\\'))[1] = 0;   
	//strIniPathName=strIniPathName.Left(strIniPathName.ReverseFind('\\'));
	int pos =strIniPathName.ReverseFind('\\');
	CString str=strIniPathName.Right(10);
	//strcat(szPath,strIniFileName.GetBuffer(MAX_PATH));
	//strIniPathName=szPath;
	strIniPathName += "test";
	CFileFind cFile;
	if(!cFile.FindFile(strIniPathName))
		MakeIniFile(strIniPathName);
}

CDoIniFile::~CDoIniFile()
{

}

void CDoIniFile::MakeIniFile(CString strIniPathName)
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

BOOL CDoIniFile::WriteString(CString strSection, CString strKey, CString strAdd, CString strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;

    return ::WritePrivateProfileString(strSection.GetBuffer(strSection.GetLength()),strKey.GetBuffer(strKey.GetLength()),strAdd.GetBuffer(strAdd.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength())); 
}


DWORD CDoIniFile::ReadString(CString strSection,CString strKey,CString& strRead,CString strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;
	
    return ::GetPrivateProfileString(strSection.GetBuffer(strSection.GetLength()), strKey.GetBuffer(strKey.GetLength()),NULL,strRead.GetBuffer(MAX_PATH),MAX_PATH,strIniPathName.GetBuffer(strIniPathName.GetLength()));  
}

BOOL CDoIniFile::WriteString(CString strSection,int nKey, CString strAdd, CString strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;
	CString strKey;
	strKey.Format("%d",nKey);
    return ::WritePrivateProfileString(strSection.GetBuffer(strSection.GetLength()),strKey.GetBuffer(strKey.GetLength()),strAdd.GetBuffer(strAdd.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength())); 
}

DWORD CDoIniFile::ReadString(CString strSection,int nKey,CString& strRead,CString strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;
	CString strKey,strBuff;
	strKey.Format("%d",nKey);
	DWORD nRet= ::GetPrivateProfileString(strSection.GetBuffer(strSection.GetLength()), strKey.GetBuffer(strKey.GetLength()),NULL,strBuff.GetBuffer(MAX_PATH),MAX_PATH,strIniPathName.GetBuffer(strIniPathName.GetLength()));  
	strRead=strBuff;

    return nRet;
}

DWORD CDoIniFile::GetSectionString(CString strSection, vector<CString>& vecSecData, CString strIniFileName)
{
	CString strIniPathName;
	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
	strIniPathName=strIniPathName +strIniFileName;
	const int BUFFSIZE=2048;
	CHAR szBuff[BUFFSIZE];
	DWORD nRet= ::GetPrivateProfileSection(strSection.GetBuffer(strSection.GetLength()),szBuff,BUFFSIZE,strIniPathName.GetBuffer(strIniPathName.GetLength()));  
	CHAR *pBuff=szBuff;
	size_t size=strlen(pBuff);
	int i=0; //i记录总数据行数
	while(size) //当取到的行长度不为0时，说明此行存在，继续取值
	{
		CString str=pBuff;
		vecSecData.push_back(str);
		pBuff+=size+1;
		size=strlen(pBuff);
		i++;
	} 
	
    return nRet;
}
