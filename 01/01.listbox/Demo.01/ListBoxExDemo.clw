; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CListBoxExBuddy
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "listboxexdemo.h"
LastPage=0

ClassCount=6
Class1=CInPlaceEdit
Class2=CInPlaceButton
Class3=CListBoxEx
Class4=CListBoxExBuddy
Class5=CListBoxExDemoApp
Class6=CListBoxExDemoDlg

ResourceCount=2
Resource1=IDD_LISTBOXEXDEMO_DIALOG
Resource2=IDD_LISTBOXEXDEMO_DIALOG (English (U.S.))

[CLS:CInPlaceEdit]
Type=0
BaseClass=CEdit
HeaderFile=Include\InPlaceCtrls.h
ImplementationFile=Source\InPlaceCtrls.cpp

[CLS:CInPlaceButton]
Type=0
BaseClass=CButton
HeaderFile=Include\InPlaceCtrls.h
ImplementationFile=Source\InPlaceCtrls.cpp
Filter=W
LastObject=CInPlaceButton

[CLS:CListBoxEx]
Type=0
BaseClass=CDragListBox 
HeaderFile=Include\listboxex.h
ImplementationFile=Source\listboxex.cpp
Filter=W
VirtualFilter=bWC
LastObject=CListBoxEx

[CLS:CListBoxExBuddy]
Type=0
BaseClass=CWnd
HeaderFile=Include\listboxex.h
ImplementationFile=Source\listboxex.cpp
Filter=W
VirtualFilter=WC
LastObject=CListBoxExBuddy

[CLS:CListBoxExDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=ListBoxExDemo.h
ImplementationFile=ListBoxExDemo.cpp

[CLS:CListBoxExDemoDlg]
Type=0
BaseClass=CDialog
HeaderFile=ListBoxExDemoDlg.h
ImplementationFile=ListBoxExDemoDlg.cpp
Filter=D
VirtualFilter=dWC

[DLG:IDD_LISTBOXEXDEMO_DIALOG]
Type=1
Class=CListBoxExDemoDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,listbox,1352728913
Control4=IDC_LISTBUDDY,button,1342242827

[DLG:IDD_LISTBOXEXDEMO_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,listbox,1353778513
Control4=IDC_LISTBUDDY,button,1342242827

