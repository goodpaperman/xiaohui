# Microsoft Developer Studio Project File - Name="Demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=Demo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Demo.mak" CFG="Demo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Demo - Win32 Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "Demo - Win32 Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "Demo - Win32 (x86) Debug" (based on "Win32 (x86) Application")
!MESSAGE "Demo - Win32 (x86) Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Demo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaRel"
# PROP BASE Intermediate_Dir "AlphaRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaRel"
# PROP Intermediate_Dir "AlphaRel"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /Gt0 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaDbg"
# PROP BASE Intermediate_Dir "AlphaDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaDbg"
# PROP Intermediate_Dir "AlphaDbg"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /Gt0 /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /debug /machine:ALPHA

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

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
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

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
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /machine:IX86

!ENDIF 

# Begin Target

# Name "Demo - Win32 Release"
# Name "Demo - Win32 Debug"
# Name "Demo - Win32 (x86) Debug"
# Name "Demo - Win32 (x86) Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Demo.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Demo.rc
# End Source File
# Begin Source File

SOURCE=.\DemoDoc.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DemoView.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PopupMenu.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TABVIEW.RC
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ViewManager.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WindowManager.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WindowTabCtrl.cpp

!IF  "$(CFG)" == "Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "Demo - Win32 Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Debug"

!ELSEIF  "$(CFG)" == "Demo - Win32 (x86) Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Demo.h
# End Source File
# Begin Source File

SOURCE=.\DemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\DemoView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ViewManager.h
# End Source File
# Begin Source File

SOURCE=.\WindowManager.h
# End Source File
# Begin Source File

SOURCE=.\WindowTabCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\Demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\tabview.bmp
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
