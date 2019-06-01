# Microsoft Developer Studio Project File - Name="Tetris" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Tetris - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tetris.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tetris.mak" CFG="Tetris - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tetris - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tetris - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Tetris - Win32 DynRelease" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tetris - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/CGTetris.exe"

!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/CGTetris.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Tetris - Win32 DynRelease"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Tetris__"
# PROP BASE Intermediate_Dir "Tetris__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "DynRelease"
# PROP Intermediate_Dir "DynRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "Tetris - Win32 Release"
# Name "Tetris - Win32 Debug"
# Name "Tetris - Win32 DynRelease"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\CreditStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\dib256.cpp
# End Source File
# Begin Source File

SOURCE=.\dibpal.cpp
# End Source File
# Begin Source File

SOURCE=.\DigiDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectSound.cpp
# End Source File
# Begin Source File

SOURCE=.\GameBoard.cpp
# End Source File
# Begin Source File

SOURCE=.\GameOverDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Language.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MIDI.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PiecePreview.cpp
# End Source File
# Begin Source File

SOURCE=.\PropSheetTab.cpp
# End Source File
# Begin Source File

SOURCE=.\RoundBmpButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RoundButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringRes.rc

!IF  "$(CFG)" == "Tetris - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Tetris - Win32 DynRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tetris.cpp
# End Source File
# Begin Source File

SOURCE=.\Tetris.rc
# End Source File
# Begin Source File

SOURCE=.\TetrisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VolumeCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BitmapDialog.h
# End Source File
# Begin Source File

SOURCE=.\BitmapPropPage.h
# End Source File
# Begin Source File

SOURCE=.\BitmapPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\CreditStatic.h
# End Source File
# Begin Source File

SOURCE=.\dib256.h
# End Source File
# Begin Source File

SOURCE=.\dibpal.h
# End Source File
# Begin Source File

SOURCE=.\DigiDisplay.h
# End Source File
# Begin Source File

SOURCE=.\DirectSound.h
# End Source File
# Begin Source File

SOURCE=.\GameBoard.h
# End Source File
# Begin Source File

SOURCE=.\GameOverDlg.h
# End Source File
# Begin Source File

SOURCE=.\HelpDlg.h
# End Source File
# Begin Source File

SOURCE=.\Language.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\MIDI.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Piece.h
# End Source File
# Begin Source File

SOURCE=.\PiecePreview.h
# End Source File
# Begin Source File

SOURCE=.\PropSheetTab.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoundBmpButton.h
# End Source File
# Begin Source File

SOURCE=.\RoundButton.h
# End Source File
# Begin Source File

SOURCE=.\ScoreDlg.h
# End Source File
# Begin Source File

SOURCE=.\SplashWnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringRes.h
# End Source File
# Begin Source File

SOURCE=.\Tetris.h
# End Source File
# Begin Source File

SOURCE=.\TetrisDlg.h
# End Source File
# Begin Source File

SOURCE=.\VolumeCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\boom_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_10.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_2.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_4.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_5.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_6.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_7.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_8.ico
# End Source File
# Begin Source File

SOURCE=.\res\boom_9.ico
# End Source File
# Begin Source File

SOURCE=.\res\bumm_7.ico
# End Source File
# Begin Source File

SOURCE=.\res\GameOver.wav
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\kalinka.mid
# End Source File
# Begin Source File

SOURCE=.\res\Kalinka.wav
# End Source File
# Begin Source File

SOURCE=.\res\Key.wav
# End Source File
# Begin Source File

SOURCE=.\res\Keyboard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LevelWarp.wav
# End Source File
# Begin Source File

SOURCE=.\res\LineComplete.wav
# End Source File
# Begin Source File

SOURCE=.\res\moveleft.ico
# End Source File
# Begin Source File

SOURCE=.\res\moverigh.ico
# End Source File
# Begin Source File

SOURCE=.\res\Paragraph.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Place.wav
# End Source File
# Begin Source File

SOURCE=.\res\place1.ico
# End Source File
# Begin Source File

SOURCE=.\res\RedPlace.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shield.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Spfairy.mid
# End Source File
# Begin Source File

SOURCE=.\res\Splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tetris.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tetris.rc2
# End Source File
# Begin Source File

SOURCE=.\res\windof.mid
# End Source File
# End Group
# End Target
# End Project
