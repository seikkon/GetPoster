// getposterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getposter.h"
#include "getposterDlg.h"
#include "SetupDlg.h"
#include <fstream> 
#include <atlimage.h>
using namespace std;


#define INITEFILE "setup.def"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern struct ENV struEnvSetup;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetposterDlg dialog

CGetposterDlg::CGetposterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetposterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetposterDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetposterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetposterDlg)
	DDX_Control(pDX, IDC_RICHEDIT, m_edit);
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetposterDlg, CDialog)
	//{{AFX_MSG_MAP(CGetposterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE, OnItemexpandedTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetposterDlg message handlers

BOOL CGetposterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	// IDM_SETUPDLG must be in the system command range.
//	ASSERT((IDM_SETUPDLG & 0xFFF0) == IDM_SETUPDLG);
//	ASSERT(IDM_SETUPDLG < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu,strSetupDialog;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		strSetupDialog.LoadString(IDS_SETUPDLG);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_STRING, IDM_SETUPDLG, strSetupDialog);			
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	vector<ENV> vecInit;
	DoInitENV("setup.def",m_vecENV);

	m_ImageList.Create(32,32,ILC_COLOR32,10,30);     //创建图像序列CImageList对象 
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_ImageList.Add(hIcon);

    m_list.SetImageList(&m_ImageList,LVSIL_NORMAL);  //为树形控件设置图像序列     
    m_tree.ModifyStyle(NULL,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS);  
    m_hRoot = m_tree.InsertItem(_T("我的电脑"),0,0);         //插入根节点  
    GetLogicalDrives(m_hRoot);                      //自定义函数 获取驱动  
    GetDriveDir(m_hRoot);                           //自定义函数 获取驱动子项  
    m_tree.Expand(m_hRoot,TVE_EXPAND);              //展开或折叠子项列表 TVE_EXPAND展开列表 

	HTREEITEM hParent=m_hRoot,hChild=NULL;
	TCHAR strBuf[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,strBuf);	
	CString strCurrentPath(strBuf);
	CString strDir="Dir";
	BOOL bExpandAll=FALSE;	
	CString strText="Text";
	while(!bExpandAll)
	{
		int nFind=strCurrentPath.Find('\\');
		if(nFind>0)
		{
			strDir=strCurrentPath.Left(nFind);
			strCurrentPath=strCurrentPath.Mid(strCurrentPath.Find('\\')+1);
			hChild=m_tree.GetChildItem(hParent);			
			while(strText!=strDir)
			{
				strText=m_tree.GetItemText(hChild);
				if(strText.Right(1)=='\\') strText.TrimRight('\\');
				if(strText==strDir)
					m_tree.Expand(hChild,TVE_EXPAND) ;
				else
					hChild=m_tree.GetNextSiblingItem(hChild) ;
			} 

		}
		else
		{
			strText.Empty();
			strDir=strCurrentPath;
			hChild=m_tree.GetChildItem(hParent);
			while(strText!=strDir)
			{
				strText=m_tree.GetItemText(hChild);
				if(strText.Right(1)=='\\') strText.TrimRight('\\');
				if(strText==strDir)
				{
					m_tree.Expand(hChild,TVE_EXPAND);//.GetFocus(hChild);
					m_tree.SetFocus();
					m_tree.SetItemState(hChild,LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);

					m_tree.SelectItem(hChild);

				}
				 else
					hChild=m_tree.GetNextSiblingItem(hChild) ;
			} 

			bExpandAll=TRUE;
		}
		hParent=hChild;

	} 
	
    return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE  

}

void CGetposterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == IDM_SETUPDLG)
	{
		CSetupDlg dlgSetup;
		dlgSetup.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetposterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetposterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetposterDlg::GetLogicalDrives(HTREEITEM hParent)
{
    //获取系统分区驱动器字符串信息  
    size_t szAllDriveStrings = GetLogicalDriveStrings(0,NULL);           //驱动器总长度  
    char *pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];  //建立数组  
    GetLogicalDriveStrings(szAllDriveStrings,pDriveStrings);  
    size_t szDriveString = strlen(pDriveStrings);                        //驱动大小  
    while(szDriveString > 0)  
    {  
        m_tree.InsertItem(pDriveStrings,hParent);       //在父节点hParent下添加盘符  
        pDriveStrings += szDriveString + 1;             //pDriveStrings即C:\ D:\ E:\盘  
        szDriveString = strlen(pDriveStrings);  
    }  
}

