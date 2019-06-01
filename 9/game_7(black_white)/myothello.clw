; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyothelloDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "myothello.h"

ClassCount=3
Class1=CMyothelloApp
Class2=CMyothelloDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_MYOTHELLO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU1

[CLS:CMyothelloApp]
Type=0
HeaderFile=myothello.h
ImplementationFile=myothello.cpp
Filter=N

[CLS:CMyothelloDlg]
Type=0
HeaderFile=myothelloDlg.h
ImplementationFile=myothelloDlg.cpp
Filter=D
LastObject=ID_MOVEBACK
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=myothelloDlg.h
ImplementationFile=myothelloDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342179342

[DLG:IDD_MYOTHELLO_DIALOG]
Type=1
Class=CMyothelloDlg
ControlCount=1
Control1=IDC_STATUS,static,1342308864

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDOK
Command2=ID_NEWGAME
Command3=ID_EASY
Command4=ID_MID
Command5=ID_ADV
Command6=ID_MOVEBACK
Command7=IDC_BUTTON1
Command8=IDM_ABOUTBOX
CommandCount=8

