# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TestTipDay - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TestTipDay - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TestTipDay - Win32 Release" && "$(CFG)" !=\
 "TestTipDay - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestTipDay.mak" CFG="TestTipDay - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestTipDay - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestTipDay - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "TestTipDay - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\TestTipDay.exe"

CLEAN : 
	-@erase ".\Release\TestTipDay.exe"
	-@erase ".\Release\TestTipDay.obj"
	-@erase ".\Release\TestTipDay.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\TestTipDayDoc.obj"
	-@erase ".\Release\TestTipDayView.obj"
	-@erase ".\Release\TestTipDay.res"
	-@erase ".\Release\TipDlg.obj"
	-@erase ".\Release\SplitPath.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/TestTipDay.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x100c /d "NDEBUG"
# ADD RSC /l 0x100c /d "NDEBUG"
RSC_PROJ=/l 0x100c /fo"$(INTDIR)/TestTipDay.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TestTipDay.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/TestTipDay.pdb" /machine:I386 /out:"$(OUTDIR)/TestTipDay.exe" 
LINK32_OBJS= \
	".\Release\TestTipDay.obj" \
	".\Release\StdAfx.obj" \
	".\Release\MainFrm.obj" \
	".\Release\TestTipDayDoc.obj" \
	".\Release\TestTipDayView.obj" \
	".\Release\TipDlg.obj" \
	".\Release\SplitPath.obj" \
	".\Release\TestTipDay.res"

"$(OUTDIR)\TestTipDay.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestTipDay - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\TestTipDay.exe"

CLEAN : 
	-@erase ".\Debug\TestTipDay.exe"
	-@erase ".\Debug\TestTipDay.obj"
	-@erase ".\Debug\TestTipDay.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\TestTipDayDoc.obj"
	-@erase ".\Debug\TestTipDayView.obj"
	-@erase ".\Debug\TestTipDay.res"
	-@erase ".\Debug\TipDlg.obj"
	-@erase ".\Debug\SplitPath.obj"
	-@erase ".\Debug\TestTipDay.ilk"
	-@erase ".\Debug\TestTipDay.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/TestTipDay.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x100c /d "_DEBUG"
# ADD RSC /l 0x100c /d "_DEBUG"
RSC_PROJ=/l 0x100c /fo"$(INTDIR)/TestTipDay.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TestTipDay.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/TestTipDay.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/TestTipDay.exe" 
LINK32_OBJS= \
	".\Debug\TestTipDay.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\MainFrm.obj" \
	".\Debug\TestTipDayDoc.obj" \
	".\Debug\TestTipDayView.obj" \
	".\Debug\TipDlg.obj" \
	".\Debug\SplitPath.obj" \
	".\Debug\TestTipDay.res"

"$(OUTDIR)\TestTipDay.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "TestTipDay - Win32 Release"
# Name "TestTipDay - Win32 Debug"

!IF  "$(CFG)" == "TestTipDay - Win32 Release"

!ELSEIF  "$(CFG)" == "TestTipDay - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "TestTipDay - Win32 Release"

!ELSEIF  "$(CFG)" == "TestTipDay - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TestTipDay.cpp
DEP_CPP_TESTT=\
	".\StdAfx.h"\
	".\TestTipDay.h"\
	".\MainFrm.h"\
	".\TestTipDayDoc.h"\
	".\TestTipDayView.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TestTipDay.obj" : $(SOURCE) $(DEP_CPP_TESTT) "$(INTDIR)"\
 "$(INTDIR)\TestTipDay.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TestTipDay - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/TestTipDay.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TestTipDay.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TestTipDay - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/TestTipDay.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TestTipDay.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\TestTipDay.h"\
	".\MainFrm.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TestTipDay.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TestTipDayDoc.cpp
DEP_CPP_TESTTI=\
	".\StdAfx.h"\
	".\TestTipDay.h"\
	".\TestTipDayDoc.h"\
	

"$(INTDIR)\TestTipDayDoc.obj" : $(SOURCE) $(DEP_CPP_TESTTI) "$(INTDIR)"\
 "$(INTDIR)\TestTipDay.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TestTipDayView.cpp
DEP_CPP_TESTTIP=\
	".\StdAfx.h"\
	".\TestTipDay.h"\
	".\TestTipDayDoc.h"\
	".\TestTipDayView.h"\
	

"$(INTDIR)\TestTipDayView.obj" : $(SOURCE) $(DEP_CPP_TESTTIP) "$(INTDIR)"\
 "$(INTDIR)\TestTipDay.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TestTipDay.rc
DEP_RSC_TESTTIPD=\
	".\res\TestTipDayDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\TestTipDay.ico"\
	".\res\litebulb.bmp"\
	".\res\TestTipDay.rc2"\
	

"$(INTDIR)\TestTipDay.res" : $(SOURCE) $(DEP_RSC_TESTTIPD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TipDlg.cpp
DEP_CPP_TIPDL=\
	".\StdAfx.h"\
	".\SplitPath.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\TestTipDay.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SplitPath.cpp
DEP_CPP_SPLIT=\
	".\StdAfx.h"\
	".\SplitPath.h"\
	

"$(INTDIR)\SplitPath.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\TestTipDay.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section TestTipDay : {56525CEB-B9F8-11CF-BF49-00A02472F21C}
# 	0:8:TipDlg.h:e:\MSDEV\Projects\Tip of the Day\TestTipDay\TipDlg.h
# 	0:10:TipDlg.cpp:e:\MSDEV\Projects\Tip of the Day\TestTipDay\TipDlg.cpp
# 	1:17:CG_IDS_DIDYOUKNOW:106
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:105
# 	1:18:CG_IDS_TIPOFTHEDAY:104
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:109
# 	1:19:CG_IDP_FILE_CORRUPT:108
# 	1:7:IDD_TIP:103
# 	1:13:IDB_LIGHTBULB:102
# 	1:18:CG_IDS_FILE_ABSENT:107
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:  
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
################################################################################