void CGetposterDlg::GetDriveDir(HTREEITEM hParent)
{
    HTREEITEM hChild = m_tree.GetChildItem(hParent);   //获取指定位置中的子项  
    while(hChild)                                        
    {  
        CString strText = m_tree.GetItemText(hChild);  //检索列表中项目文字  
//        if(strText.Right(1) != "\\")                   //从右边1开始获取从右向左nCount个字符  
//		strText += _T("\\");  
//        strText += "*.*";  
		strText += "\\*.*";  
        //将当前目录下文件枚举并InsertItem树状显示  
        CFileFind file;                                       //定义本地文件查找  
        BOOL bContinue = file.FindFile(strText);              //查找包含字符串的文件  
        while(bContinue)  
        {  
            bContinue = file.FindNextFile();                  //查找下一个文件  
            if(file.IsDirectory() && !file.IsDots())          //找到文件为内容且不为点"."  
                m_tree.InsertItem(file.GetFileName(),hChild); //添加盘符路径下树状文件夹  
        }  
        GetDriveDir(hChild);                                  //递归调用  
        hChild = m_tree.GetNextItem(hChild,TVGN_NEXT);        //获取树形控件TVGN_NEXT下兄弟项  
    }  
}

CString CGetposterDlg::GetFullPath(HTREEITEM hCurrent)
{
    CString strTemp;  
	CString strReturn = "";
    while(hCurrent != m_hRoot)  
    {  
        strTemp = m_tree.GetItemText(hCurrent);    //检索列表中项目文字  
        if(strTemp.Right(1) != "\\")  
            strTemp += "\\";  
        strReturn = strTemp  + strReturn;          
        hCurrent = m_tree.GetParentItem(hCurrent); //返回父项目句柄  
    }  
	strReturn.TrimRight('\\');
    return strReturn;
}

void CGetposterDlg::AddSubDir(HTREEITEM hParent)
{
    CString strPath = GetFullPath(hParent);     //获取全路径  
//    if(strPath.Right(1) != "\\")  
//        strPath += "\\";  
//    strPath += "*.*";  
	strPath += "\\*.*";  
    CFileFind file;  
    BOOL bContinue = file.FindFile(strPath);    //查找包含字符串的文件  
    while(bContinue)  
    {  
        bContinue = file.FindNextFile();        //查找下一个文件  
        if(file.IsDirectory() && !file.IsDots())  
            m_tree.InsertItem(file.GetFileName(),hParent);  
    }  
}

void CGetposterDlg::OnItemexpandedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	TVITEM item = pNMTreeView->itemNew;                  //发送\接受关于树形视图项目信息  
    if(item.hItem == m_hRoot)  
        return;  
    HTREEITEM hChild = m_tree.GetChildItem(item.hItem);  //获取指定位置中的子项  
    while(hChild)  
    {  
        AddSubDir(hChild);                               //添加子目录  
        hChild = m_tree.GetNextItem(hChild,TVGN_NEXT);   //获取树形控件TVGN_NEXT下兄弟项  
    }  

	*pResult = 0;
}

void CGetposterDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();  
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;  
    TVITEM item = pNMTreeView->itemNew;  
    if(item.hItem == m_hRoot)  
        return;  
    CString str = GetFullPath(item.hItem);
	m_strCurrentPath=str;
	if(str.Right(1)=='\\')
		str.TrimRight('\\');
	int nIndex=1;
	nIndex=str.Find('\\',nIndex);
	while(nIndex>0)
	{
		str=str.Left(nIndex)+" >> "+str.Right(str.GetLength()-nIndex-1);
		nIndex=str.Find('\\',nIndex);
	}
	SetDlgItemText(IDC_EDIT_PATH,str);

	str = GetFullPath(item.hItem);
