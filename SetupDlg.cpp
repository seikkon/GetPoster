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
#define BUFSIZE MAX_PATH




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
//	GetCurrentDirectory(BUFSIZE,strPath);
	GetModuleFileName(NULL,strPath,BUFSIZE);
	CString strInitFile(strPath);
	strInitFile=strInitFile.Left(strInitFile.ReverseFind('\\'))+"\\setup.def"; 

	ifstream _inFile;
	ofstream _outFile;
	_inFile.open(strInitFile,ios::in);
	if(!_inFile.good())
	{	
		_inFile.close();
		SetDlgItemText(IDC_EDIT_THUMBNAILWIDTH,struEnvSetup.strThumbnailWidth="200");
		SetDlgItemText(IDC_EDIT_AUDIOPREFIX,struEnvSetup.strAudioPrefix="audio");
		SetDlgItemText(IDC_EDIT_FFMEPGPATH,struEnvSetup.strFfmpegDir="");
		SetDlgItemText(IDC_EDIT_IMAGEPREFIX,struEnvSetup.strImagePrefix="image");
		SetDlgItemText(IDC_EDIT_POSTERDIR,struEnvSetup.strPosterDir="VideoPoster");
		SetDlgItemText(IDC_EDIT_THUMBNAILDIR,struEnvSetup.strThumbnailDir="Thumbnail");
		SetDlgItemText(IDC_EDIT_VIDEOPREFIX,struEnvSetup.strVideoPrefix="video");
		_outFile.open(strInitFile,ios::out);
		{
			if(!_outFile.good()) 
			{
				AfxMessageBox("创建设定档失败",MB_OK);
			}
			else
			{
				_outFile<<"ThumbnailWidth="<<struEnvSetup.strThumbnailWidth.GetBuffer(struEnvSetup.strThumbnailWidth.GetLength())<<endl;
				_outFile<<"AudioPrefix="<<struEnvSetup.strAudioPrefix.GetBuffer(struEnvSetup.strAudioPrefix.GetLength())<<endl;
				_outFile<<"FfmpegDir="<<struEnvSetup.strFfmpegDir.GetBuffer(struEnvSetup.strFfmpegDir.GetLength())<<endl;
				_outFile<<"ImagePrefix="<<struEnvSetup.strImagePrefix.GetBuffer(struEnvSetup.strImagePrefix.GetLength())<<endl;
				_outFile<<"PosterDir="<<struEnvSetup.strPosterDir.GetBuffer(struEnvSetup.strPosterDir.GetLength())<<endl;
				_outFile<<"ThumbnailDir="<<struEnvSetup.strThumbnailDir.GetBuffer(struEnvSetup.strThumbnailDir.GetLength())<<endl;
				_outFile<<"VideoPrefix="<<struEnvSetup.strVideoPrefix.GetBuffer(struEnvSetup.strVideoPrefix.GetLength())<<endl<<flush;
				_outFile.close();
			}
		}

	}
	else
	{	
		TCHAR strbuf[MAX_PATH];			
		int nLine=0;
		while(!_inFile.eof())
		{

			CString strInit[]={"ThumbnailWidth","AudioPrefix","FfmpegDir","ImagePrefix","PosterDir","ThumbnailDir","VideoPrefix"};

			_inFile.getline(strbuf,MAX_PATH);
			CString strLine(strbuf);
			CString strInitItem=strLine.Left(strLine.Find('='));
			CString strInitValue=strLine.Right(strLine.GetLength()-strLine.Find('=')-1);
//			for(int nChoice=0;nChoice<=sizeof(strInit)||strInit[nChoice]!=strInitItem;nChoice++){}；

			switch(nLine)
			{
				case 0: SetDlgItemText(IDC_EDIT_THUMBNAILWIDTH,struEnvSetup.strThumbnailWidth=strInitValue); break;
				case 1: SetDlgItemText(IDC_EDIT_AUDIOPREFIX,struEnvSetup.strAudioPrefix=strInitValue); break;
				case 2: SetDlgItemText(IDC_EDIT_FFMEPGPATH,struEnvSetup.strFfmpegDir=strInitValue); break;
				case 3: SetDlgItemText(IDC_EDIT_IMAGEPREFIX,struEnvSetup.strImagePrefix=strInitValue); break;
				case 4: SetDlgItemText(IDC_EDIT_POSTERDIR,struEnvSetup.strPosterDir=strInitValue); break;
				case 5: SetDlgItemText(IDC_EDIT_THUMBNAILDIR,struEnvSetup.strThumbnailDir=strInitValue); break;
				case 6: SetDlgItemText(IDC_EDIT_VIDEOPREFIX,struEnvSetup.strVideoPrefix=strInitValue); break;

			}
			nLine++;
		}
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
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
		AfxMessageBox("设定不能空白！请重新输入",MB_OK);
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
			AfxMessageBox("设定档失败",MB_OK);
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

}
