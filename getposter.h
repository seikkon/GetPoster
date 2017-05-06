// getposter.h : main header file for the GETPOSTER application
//

#if !defined(AFX_GETPOSTER_H__E92F2622_5C5E_41B4_867E_E08A065AB21B__INCLUDED_)
#define AFX_GETPOSTER_H__E92F2622_5C5E_41B4_867E_E08A065AB21B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetposterApp:
// See getposter.cpp for the implementation of this class
//

class CGetposterApp : public CWinApp
{
public:
	CGetposterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetposterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetposterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETPOSTER_H__E92F2622_5C5E_41B4_867E_E08A065AB21B__INCLUDED_)
