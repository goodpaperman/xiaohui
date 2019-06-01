; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRealDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Real.h"

ClassCount=3
Class1=CRealApp
Class2=CRealDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_REAL_DIALOG
Resource4=IDR_MENU
Resource5=IDR_MENU (Korean)
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDD_REAL_DIALOG (English (U.S.))

[CLS:CRealApp]
Type=0
HeaderFile=Real.h
ImplementationFile=Real.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CRealApp

[CLS:CRealDlg]
Type=0
HeaderFile=RealDlg.h
ImplementationFile=RealDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CRealDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=RealDlg.h
ImplementationFile=RealDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_REAL_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CRealDlg

[DLG:IDD_REAL_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342177294

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDM_IMAGE
Command2=IDM_EXIT
Command3=IDM_ABOUT
CommandCount=3

[MNU:IDR_MENU (Korean)]
Type=1
Class=?
Command1=IDM_IMAGE
Command2=IDM_EXIT
Command3=IDM_ABOUTBOX
CommandCount=3