//    if(str.Right(1) != "\\")  
//		str += "\\";  
    str += "\\*.*";  
    CFileFind file;  
    BOOL bContinue = file.FindFile(str);  
    while(bContinue)  
    {  
        bContinue = file.FindNextFile();  
		if(!file.IsDirectory()&&!file.IsDots())
        {  
            SHFILEINFO info;  
            CString temp = str;  
            int index = temp.Find("*.*");  
            temp.Delete(index,3);  
            SHGetFileInfo(temp + file.GetFileName(),0,&info,sizeof(&info),SHGFI_DISPLAYNAME | SHGFI_ICON);  
            int i = m_ImageList.Add(info.hIcon);  
            m_list.InsertItem(i,info.szDisplayName,i);  
        }  
    }  
	*pResult = 0;
}

extern struct ENV struEnvSetup;

void CGetposterDlg::OnOK() 
{
	// TODO: Add extra validation here
/*
	vector<CString> vecVideo,vecImage;//,vecAudio
	GetMediaExtension(vecVideo,"video");
	GetMediaExtension(vecImage,"picture");*/
	

	CString strCurrentPath,strPosterDir,strThumbnailDir,strVideoPrefix,strImagePrefix,strFfmpegPath;
	int nWSize;
	strCurrentPath=m_strCurrentPath;
	
  	CreateDir(strPosterDir=GetENVValue("POSTERDIR",m_vecENV),strCurrentPath);
   	CreateDir(strThumbnailDir=GetENVValue("THUMBNAILDIR",m_vecENV),strCurrentPath);
	strFfmpegPath=GetENVValue("FFMEPGPATH",m_vecENV);
	strVideoPrefix=GetENVValue("VIDEOPREFIX",m_vecENV);
	strImagePrefix=GetENVValue("IMAGEPREFIX",m_vecENV);
	nWSize=_ttoi(GetENVValue("THUMBNAILWIDTH",m_vecENV));
//    strPath += "\\*.*";  
	CFileFind file;
    BOOL bContinue = file.FindFile(strCurrentPath+"\\*.*");  
    while(bContinue)  
    {  
		bContinue = file.FindNextFile(); 
		if(!file.IsDirectory()&&!file.IsDots())
        {  
			CString strFileName =file.GetFileName();
			CString strFileExt =strFileName.Right(strFileName.GetLength()-strFileName.Find('.'));
			strFileExt.MakeLower();
			CString strFileType= GetMediaExtType(strFileExt);
			if(strFileType=="picture")
			{
				MakeThumbnail(file.GetFilePath(),strCurrentPath+'\\'+strThumbnailDir,strImagePrefix,nWSize);
				
			}
			else 
			{
				CString strSrcPath,strDestPath;
				strSrcPath=file.GetFilePath();//+'\\'+strFileName;
				strDestPath=strCurrentPath+'\\'+strPosterDir+'\\'+strFileName.Left(strFileName.Find('.')+1)+"jpg";
				CString strArq;
				strArq.Format("-i %s -ss 00:00:01 -f image2 -vframes 1 %s",strSrcPath,strDestPath);
				HINSTANCE hNewExe = ShellExecute(NULL,"open","c:\\tools\\ffmpeg.exe",strArq, NULL, SW_SHOW );
				if((int)hNewExe<=32)
				{
					DWORD err=GetLastError();
					AfxMessageBox("执行ffmpeg.exe错误",MB_OK);
				}
				else
				{
					MakeThumbnail(strDestPath,strCurrentPath+'\\'+strThumbnailDir,strVideoPrefix,nWSize);
				}

			}
			
        }          
 
    }  
//	CString strArq = "-i c:\\tmp\\testfile.mp4 -ss 00:00:01 -f image2 -s 352x240 -vframes 1 c:\\tmp\\test.jpg";
//	HINSTANCE hNewExe = ShellExecute(NULL,"open","c:\\tmp\\ffmpeg.exe",strArq, NULL, NULL);

	CDialog::OnOK();
}

