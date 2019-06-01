; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMRUParamsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MRUComboTest.h"

ClassCount=5
Class1=CMRUComboTestApp
Class2=CMRUComboTestDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMRUComboBox
Resource3=IDD_SET_MRU_PARAMS
Class5=CMRUParamsDlg
Resource4=IDD_MRUCOMBOTEST_DIALOG
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_MRUCOMBOTEST_DIALOG (English (U.S.))
Resource7=IDD_SET_MRU_PARAMS (English (U.S.))

[CLS:CMRUComboTestApp]
Type=0
HeaderFile=MRUComboTest.h
ImplementationFile=MRUComboTest.cpp
Filter=N

[CLS:CMRUComboTestDlg]
Type=0
HeaderFile=MRUComboTestDlg.h
ImplementationFile=MRUComboTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SET_MRU_SIZE

[CLS:CAboutDlg]
Type=0
HeaderFile=MRUComboTestDlg.h
ImplementationFile=MRUComboTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MRUCOMBOTEST_DIALOG]
Type=1
Class=CMRUComboTestDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344471106
Control5=IDC_BROWSE,button,1342373888
Control6=IDC_CLEAR_MRU,button,1342242816
Control7=IDC_CHANGE_MRU,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_FILESIZE,static,1342308352

[CLS:CMRUComboBox]
Type=0
HeaderFile=MRUCombo.h
ImplementationFile=MRUCombo.cpp
BaseClass=CComboBox
Filter=W
LastObject=CMRUComboBox

[DLG:IDD_SET_MRU_PARAMS]
Type=1
Class=CMRUParamsDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_REG_KEY,edit,1350762624
Control3=IDC_STATIC,static,1342308352
Control4=IDC_REG_VALUE,edit,1350762624
Control5=IDC_STATIC,static,1342308352
Control6=IDC_MRU_SIZE,edit,1350762624
Control7=IDC_SPIN1,msctls_updown32,1342177334
Control8=IDOK,button,1342373889
Control9=IDCANCEL,button,1342242816

[CLS:CMRUParamsDlg]
Type=0
HeaderFile=MRUParamsDlg.h
ImplementationFile=MRUParamsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMRUParamsDlg

[DLG:IDD_MRUCOMBOTEST_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344471106
Control5=IDC_BROWSE,button,1342373888
Control6=IDC_CLEAR_MRU,button,1342242816
Control7=IDC_CHANGE_MRU,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_FILESIZE,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SET_MRU_PARAMS (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_REG_KEY,edit,1350762624
Control3=IDC_STATIC,static,1342308352
Control4=IDC_REG_VALUE,edit,1350762624
Control5=IDC_STATIC,static,1342308352
Control6=IDC_MRU_SIZE,edit,1350762624
Control7=IDC_SPIN1,msctls_updown32,1342177334
Control8=IDOK,button,1342373889
Control9=IDCANCEL,button,1342242816

