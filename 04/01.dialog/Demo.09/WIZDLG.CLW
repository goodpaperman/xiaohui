; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWizDlgView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WizDlg.h"
LastPage=0

ClassCount=10
Class1=CWizDlgApp
Class2=CWizDlgDoc
Class3=CWizDlgView
Class4=CMainFrame

ResourceCount=12
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_TESTPAGE3
Resource4=IDD_WIZARDBASE
Resource5=IDD_TESTPAGE2
Class5=CAboutDlg
Class6=CWizardDlg
Class7=CNetButton
Class8=CTestPage1
Class9=CTestPage2
Class10=CTestPage3
Resource6=IDD_TESTPAGE1
Resource7=IDD_TESTPAGE2 (Italian (Italy))
Resource8=IDR_MAINFRAME (Italian (Italy))
Resource9=IDD_ABOUTBOX (Italian (Italy))
Resource10=IDD_WIZARDBASE (Italian (Italy))
Resource11=IDD_TESTPAGE1 (Italian (Italy))
Resource12=IDD_TESTPAGE3 (Italian (Italy))

[CLS:CWizDlgApp]
Type=0
HeaderFile=WizDlg.h
ImplementationFile=WizDlg.cpp
Filter=N

[CLS:CWizDlgDoc]
Type=0
HeaderFile=WizDlgDoc.h
ImplementationFile=WizDlgDoc.cpp
Filter=N

[CLS:CWizDlgView]
Type=0
HeaderFile=WizDlgView.h
ImplementationFile=WizDlgView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_CUSTOM_WIZARD

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=WizDlg.cpp
ImplementationFile=WizDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_TEST_WIZARD
Command16=ID_CUSTOM_WIZARD
Command17=ID_APP_ABOUT
CommandCount=17

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
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
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

[DLG:IDD_WIZARDBASE]
Type=1
Class=CWizardDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BACK,button,1476460544
Control4=IDC_STATIC1,static,1342177296
Control5=IDC_PICTURE,static,1342177294
Control6=IDC_BT_TITLE,button,1342177291
Control7=IDC_PAGEFRAME,static,1073741842

[CLS:CWizardDlg]
Type=0
HeaderFile=WizardDlg.h
ImplementationFile=WizardDlg.cpp
BaseClass=CDialog
LastObject=CWizardDlg

[DLG:IDD_TESTPAGE1]
Type=1
Class=CTestPage1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_TESTPAGE2]
Type=1
Class=CTestPage2
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_TESTPAGE3]
Type=1
Class=CTestPage3
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352

[CLS:CNetButton]
Type=0
HeaderFile=NetButton.h
ImplementationFile=NetButton.cpp
BaseClass=CButton
LastObject=CNetButton

[CLS:CTestPage1]
Type=0
HeaderFile=TestPage1.h
ImplementationFile=TestPage1.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestPage1

[CLS:CTestPage2]
Type=0
HeaderFile=TestPage2.h
ImplementationFile=TestPage2.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[CLS:CTestPage3]
Type=0
HeaderFile=TestPage3.h
ImplementationFile=TestPage3.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestPage3
VirtualFilter=dWC

[TB:IDR_MAINFRAME (Italian (Italy))]
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

[MNU:IDR_MAINFRAME (Italian (Italy))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_TEST_WIZARD
Command16=ID_CUSTOM_WIZARD
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME (Italian (Italy))]
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

[DLG:IDD_ABOUTBOX (Italian (Italy))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WIZARDBASE (Italian (Italy))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BACK,button,1476460544
Control4=IDC_STATIC1,static,1342177296
Control5=IDC_PICTURE,static,1342177294
Control6=IDC_BT_TITLE,button,1342177291
Control7=IDC_PAGEFRAME,static,1073741842

[DLG:IDD_TESTPAGE1 (Italian (Italy))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_TESTPAGE2 (Italian (Italy))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_TESTPAGE3 (Italian (Italy))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352

