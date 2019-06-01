; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAutoCompletionDlg
LastTemplate=CComboBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AutoCompletion.h"

ClassCount=3
Class1=CAutoCompletionApp
Class2=CAutoCompletionDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Class3=CAutoCompletionComboBox
Resource2=IDD_AUTOCOMPLETION_DIALOG
Resource3=IDD_AUTOCOMPLETION_DIALOG (English (U.S.))

[CLS:CAutoCompletionApp]
Type=0
HeaderFile=AutoCompletion.h
ImplementationFile=AutoCompletion.cpp
Filter=N

[CLS:CAutoCompletionDlg]
Type=0
HeaderFile=AutoCompletionDlg.h
ImplementationFile=AutoCompletionDlg.cpp
Filter=D
LastObject=IDC_COMBO1
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_AUTOCOMPLETION_DIALOG]
Type=1
Class=CAutoCompletionDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344340226

[CLS:CAutoCompletionComboBox]
Type=0
HeaderFile=AutoCompletionComboBox.h
ImplementationFile=AutoCompletionComboBox.cpp
BaseClass=CComboBox
Filter=W
LastObject=CAutoCompletionComboBox

[DLG:IDD_AUTOCOMPLETION_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344340226

