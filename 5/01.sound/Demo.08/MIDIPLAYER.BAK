# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MidiPlayer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MidiPlayer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MidiPlayer - Win32 Release" && "$(CFG)" !=\
 "MidiPlayer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MidiPlayer.mak" CFG="MidiPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MidiPlayer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MidiPlayer - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MidiPlayer - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "MidiPlayer - Win32 Release"

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

ALL : "$(OUTDIR)\MidiPlayer.exe"

CLEAN : 
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\Mci.obj"
	-@erase "$(INTDIR)\MidiPlayer.obj"
	-@erase "$(INTDIR)\MidiPlayer.pch"
	-@erase "$(INTDIR)\MidiPlayer.res"
	-@erase "$(INTDIR)\MidiPlayerDlg.obj"
	-@erase "$(INTDIR)\Sequencer.obj"
	-@erase "$(INTDIR)\SingleInstanceApp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\MidiPlayer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MidiPlayer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/MidiPlayer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MidiPlayer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MidiPlayer.pdb" /machine:I386 /out:"$(OUTDIR)/MidiPlayer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\Mci.obj" \
	"$(INTDIR)\MidiPlayer.obj" \
	"$(INTDIR)\MidiPlayer.res" \
	"$(INTDIR)\MidiPlayerDlg.obj" \
	"$(INTDIR)\Sequencer.obj" \
	"$(INTDIR)\SingleInstanceApp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MidiPlayer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MidiPlayer - Win32 Debug"

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

ALL : "$(OUTDIR)\MidiPlayer.exe"

CLEAN : 
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\Mci.obj"
	-@erase "$(INTDIR)\MidiPlayer.obj"
	-@erase "$(INTDIR)\MidiPlayer.pch"
	-@erase "$(INTDIR)\MidiPlayer.res"
	-@erase "$(INTDIR)\MidiPlayerDlg.obj"
	-@erase "$(INTDIR)\Sequencer.obj"
	-@erase "$(INTDIR)\SingleInstanceApp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MidiPlayer.exe"
	-@erase "$(OUTDIR)\MidiPlayer.ilk"
	-@erase "$(OUTDIR)\MidiPlayer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MidiPlayer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/MidiPlayer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MidiPlayer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MidiPlayer.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/MidiPlayer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\Mci.obj" \
	"$(INTDIR)\MidiPlayer.obj" \
	"$(INTDIR)\MidiPlayer.res" \
	"$(INTDIR)\MidiPlayerDlg.obj" \
	"$(INTDIR)\Sequencer.obj" \
	"$(INTDIR)\SingleInstanceApp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MidiPlayer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MidiPlayer - Win32 Release"
# Name "MidiPlayer - Win32 Debug"

!IF  "$(CFG)" == "MidiPlayer - Win32 Release"

!ELSEIF  "$(CFG)" == "MidiPlayer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MidiPlayer - Win32 Release"

!ELSEIF  "$(CFG)" == "MidiPlayer - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MidiPlayer.cpp
DEP_CPP_MIDIP=\
	".\hyperlink.h"\
	".\Mci.h"\
	".\MidiPlayer.h"\
	".\MidiPlayerDlg.h"\
	".\Sequencer.h"\
	".\SingleInstanceApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MidiPlayer.obj" : $(SOURCE) $(DEP_CPP_MIDIP) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MidiPlayerDlg.cpp
DEP_CPP_MIDIPL=\
	".\hyperlink.h"\
	".\Mci.h"\
	".\MidiPlayer.h"\
	".\MidiPlayerDlg.h"\
	".\Sequencer.h"\
	".\SingleInstanceApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MidiPlayerDlg.obj" : $(SOURCE) $(DEP_CPP_MIDIPL) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MidiPlayer - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MidiPlayer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MidiPlayer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MidiPlayer - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MidiPlayer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MidiPlayer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MidiPlayer.rc
DEP_RSC_MIDIPLA=\
	".\idr_main.ico"\
	".\res\MidiPlayer.rc2"\
	

"$(INTDIR)\MidiPlayer.res" : $(SOURCE) $(DEP_RSC_MIDIPLA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sequencer.cpp
DEP_CPP_SEQUE=\
	".\Sequencer.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SEQUE=\
	".\Mci.h"\
	

"$(INTDIR)\Sequencer.obj" : $(SOURCE) $(DEP_CPP_SEQUE) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mci.cpp

!IF  "$(CFG)" == "MidiPlayer - Win32 Release"

DEP_CPP_MCI_C=\
	".\Mci.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MCI_C=\
	".\develeped"\
	

"$(INTDIR)\Mci.obj" : $(SOURCE) $(DEP_CPP_MCI_C) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


!ELSEIF  "$(CFG)" == "MidiPlayer - Win32 Debug"

DEP_CPP_MCI_C=\
	".\Mci.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mci.obj" : $(SOURCE) $(DEP_CPP_MCI_C) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HyperLink.cpp

!IF  "$(CFG)" == "MidiPlayer - Win32 Release"

DEP_CPP_HYPER=\
	".\hyperlink.h"\
	".\StdAfx.h"\
	
NODEP_CPP_HYPER=\
	".\Default hand cursor"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


!ELSEIF  "$(CFG)" == "MidiPlayer - Win32 Debug"

DEP_CPP_HYPER=\
	".\hyperlink.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleInstanceApp.cpp
DEP_CPP_SINGL=\
	".\SingleInstanceApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SingleInstanceApp.obj" : $(SOURCE) $(DEP_CPP_SINGL) "$(INTDIR)"\
 "$(INTDIR)\MidiPlayer.pch"


# End Source File
# End Target
# End Project
################################################################################
