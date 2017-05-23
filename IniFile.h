// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////
#include <VECTOR>
using namespace std;

#if !defined(AFX_INIFILE_H__F94146B8_3484_49D1_B9C9_2B33FA19658D__INCLUDED_)
#define AFX_INIFILE_H__F94146B8_3484_49D1_B9C9_2B33FA19658D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
	BOOL GetSectionName(vector<CString>& vecSecName,CString const& strIniFileName);
	DWORD GetSectionString(CString const& strSection,vector<CString>& vecSecData,CString const& strIniFileName);

//	BOOL WriteString(CString strSection,int nKey, CString strAdd);
//	DWORD ReadString(CString strSection,int nKey, CString& strRead);
	BOOL WriteString(CString const& strSection, CString const& strKey, CString& strAdd,CString const& strIniFileName);
	DWORD ReadString(CString const& strSection, CString const& strKey, CString& strRead,CString const& strIniFileName);
	void MakeIniFile(CString const& strIniFileName);
	CString GetIniPathName(CString const& strIniFileName);

	CIniFile();
	virtual ~CIniFile();

private:
	CString m_strIniPathName;
};

#endif // !defined(AFX_INIFILE_H__F94146B8_3484_49D1_B9C9_2B33FA19658D__INCLUDED_)
