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
	{		//�����ҵ��ļ���ȷ����ʱ   
		CString strFilePath = Dlg.GetPathName();
		CString strFileName=strFilePath.Right(strFilePath.GetLength()-strFilePath.ReverseFind('\\')-1);
		strFileName.MakeLower();
		if(strFileName=="ffmpeg.exe")
		{
//			struEnvSetup.strFfmpegDir=strFilePath;
			SetDlgItemText(IDC_EDIT_FFMEPGPATH,strFilePath);
		}
		else
		{
			AfxMessageBox(_T("������mmfpeg.exe��������ѡ��"), MB_OK);
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
			pChildWnd->SetWindowText(m_cENV.GetENVVal(pChildWnd->GetDlgCtrlID())); //ID������Դƥ��
		}
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
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
			AfxMessageBox("�趨���ܿհף�����������",MB_OK);
			break;
		}
		else
		{
			m_cENV.SetENVVal(pChildWnd->GetDlgCtrlID(),strText);
		}
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
	m_cENV.SaveToData();

/*
	BOOL bCheck=TRUE;
	int arryIDC[]={IDC_EDIT_THUMBNAILWIDTH,IDC_EDIT_AUDIOPREFIX,IDC_EDIT_FFMEPGPATH,IDC_EDIT_IMAGEPREFIX,IDC_EDIT_POSTERDIR,IDC_EDIT_THUMBNAILDIR,IDC_EDIT_VIDEOPREFIX};
	ofstream _outFile;
	for(int i=0;i<(sizeof(arryIDC)/sizeof(i));i++)
	{
		CString strText;
		GetDlgItemText(arryIDC[i],strText);
		if(strText=="") 
		{
			bCheck=FALSE;
			break;
		}
	}
	if(!bCheck)
	{
		AfxMessageBox("�趨���ܿհף�����������",MB_OK);
	}
	else
	{
		TCHAR strPath[BUFSIZE];
//		GetCurrentDirectory(BUFSIZE,strPath);
		GetModuleFileName(NULL,strPath,BUFSIZE);
		CString strInitFile(strPath);
		strInitFile=strInitFile.Left(strInitFile.ReverseFind('\\'))+"\\setup.def"; 

		_outFile.open(strInitFile,ios::out|ios::trunc);
		if(!_outFile.good()) 
		{
			AfxMessageBox("�趨��ʧ��",MB_OK);
		}
		else
		{
			ENV *pStruEnv=&struEnvSetup;
			CString strText;
			GetDlgItemText(arryIDC[0],strText);struEnvSetup.strThumbnailWidth=strText;
			_outFile<<"ThumbnailWidth="<<struEnvSetup.strThumbnailWidth.GetBuffer(struEnvSetup.strThumbnailWidth.GetLength())<<endl;
			GetDlgItemText(arryIDC[1],strText);struEnvSetup.strAudioPrefix=strText;
			_outFile<<"AudioPrefix="<<struEnvSetup.strAudioPrefix.GetBuffer(struEnvSetup.strAudioPrefix.GetLength())<<endl;
			GetDlgItemText(arryIDC[2],strText);struEnvSetup.strFfmpegDir=strText;
			_outFile<<"FfmpegDir="<<struEnvSetup.strFfmpegDir.GetBuffer(struEnvSetup.strFfmpegDir.GetLength())<<endl;
			GetDlgItemText(arryIDC[3],strText);struEnvSetup.strImagePrefix=strText;
			_outFile<<"ImagePrefix="<<struEnvSetup.strImagePrefix.GetBuffer(struEnvSetup.strImagePrefix.GetLength())<<endl;
			GetDlgItemText(arryIDC[4],strText);struEnvSetup.strPosterDir=strText;
			_outFile<<"PosterDir="<<struEnvSetup.strPosterDir.GetBuffer(struEnvSetup.strPosterDir.GetLength())<<endl;
			GetDlgItemText(arryIDC[5],strText);struEnvSetup.strThumbnailDir=strText;
			_outFile<<"ThumbnailDir="<<struEnvSetup.strThumbnailDir.GetBuffer(struEnvSetup.strThumbnailDir.GetLength())<<endl;
			GetDlgItemText(arryIDC[6],strText);struEnvSetup.strVideoPrefix=strText;
			_outFile<<"VideoPrefix="<<struEnvSetup.strVideoPrefix.GetBuffer(struEnvSetup.strVideoPrefix.GetLength())<<endl<<flush;
			_outFile.close();
		}

		CDialog::OnOK();
	}
*/

		CDialog::OnOK();
}
