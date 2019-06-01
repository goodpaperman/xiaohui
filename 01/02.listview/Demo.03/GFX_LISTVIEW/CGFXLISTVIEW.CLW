; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyListView
LastTemplate=CListView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CGfxListView.h"
LastPage=0

ClassCount=15
Class1=CCGfxListViewApp
Class2=CCGfxListViewDoc
Class3=CGfxListView
Class4=CMainFrame
Class7=CGfxFormatColumnDlg

ResourceCount=10
Resource1=IDD_GFX_FORMATCOL
Resource2=IDR_LISTMENUBMP
Class9=CGfxInComboEdit
Class10=CGfxInComboList
Class11=CGfxInComboStatic
Class12=CGfxInCombo
Class13=CGfxInEdit
Class14=CGfxListTip
Class5=CAboutDlg
Class6=CGfxCustomizeColumnDlg
Class8=CGfxHeaderCtrl
Resource3=IDD_ABOUTBOX
Resource4=IDD_GFX_CUSTOMIZECOL
Class15=CMyListView
Resource5=IDR_MAINFRAME
Resource6=IDD_GFX_CUSTOMIZECOL (Italian (Italy))
Resource7=IDR_LISTMENUBMP (Italian (Italy))
Resource8=IDR_MAINFRAME (Italian (Italy))
Resource9=IDD_ABOUTBOX (Italian (Italy))
Resource10=IDD_GFX_FORMATCOL (Italian (Italy))

[CLS:CCGfxListViewApp]
Type=0
HeaderFile=CGfxListView.h
ImplementationFile=CGfxListView.cpp
Filter=N

[CLS:CCGfxListViewDoc]
Type=0
HeaderFile=CGfxListViewDoc.h
ImplementationFile=CGfxListViewDoc.cpp
Filter=N

[CLS:CGfxListView]
Type=0
HeaderFile=GfxListView.h
ImplementationFile=GfxListView.cpp
Filter=C
LastObject=CGfxListView
BaseClass=CListView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=CGfxListView.cpp
ImplementationFile=CGfxListView.cpp
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
Command15=ID_TEST_CAT
Command16=ID_APP_ABOUT
CommandCount=16

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

[DLG:IDD_GFX_CUSTOMIZECOL]
Type=1
Class=CGfxCustomizeColumnDlg
ControlCount=10
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FREECOL,listbox,1352730883
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ACTCOL,listbox,1352730881
Control7=IDC_ADD,button,1476460544
Control8=IDC_REMOVE,button,1476460544
Control9=IDC_MOVEUP,button,1476460544
Control10=IDC_MOVEDOWN,button,1476460544

[CLS:CGfxCustomizeColumnDlg]
Type=0
HeaderFile=GfxCustomizeColumnDlg.h
ImplementationFile=GfxCustomizeColumnDlg.cpp
BaseClass=CDialog

[DLG:IDD_GFX_FORMATCOL]
Type=1
Class=CGfxFormatColumnDlg
ControlCount=21
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ACTCOL,listbox,1352728833
Control3=IDC_STATIC,static,1342177298
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CB_FORMAT,combobox,1344339971
Control6=IDC_FMT,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CD_LABEL,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_LABEL_DT,edit,1350631552
Control11=IDC_STATIC,static,1342177296
Control12=IDC_STATIC,static,1342308352
Control13=IDC_WIDTH,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342177296
Control16=IDC_STATIC,static,1342308352
Control17=IDC_RD_LEFT,button,1342177289
Control18=IDC_RD_CENTER,button,1342177289
Control19=IDC_RD_RIGHT,button,1342177289
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816

[CLS:CGfxFormatColumnDlg]
Type=0
HeaderFile=GfxFormatColumnDlg.h
ImplementationFile=GfxFormatColumnDlg.cpp
BaseClass=CDialog

[CLS:CGfxHeaderCtrl]
Type=0
HeaderFile=GfxHeaderCtrl.h
ImplementationFile=GfxHeaderCtrl.cpp
BaseClass=CHeaderCtrl

[CLS:CGfxInComboEdit]
Type=0
HeaderFile=GfxInComboEdit.h
ImplementationFile=GfxInComboEdit.cpp
BaseClass=CRichEditCtrl

[CLS:CGfxInComboList]
Type=0
HeaderFile=GfxInComboList.h
ImplementationFile=GfxInComboList.cpp
BaseClass=CListBox

[CLS:CGfxInComboStatic]
Type=0
HeaderFile=GfxInComboStatic.h
ImplementationFile=GfxInComboStatic.cpp
BaseClass=CStatic

[CLS:CGfxInCombo]
Type=0
HeaderFile=GfxInCombo.h
ImplementationFile=GfxInCombo.cpp
BaseClass=CWnd

[CLS:CGfxInEdit]
Type=0
HeaderFile=GfxInEdit.h
ImplementationFile=GfxInEdit.cpp
BaseClass=CRichEditCtrl

[CLS:CGfxListTip]
Type=0
HeaderFile=GfxListTip.h
ImplementationFile=GfxListTip.cpp
BaseClass=CWnd

[TB:IDR_LISTMENUBMP]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_UNDO
Command5=ID_GFX_CUSTOMIZEHEAD
Command6=ID_GFX_SORTASC
Command7=ID_GFX_SORTDESC
CommandCount=7

[CLS:CMyListView]
Type=0
HeaderFile=MyListView.h
ImplementationFile=MyListView.cpp
BaseClass=CGfxListView
Filter=C
LastObject=CMyListView
VirtualFilter=VWC

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

[TB:IDR_LISTMENUBMP (Italian (Italy))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_UNDO
Command5=ID_GFX_CUSTOMIZEHEAD
Command6=ID_GFX_SORTASC
Command7=ID_GFX_SORTDESC
CommandCount=7

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
Command15=ID_TEST_CAT
Command16=ID_APP_ABOUT
CommandCount=16

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

[DLG:IDD_GFX_CUSTOMIZECOL (Italian (Italy))]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FREECOL,listbox,1352730883
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ACTCOL,listbox,1352730881
Control7=IDC_ADD,button,1476460544
Control8=IDC_REMOVE,button,1476460544
Control9=IDC_MOVEUP,button,1476460544
Control10=IDC_MOVEDOWN,button,1476460544

[DLG:IDD_GFX_FORMATCOL (Italian (Italy))]
Type=1
Class=?
ControlCount=21
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ACTCOL,listbox,1352728833
Control3=IDC_STATIC,static,1342177298
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CB_FORMAT,combobox,1344339971
Control6=IDC_FMT,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CD_LABEL,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_LABEL_DT,edit,1350631552
Control11=IDC_STATIC,static,1342177296
Control12=IDC_STATIC,static,1342308352
Control13=IDC_WIDTH,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342177296
Control16=IDC_STATIC,static,1342308352
Control17=IDC_RD_LEFT,button,1342177289
Control18=IDC_RD_CENTER,button,1342177289
Control19=IDC_RD_RIGHT,button,1342177289
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816

