// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__479D2B4F_E4B8_437B_B4AC_82AFF0209D50__INCLUDED_)
#define AFX_STDAFX_H__479D2B4F_E4B8_437B_B4AC_82AFF0209D50__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define __VC6_ATL_IMAGE_H__ 1  


#define SECTIONA _T("ControlID")
#define SECTIONB _T("Value")
#define SECTIONC _T("Content")
#define INIFILE _T("setinfo.ini")
#define PLAYMARK _T("playmark_50.png")
#define FFMPEG _T("ffmpeg.exe")

#define THUMBNAILWIDTH         1024
#define VIDEOPREFIX            1017
#define AUDIOPREFIX            1018
#define IMAGEPREFIX            1019
#define FFMEPGPATH             1011
#define THUMBNAILDIR           1012
#define POSTERDIR              1013

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlimage.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__479D2B4F_E4B8_437B_B4AC_82AFF0209D50__INCLUDED_)
