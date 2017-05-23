// ENVData.h: interface for the CENVData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETUPENV_H__98964C04_52EB_46C5_AE2B_76E0C5B5705D__INCLUDED_)
#define AFX_SETUPENV_H__98964C04_52EB_46C5_AE2B_76E0C5B5705D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <VECTOR>
using namespace std;

struct ENV{

	CString strSection;
	WORD nCtrlID;
	CString strValue;
 	CString strContent;
};

class CENVData  
{
public:
//	void UpdateENV();
//	BOOL SaveToFile();
//	BOOL LoadFile(CString const& strFile, vector<ENV> &vecENV);
//	BOOL SaveToData(CString strFile, vector<ENV> &vecENV);

//	void CreatInitFile(CString strInitPath);
 	BOOL DoInitENV(CString strFileName,vector<ENV>& vecENV);
	CString GetENVVal(WORD ENVCtrlID);
	BOOL SetENVVal(WORD ENVCtrlID,CString strValue);
//	BOOL GetAllENV(vector<ENV> &vecENV);
//	BOOL SetAllENV(vector<ENV> &vecENV);

	CENVData();
	virtual ~CENVData();

private:
	vector<ENV> m_vecENV;
};

#endif // !defined(AFX_ENVData_H__98964C04_52EB_46C5_AE2B_76E0C5B5705D__INCLUDED_)
