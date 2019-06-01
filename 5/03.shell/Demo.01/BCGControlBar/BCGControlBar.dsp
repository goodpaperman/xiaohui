# Microsoft Developer Studio Project File - Name="BCGControlBar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BCGControlBar - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBar.mak" CFG="BCGControlBar - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGControlBar - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BCGControlBar - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BCGControlBar - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BCGControlBar - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/BCG/BCGControlBar", TWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGControlBar - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_BCGCONTROLBAR_" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "BCGControlBar - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_BCGCONTROLBAR_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin/BCGControlBarD.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGControlBar - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGControlBar___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "BCGControlBar___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "UnicodeDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_BCGCONTROLBAR_" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_BCGCONTROLBAR_" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\lib/BCGControlBarD.dll" /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin/BCGControlBarUD.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGControlBar - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGControlBar___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "BCGControlBar___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "UnicodeRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_BCGCONTROLBAR_" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_BCGCONTROLBAR_" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\bin/BCGControlBarU.dll"

!ENDIF 

# Begin Target

# Name "BCGControlBar - Win32 Release"
# Name "BCGControlBar - Win32 Debug"
# Name "BCGControlBar - Win32 Unicode Debug"
# Name "BCGControlBar - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGContextMenuManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGControlBar.rc
# End Source File
# Begin Source File

SOURCE=.\BCGExCheckList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGKeyboardManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGMainClientAreaWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGMDIFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGMouseManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGOleIPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPopupMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarComboBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropSource.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolBarImages.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarMenuButtonsButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarSystemMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonsList.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonsTextList.cpp
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomize.cpp
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomizePages.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.CPP
# End Source File
# Begin Source File

SOURCE=.\ImageEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageHash.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagePaintArea.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyAssign.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyboardPage.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuHash.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MousePage.cpp
# End Source File
# Begin Source File

SOURCE=.\PaletteCommandFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolbarNameDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGContextMenuManager.h
# End Source File
# Begin Source File

SOURCE=.\BCGExCheckList.h
# End Source File
# Begin Source File

SOURCE=.\BCGFrameImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCGFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCGKeyboardManager.h
# End Source File
# Begin Source File

SOURCE=.\bcglocalres.h
# End Source File
# Begin Source File

SOURCE=.\BCGMainClientAreaWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCGMDIFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCGMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGMouseManager.h
# End Source File
# Begin Source File

SOURCE=.\BCGOleIPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCGPopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\BCGPopupMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarComboBoxButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropSource.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolBarImages.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarMenuButtonsButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarSystemMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\ButtonAppearanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\ButtonsList.h
# End Source File
# Begin Source File

SOURCE=.\ButtonsTextList.h
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomize.h
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomizePages.h
# End Source File
# Begin Source File

SOURCE=.\ColorSelector.h
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=.\ImageEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageHash.h
# End Source File
# Begin Source File

SOURCE=.\ImagePaintArea.h
# End Source File
# Begin Source File

SOURCE=.\KeyAssign.h
# End Source File
# Begin Source File

SOURCE=.\KeyboardPage.h
# End Source File
# Begin Source File

SOURCE=.\KeyHelper.h
# End Source File
# Begin Source File

SOURCE=.\MenuHash.h
# End Source File
# Begin Source File

SOURCE=.\MenuPage.h
# End Source File
# Begin Source File

SOURCE=.\MousePage.h
# End Source File
# Begin Source File

SOURCE=.\PaletteCommandFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolbarNameDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arrows.bmp
# End Source File
# Begin Source File

SOURCE=.\bcgbarres.h
# End Source File
# Begin Source File

SOURCE=.\res\BCGControlBar.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\color.cur
# End Source File
# Begin Source File

SOURCE=.\res\copy.cur
# End Source File
# Begin Source File

SOURCE=.\res\delete.cur
# End Source File
# Begin Source File

SOURCE=.\res\ellipse.cur
# End Source File
# Begin Source File

SOURCE=.\res\fill.cur
# End Source File
# Begin Source File

SOURCE=.\res\help.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line.cur
# End Source File
# Begin Source File

SOURCE=.\res\menuimg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\move.cur
# End Source File
# Begin Source File

SOURCE=.\res\palette.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pen.cur
# End Source File
# Begin Source File

SOURCE=.\res\rect.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
