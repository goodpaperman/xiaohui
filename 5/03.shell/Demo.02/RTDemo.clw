; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRTDemoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RTDemo.h"
LastPage=0

ClassCount=12
Class1=CRTDemoApp
Class2=CRTDemoDoc
Class3=CRTDemoView
Class4=CMainFrame

ResourceCount=19
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_RTDemoTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_DDELETE
Resource5=IDR_RTDemoTYPE (English (U.S.))
Class7=CRTSlider
Resource6=IDD_DMODIFY
Class8=CRTForm
Resource7=CG_IDR_POPUP_RTDemo_VIEW (English (U.S.))
Class9=CRTDlg
Resource8=CG_IDR_POPUP_RTDEMO_VIEW (English (U.S.))
Class10=CModify
Resource9=IDD_DTIMER
Class11=CInsert
Resource10=IDD_RTFORM
Resource11=IDD_DINSERT
Class12=CTimerSpeed
Resource12=IDD_ABOUTBOX (English (U.S.))
Resource13=IDR_RTDEMOTYPE (English (U.S.))
Resource14=IDD_DDELETE (English (Australia))
Resource15=IDD_RTFORM (English (Australia))
Resource16=IDR_MAINFRAME (English (U.S.))
Resource17=IDD_DINSERT (English (Australia))
Resource18=IDD_DMODIFY (English (Australia))
Resource19=IDD_DTIMER (English (Australia))

[CLS:CRTDemoApp]
Type=0
HeaderFile=RTDemo.h
ImplementationFile=RTDemo.cpp
Filter=N
LastObject=CRTDemoApp

[CLS:CRTDemoDoc]
Type=0
HeaderFile=RTDemoDoc.h
ImplementationFile=RTDemoDoc.cpp
Filter=N
LastObject=CRTDemoDoc

[CLS:CRTDemoView]
Type=0
HeaderFile=RTDemoView.h
ImplementationFile=RTDemoView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_TYPE_MEMORYDRAW


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=ID_EDIT_MODIFY


[CLS:CAboutDlg]
Type=0
HeaderFile=RTDemo.cpp
ImplementationFile=RTDemo.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_RTDemoTYPE]
Type=1
Class=CRTDemoView
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
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

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
Command8=ID_APP_ABOUT
CommandCount=8

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

[MNU:IDR_RTDemoTYPE (English (U.S.))]
Type=1
Class=CRTDemoView
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
Command11=ID_EDIT_INSERT
Command12=ID_EDIT_DELETE
Command13=ID_EDIT_MODIFY
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_VIEW_KILLTIMER
Command17=ID_VIEW_RESTORETIMER
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

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

[CLS:CRTSlider]
Type=0
HeaderFile=RTSlider.h
ImplementationFile=RTSlider.cpp
BaseClass=CSliderCtrl
Filter=W
LastObject=CRTSlider
VirtualFilter=KWC

[DLG:IDD_RTFORM]
Type=1
Class=CRTForm
ControlCount=2
Control1=IDC_SLIDERPAGE,msctls_trackbar32,1342242821
Control2=IDC_RTGRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816

[CLS:CRTForm]
Type=0
HeaderFile=RTForm.h
ImplementationFile=RTForm.cpp
BaseClass=CFormView
Filter=W
LastObject=CRTForm
VirtualFilter=VWC

[DLG:IDD_DDELETE]
Type=1
Class=CRTDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_LDELETENAME,listbox,1352728865
Control3=IDC_BDELETE,button,1342242816

[CLS:CRTDlg]
Type=0
HeaderFile=RTDlg.h
ImplementationFile=RTDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRTDlg

[DLG:IDD_DMODIFY]
Type=1
Class=CModify
ControlCount=26
Control1=IDC_CMNAME,combobox,1344339971
Control2=IDC_EMDESC,edit,1350631552
Control3=IDC_EMUNIT,edit,1350631552
Control4=IDC_BMCOLOR,button,1342242816
Control5=IDC_CMSTYLE,combobox,1344339971
Control6=IDC_EMWIDTH,edit,1350641792
Control7=IDC_SMWIDTH,msctls_updown32,1342177334
Control8=IDC_EMMIN,edit,1350631552
Control9=IDC_EMMAX,edit,1350631552
Control10=IDC_EMSCALEMIN,edit,1350639744
Control11=IDC_EMSCALEMAX,edit,1350639744
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_BAPPLY,button,1342242816
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EMNAME,edit,1350631552

[CLS:CModify]
Type=0
HeaderFile=rtdlg.h
ImplementationFile=rtdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CModify
VirtualFilter=dWC

