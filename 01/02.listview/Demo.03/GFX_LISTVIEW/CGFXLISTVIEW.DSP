# Microsoft Developer Studio Project File - Name="CGfxListView" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CGfxListView - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CGfxListView.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CGfxListView.mak" CFG="CGfxListView - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CGfxListView - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CGfxListView - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CGfxListView - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CGfxListView - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CGfxListView - Win32 Release"
# Name "CGfxListView - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CGfxListView.cpp
# End Source File
# Begin Source File

SOURCE=.\CGfxListView.rc
# End Source File
# Begin Source File

SOURCE=.\CGfxListViewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxCategoryManager.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxColumnManager.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxCustomizeColumnDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxFormatColumnDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxInCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxInComboEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxInComboList.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxInComboStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxInEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxListTip.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxListView.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CGfxListView.h
# End Source File
# Begin Source File

SOURCE=.\CGfxListViewDoc.h
# End Source File
# Begin Source File

SOURCE=.\GfxCategoryManager.h
# End Source File
# Begin Source File

SOURCE=.\GfxColumnManager.h
# End Source File
# Begin Source File

SOURCE=.\GfxCustomizeColumnDlg.h
# End Source File
# Begin Source File

SOURCE=.\GfxFormatColumnDlg.h
# End Source File
# Begin Source File

SOURCE=.\GfxHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GfxInCombo.h
# End Source File
# Begin Source File

SOURCE=.\GfxInComboEdit.h
# End Source File
# Begin Source File

SOURCE=.\GfxInComboList.h
# End Source File
# Begin Source File

SOURCE=.\GfxInComboStatic.h
# End Source File
# Begin Source File

SOURCE=.\GfxInEdit.h
# End Source File
# Begin Source File

SOURCE=.\GfxListTip.h
# End Source File
# Begin Source File

SOURCE=.\GfxListView.h
# End Source File
# Begin Source File

SOURCE=.\GfxPopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyListView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arancol.bmp
# End Source File
# Begin Source File

SOURCE=.\res\aranlist.bmp
# End Source File
# Begin Source File

SOURCE=.\res\back.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CGfxListView.ico
# End Source File
# Begin Source File

SOURCE=.\res\CGfxListView.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CGfxListViewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\listmenu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section CGfxListView : {A37DE343-2092-11D2-8476-0000B43382FE}
# 	1:17:IDD_GFX_FORMATCOL:103
# 	2:16:Resource Include:resource.h
# 	2:22:GfxFormatColumnDlg.cpp:GfxFormatColumnDlg.cpp
# 	2:20:GfxFormatColumnDlg.h:GfxFormatColumnDlg.h
# 	2:10:ENUM: enum:enum
# 	2:26:CLASS: CGfxFormatColumnDlg:CGfxFormatColumnDlg
# 	2:19:Application Include:CGfxListView.h
# 	2:17:IDD_GFX_FORMATCOL:IDD_GFX_FORMATCOL
# End Section
# Section CGfxListView : {A37DE347-2092-11D2-8476-0000B43382FE}
# 	2:22:CLASS: CGfxInComboList:CGfxInComboList
# 	2:16:GfxInComboList.h:GfxInComboList.h
# 	2:18:GfxInComboList.cpp:GfxInComboList.cpp
# 	2:19:Application Include:CGfxListView.h
# End Section
# Section CGfxListView : {A37DE342-2092-11D2-8476-0000B43382FE}
# 	1:20:IDD_GFX_CUSTOMIZECOL:102
# 	2:16:Resource Include:resource.h
# 	2:29:CLASS: CGfxCustomizeColumnDlg:CGfxCustomizeColumnDlg
# 	2:10:ENUM: enum:enum
# 	2:23:GfxCustomizeColumnDlg.h:GfxCustomizeColumnDlg.h
# 	2:19:Application Include:CGfxListView.h
# 	2:25:GfxCustomizeColumnDlg.cpp:GfxCustomizeColumnDlg.cpp
# 	2:20:IDD_GFX_CUSTOMIZECOL:IDD_GFX_CUSTOMIZECOL
# End Section
# Section CGfxListView : {A37DE346-2092-11D2-8476-0000B43382FE}
# 	2:18:GfxInComboEdit.cpp:GfxInComboEdit.cpp
# 	2:22:CLASS: CGfxInComboEdit:CGfxInComboEdit
# 	2:16:GfxInComboEdit.h:GfxInComboEdit.h
# 	2:19:Application Include:CGfxListView.h
# End Section
# Section CGfxListView : {A37DE341-2092-11D2-8476-0000B43382FE}
# 	2:20:GfxColumnManager.cpp:GfxColumnManager.cpp
# 	2:24:CLASS: CGfxColumnManager:CGfxColumnManager
# 	2:18:GfxColumnManager.h:GfxColumnManager.h
# 	2:19:Application Include:CGfxListView.h
# End Section
# Section CGfxListView : {A37DE345-2092-11D2-8476-0000B43382FE}
# 	2:14:GfxInCombo.cpp:GfxInCombo.cpp
# 	2:12:GfxInCombo.h:GfxInCombo.h
# 	2:18:CLASS: CGfxInCombo:CGfxInCombo
# 	2:19:Application Include:CGfxListView.h
# End Section
# Section CGfxListView : {A37DE340-2092-11D2-8476-0000B43382FE}
# 	2:26:CLASS: CGfxCategoryManager:CGfxCategoryManager
# 	2:22:GfxCategoryManager.cpp:GfxCategoryManager.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:CGfxListView.h
# 	2:20:GfxCategoryManager.h:GfxCategoryManager.h
# End Section
# Section CGfxListView : {A37DE34C-2092-11D2-8476-0000B43382FE}
# 	2:16:GfxPopupMenu.cpp:GfxPopupMenu.cpp
# 	2:14:GfxPopupMenu.h:GfxPopupMenu.h
# 	2:19:Application Include:CGfxListView.h
# 	2:20:CLASS: CGfxPopupMenu:CGfxPopupMenu
# End Section
# Section CGfxListView : {A37DE349-2092-11D2-8476-0000B43382FE}
# 	2:13:GfxInEdit.cpp:GfxInEdit.cpp
# 	2:17:CLASS: CGfxInEdit:CGfxInEdit
# 	2:19:Application Include:CGfxListView.h
# 	2:11:GfxInEdit.h:GfxInEdit.h
# End Section
# Section CGfxListView : {A37DE344-2092-11D2-8476-0000B43382FE}
# 	2:15:GfxHeaderCtrl.h:GfxHeaderCtrl.h
# 	2:17:GfxHeaderCtrl.cpp:GfxHeaderCtrl.cpp
# 	2:21:CLASS: CGfxHeaderCtrl:CGfxHeaderCtrl
# 	2:19:Application Include:CGfxListView.h
# End Section
# Section CGfxListView : {A37DE34B-2092-11D2-8476-0000B43382FE}
# 	2:14:GfxListTip.cpp:GfxListTip.cpp
# 	2:18:CLASS: CGfxListTip:CGfxListTip
# 	2:19:Application Include:CGfxListView.h
# 	2:12:GfxListTip.h:GfxListTip.h
# End Section
# Section CGfxListView : {A37DE348-2092-11D2-8476-0000B43382FE}
# 	2:20:GfxInComboStatic.cpp:GfxInComboStatic.cpp
# 	2:18:GfxInComboStatic.h:GfxInComboStatic.h
# 	2:24:CLASS: CGfxInComboStatic:CGfxInComboStatic
# 	2:19:Application Include:CGfxListView.h
# End Section
