; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dlg_ttbar.h"
LastPage=0

ClassCount=3
Class1=CDlg_ttbarApp
Class2=CAboutDlg
Class3=CDlg_TTBarDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_DLG_TTBAR_DIALOG
Resource3=IDD_ABOUTBOX

[CLS:CDlg_ttbarApp]
Type=0
BaseClass=CWinApp
HeaderFile=dlg_ttbar.h
ImplementationFile=dlg_ttbar.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=dlg_ttbarDlg.cpp
ImplementationFile=dlg_ttbarDlg.cpp
LastObject=CAboutDlg

[CLS:CDlg_TTBarDlg]
Type=0
BaseClass=CDialog
HeaderFile=dlg_ttbarDlg.h
ImplementationFile=dlg_ttbarDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DLG_TTBAR_DIALOG]
Type=1
Class=CDlg_TTBarDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_TOP,button,1342242817
Control4=ID_BOTTOM,button,1342242817

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_EDIT_CUT
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

