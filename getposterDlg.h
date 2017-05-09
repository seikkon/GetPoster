// getposterDlg.h : header file
//


#if !defined(AFX_GETPOSTERDLG_H__47443455_53D1_41A2_8ABD_9BD0E0ACE3C0__INCLUDED_)
#define AFX_GETPOSTERDLG_H__47443455_53D1_41A2_8ABD_9BD0E0ACE3C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetposterDlg dialog
#include <vector>
using namespace std;

extern struct ENV {
	CString strFfmpegDir;
	CString strThumbnailDir;
	CString strPosterDir;
	CString strVideoPrefix;
	CString strAudioPrefix;
	CString strImagePrefix;
	CString strThumbnailWidth;
} struEnvSetup;  


class CGetposterDlg : public CDialog
{
// Construction
public:
	BOOL CreateDir(CString strDirName,CString CurrentPath);
	CString m_strCurrentDir;
	void AddSubDir(HTREEITEM hParent);
	CString GetFullPath(HTREEITEM hCurrent);
	void GetDriveDir(HTREEITEM hParent);
	void GetLogicalDrives(HTREEITEM hParent);
	void GetMediaExtension(vector<CString>& vctExtensions, LPCTSTR lpVideoType);

	CGetposterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetposterDlg)
	enum { IDD = IDD_GETPOSTER_DIALOG };
	CRichEditCtrl	m_edit;
	CTreeCtrl	m_tree;
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetposterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ImageList;  //图像列表(相同大小图像集合)   
    HTREEITEM m_hRoot;       //句柄 CTreeCtrl的根结点"我的电脑"  

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetposterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnItemexpandedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETPOSTERDLG_H__47443455_53D1_41A2_8ABD_9BD0E0ACE3C0__INCLUDED_)
