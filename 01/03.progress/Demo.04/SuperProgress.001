# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SuperProgress - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SuperProgress - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "SuperProgress - Win32 Release" && "$(CFG)" !=\
 "SuperProgress - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SuperProgress.mak" CFG="SuperProgress - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SuperProgress - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SuperProgress - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "SuperProgress - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "SuperProgress - Win32 Release"

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

ALL : "$(OUTDIR)\SuperProgress.exe"

CLEAN : 
	-@erase ".\Release\SuperProgress.exe"
	-@erase ".\Release\SuperProgress.obj"
	-@erase ".\Release\SuperProgress.pch"
	-@erase ".\Release\SuperProgressDlg.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\SuperProgress.res"
	-@erase ".\Release\SuperProgressCtrl.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL"\
 /D "_MBCS" /Fp"$(INTDIR)/SuperProgress.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)/SuperProgress.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SuperProgress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SuperProgress.pdb" /machine:I386\
 /out:"$(OUTDIR)/SuperProgress.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SuperProgress.obj" \
	"$(INTDIR)/SuperProgressDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/SuperProgressCtrl.obj" \
	"$(INTDIR)/SuperProgress.res"

"$(OUTDIR)\SuperProgress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperProgress - Win32 Debug"

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

ALL : "$(OUTDIR)\SuperProgress.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\SuperProgress.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\SuperProgress.exe"
	-@erase ".\Debug\SuperProgressDlg.obj"
	-@erase ".\Debug\SuperProgress.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\SuperProgress.res"
	-@erase ".\Debug\SuperProgressCtrl.obj"
	-@erase ".\Debug\SuperProgress.ilk"
	-@erase ".\Debug\SuperProgress.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SuperProgress.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)/SuperProgress.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SuperProgress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SuperProgress.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SuperProgress.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SuperProgressDlg.obj" \
	"$(INTDIR)/SuperProgress.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/SuperProgressCtrl.obj" \
	"$(INTDIR)/SuperProgress.res"

"$(OUTDIR)\SuperProgress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SuperProgress - Win32 Release"
# Name "SuperProgress - Win32 Debug"

!IF  "$(CFG)" == "SuperProgress - Win32 Release"

!ELSEIF  "$(CFG)" == "SuperProgress - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "SuperProgress - Win32 Release"

!ELSEIF  "$(CFG)" == "SuperProgress - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuperProgress.cpp

!IF  "$(CFG)" == "SuperProgress - Win32 Release"

DEP_CPP_SUPER=\
	".\StdAfx.h"\
	".\SuperProgress.h"\
	".\SuperProgressDlg.h"\
	

"$(INTDIR)\SuperProgress.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\SuperProgress.pch"


!ELSEIF  "$(CFG)" == "SuperProgress - Win32 Debug"

DEP_CPP_SUPER=\
	".\StdAfx.h"\
	".\SuperProgress.h"\
	".\SuperProgressDlg.h"\
	
NODEP_CPP_SUPER=\
	".\;"\
	

"$(INTDIR)\SuperProgress.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\SuperProgress.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuperProgressDlg.cpp
DEP_CPP_SUPERP=\
	".\StdAfx.h"\
	".\SuperProgress.h"\
	".\SuperProgressDlg.h"\
	".\SuperProgressCtrl.h"\
	

"$(INTDIR)\SuperProgressDlg.obj" : $(SOURCE) $(DEP_CPP_SUPERP) "$(INTDIR)"\
 "$(INTDIR)\SuperProgress.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "SuperProgress - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL"\
 /D "_MBCS" /Fp"$(INTDIR)/SuperProgress.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SuperProgress.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperProgress - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SuperProgress.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SuperProgress.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuperProgress.rc
DEP_RSC_SUPERPR=\
	".\res\SuperProgress.ico"\
	".\res\progress.bmp"\
	".\res\SuperProgress.rc2"\
	

"$(INTDIR)\SuperProgress.res" : $(SOURCE) $(DEP_RSC_SUPERPR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuperProgressCtrl.cpp
DEP_CPP_SUPERPRO=\
	".\StdAfx.h"\
	".\SuperProgressCtrl.h"\
	

"$(INTDIR)\SuperProgressCtrl.obj" : $(SOURCE) $(DEP_CPP_SUPERPRO) "$(INTDIR)"\
 "$(INTDIR)\SuperProgress.pch"


# End Source File
# End Target
# End Project
################################################################################
