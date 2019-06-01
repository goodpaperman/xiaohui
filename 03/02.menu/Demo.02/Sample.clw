; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSampleView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Sample.h"
LastPage=0

ClassCount=5
Class1=CSampleApp
Class2=CSampleDoc
Class3=CSampleView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX (English (U.S.))
Class5=CAboutDlg
Resource2=IDR_MAINFRAME (English (U.S.))

[CLS:CSampleApp]
Type=0
HeaderFile=Sample.h
ImplementationFile=Sample.cpp
Filter=N

[CLS:CSampleDoc]
Type=0
HeaderFile=SampleDoc.h
ImplementationFile=SampleDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CSampleDoc

[CLS:CSampleView]
Type=0
HeaderFile=SampleView.h
ImplementationFile=SampleView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CSampleView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Sample.cpp
ImplementationFile=Sample.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_EXIT
CommandCount=1

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

