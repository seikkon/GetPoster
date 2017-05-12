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


struct ENV {
	CString strCtrlID;
	CString strValue;
	CString strContent;
};

class CGetposterDlg : public CDialog
{
// Construction
public:
	BOOL MakeThumbnail(CString strOriginIamge,CString strThumbNailPath,CString  strPrex,int nSize);
	CString GetENVValue(CString ENVCtrlID,vector<ENV> &vecENV);
	void CreatInitFile(CString strFileName,vector<ENV>& vecInit);
	BOOL DoInitENV(CString strFileName,vector<ENV>& vecENV);
	BOOL CreateDir(CString strDirName,CString CurrentPath);
	void AddSubDir(HTREEITEM hParent);
	CString GetFullPath(HTREEITEM hCurrent);
	void GetDriveDir(HTREEITEM hParent);
	void GetLogicalDrives(HTREEITEM hParent);
	CString GetMediaExtType(CString strFileExt);


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
	vector<ENV> m_vecENV;
	CString m_strCurrentPath;

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
