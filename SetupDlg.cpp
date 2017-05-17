// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getposter.h"
#include "SetupDlg.h"
#include <iostream>
#include <fstream> 
#include <cstdlib> 
#include <afx.h>

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog
//#define BUFSIZE MAX_PATH


  

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CSetupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetupDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_BUTTON_FINDFILE, OnButtonFindFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSetupDlg, CDialog)
	//{{AFX_DISPATCH_MAP(CSetupDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISetupDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B8DF2544-AC42-4A1D-824F-A8245DCD1B0B}
static const IID IID_ISetupDlg =
{ 0xb8df2544, 0xac42, 0x4a1d, { 0x82, 0x4f, 0xa8, 0x24, 0x5d, 0xcd, 0x1b, 0xb } };

BEGIN_INTERFACE_MAP(CSetupDlg, CDialog)
	INTERFACE_PART(CSetupDlg, IID_ISetupDlg, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnButtonFindFile() 
{
	// TODO: Add your control notification handler code here
	
	CFileDialog Dlg(TRUE,NULL,"*.*");

	
	if(Dlg.DoModal()==IDOK)
	{		//当你找到文件并确定打开时   
		CString strFilePath = Dlg.GetPathName();
		CString strFileName=strFilePath.Right(strFilePath.GetLength()-strFilePath.ReverseFind('\\')-1);
		strFileName.MakeLower();
		if(strFileName=="ffmpeg.exe")
		{
//			struEnvSetup.strFfmpegDir=strFilePath;
			SetDlgItemText(FFMEPGPATH,strFilePath);
		}
		else
		{
			AfxMessageBox(_T("并不是ffmpeg.exe！请重新选择"), MB_OK);
		}
	}
	UpdateData(FALSE);
}   

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	//MAKEINTRESOURCE
	CWnd* pChildWnd = this->GetWindow(GW_CHILD);
	while(pChildWnd != NULL)
	{   
		if(!m_cENV.GetENVVal(pChildWnd->GetDlgCtrlID()).IsEmpty())
		{
			pChildWnd->SetWindowText(m_cENV.GetENVVal(pChildWnd->GetDlgCtrlID())); //ID号与资源匹配
		}
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
	return TRUE;  
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnOK() 
{
	// TODO: Add extra validation here

	CWnd* pChildWnd = this->GetWindow(GW_CHILD);
	while(pChildWnd != NULL)
	{   
		CString strText;
		pChildWnd->GetWindowText(strText);
		if(strText.IsEmpty())
		{
			AfxMessageBox("设定不能空白！请重新输入",MB_OK);
			break;
		}
		else
		{
			m_cENV.SetENVVal(pChildWnd->GetDlgCtrlID(),strText);
		}
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
	m_cENV.SaveToFile();

	CDialog::OnOK();
}

void CSetupDlg::OnlyFfmpeg()
{
	CWnd* pChildWnd = this->GetWindow(GW_CHILD);
	while(pChildWnd != NULL)
	{   
		CHAR szClassName[MAX_PATH];
		WORD nID = pChildWnd->GetDlgCtrlID();
		GetClassName(pChildWnd->GetSafeHwnd(),szClassName,MAX_PATH);
		if(!strcmp(szClassName,"Edit"))
		{
			((CEdit* )pChildWnd)->SetReadOnly(TRUE);
		}
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
	OnButtonFindFile();
}