BOOL CGetposterDlg::CreateDir(CString strDirName, CString strCurrentPath)
{
    CFileFind file; 
 	BOOL bExsist=file.FindFile(strCurrentPath+'\\'+strDirName,0);

	if(bExsist!=TRUE)
	{
		DWORD err=GetLastError();
		if(err==2)
		{
			BOOL bDone = CreateDirectory(strCurrentPath+'\\'+strDirName, NULL); 
			if(bDone!=TRUE)
			{
				DWORD err = GetLastError();		
				//			AfxMessageBox("创建文件夹错误！"，MB_OK);
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox("创建文件夹时系统错误",MB_OK);
		}
	}
	
 	return TRUE;
}

//void CGetposterDlg::GetMediaExtension(vector<wstring>& vctExtensions, LPCWSTR lpVideoType)  
CString CGetposterDlg::GetMediaExtType(CString strFileExt)
{  
	HKEY hKey = NULL;  
	DWORD dwType  = REG_SZ;  
	LONG retv = -1;  
//	const TCHAR *pVideoType = lpVideoType;//(NULL == lpVideoType) ? KIND_VIDEO : lpVideoType;  
	const TCHAR *pRegPath =   
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\KindMap");  
	
	retv = RegOpenKeyEx(HKEY_LOCAL_MACHINE, pRegPath, 0, KEY_READ, &hKey);  
	if (ERROR_SUCCESS == retv)  
	{  
		TCHAR    achClass[MAX_PATH] = _T("");  
		DWORD    cchClassName = MAX_PATH;  
		DWORD    cSubKeys = 0;  
		DWORD    cbMaxSubKey = 0;  
		DWORD    cchMaxClass = 0;  
		DWORD    kNumber = 0;  
		DWORD    cchMaxValue = 0;  
		DWORD    cbMaxValueData = 0;  
		DWORD    cbSecurityDescriptor = 0;  
		FILETIME ftLastWriteTime;  
		
		retv = RegQueryInfoKey(  
			hKey,  
			achClass,  
			&cchClassName,  
			NULL,  
			&cSubKeys,  
			&cbMaxSubKey,  
			&cchMaxClass,  
			&kNumber,  
			&cchMaxValue,  
			&cbMaxValueData,  
			&cbSecurityDescriptor,  
			&ftLastWriteTime);  
		
		if (ERROR_SUCCESS == retv)  
		{  
			TCHAR szValueName[MAX_PATH] = { 0 };  
			TCHAR szValueData[MAX_PATH] = { 0 };  
			DWORD dwcchValueName = MAX_PATH;  
			DWORD dwcchValueData = MAX_PATH;  
			
			for (int i = 0; i < (int)kNumber; ++i)  
			{  
				dwcchValueName = MAX_PATH;  
				ZeroMemory(szValueName, sizeof(TCHAR) * MAX_PATH);  
				
				retv = RegEnumValue(  
					hKey,  
					i,  
					szValueName,  
					&dwcchValueName,  
					NULL,  
					NULL,  
					NULL,  
					NULL);  
				
				if (ERROR_SUCCESS == retv)  
				{  
					dwType = REG_SZ;  
					dwcchValueData = MAX_PATH;  
					ZeroMemory(szValueData, sizeof(TCHAR) * MAX_PATH);  
					
					retv = RegQueryValueEx(  
						hKey,  
						szValueName,  
						NULL,  
						&dwType,  
						(PBYTE)szValueData,  
						&dwcchValueData);  
					
					if (ERROR_SUCCESS == retv)  
					{  
// 						if (0 == _stricmp(szValueData, pVideoType))  
// 						{  
// 						   vctExtensions.push_back(CString(szValueName));  
// 						} 
						if(CString(szValueName)==strFileExt)
						{
							RegCloseKey(hKey);  
							return CString(szValueData);
						}
					}
				}  
			}  
		}  
	}  
	

	if (NULL != hKey)  
	{  
		RegCloseKey(hKey);  
		return CString("");
	}  
}  

BOOL CGetposterDlg::DoInitENV(CString strFileName,vector<ENV>& vecInit)
{
//	pstruENV=new ENV;
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitFile(strPath);
	strInitFile=strInitFile.Left(strInitFile.ReverseFind('\\')+1)+strFileName; 
	
	ifstream _inFile;
	_inFile.open(strInitFile,ios::in);
	if(!_inFile.good())
	{	
		_inFile.close();
		CreatInitFile(strFileName,vecInit);
		_inFile.open(strInitFile,ios::in);
	}

	TCHAR strBuf[MAX_PATH];			
	struct ENV struInitENV;
	while(!_inFile.eof())
	{
		_inFile.getline(strBuf,MAX_PATH);
		CString strLine(strBuf);
		int nPos=0;
		strLine.TrimLeft('\'');struInitENV.strCtrlID=strLine.Left(nPos=strLine.Find('\'',1));strLine=strLine.Right(strLine.GetLength()-nPos-2);
		strLine.TrimLeft('\'');struInitENV.strValue=strLine.Left(nPos=strLine.Find('\'',1));strLine=strLine.Right(strLine.GetLength()-nPos-2);
		strLine.TrimLeft('\'');strLine.TrimRight('\'');struInitENV.strContent=strLine;
		vecInit.push_back(struInitENV);
	}
	_inFile.close();

	return TRUE;
}

void CGetposterDlg::CreatInitFile(CString strFileName,vector<ENV>& vecInit)
{
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitFile(strPath);
	strInitFile=strInitFile.Left(strInitFile.ReverseFind('\\')+1)+strFileName; 
	
	ofstream _outFile;
	if(!_outFile.good()) 
	{
		AfxMessageBox("创建设定档失败",MB_OK);
	}
	else
	{
		_outFile<<"\'THUMBNAILWIDTH\' \'200\' \'缩图宽度\'"<<endl;
		_outFile<<"\'AUDIOPREFIX\' \'audio\' \'音档前置\'"<<endl;
		_outFile<<"\'FFMEPGPATH\' \'C:\' \'FFMEPG档\'"<<endl;
		_outFile<<"\'IMAGEPREFIX\' \'image\' \'图档前置\'"<<endl;
		_outFile<<"\'POSTERDIR\' \'Poster\' \'海报目录\'"<<endl;
		_outFile<<"\'THUMBNAILDIR\' \'Thumbnail\' \'缩图目录\'"<<endl;
		_outFile<<"\'VIDEOPREFIX\' \'video\' \'视频前置\'"<<endl<<flush;
		_outFile.close();
	}
}

CString CGetposterDlg::GetENVValue(CString strENVCtrlID,vector<ENV> &vecENV)
{
	vector<ENV>::iterator ite;
	for (ite = vecENV.begin(); ite != vecENV.end();ite++)
	{
		if(ite->strCtrlID==strENVCtrlID)
		{
			return ite->strValue;
		}
	}
	return "";
}

BOOL CGetposterDlg::MakeThumbnail(CString strOriginImgPath, CString strThumbnailPath, CString strPrefix, int nSize)
{
    const WIDTH = 200;
    const HEIGHT = 200;
    CImage cOriginImg;
    CImage cThumbnail;
    cOriginImg.Load(strOriginImgPath);
    if(cOriginImg.IsNull())
        return false;
    int nWidth = 200;
    int nHeight = 200;
	
    nWidth = cOriginImg.GetWidth();
    nHeight = cOriginImg.GetHeight();
	
    if(nWidth > WIDTH)
    {
        double dRatio = nWidth * 1.0 / nHeight;
        if(nWidth > nHeight)
        {
            nWidth = WIDTH;
            nHeight = nWidth / dRatio;
        }
        else
        {
            nHeight = HEIGHT;
            nWidth = nHeight * dRatio;
        }
    }
	
    if(!cThumbnail.CreateEx(nWidth, nHeight, 24, BI_RGB))
    {
        cOriginImg.Destroy();
        return false;
    }
	
    int nPreMode = ::SetStretchBltMode(cThumbnail.GetDC(),HALFTONE);
    cThumbnail.ReleaseDC();
    cOriginImg.Draw(cThumbnail.GetDC(), 0, 0, nWidth, nHeight, 0, 0, cOriginImg.GetWidth(), cOriginImg.GetHeight());
    cThumbnail.ReleaseDC();
    ::SetBrushOrgEx(cThumbnail.GetDC(), 0, 0, NULL); 
    cThumbnail.ReleaseDC();
    ::SetStretchBltMode(cThumbnail.GetDC(), nPreMode);
    cThumbnail.ReleaseDC();
	//CString NewFilName=(strThumbnailPath+'\\'++strPrix+'-'+strOriginImgPath.Right(strOriginImgPath.GetLength()-strOriginImgPath.ReverseFind('\\')-1));	
    cThumbnail.Save((strThumbnailPath+'\\'+strPrefix+'-'+strOriginImgPath.Right(strOriginImgPath.GetLength()-strOriginImgPath.ReverseFind('\\')-1)),Gdiplus::ImageFormatJPEG);
    cThumbnail.Destroy();
    cOriginImg.Destroy();
	
    return true;
}
