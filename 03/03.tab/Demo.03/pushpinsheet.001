# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=pushpinsheet - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to pushpinsheet - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "pushpinsheet - Win32 Release" && "$(CFG)" !=\
 "pushpinsheet - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "pushpinsheet.mak" CFG="pushpinsheet - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pushpinsheet - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pushpinsheet - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "pushpinsheet - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "pushpinsheet - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\pushpinsheet.exe"

CLEAN : 
	-@erase "$(INTDIR)\MyPropertyPage1.obj"
	-@erase "$(INTDIR)\MyPropertySheet.obj"
	-@erase "$(INTDIR)\PushPin.obj"
	-@erase "$(INTDIR)\pushpinFrame.obj"
	-@erase "$(INTDIR)\PushPinSheet.obj"
	-@erase "$(INTDIR)\PushPinSheet.res"
	-@erase "$(INTDIR)\PushPinSheetDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\pushpinsheet.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/pushpinsheet.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/PushPinSheet.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pushpinsheet.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/pushpinsheet.pdb" /machine:I386\
 /out:"$(OUTDIR)/pushpinsheet.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MyPropertyPage1.obj" \
	"$(INTDIR)\MyPropertySheet.obj" \
	"$(INTDIR)\PushPin.obj" \
	"$(INTDIR)\pushpinFrame.obj" \
	"$(INTDIR)\PushPinSheet.obj" \
	"$(INTDIR)\PushPinSheet.res" \
	"$(INTDIR)\PushPinSheetDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\pushpinsheet.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pushpinsheet - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\pushpinsheet.exe"

CLEAN : 
	-@erase "$(INTDIR)\MyPropertyPage1.obj"
	-@erase "$(INTDIR)\MyPropertySheet.obj"
	-@erase "$(INTDIR)\PushPin.obj"
	-@erase "$(INTDIR)\pushpinFrame.obj"
	-@erase "$(INTDIR)\PushPinSheet.obj"
	-@erase "$(INTDIR)\PushPinSheet.res"
	-@erase "$(INTDIR)\PushPinSheetDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\pushpinsheet.exe"
	-@erase "$(OUTDIR)\pushpinsheet.ilk"
	-@erase "$(OUTDIR)\pushpinsheet.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/pushpinsheet.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/PushPinSheet.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pushpinsheet.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/pushpinsheet.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/pushpinsheet.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MyPropertyPage1.obj" \
	"$(INTDIR)\MyPropertySheet.obj" \
	"$(INTDIR)\PushPin.obj" \
	"$(INTDIR)\pushpinFrame.obj" \
	"$(INTDIR)\PushPinSheet.obj" \
	"$(INTDIR)\PushPinSheet.res" \
	"$(INTDIR)\PushPinSheetDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\pushpinsheet.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "pushpinsheet - Win32 Release"
# Name "pushpinsheet - Win32 Debug"

!IF  "$(CFG)" == "pushpinsheet - Win32 Release"

!ELSEIF  "$(CFG)" == "pushpinsheet - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyPropertySheet.cpp
DEP_CPP_MYPRO=\
	".\MyPropertyPage1.h"\
	".\MyPropertySheet.h"\
	".\stdafx.h"\
	

"$(INTDIR)\MyPropertySheet.obj" : $(SOURCE) $(DEP_CPP_MYPRO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPin.cpp

!IF  "$(CFG)" == "pushpinsheet - Win32 Release"

DEP_CPP_PUSHP=\
	".\stdafx.h"\
	
NODEP_CPP_PUSHP=\
	".\PushPin.h"\
	

"$(INTDIR)\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pushpinsheet - Win32 Debug"

DEP_CPP_PUSHP=\
	".\PushPin.h"\
	".\stdafx.h"\
	

"$(INTDIR)\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pushpinFrame.cpp
DEP_CPP_PUSHPI=\
	".\PushPin.h"\
	".\PushPinFrame.h"\
	".\stdafx.h"\
	

"$(INTDIR)\pushpinFrame.obj" : $(SOURCE) $(DEP_CPP_PUSHPI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPinSheet.cpp
DEP_CPP_PUSHPIN=\
	".\PushPinFrame.h"\
	".\PushPinSheet.h"\
	".\pushpinsheetdlg.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\pushpin.h"\
	

"$(INTDIR)\PushPinSheet.obj" : $(SOURCE) $(DEP_CPP_PUSHPIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPinSheet.rc
DEP_RSC_PUSHPINS=\
	".\res\pinned.bmp"\
	".\res\pinnede.bmp"\
	".\res\PushPinSheet.ico"\
	".\res\PushPinSheet.rc2"\
	".\res\unpinned.bmp"\
	".\res\unpinnede.bmp"\
	

"$(INTDIR)\PushPinSheet.res" : $(SOURCE) $(DEP_RSC_PUSHPINS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPinSheetDlg.cpp
DEP_CPP_PUSHPINSH=\
	".\MyPropertyPage1.h"\
	".\MyPropertySheet.h"\
	".\PushPin.h"\
	".\PushPinFrame.h"\
	".\PushPinSheet.h"\
	".\pushpinsheetdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\PushPinSheetDlg.obj" : $(SOURCE) $(DEP_CPP_PUSHPINSH) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyPropertyPage1.cpp
DEP_CPP_MYPROP=\
	".\MyPropertyPage1.h"\
	".\stdafx.h"\
	

"$(INTDIR)\MyPropertyPage1.obj" : $(SOURCE) $(DEP_CPP_MYPROP) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
