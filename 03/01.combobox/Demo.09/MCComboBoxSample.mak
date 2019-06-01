# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MCComboBoxSample - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MCComboBoxSample - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "MCComboBoxSample - Win32 Release" && "$(CFG)" !=\
 "MCComboBoxSample - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MCComboBoxSample.mak" CFG="MCComboBoxSample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MCComboBoxSample - Win32 Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "MCComboBoxSample - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MCComboBoxSample - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MCComboBoxSample - Win32 Release"

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

ALL : "$(OUTDIR)\MCComboBoxSample.exe"

CLEAN : 
	-@erase ".\Release\MCComboBoxSample.exe"
	-@erase ".\Release\MCComboBoxSampleDlg.obj"
	-@erase ".\Release\MCComboBoxSample.pch"
	-@erase ".\Release\MultiColumnComboBox.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MCComboBoxSample.obj"
	-@erase ".\Release\MCComboBoxSample.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCComboBoxSample.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MCComboBoxSample.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MCComboBoxSample.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MCComboBoxSample.pdb" /machine:I386\
 /out:"$(OUTDIR)/MCComboBoxSample.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MCComboBoxSampleDlg.obj" \
	"$(INTDIR)/MultiColumnComboBox.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MCComboBoxSample.obj" \
	"$(INTDIR)/MCComboBoxSample.res"

"$(OUTDIR)\MCComboBoxSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MCComboBoxSample - Win32 Debug"

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

ALL : "$(OUTDIR)\MCComboBoxSample.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\MCComboBoxSample.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\MCComboBoxSample.exe"
	-@erase ".\Debug\MCComboBoxSampleDlg.obj"
	-@erase ".\Debug\MultiColumnComboBox.obj"
	-@erase ".\Debug\MCComboBoxSample.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MCComboBoxSample.res"
	-@erase ".\Debug\MCComboBoxSample.ilk"
	-@erase ".\Debug\MCComboBoxSample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCComboBoxSample.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MCComboBoxSample.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MCComboBoxSample.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MCComboBoxSample.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/MCComboBoxSample.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MCComboBoxSampleDlg.obj" \
	"$(INTDIR)/MultiColumnComboBox.obj" \
	"$(INTDIR)/MCComboBoxSample.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MCComboBoxSample.res"

"$(OUTDIR)\MCComboBoxSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MCComboBoxSample - Win32 Release"
# Name "MCComboBoxSample - Win32 Debug"

!IF  "$(CFG)" == "MCComboBoxSample - Win32 Release"

!ELSEIF  "$(CFG)" == "MCComboBoxSample - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MCComboBoxSample - Win32 Release"

!ELSEIF  "$(CFG)" == "MCComboBoxSample - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MCComboBoxSample.cpp
DEP_CPP_MCCOM=\
	".\StdAfx.h"\
	".\MCComboBoxSample.h"\
	".\MCComboBoxSampleDlg.h"\
	".\MultiColumnComboBox.h"\
	

"$(INTDIR)\MCComboBoxSample.obj" : $(SOURCE) $(DEP_CPP_MCCOM) "$(INTDIR)"\
 "$(INTDIR)\MCComboBoxSample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MCComboBoxSampleDlg.cpp
DEP_CPP_MCCOMB=\
	".\StdAfx.h"\
	".\MultiColumnComboBox.h"\
	".\MCComboBoxSample.h"\
	".\MCComboBoxSampleDlg.h"\
	

"$(INTDIR)\MCComboBoxSampleDlg.obj" : $(SOURCE) $(DEP_CPP_MCCOMB) "$(INTDIR)"\
 "$(INTDIR)\MCComboBoxSample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MCComboBoxSample - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCComboBoxSample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MCComboBoxSample.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MCComboBoxSample - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCComboBoxSample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MCComboBoxSample.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MCComboBoxSample.rc
DEP_RSC_MCCOMBO=\
	".\res\MCComboBoxSample.ico"\
	".\res\MCComboBoxSample.rc2"\
	

"$(INTDIR)\MCComboBoxSample.res" : $(SOURCE) $(DEP_RSC_MCCOMBO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MultiColumnComboBox.cpp

!IF  "$(CFG)" == "MCComboBoxSample - Win32 Release"

DEP_CPP_MULTI=\
	".\StdAfx.h"\
	".\MultiColumnComboBox.h"\
	

"$(INTDIR)\MultiColumnComboBox.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 "$(INTDIR)\MCComboBoxSample.pch"


!ELSEIF  "$(CFG)" == "MCComboBoxSample - Win32 Debug"

DEP_CPP_MULTI=\
	".\StdAfx.h"\
	".\MultiColumnComboBox.h"\
	
NODEP_CPP_MULTI=\
	".\m_TotalColumn"\
	

"$(INTDIR)\MultiColumnComboBox.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 "$(INTDIR)\MCComboBoxSample.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
