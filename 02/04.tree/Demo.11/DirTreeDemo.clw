; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DirTreeDemo.h"
LastPage=0

ClassCount=7
Class1=CDirTreeDemoApp
Class2=CDirTreeDemoDoc
Class3=CDirTreeDemoView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CLeftView
Class6=CAboutDlg
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_TREEDLG (German (Germany))
Class7=CTreeDialog
Resource5=IDD_TREEDLG
Resource6=IDR_MAINFRAME (English (U.S.))

[CLS:CDirTreeDemoApp]
Type=0
HeaderFile=DirTreeDemo.h
ImplementationFile=DirTreeDemo.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CDirTreeDemoApp

[CLS:CDirTreeDemoDoc]
Type=0
HeaderFile=DirTreeDemoDoc.h
ImplementationFile=DirTreeDemoDoc.cpp
Filter=N

[CLS:CDirTreeDemoView]
Type=0
HeaderFile=DirTreeDemoView.h
ImplementationFile=DirTreeDemoView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
LastObject=CLeftView
BaseClass=CView
VirtualFilter=VWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DirTreeDemo.cpp
ImplementationFile=DirTreeDemo.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_VIEW_LARGEICON
Command9=ID_VIEW_SMALLICON
Command10=ID_VIEW_LIST
Command11=ID_VIEW_DETAILS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=IDM_TREEDLG
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TREEDLG]
Type=1
Class=CTreeDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_TREE1,SysTreeView32,1350631463
Control3=IDC_PATHNAME,static,1342312448
Control4=IDC_SETPATH,button,1342242816
Control5=IDC_SELECTION,edit,1350631552

[CLS:CTreeDialog]
Type=0
HeaderFile=TreeDialog.h
ImplementationFile=TreeDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTreeDialog

[DLG:IDD_TREEDLG (German (Germany))]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_TREE1,SysTreeView32,1350631463
Control3=IDC_PATHNAME,static,1342312448
Control4=IDC_SETPATH,button,1342242816
Control5=IDC_SELECTION,edit,1350631552

