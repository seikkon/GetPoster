// DoIniFile.h: interface for the DoIniFile class.
//
//////////////////////////////////////////////////////////////////////
#include <VECTOR>
using namespace std;

#if !defined(AFX_DOINIFILE_H__14A631BC_9E4C_4BB2_AED0_12112D82E1E2__INCLUDED_)
#define AFX_DOINIFILE_H__14A631BC_9E4C_4BB2_AED0_12112D82E1E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDoIniFile  
{
public:
	DWORD GetSectionString(CString strSection,vector<CString>& vecSecData,CString strIniFileName);
	BOOL WriteString(CString strSection,int nKey, CString strAdd, CString strIniFileName);
	DWORD ReadString(CString strSection,int nKey, CString& strRead,CString strIniFileName);
	BOOL WriteString(CString strSection, CString  strKey, CString strAdd, CString  strIniFileName);
	DWORD ReadString(CString strSection, CString  strKey, CString& strRead, CString strIniFileName);
	void MakeIniFile(CString strIniPathName);
	CDoIniFile();
	virtual ~CDoIniFile();

private:
	CString m_strIniFileName;
};

#endif // !defined(AFX_DOINIFILE_H__14A631BC_9E4C_4BB2_AED0_12112D82E1E2__INCLUDED_)
