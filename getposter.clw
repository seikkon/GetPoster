; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "getposter.h"

ClassCount=4
Class1=CGetposterApp
Class2=CGetposterDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_GETPOSTER_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CSetupDlg
Resource4=IDD_SETUP_DIALOG

[CLS:CGetposterApp]
Type=0
HeaderFile=getposter.h
ImplementationFile=getposter.cpp
Filter=N

[CLS:CGetposterDlg]
Type=0
HeaderFile=getposterDlg.h
ImplementationFile=getposterDlg.cpp
Filter=D
LastObject=CGetposterDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=getposterDlg.h
ImplementationFile=getposterDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GETPOSTER_DIALOG]
Type=1
Class=CGetposterDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TREE,SysTreeView32,1350631424
Control4=IDC_LIST,SysListView32,1350631424
Control5=IDC_RICHEDIT,RICHEDIT,1350631552
Control6=IDC_RICHEDIT1,RICHEDIT,1484851328
Control7=IDC_EDIT_PATH,edit,1350633600

[DLG:IDD_SETUP_DIALOG]
Type=1
Class=CSetupDlg
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,static,1342308352
Control4=IDC_BUTTON_FINDFILE,button,1342242816
Control5=IDC_EDIT_FFMEPGPATH,edit,1484849280
Control6=IDC_STATIC2,static,1342308352
Control7=IDC_EDIT_THUMBNAILDIR,edit,1350631552
Control8=IDC_STATIC3,static,1342308352
Control9=IDC_EDIT_POSTERDIR,edit,1350631552
Control10=IDC_STATIC4,static,1342308352
Control11=IDC_EDIT_VIDEOPREFIX,edit,1350631552
Control12=IDC_STATIC5,static,1342308352
Control13=IDC_EDIT_AUDIOPREFIX,edit,1350631552
Control14=IDC_STATIC6,static,1342308352
Control15=IDC_EDIT_IMAGEPREFIX,edit,1350631552
Control16=IDC_STATIC7,static,1342308352
Control17=IDC_EDIT_THUMBNAILWIDTH,edit,1350631552

[CLS:CSetupDlg]
Type=0
HeaderFile=SetupDlg.h
ImplementationFile=SetupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetupDlg
VirtualFilter=dWC

