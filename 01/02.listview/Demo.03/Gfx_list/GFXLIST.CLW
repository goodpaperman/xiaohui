; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSuperGrid1View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GfxList.h"
LastPage=0

ClassCount=17
Class1=CGfxListApp
Class2=CSuperGrid1Doc
Class3=CSuperGrid1View
Class4=CMainFrame
Class7=CGfxFormatColumnDlg

ResourceCount=18
Resource1=IDD_GFX_FORMATCOL
Resource2=IDD_ABOUTBOX
Class9=CGfxInComboEdit
Class10=CGfxInComboList
Class11=CGfxInComboStatic
Class12=CGfxInCombo
Class13=CGfxInEdit
Class14=CGfxListCtrl
Class15=CGfxListTip
Class16=CTestDaoSet
Resource3=IDD_GFX_CUSTOMIZECOL_ITA
Resource4=IDD_GFXLIST_FORM
Resource5=IDR_LISTMENUBMP
Resource6=IDD_GFX_CUSTOMIZECOL
Class5=CAboutDlg
Class6=CGfxCustomizeColumnDlg
Class8=CGfxHeaderCtrl
Class17=CTestDialog
Resource7=IDD_TEST_DIALOG
Resource8=IDD_GFX_FORMATCOL_ITA
Resource9=IDR_MAINFRAME
Resource10=IDD_GFX_FORMATCOL_ITA (Italian (Italy))
Resource11=IDR_LISTMENUBMP (Italian (Italy))
Resource12=IDD_GFX_CUSTOMIZECOL_ITA (Italian (Italy))
Resource13=IDD_ABOUTBOX (Italian (Italy))
Resource14=IDD_GFXLIST_FORM (Italian (Italy))
Resource15=IDD_GFX_CUSTOMIZECOL (Italian (Italy))
Resource16=IDD_GFX_FORMATCOL (Italian (Italy))
Resource17=IDD_TEST_DIALOG (Italian (Italy))
Resource18=IDR_MAINFRAME (Italian (Italy))

[CLS:CGfxListApp]
Type=0
HeaderFile=GfxList.h
ImplementationFile=GfxList.cpp
Filter=N

[CLS:CSuperGrid1Doc]
Type=0
HeaderFile=SuperGrid1Doc.h
ImplementationFile=SuperGrid1Doc.cpp
Filter=N

[CLS:CSuperGrid1View]
Type=0
HeaderFile=SuperGrid1View.h
ImplementationFile=SuperGrid1View.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=ID_AUTOPREVIEW

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=GfxList.cpp
ImplementationFile=GfxList.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

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

[DLG:IDD_GFXLIST_FORM]
Type=1
Class=CSuperGrid1View
ControlCount=1
Control1=IDC_LIST1,SysListView32,1342243853

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_FILE_PRINT
Command9=ID_APP_ABOUT
Command10=ID_TESTCAT
Command11=ID_TRYBITMAP1
Command12=ID_TRYBITMAP2
Command13=ID_BLENDBMP
Command14=ID_DRAGGABLECOL
Command15=ID_GRIDH
Command16=ID_GRIDV
Command17=ID_TESTDAO
CommandCount=17

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

[CLS:CGfxListCtrl]
Type=0
HeaderFile=GfxListCtrl.h
ImplementationFile=GfxListCtrl.cpp
BaseClass=CListCtrl
LastObject=CGfxListCtrl

[CLS:CGfxListTip]
Type=0
HeaderFile=GfxListTip.h
ImplementationFile=GfxListTip.cpp
BaseClass=CWnd

[MNU:IDR_MAINFRAME]
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
Command13=ID_ADDANITEM
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_CUSTOMHEADER
Command17=ID_FORMATHEADER
Command18=ID_AUTOPREVIEW
Command19=ID_APP_ABOUT
CommandCount=19

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

[CLS:CTestDaoSet]
Type=0
HeaderFile=TestDaoSet.h
ImplementationFile=TestDaoSet.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:CTestDaoSet]
DB=1
DBType=DAO
ColumnCount=23
Column1=[ObjCode], 4, 4
Column2=[ImpCode], 4, 4
Column3=[Geometria], 4, 4
Column4=[Dimensioni], 12, 50
Column5=[Pellicola], 4, 4
Column6=[Materiale], 4, 4
Column7=[Tipo], 4, 4
Column8=[Attacco], 4, 4
Column9=[Ordinanza], 12, 50
Column10=[Fabbricazione], 12, 16
Column11=[Figura], 12, 16
Column12=[Stato], 4, 4
Column13=[CDS], 5, 2
Column14=[Installazione], 12, 16
Column15=[Fabbricante], 4, 4
Column16=[Autorizzazione], 12, 16
Column17=[Fornitore], 4, 4
Column18=[Rilevamento], 12, 16
Column19=[Note], -1, 0
Column20=[NoteDt], -1, 0
Column21=[NoteRev], 12, 200
Column22=[Posa], 12, 16
Column23=[Ente], 4, 4

[DLG:IDD_TEST_DIALOG]
Type=1
Class=CTestDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1342243853

[CLS:CTestDialog]
Type=0
HeaderFile=TestDialog.h
ImplementationFile=TestDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTestDialog

[DLG:IDD_GFX_FORMATCOL_ITA]
Type=1
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

[DLG:IDD_GFX_CUSTOMIZECOL_ITA]
Type=1
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

[DLG:IDD_GFXLIST_FORM (Italian (Italy))]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST1,SysListView32,1342243853

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

[DLG:IDD_TEST_DIALOG (Italian (Italy))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1342243853

[DLG:IDD_GFX_FORMATCOL_ITA (Italian (Italy))]
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

[DLG:IDD_GFX_CUSTOMIZECOL_ITA (Italian (Italy))]
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

[TB:IDR_MAINFRAME (Italian (Italy))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_FILE_PRINT
Command9=ID_APP_ABOUT
Command10=ID_TESTCAT
Command11=ID_TRYBITMAP1
Command12=ID_TRYBITMAP2
Command13=ID_BLENDBMP
Command14=ID_DRAGGABLECOL
Command15=ID_GRIDH
Command16=ID_GRIDV
Command17=ID_TESTDAO
CommandCount=17

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
Command13=ID_ADDANITEM
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_CUSTOMHEADER
Command17=ID_FORMATHEADER
Command18=ID_AUTOPREVIEW
Command19=ID_APP_ABOUT
CommandCount=19

