# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ColorSpace - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ColorSpace - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ColorSpace - Win32 Release" && "$(CFG)" !=\
 "ColorSpace - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ColorSpace.mak" CFG="ColorSpace - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ColorSpace - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ColorSpace - Win32 Debug" (based on "Win32 (x86) Application")
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
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ColorSpace - Win32 Release"

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

ALL : "$(OUTDIR)\ColorSpace.exe"

CLEAN : 
	-@erase "$(INTDIR)\ColorPickerDlg.obj"
	-@erase "$(INTDIR)\ColorSpace.obj"
	-@erase "$(INTDIR)\ColorSpace.pch"
	-@erase "$(INTDIR)\ColorSpace.res"
	-@erase "$(INTDIR)\ColorSpaceDoc.obj"
	-@erase "$(INTDIR)\ColorSpaceView.obj"
	-@erase "$(INTDIR)\Common.obj"
	-@erase "$(INTDIR)\DIB.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\ColorSpace.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ColorSpace.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ColorSpace.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ColorSpace.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/ColorSpace.pdb" /machine:I386 /out:"$(OUTDIR)/ColorSpace.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ColorPickerDlg.obj" \
	"$(INTDIR)\ColorSpace.obj" \
	"$(INTDIR)\ColorSpace.res" \
	"$(INTDIR)\ColorSpaceDoc.obj" \
	"$(INTDIR)\ColorSpaceView.obj" \
	"$(INTDIR)\Common.obj" \
	"$(INTDIR)\DIB.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ColorSpace.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ColorSpace - Win32 Debug"

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

ALL : "$(OUTDIR)\ColorSpace.exe"

CLEAN : 
	-@erase "$(INTDIR)\ColorPickerDlg.obj"
	-@erase "$(INTDIR)\ColorSpace.obj"
	-@erase "$(INTDIR)\ColorSpace.pch"
	-@erase "$(INTDIR)\ColorSpace.res"
	-@erase "$(INTDIR)\ColorSpaceDoc.obj"
	-@erase "$(INTDIR)\ColorSpaceView.obj"
	-@erase "$(INTDIR)\Common.obj"
	-@erase "$(INTDIR)\DIB.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ColorSpace.exe"
	-@erase "$(OUTDIR)\ColorSpace.ilk"
	-@erase "$(OUTDIR)\ColorSpace.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ColorSpace.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ColorSpace.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ColorSpace.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/ColorSpace.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/ColorSpace.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ColorPickerDlg.obj" \
	"$(INTDIR)\ColorSpace.obj" \
	"$(INTDIR)\ColorSpace.res" \
	"$(INTDIR)\ColorSpaceDoc.obj" \
	"$(INTDIR)\ColorSpaceView.obj" \
	"$(INTDIR)\Common.obj" \
	"$(INTDIR)\DIB.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ColorSpace.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ColorSpace - Win32 Release"
# Name "ColorSpace - Win32 Debug"

!IF  "$(CFG)" == "ColorSpace - Win32 Release"

!ELSEIF  "$(CFG)" == "ColorSpace - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ColorSpace - Win32 Release"

!ELSEIF  "$(CFG)" == "ColorSpace - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorSpace.cpp
DEP_CPP_COLOR=\
	".\ColorSpace.h"\
	".\ColorSpaceDoc.h"\
	".\ColorSpaceView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ColorSpace.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ColorSpace - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ColorSpace.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ColorSpace.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ColorSpace - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ColorSpace.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ColorSpace.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\ColorSpace.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorSpaceDoc.cpp
DEP_CPP_COLORS=\
	".\ColorSpace.h"\
	".\ColorSpaceDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ColorSpaceDoc.obj" : $(SOURCE) $(DEP_CPP_COLORS) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorSpaceView.cpp
DEP_CPP_COLORSP=\
	".\ColorPickerDlg.h"\
	".\ColorSpace.h"\
	".\ColorSpaceDoc.h"\
	".\ColorSpaceView.h"\
	".\Common.h"\
	".\DIB.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ColorSpaceView.obj" : $(SOURCE) $(DEP_CPP_COLORSP) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorSpace.rc
DEP_RSC_COLORSPA=\
	".\res\ColorSpace.ico"\
	".\res\ColorSpace.rc2"\
	".\res\ColorSpaceDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\ColorSpace.res" : $(SOURCE) $(DEP_RSC_COLORSPA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIB.cpp
DEP_CPP_DIB_C=\
	".\DIB.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DIB.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Common.cpp
DEP_CPP_COMMO=\
	".\Common.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorPickerDlg.cpp
DEP_CPP_COLORP=\
	".\ColorPickerDlg.h"\
	".\ColorSpace.h"\
	".\Common.h"\
	".\DIB.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ColorPickerDlg.obj" : $(SOURCE) $(DEP_CPP_COLORP) "$(INTDIR)"\
 "$(INTDIR)\ColorSpace.pch"


# End Source File
# End Target
# End Project
################################################################################
