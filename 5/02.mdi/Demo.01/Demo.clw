; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"
LastPage=0

ClassCount=10
Class1=CChildFrame
Class2=CDemoApp
Class3=CAboutDlg
Class4=CDemoDoc
Class5=CDemoView
Class6=CMainFrame
Class7=CViewManager
Class8=CWindowDlg
Class9=CMDIClient
Class10=CWindowTabCtrl

ResourceCount=5
Resource1=IDR_TABVIEW_MENU (English (U.S.))
Resource2=IDR_DEMOTYPE (English (U.S.))
Resource3=IDD_WINDOW_MANAGE (English (U.S.))
Resource4=IDR_MAINFRAME (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=Demo.h
ImplementationFile=Demo.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Demo.cpp
ImplementationFile=Demo.cpp
LastObject=CAboutDlg

[CLS:CDemoDoc]
Type=0
BaseClass=CDocument
HeaderFile=DemoDoc.h
ImplementationFile=DemoDoc.cpp

[CLS:CDemoView]
Type=0
BaseClass=CView
HeaderFile=DemoView.h
ImplementationFile=DemoView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CViewManager]
Type=0
BaseClass=CControlBar
HeaderFile=ViewManager.h
ImplementationFile=ViewManager.cpp

[CLS:CWindowDlg]
Type=0
BaseClass=CDialog
HeaderFile=WindowManager.h
ImplementationFile=WindowManager.cpp

[CLS:CMDIClient]
Type=0
BaseClass=CWnd
HeaderFile=WindowManager.h
ImplementationFile=WindowManager.cpp
Filter=W
VirtualFilter=WC
LastObject=CMDIClient

[CLS:CWindowTabCtrl]
Type=0
BaseClass=CTabCtrl
HeaderFile=WindowTabCtrl.h
ImplementationFile=WindowTabCtrl.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_WINDOW_MANAGE]
Type=1
Class=CWindowDlg

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
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_TABVIEW_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_FULLSCREEN
Command2=ID_FILE_CLOSE
Command3=ID_WINDOW_CLOSE_ALL
Command4=ID_FILE_SAVE
Command5=ID_WINDOW_SAVE_ALL
Command6=ID_FILE_PRINT
Command7=ID_WINDOW_NEW
Command8=ID_WINDOW_NEXT
Command9=ID_WINDOW_PREVIOUS
Command10=ID_WINDOW_CASCADE
Command11=ID_WINDOW_TILE_HORZ
Command12=ID_WINDOW_TILE_VERT
Command13=ID_WINDOW_MANAGE
CommandCount=13

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DEMOTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_VIEW_VIEWTAB
Command18=ID_VIEW_FULLSCREEN
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_WINDOW_NEXT
Command24=ID_WINDOW_PREVIOUS
Command25=ID_WINDOW_CLOSE_ALL
Command26=ID_WINDOW_SAVE_ALL
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WINDOW_MANAGE (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_WINDOWLIST_LIST,listbox,1352731091
Control2=IDC_WINDOWLIST_ACTIVATE,button,1342242817
Control3=IDOK,button,1342242816
Control4=IDC_WINDOWLIST_SAVE,button,1342242816
Control5=IDC_WINDOWLIST_CLOSE,button,1342242816
Control6=IDC_WINDOWLIST_CASCADE,button,1342242816
Control7=IDC_WINDOWLIST_TILEHORZ,button,1342242816
Control8=IDC_WINDOWLIST_TILEVERT,button,1342242816
Control9=IDC_WINDOWLIST_MINIMIZE,button,1342242816
Control10=IDC_STATIC,static,1342308352

