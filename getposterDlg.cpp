// getposterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getposter.h"
#include "getposterDlg.h"
#include "SetupDlg.h"
//#include "propkey.h"
#include <vector>
using namespace std;


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

	m_ImageList.Create(32,32,ILC_COLOR32,10,30);     //����ͼ������CImageList���� 
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_ImageList.Add(hIcon);

    m_list.SetImageList(&m_ImageList,LVSIL_NORMAL);  //Ϊ���οؼ�����ͼ������     
    m_tree.ModifyStyle(NULL,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS);  
    m_hRoot = m_tree.InsertItem(_T("�ҵĵ���"),0,0);         //������ڵ�  
    GetLogicalDrives(m_hRoot);                      //�Զ��庯�� ��ȡ����  
    GetDriveDir(m_hRoot);                           //�Զ��庯�� ��ȡ��������  
    m_tree.Expand(m_hRoot,TVE_EXPAND);              //չ�����۵������б� TVE_EXPANDչ���б� 

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
	
    return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE  

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
    //��ȡϵͳ�����������ַ�����Ϣ  
    size_t szAllDriveStrings = GetLogicalDriveStrings(0,NULL);           //�������ܳ���  
    char *pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];  //��������  
    GetLogicalDriveStrings(szAllDriveStrings,pDriveStrings);  
    size_t szDriveString = strlen(pDriveStrings);                        //������С  
    while(szDriveString > 0)  
    {  
        m_tree.InsertItem(pDriveStrings,hParent);       //�ڸ��ڵ�hParent������̷�  
        pDriveStrings += szDriveString + 1;             //pDriveStrings��C:\ D:\ E:\��  
        szDriveString = strlen(pDriveStrings);  
    }  
}

void CGetposterDlg::GetDriveDir(HTREEITEM hParent)
{
    HTREEITEM hChild = m_tree.GetChildItem(hParent);   //��ȡָ��λ���е�����  
    while(hChild)                                        
    {  
        CString strText = m_tree.GetItemText(hChild);  //�����б�����Ŀ����  
        if(strText.Right(1) != "\\")                   //���ұ�1��ʼ��ȡ��������nCount���ַ�  
            strText += _T("\\");  
        strText += "*.*";  
        //����ǰĿ¼���ļ�ö�ٲ�InsertItem��״��ʾ  
        CFileFind file;                                       //���屾���ļ�����  
        BOOL bContinue = file.FindFile(strText);              //���Ұ����ַ������ļ�  
        while(bContinue)  
        {  
            bContinue = file.FindNextFile();                  //������һ���ļ�  
            if(file.IsDirectory() && !file.IsDots())          //�ҵ��ļ�Ϊ�����Ҳ�Ϊ��"."  
                m_tree.InsertItem(file.GetFileName(),hChild); //����̷�·������״�ļ���  
        }  
        GetDriveDir(hChild);                                  //�ݹ����  
        hChild = m_tree.GetNextItem(hChild,TVGN_NEXT);        //��ȡ���οؼ�TVGN_NEXT���ֵ���  
    }  
}

CString CGetposterDlg::GetFullPath(HTREEITEM hCurrent)
{
    CString strTemp;  
    CString strReturn = "";  
    while(hCurrent != m_hRoot)  
    {  
        strTemp = m_tree.GetItemText(hCurrent);    //�����б�����Ŀ����  
        if(strTemp.Right(1) != "\\")  
            strTemp += "\\";  
        strReturn = strTemp  + strReturn;          
        hCurrent = m_tree.GetParentItem(hCurrent); //���ظ���Ŀ���  
    }  
    return strReturn;
}

void CGetposterDlg::AddSubDir(HTREEITEM hParent)
{
    CString strPath = GetFullPath(hParent);     //��ȡȫ·��  
    if(strPath.Right(1) != "\\")  
        strPath += "\\";  
    strPath += "*.*";  
    CFileFind file;  
    BOOL bContinue = file.FindFile(strPath);    //���Ұ����ַ������ļ�  
    while(bContinue)  
    {  
        bContinue = file.FindNextFile();        //������һ���ļ�  
        if(file.IsDirectory() && !file.IsDots())  
            m_tree.InsertItem(file.GetFileName(),hParent);  
    }  
}

void CGetposterDlg::OnItemexpandedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	TVITEM item = pNMTreeView->itemNew;                  //����\���ܹ���������ͼ��Ŀ��Ϣ  
    if(item.hItem == m_hRoot)  
        return;  
    HTREEITEM hChild = m_tree.GetChildItem(item.hItem);  //��ȡָ��λ���е�����  
    while(hChild)  
    {  
        AddSubDir(hChild);                               //�����Ŀ¼  
        hChild = m_tree.GetNextItem(hChild,TVGN_NEXT);   //��ȡ���οؼ�TVGN_NEXT���ֵ���  
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
	m_strCurrentDir=str;
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
//	vector<wstring> vecVideo,vecImage;//,vecAudio
//	GetMediaExtension(vecVideo,L"video");
//	GetMediaExtension(vecImage,L"picture");

	CString str = m_strCurrentDir;
    if(str.Right(1) != "\\")  
		str += "\\";  


 	CreateDir(struEnvSetup.strPosterDir,str);
 	CreateDir(struEnvSetup.strThumbnailDir,str);
  

    if(str.Right(1) != "\\")  
		str += "\\";  
    str += "*.*";  
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
	CString strArq = "-i c:\\tmp\\testfile.mp4 -ss 00:00:01 -f image2 -vframes 1 c:\\tmp\\test.jpg";
	HINSTANCE hNewExe = ShellExecute(NULL,"open","c:\\tmp\\ffmpeg.exe",strArq, NULL, NULL);

	CDialog::OnOK();
}

BOOL CGetposterDlg::CreateDir(CString strDirName, CString strCurrentPath)
{
    CFileFind file; 
	BOOL bExsist=file.FindFile(strCurrentPath+strDirName,0);
	if(bExsist!=FALSE)
	{
		BOOL bFlag = CreateDirectory(strDirName, NULL); 
		if(bFlag==TRUE)
		{
			DWORD err = GetLastError();		
//			AfxMessageBox("�����ļ��д���"��MB_OK);
			return FALSE;
		}
	}
	return TRUE;
}

//void CGetposterDlg::GetMediaExtension(vector<wstring>& vctExtensions, LPCWSTR lpVideoType)  
void CGetposterDlg::GetMediaExtension(vector<CString>& vctExtensions, LPCTSTR lpVideoType)
{  
	HKEY hKey = NULL;  
	DWORD dwType  = REG_SZ;  
	LONG retv = -1;  
	const TCHAR *pVideoType = lpVideoType;//(NULL == lpVideoType) ? KIND_VIDEO : lpVideoType;  
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
						if (0 == _stricmp(szValueData, pVideoType))  
						{  
							vctExtensions.push_back(CString(szValueName));  
						}  
					}  
				}  
			}  
		}  
	}  
	
	if (NULL != hKey)  
	{  
		RegCloseKey(hKey);  
	}  
}  
