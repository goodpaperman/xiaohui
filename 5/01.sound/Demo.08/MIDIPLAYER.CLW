; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MidiPlayer.h"

ClassCount=4
Class1=CMidiPlayerApp
Class2=CMidiPlayerDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU1
Class4=CHyperLink
Resource4=IDD_MIDIPLAYER_DIALOG
Resource5=IDD_MIDIPLAYER_DIALOG (Italian (Italy))
Resource6=IDD_ABOUTBOX (Italian (Italy))
Resource7=IDR_MENU1 (Italian (Italy))

[CLS:CMidiPlayerApp]
Type=0
HeaderFile=MidiPlayer.h
ImplementationFile=MidiPlayer.cpp
Filter=N

[CLS:CMidiPlayerDlg]
Type=0
HeaderFile=MidiPlayerDlg.h
ImplementationFile=MidiPlayerDlg.cpp
Filter=D
LastObject=CMidiPlayerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MidiPlayerDlg.h
ImplementationFile=MidiPlayerDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_MAILTO,static,1342308352

[DLG:IDD_MIDIPLAYER_DIALOG]
Type=1
Class=CMidiPlayerDlg
ControlCount=5
Control1=IDC_PROGRESS,msctls_progress32,1350565888
Control2=IDC_PLAY,button,1342242816
Control3=IDC_STOP,button,1342242816
Control4=IDC_STATIC,static,1342177296
Control5=IDOK,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CAboutDlg
Command1=ID_FILE_OPEN
CommandCount=1

[CLS:CHyperLink]
Type=0
HeaderFile=hyperlink.h
ImplementationFile=hyperlink.cpp
BaseClass=CStatic
LastObject=ID_FILE_OPEN

[DLG:IDD_MIDIPLAYER_DIALOG (Italian (Italy))]
Type=1
Class=?
ControlCount=5
Control1=IDC_PROGRESS,msctls_progress32,1350565888
Control2=IDC_PLAY,button,1342242816
Control3=IDC_STOP,button,1342242816
Control4=IDC_STATIC,static,1342177296
Control5=IDOK,button,1342242816

[DLG:IDD_ABOUTBOX (Italian (Italy))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_MAILTO,static,1342308352

[MNU:IDR_MENU1 (Italian (Italy))]
Type=1
Class=?
Command1=ID_FILE_OPEN
CommandCount=1

