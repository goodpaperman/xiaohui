# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TPS_Demo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TPS_Demo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TPS_Demo - Win32 Release" && "$(CFG)" !=\
 "TPS_Demo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TPS_Demo.mak" CFG="TPS_Demo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TPS_Demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TPS_Demo - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TPS_Demo - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "TPS_Demo - Win32 Release"

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

ALL : "$(OUTDIR)\TPS_Demo.exe"

CLEAN : 
	-@erase ".\Release\TPS_Demo.exe"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\TPS_DemoDoc.obj"
	-@erase ".\Release\TPS_Demo.pch"
	-@erase ".\Release\TPS_Demo.obj"
	-@erase ".\Release\GeneralPrefsDlg.obj"
	-@erase ".\Release\TreePropertySheet.obj"
	-@erase ".\Release\TreePropertySheetAnimateWidget.obj"
	-@erase ".\Release\TPS_DemoView.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\TPS_Demo.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TPS_Demo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TPS_Demo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TPS_Demo.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/TPS_Demo.pdb" /machine:I386 /out:"$(OUTDIR)/TPS_Demo.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TPS_DemoDoc.obj" \
	"$(INTDIR)/TPS_Demo.obj" \
	"$(INTDIR)/GeneralPrefsDlg.obj" \
	"$(INTDIR)/TreePropertySheet.obj" \
	"$(INTDIR)/TreePropertySheetAnimateWidget.obj" \
	"$(INTDIR)/TPS_DemoView.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/TPS_Demo.res"

"$(OUTDIR)\TPS_Demo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TPS_Demo - Win32 Debug"

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

ALL : "$(OUTDIR)\TPS_Demo.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\TPS_Demo.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\TPS_Demo.exe"
	-@erase ".\Debug\TPS_DemoView.obj"
	-@erase ".\Debug\TPS_Demo.obj"
	-@erase ".\Debug\TPS_DemoDoc.obj"
	-@erase ".\Debug\TreePropertySheetAnimateWidget.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\TreePropertySheet.obj"
	-@erase ".\Debug\GeneralPrefsDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\TPS_Demo.res"
	-@erase ".\Debug\TPS_Demo.ilk"
	-@erase ".\Debug\TPS_Demo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TPS_Demo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TPS_Demo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TPS_Demo.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/TPS_Demo.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/TPS_Demo.exe" 
LINK32_OBJS= \
	"$(INTDIR)/TPS_DemoView.obj" \
	"$(INTDIR)/TPS_Demo.obj" \
	"$(INTDIR)/TPS_DemoDoc.obj" \
	"$(INTDIR)/TreePropertySheetAnimateWidget.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/TreePropertySheet.obj" \
	"$(INTDIR)/GeneralPrefsDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TPS_Demo.res"

"$(OUTDIR)\TPS_Demo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TPS_Demo - Win32 Release"
# Name "TPS_Demo - Win32 Debug"

!IF  "$(CFG)" == "TPS_Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "TPS_Demo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "TPS_Demo - Win32 Release"

!ELSEIF  "$(CFG)" == "TPS_Demo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPS_Demo.cpp
DEP_CPP_TPS_D=\
	".\StdAfx.h"\
	".\TPS_Demo.h"\
	".\MainFrm.h"\
	".\TPS_DemoDoc.h"\
	".\TPS_DemoView.h"\
	

"$(INTDIR)\TPS_Demo.obj" : $(SOURCE) $(DEP_CPP_TPS_D) "$(INTDIR)"\
 "$(INTDIR)\TPS_Demo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TPS_Demo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TPS_Demo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TPS_Demo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TPS_Demo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TPS_Demo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TPS_Demo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\TPS_Demo.h"\
	".\MainFrm.h"\
	".\TreePropertySheet.h"\
	".\GeneralPrefsDlg.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TPS_Demo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPS_DemoDoc.cpp
DEP_CPP_TPS_DE=\
	".\StdAfx.h"\
	".\TPS_Demo.h"\
	".\TPS_DemoDoc.h"\
	

"$(INTDIR)\TPS_DemoDoc.obj" : $(SOURCE) $(DEP_CPP_TPS_DE) "$(INTDIR)"\
 "$(INTDIR)\TPS_Demo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPS_DemoView.cpp
DEP_CPP_TPS_DEM=\
	".\StdAfx.h"\
	".\TPS_Demo.h"\
	".\TPS_DemoDoc.h"\
	".\TPS_DemoView.h"\
	

"$(INTDIR)\TPS_DemoView.obj" : $(SOURCE) $(DEP_CPP_TPS_DEM) "$(INTDIR)"\
 "$(INTDIR)\TPS_Demo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPS_Demo.rc
DEP_RSC_TPS_DEMO=\
	".\res\TPS_Demo.ico"\
	".\res\TPS_DemoDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\TPS_Demo.rc2"\
	

"$(INTDIR)\TPS_Demo.res" : $(SOURCE) $(DEP_RSC_TPS_DEMO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TreePropertySheetAnimateWidget.cpp
DEP_CPP_TREEP=\
	".\StdAfx.h"\
	".\TreePropertySheet.h"\
	".\TreePropertySheetAnimateWidget.h"\
	

"$(INTDIR)\TreePropertySheetAnimateWidget.obj" : $(SOURCE) $(DEP_CPP_TREEP)\
 "$(INTDIR)" "$(INTDIR)\TPS_Demo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TreePropertySheet.cpp
DEP_CPP_TREEPR=\
	".\StdAfx.h"\
	".\TreePropertySheet.h"\
	".\TreePropertySheetAnimateWidget.h"\
	

"$(INTDIR)\TreePropertySheet.obj" : $(SOURCE) $(DEP_CPP_TREEPR) "$(INTDIR)"\
 "$(INTDIR)\TPS_Demo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeneralPrefsDlg.cpp
DEP_CPP_GENER=\
	".\StdAfx.h"\
	".\TPS_Demo.h"\
	".\GeneralPrefsDlg.h"\
	

"$(INTDIR)\GeneralPrefsDlg.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"\
 "$(INTDIR)\TPS_Demo.pch"


# End Source File
# End Target
# End Project
################################################################################
