// getposterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getposter.h"
#include "getposterDlg.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

	m_ImageList.Create(32,32,ILC_COLOR32,10,30);     //创建图像序列CImageList对象 
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_ImageList.Add(hIcon);

    m_list.SetImageList(&m_ImageList,LVSIL_NORMAL);  //为树形控件设置图像序列     
    m_tree.ModifyStyle(NULL,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS);  
    m_hRoot = m_tree.InsertItem("我的电脑",0,0);         //插入根节点  
    GetLogicalDrives(m_hRoot);                      //自定义函数 获取驱动  
    GetDriveDir(m_hRoot);                           //自定义函数 获取驱动子项  
    m_tree.Expand(m_hRoot,TVE_EXPAND);              //展开或折叠子项列表 TVE_EXPAND展开列表 

	TCHAR strBuf[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,strBuf);
	CString strCurrentPath(strBuf);
	CString strDir;
	BOOL bExpand=TRUE;
	{
		if(strCurrentPath.Find('\\')!=-1)
		{
			strDir=strCurrentPath.Left(strCurrentPath.Find('\\'));
			strCurrentPath=strCurrentPath.Mid(strCurrentPath.Find('\\')+1);
		}
		else
		{
			strDir=strCurrentPath;
			bExpand=FALSE;
			} 
//		HTREEITEM
//		m_tree.Expand(m_hRoot,TVE_EXPAND);
//		m_tree.f
//		m_tree.Expand()
	}while(bExpand)	
	
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE  

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
        if(strText.Right(1) != "\\")                   //从右边1开始获取从右向左nCount个字符  
            strText += _T("\\");  
        strText += "*.*";  
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
    return strReturn;
}

void CGetposterDlg::AddSubDir(HTREEITEM hParent)
{
    CString strPath = GetFullPath(hParent);     //获取全路径  
    if(strPath.Right(1) != "\\")  
        strPath += "\\";  
    strPath += "*.*";  
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
    if(str.Right(1) != "\\")  
		str += "\\";  
    str += "*.*";  
    CFileFind file;  
    BOOL bContinue = file.FindFile(str);  
    while(bContinue)  
    {  
        bContinue = file.FindNextFile();  
        //if(!file.IsDirectory() && !file.IsDots())  
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

void CGetposterDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString strArq = "-i c:\\tmp\\testfile.mp4 -ss 00:00:01 -f image2 -vframes 1 c:\\tmp\\test.jpg";
	HINSTANCE hNewExe = ShellExecute(NULL,"open","c:\\tmp\\ffmpeg.exe",strArq, NULL, NULL);

	//HINSTANCE hNewExe = ShellExecute(NULL,"open","c:\\UltraISO.exe",NULL,NULL,SW_SHOW);
	CDialog::OnOK();
}