[DLG:IDD_DINSERT]
Type=1
Class=CInsert
ControlCount=27
Control1=IDC_EIName,edit,1350631552
Control2=IDC_EIINDEX,edit,1350633600
Control3=IDC_SIINDEX,msctls_updown32,1342177334
Control4=IDC_EIDESCRIPTION,edit,1350631552
Control5=IDC_EIUNIT,edit,1350631552
Control6=IDC_BICOLOR,button,1342242816
Control7=IDC_CISTYLE,combobox,1344339970
Control8=IDC_EIWIDTH,edit,1350633600
Control9=IDC_SIWIDTH,msctls_updown32,1342177334
Control10=IDC_EIMIN,edit,1350631552
Control11=IDC_EIMAX,edit,1350631552
Control12=IDC_EISCALEDMIN,edit,1350639744
Control13=IDC_EISCALEDMAX,edit,1350639744
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287
Control27=IDC_BIAPPLY,button,1342242816

[CLS:CInsert]
Type=0
HeaderFile=rtdlg.h
ImplementationFile=rtdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BIAPPLY

[MNU:CG_IDR_POPUP_RTDemo_VIEW (English (U.S.))]
Type=1
Class=?
Command1=ID_SPEED_TIMERSPEED
CommandCount=1

[DLG:IDD_DTIMER]
Type=1
Class=CTimerSpeed
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STIMERSPEED,msctls_trackbar32,1342242821
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SPPEDMSG,static,1342308352

[CLS:CTimerSpeed]
Type=0
HeaderFile=TimerSpeed.h
ImplementationFile=TimerSpeed.cpp
BaseClass=CDialog
Filter=D
LastObject=CTimerSpeed
VirtualFilter=dWC

[MNU:CG_IDR_POPUP_RTDEMO_VIEW (English (U.S.))]
Type=1
Class=?
Command1=ID_SPEED_TIMERSPEED
CommandCount=1

[MNU:IDR_RTDEMOTYPE (English (U.S.))]
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
Command11=ID_EDIT_INSERT
Command12=ID_EDIT_DELETE
Command13=ID_EDIT_MODIFY
Command14=ID_TYPE_GRID
Command15=ID_TYPE_BOUNDARY
Command16=ID_TYPE_TITLE
Command17=ID_TYPE_MEMORYDRAW
Command18=ID_TYPE_BACKCOLOR
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_VIEW_KILLTIMER
Command22=ID_VIEW_RESTORETIMER
Command23=ID_WINDOW_NEW
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_ARRANGE
Command27=ID_APP_ABOUT
CommandCount=27

[DLG:IDD_RTFORM (English (Australia))]
Type=1
Class=?
ControlCount=2
Control1=IDC_SLIDERPAGE,msctls_trackbar32,1342242821
Control2=IDC_RTGRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816

[DLG:IDD_DDELETE (English (Australia))]
Type=1
Class=?
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_LDELETENAME,listbox,1352728865
Control3=IDC_BDELETE,button,1342242816

[DLG:IDD_DMODIFY (English (Australia))]
Type=1
Class=?
ControlCount=26
Control1=IDC_CMNAME,combobox,1344339971
Control2=IDC_EMDESC,edit,1350631552
Control3=IDC_EMUNIT,edit,1350631552
Control4=IDC_BMCOLOR,button,1342242816
Control5=IDC_CMSTYLE,combobox,1344339971
Control6=IDC_EMWIDTH,edit,1350641792
Control7=IDC_SMWIDTH,msctls_updown32,1342177334
Control8=IDC_EMMIN,edit,1350631552
Control9=IDC_EMMAX,edit,1350631552
Control10=IDC_EMSCALEMIN,edit,1350639744
Control11=IDC_EMSCALEMAX,edit,1350639744
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_BAPPLY,button,1342242816
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EMNAME,edit,1350631552

[DLG:IDD_DINSERT (English (Australia))]
Type=1
Class=?
ControlCount=27
Control1=IDC_EIName,edit,1350631552
Control2=IDC_EIINDEX,edit,1350633600
Control3=IDC_SIINDEX,msctls_updown32,1342177334
Control4=IDC_EIDESCRIPTION,edit,1350631552
Control5=IDC_EIUNIT,edit,1350631552
Control6=IDC_BICOLOR,button,1342242816
Control7=IDC_CISTYLE,combobox,1344339970
Control8=IDC_EIWIDTH,edit,1350633600
Control9=IDC_SIWIDTH,msctls_updown32,1342177334
Control10=IDC_EIMIN,edit,1350631552
Control11=IDC_EIMAX,edit,1350631552
Control12=IDC_EISCALEDMIN,edit,1350639744
Control13=IDC_EISCALEDMAX,edit,1350639744
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287
Control27=IDC_BIAPPLY,button,1342242816

[DLG:IDD_DTIMER (English (Australia))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STIMERSPEED,msctls_trackbar32,1342242821
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SPPEDMSG,static,1342308352

