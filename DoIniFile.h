// DoIniFile.h: interface for the DoIniFile class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_DOINIFILE_H__14A631BC_9E4C_4BB2_AED0_12112D82E1E2__INCLUDED_)
#define AFX_DOINIFILE_H__14A631BC_9E4C_4BB2_AED0_12112D82E1E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DoIniFile  
{
public:
	DWORD ReadString(CString const& strSection, CString const& strKey, CString const& strRead, CString const& strIniFileName);
	BOOL WriteString(CString const& strSection, CString const& strKey, CString const& strAdd, CString const& strIniFileName);
	void MakeIniFile(CString const& strIniPathName);
	DoIniFile();
	virtual ~DoIniFile();

private:
	CString m_strIniFileName;
};

#endif // !defined(AFX_DOINIFILE_H__14A631BC_9E4C_4BB2_AED0_12112D82E1E2__INCLUDED_)
