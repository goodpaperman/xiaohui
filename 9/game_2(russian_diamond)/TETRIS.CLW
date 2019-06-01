; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHelpDlg
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tetris.h"
LastPage=0

ClassCount=17
Class1=CAboutDlg
Class2=CDigiDisplay
Class3=CGameBoard
Class4=CMainDlg
Class5=COptionsDlg
Class6=CPiecePreview
Class7=CTetrisApp
Class8=CTetrisDlg

ResourceCount=7
Resource1=IDD_Help
Resource2=IDD_GameOverDlg
Class9=CMusicNotifier
Class10=CMusicPlayer
Resource3=IDD_About
Class11=CScoreDlg
Resource4=IDD_ScoreDlg
Class12=CGameOverDlg
Class13=CBitmapPropSheet
Class14=CBitmapPropPage
Class15=CPropSheetTab
Resource5=IDD_TETRIS_DIALOG
Class16=CVolumeCtrl
Resource6=IDD_VolumeCtrl
Class17=CHelpDlg
Resource7=IDD_OptionsDlg

[CLS:CAboutDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=idWC

[CLS:CDigiDisplay]
Type=0
BaseClass=CStatic
HeaderFile=DigiDisplay.h
ImplementationFile=DigiDisplay.cpp
LastObject=CDigiDisplay

[CLS:CGameBoard]
Type=0
BaseClass=CWnd
HeaderFile=GameBoard.h
ImplementationFile=GameBoard.cpp
Filter=W
VirtualFilter=WC
LastObject=CGameBoard

[CLS:CMainDlg]
Type=0
BaseClass=CBitmapPropSheet
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
LastObject=CMainDlg
Filter=D

[CLS:COptionsDlg]
Type=0
BaseClass=CBitmapPropPage
HeaderFile=OptionsDlg.h
ImplementationFile=OptionsDlg.cpp
Filter=D
VirtualFilter=idWC
LastObject=COptionsDlg

[CLS:CPiecePreview]
Type=0
BaseClass=CWnd
HeaderFile=PiecePreview.h
ImplementationFile=PiecePreview.cpp
Filter=W
VirtualFilter=WC
LastObject=IDC_Volume

[CLS:CTetrisApp]
Type=0
BaseClass=CWinApp
HeaderFile=Tetris.h
ImplementationFile=Tetris.cpp

[CLS:CTetrisDlg]
Type=0
BaseClass=CBitmapPropPage
HeaderFile=TetrisDlg.h
ImplementationFile=TetrisDlg.cpp
LastObject=CTetrisDlg
Filter=D
VirtualFilter=idWC

[DLG:IDD_About]
Type=1
Class=CAboutDlg
ControlCount=1
Control1=IDC_Credits,static,1342308352

[DLG:IDD_OptionsDlg]
Type=1
Class=COptionsDlg
ControlCount=15
Control1=IDC_EditWidth,edit,1350639744
Control2=IDC_SpinWidth,msctls_updown32,1342177463
Control3=IDC_EditHeight,edit,1350639744
Control4=IDC_SpinHeight,msctls_updown32,1342177463
Control5=IDC_CheckGrid,button,1342242819
Control6=IDC_ExtendedFigureSet,button,1342242819
Control7=IDC_TxtSoundCard,static,1342308352
Control8=IDC_ChkSound,button,1342242819
Control9=IDC_ChkMusic,button,1342242819
Control10=IDC_MusicBox,combobox,1344339971
Control11=IDC_Splash,button,1342242816
Control12=IDC_GroupBoard,button,1342177287
Control13=IDC_TxtSquareWidth,static,1342308352
Control14=IDC_TxtSquareHeight,static,1342308352
Control15=IDC_GroupSound,button,1342177287

[DLG:IDD_TETRIS_DIALOG]
Type=1
Class=CTetrisDlg
ControlCount=14
Control1=IDC_BtnStart,button,1342242816
Control2=IDC_Pause,button,1342242816
Control3=IDC_GameBoard,TetrisGameBoard,1350631424
Control4=IDC_TxtScore,static,1342308352
Control5=IDC_TxtLines,static,1342308352
Control6=IDC_TxtLevel,static,1342308352
Control7=IDC_PiecePreview,TetrisPreview,1350631424
Control8=IDC_Score,static,1342312450
Control9=IDC_Lines,static,1342312450
Control10=IDC_Level,static,1342312450
Control11=IDC_MoveLeft,button,1342242816
Control12=IDC_MoveRight,button,1342242816
Control13=IDC_Place,button,1342242816
Control14=IDC_Rotate,button,1342242816

[CLS:CMusicNotifier]
Type=0
HeaderFile=Sound.h
ImplementationFile=Sound.cpp
BaseClass=generic CWnd
Filter=W
LastObject=CMusicNotifier

[CLS:CMusicPlayer]
Type=0
HeaderFile=Sound.h
ImplementationFile=Sound.cpp
BaseClass=CWinThread
Filter=N
LastObject=CMusicPlayer
VirtualFilter=TC

[CLS:CScoreDlg]
Type=0
HeaderFile=ScoreDlg.h
ImplementationFile=ScoreDlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CScoreDlg
VirtualFilter=idWC

[DLG:IDD_ScoreDlg]
Type=1
Class=CScoreDlg
ControlCount=1
Control1=IDC_ListScore,SysListView32,1350664965

[DLG:IDD_GameOverDlg]
Type=1
Class=CGameOverDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_GameOver,static,1342308865

[CLS:CGameOverDlg]
Type=0
HeaderFile=GameOverDlg.h
ImplementationFile=GameOverDlg.cpp
BaseClass=CBitmapDialog
Filter=W
VirtualFilter=dWC
LastObject=CGameOverDlg

[CLS:CBitmapPropSheet]
Type=0
HeaderFile=BitmapPropSheet.h
ImplementationFile=BitmapPropSheet.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC
LastObject=CBitmapPropSheet

[CLS:CBitmapPropPage]
Type=0
HeaderFile=BitmapPropPage.h
ImplementationFile=BitmapPropPage.cpp
BaseClass=CPropertyPage
Filter=W
VirtualFilter=idWC
LastObject=CBitmapPropPage

[CLS:CPropSheetTab]
Type=0
HeaderFile=PropSheetTab.h
ImplementationFile=PropSheetTab.cpp
BaseClass=CTabCtrl
Filter=W
VirtualFilter=UWC
LastObject=CPropSheetTab

[DLG:IDD_VolumeCtrl]
Type=1
Class=CVolumeCtrl
ControlCount=1
Control1=IDC_Volume,msctls_trackbar32,1342242825

[CLS:CVolumeCtrl]
Type=0
HeaderFile=VolumeCtrl.h
ImplementationFile=VolumeCtrl.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVolumeCtrl

[DLG:IDD_Help]
Type=1
Class=CHelpDlg
ControlCount=1
Control1=IDC_Help,static,1342308352

[CLS:CHelpDlg]
Type=0
HeaderFile=HelpDlg.h
ImplementationFile=HelpDlg.cpp
BaseClass=CBitmapPropPage
Filter=D
LastObject=CHelpDlg

