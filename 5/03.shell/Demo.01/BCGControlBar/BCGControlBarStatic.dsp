# Microsoft Developer Studio Project File - Name="BCGControlBarStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BCGControlBarStatic - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBarStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBarStatic.mak" CFG="BCGControlBarStatic - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGControlBarStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BCGControlBarStatic - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGControlBarStatic - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "DebugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\BCGControlBarStaticD.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "UReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\BCGControlBarStaticU.lib"

!ELSEIF  "$(CFG)" == "BCGControlBarStatic - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGControlBarStatic___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "BCGControlBarStatic___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "UDebugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Lib\BCGControlBarStaticD.lib"
# ADD LIB32 /nologo /out:"..\Lib\BCGControlBarStaticUD.lib"

!ENDIF 

# Begin Target

# Name "BCGControlBarStatic - Win32 Release"
# Name "BCGControlBarStatic - Win32 Debug"
# Name "BCGControlBarStatic - Win32 Unicode Release"
# Name "BCGControlBarStatic - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\BCGControlBar\BCGContextMenuManager.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGDockBar.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGExCheckList.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGKeyboardManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGLocalRes.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMainClientAreaWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMDIFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMouseManager.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGOleIPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarComboBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropSource.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBarImages.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButtonsButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarSystemMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsList.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsTextList.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomize.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomizePages.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ColorSelector.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\GLOBALS.CPP
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageHash.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImagePaintArea.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyAssign.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyboardPage.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuHash.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuPage.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MousePage.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\PaletteCommandFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ToolbarNameDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\BCGControlBar\bcgbarres.h
# End Source File
# Begin Source File

SOURCE=.\BCGCB.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGContextMenuManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGControlBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGDockBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGExCheckList.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameImpl.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGKeyboardManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\bcglocalres.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMainClientAreaWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMDIFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMenuBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMouseManager.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGOleIPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGPopupMenuBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBar.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarComboBoxButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropSource.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarDropTarget.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolBarImages.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarMenuButtonsButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\BCGToolbarSystemMenuButton.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonAppearanceDlg.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsList.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ButtonsTextList.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomize.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\CBCGToolbarCustomizePages.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ColorSelector.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageEditDlg.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImageHash.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ImagePaintArea.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyAssign.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyboardPage.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\KeyHelper.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuHash.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MenuPage.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\MousePage.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\PaletteCommandFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\Registry.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\BCGControlBar\ToolbarNameDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
