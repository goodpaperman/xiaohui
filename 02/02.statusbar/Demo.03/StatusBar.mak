# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=StatusBar - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to StatusBar - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StatusBar - Win32 Release" && "$(CFG)" !=\
 "StatusBar - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "StatusBar.mak" CFG="StatusBar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StatusBar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StatusBar - Win32 Debug" (based on "Win32 (x86) Application")
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
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "StatusBar - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\StatusBar.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StatusBar.obj"
	-@erase "$(INTDIR)\StatusBar.pch"
	-@erase "$(INTDIR)\StatusBar.res"
	-@erase "$(INTDIR)\StatusBarDoc.obj"
	-@erase "$(INTDIR)\StatusBarView.obj"
	-@erase "$(INTDIR)\StatusEdit.obj"
	-@erase "$(INTDIR)\StatusProgress.obj"
	-@erase "$(INTDIR)\StatusStatic.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\StatusBar.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/StatusBar.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StatusBar.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StatusBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/StatusBar.pdb" /machine:I386 /out:"$(OUTDIR)/StatusBar.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StatusBar.obj" \
	"$(INTDIR)\StatusBar.res" \
	"$(INTDIR)\StatusBarDoc.obj" \
	"$(INTDIR)\StatusBarView.obj" \
	"$(INTDIR)\StatusEdit.obj" \
	"$(INTDIR)\StatusProgress.obj" \
	"$(INTDIR)\StatusStatic.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\StatusBar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StatusBar - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\StatusBar.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StatusBar.obj"
	-@erase "$(INTDIR)\StatusBar.pch"
	-@erase "$(INTDIR)\StatusBar.res"
	-@erase "$(INTDIR)\StatusBarDoc.obj"
	-@erase "$(INTDIR)\StatusBarView.obj"
	-@erase "$(INTDIR)\StatusEdit.obj"
	-@erase "$(INTDIR)\StatusProgress.obj"
	-@erase "$(INTDIR)\StatusStatic.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\StatusBar.exe"
	-@erase "$(OUTDIR)\StatusBar.ilk"
	-@erase "$(OUTDIR)\StatusBar.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/StatusBar.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StatusBar.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StatusBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/StatusBar.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/StatusBar.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StatusBar.obj" \
	"$(INTDIR)\StatusBar.res" \
	"$(INTDIR)\StatusBarDoc.obj" \
	"$(INTDIR)\StatusBarView.obj" \
	"$(INTDIR)\StatusEdit.obj" \
	"$(INTDIR)\StatusProgress.obj" \
	"$(INTDIR)\StatusStatic.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\StatusBar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "StatusBar - Win32 Release"
# Name "StatusBar - Win32 Debug"

!IF  "$(CFG)" == "StatusBar - Win32 Release"

!ELSEIF  "$(CFG)" == "StatusBar - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "StatusBar - Win32 Release"

!ELSEIF  "$(CFG)" == "StatusBar - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusBar.cpp
DEP_CPP_STATU=\
	".\MainFrm.h"\
	".\StatusBar.h"\
	".\StatusBarDoc.h"\
	".\StatusBarView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StatusBar.obj" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "StatusBar - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/StatusBar.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StatusBar.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "StatusBar - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/StatusBar.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StatusBar.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\StatusBar.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusBarDoc.cpp
DEP_CPP_STATUS=\
	".\StatusBar.h"\
	".\StatusBarDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StatusBarDoc.obj" : $(SOURCE) $(DEP_CPP_STATUS) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusBarView.cpp
DEP_CPP_STATUSB=\
	".\StatusBar.h"\
	".\StatusBarDoc.h"\
	".\StatusBarView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StatusBarView.obj" : $(SOURCE) $(DEP_CPP_STATUSB) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusBar.rc
DEP_RSC_STATUSBA=\
	".\res\StatusBar.ico"\
	".\res\StatusBar.rc2"\
	".\res\StatusBarDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\StatusBar.res" : $(SOURCE) $(DEP_RSC_STATUSBA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusEdit.cpp
DEP_CPP_STATUSE=\
	".\StatusControl.h"\
	".\StatusEdit.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StatusEdit.obj" : $(SOURCE) $(DEP_CPP_STATUSE) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusStatic.cpp
DEP_CPP_STATUSS=\
	".\StatusControl.h"\
	".\StatusStatic.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StatusStatic.obj" : $(SOURCE) $(DEP_CPP_STATUSS) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatusProgress.cpp
DEP_CPP_STATUSP=\
	".\StatusControl.h"\
	".\StatusProgress.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StatusProgress.obj" : $(SOURCE) $(DEP_CPP_STATUSP) "$(INTDIR)"\
 "$(INTDIR)\StatusBar.pch"


# End Source File
# End Target
# End Project
################################################################################
