; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRgnButton
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CRgnedButton.h"

ClassCount=3
Class1=CCRgnedButtonApp
Class2=CCRgnedButtonDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Class3=CRgnButton
Resource2=IDD_CRGNEDBUTTON_DIALOG
Resource3=IDD_CRGNEDBUTTON_DIALOG (English (U.S.))

[CLS:CCRgnedButtonApp]
Type=0
HeaderFile=CRgnedButton.h
ImplementationFile=CRgnedButton.cpp
Filter=N

[CLS:CCRgnedButtonDlg]
Type=0
HeaderFile=CRgnedButtonDlg.h
ImplementationFile=CRgnedButtonDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON1



[DLG:IDD_CRGNEDBUTTON_DIALOG]
Type=1
Class=CCRgnedButtonDlg
ControlCount=5
Control1=IDC_BUTTON2,button,1342242816
Control2=IDC_BUTTON3,button,1342242816
Control3=IDC_RADIO1,button,1342177289
Control4=IDC_SLIDER1,msctls_trackbar32,1342242840
Control5=IDC_BUTTON1,button,1342242816

[CLS:CRgnButton]
Type=0
HeaderFile=RgnButton.h
ImplementationFile=RgnButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CRgnButton

[DLG:IDD_CRGNEDBUTTON_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_BUTTON2,button,1342242816
Control2=IDC_BUTTON3,button,1342242816
Control3=IDC_RADIO1,button,1342177289
Control4=IDC_SLIDER1,msctls_trackbar32,1342242840
Control5=IDC_BUTTON1,button,1342242816

