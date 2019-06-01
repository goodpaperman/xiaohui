# Microsoft Developer Studio Project File - Name="Koules" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Koules - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Koules.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Koules.mak" CFG="Koules - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Koules - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Koules - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Koules - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fr /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Koules - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Koules - Win32 Release"
# Name "Koules - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Cmap.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectDrawApp.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectDrawWin.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Framebuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Gameplan.cpp
# End Source File
# Begin Source File

SOURCE=.\Headers.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Init.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\input.cpp
# End Source File
# Begin Source File

SOURCE=.\Ksrc\interface.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Intro.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Koules.cpp
# End Source File
# Begin Source File

SOURCE=.\KoulesApp.cpp
# End Source File
# Begin Source File

SOURCE=.\KoulesWin.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Menu.cpp
# End Source File
# Begin Source File

SOURCE=.\ksrc\Rcfiles.cpp
# End Source File
# Begin Source File

SOURCE=.\Ksrc\sound.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\DirectDrawApp.h
# End Source File
# Begin Source File

SOURCE=.\DirectDrawWin.h
# End Source File
# Begin Source File

SOURCE=.\KSRC\framebuffer.h
# End Source File
# Begin Source File

SOURCE=.\Headers.h
# End Source File
# Begin Source File

SOURCE=.\KSRC\Input.h
# End Source File
# Begin Source File

SOURCE=.\KSRC\interface.h
# End Source File
# Begin Source File

SOURCE=.\KSRC\Koules.h
# End Source File
# Begin Source File

SOURCE=.\KoulesApp.h
# End Source File
# Begin Source File

SOURCE=.\KoulesWin.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Ksrc\sound.h
# End Source File
# Begin Source File

SOURCE=.\KSRC\Text.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\4.bmp
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\Colize.raw
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\Creator1.raw
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\Creator2.raw
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\Destroy1.raw
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\Destroy2.raw
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\End.raw
# End Source File
# Begin Source File

SOURCE=".\Hand-m.cur"
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\kou.msk
# End Source File
# Begin Source File

SOURCE=.\koules.bmp
# End Source File
# Begin Source File

SOURCE=.\Koules.rc
# End Source File
# Begin Source File

SOURCE=.\Ksrc\Sounds\Start.raw
# End Source File
# Begin Source File

SOURCE=.\Zm
# End Source File
# End Group
# End Target
# End Project
