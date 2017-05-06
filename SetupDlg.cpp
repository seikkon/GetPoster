// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getposter.h"
#include "SetupDlg.h"
#include <iostream>
#include <fstream> 
#include <cstdlib> 
#include <VECTOR>
#include <afx.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog
#define BUFSIZE MAX_PATH


struct ENV {
	CString strFfmpegDir;
	CString strThumbnailDir;
	CString strPosterDir;
	CString strVideoPrefix;
	CString strAudioPrefix;
	CString strImagePrefix;
	CString strThumbnailWidth;
} struEnvSetup;

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
			SetDlgItemText(IDC_EDIT_FFMEPGPATH,strFilePath);
		}
		else
		{
			AfxMessageBox(_T("并不是mmfpeg.exe！请重新选择"), MB_OK);
		}
	}
	UpdateData(FALSE);
}   

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TCHAR strPath[BUFSIZE];
	GetCurrentDirectory(BUFSIZE,strPath);	
	CString strInitFile=strPath; 
	strInitFile+="\\setup.def";
	fstream _InitFile;
	_InitFile.open(strInitFile,ios::in);
	if(!_InitFile.is_open())
	{	

		SetDlgItemText(IDC_EDIT_THUMBNAILWIDTH,struEnvSetup.strThumbnailWidth="200");
		SetDlgItemText(IDC_EDIT_AUDIOPREFIX,struEnvSetup.strAudioPrefix="audio");
		SetDlgItemText(IDC_EDIT_FFMEPGPATH,struEnvSetup.strFfmpegDir="");
		SetDlgItemText(IDC_EDIT_IMAGEPREFIX,struEnvSetup.strImagePrefix="image");
		SetDlgItemText(IDC_EDIT_POSTERDIR,struEnvSetup.strPosterDir="VideoPoster");
		SetDlgItemText(IDC_EDIT_THUMBNAILDIR,struEnvSetup.strThumbnailDir="Thumbnail");
		SetDlgItemText(IDC_EDIT_VIDEOPREFIX,struEnvSetup.strVideoPrefix="video");
		_InitFile.open(strInitFile,ios::out);
		{
			if(!_InitFile.is_open()) 
			{
				AfxMessageBox("创建设定档失败",MB_OK);
			}
			else
			{
				_InitFile<<"ThumbnailWidth="<<struEnvSetup.strThumbnailWidth<<endl;
				_InitFile<<"AudioPrefix="<<struEnvSetup.strAudioPrefix<<endl;
				_InitFile<<"FfmpegDir="<<struEnvSetup.strFfmpegDir<<endl;
				_InitFile<<"ImagePrefix="<<struEnvSetup.strImagePrefix<<endl;
				_InitFile<<"PosterDir="<<struEnvSetup.strPosterDir<<endl;
				_InitFile<<"ThumbnailDir="<<struEnvSetup.strThumbnailDir<<endl;
				_InitFile<<"VideoPrefix="<<struEnvSetup.strVideoPrefix<<endl;

			}
		}

	}
	else
	{	
		TCHAR strbuf[100];
		while(!_InitFile.eof())
		{

			CString strInit[]={"ThumbnailWidth","AudioPrefix","FfmpegDir","ImagePrefix","PosterDir","ThumbnailDir","VideoPrefix"};

			_InitFile.getline(strbuf,100);
			CString strLine=strbuf;
			CString strInitItem=strLine.Left(strLine.GetLength()-strLine.ReverseFind('=')-1);
			CString strInitValue=strLine.Right(strLine.GetLength()-strLine.ReverseFind('=')-1);
//			for(int nChoice=0;nChoice<=sizeof(strInit)||strInit[nChoice]!=strInitItem;nChoice++){}；
			for(int nChoice=0;nChoice<=sizeof(strInit)||strInit[nChoice]!=strInitItem;nChoice++){};
			switch(nChoice)
			{
				case 0: SetDlgItemText(IDC_EDIT_THUMBNAILWIDTH,struEnvSetup.strThumbnailWidth=strInitValue); break;
				case 1: SetDlgItemText(IDC_EDIT_AUDIOPREFIX,struEnvSetup.strAudioPrefix=strInitValue); break;
				case 2: SetDlgItemText(IDC_EDIT_FFMEPGPATH,struEnvSetup.strFfmpegDir=strInitValue); break;
				case 3: SetDlgItemText(IDC_EDIT_IMAGEPREFIX,struEnvSetup.strImagePrefix=strInitValue); break;
				case 4: SetDlgItemText(IDC_EDIT_POSTERDIR,struEnvSetup.strPosterDir=strInitValue); break;
				case 5: SetDlgItemText(IDC_EDIT_THUMBNAILDIR,struEnvSetup.strThumbnailDir=strInitValue); break;
				case 6: SetDlgItemText(IDC_EDIT_VIDEOPREFIX,struEnvSetup.strVideoPrefix=strInitValue); break;

			}
		}
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
	BOOL bCheck=FALSE;
	int arryIDC[]={IDC_EDIT_THUMBNAILWIDTH,IDC_EDIT_AUDIOPREFIX,IDC_EDIT_FFMEPGPATH,IDC_EDIT_IMAGEPREFIX,IDC_EDIT_POSTERDIR,IDC_EDIT_THUMBNAILDIR,IDC_EDIT_VIDEOPREFIX};
	for(int i=0;i<sizeof(arryIDC);i++)
	{
		CString strText;
		GetDlgItemText(arryIDC[i],strText);
		if(strText!="") bCheck=TRUE;
	}
	if(!bCheck)
	{
			
	}
	else
	{
		CDialog::OnOK();
	}

}
