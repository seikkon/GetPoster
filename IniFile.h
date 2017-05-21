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
	DWORD GetSectionString(CString strSection,vector<CString>& vecSecData);

//	BOOL WriteString(CString strSection,int nKey, CString strAdd);
//	DWORD ReadString(CString strSection,int nKey, CString& strRead);
	BOOL WriteString(CString strSection, CString  strKey, CString& strAdd);
	DWORD ReadString(CString strSection, CString  strKey, CString& strRead);
	void MakeIniFile(CString strIniPathName);

	CIniFile();
	virtual ~CIniFile();

private:
	CString m_strIniPathName;
};

#endif // !defined(AFX_INIFILE_H__F94146B8_3484_49D1_B9C9_2B33FA19658D__INCLUDED_)
