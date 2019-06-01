# Microsoft Developer Studio Generated NMAKE File, Based on StackUp.dsp
!IF "$(CFG)" == ""
CFG=StackUp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to StackUp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StackUp - Win32 Release" && "$(CFG)" !=\
 "StackUp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StackUp.mak" CFG="StackUp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StackUp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StackUp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "StackUp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\StackUp.exe"

!ELSE 

ALL : "$(OUTDIR)\StackUp.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Logo.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StackUp.obj"
	-@erase "$(INTDIR)\StackUp.pch"
	-@erase "$(INTDIR)\StackUp.res"
	-@erase "$(INTDIR)\StackUpApp.obj"
	-@erase "$(INTDIR)\StackUpWnd.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\StackUp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\StackUp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x405 /fo"$(INTDIR)\StackUp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\StackUp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib dinput.lib dsound.lib dxguid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\StackUp.pdb" /machine:I386\
 /out:"$(OUTDIR)\StackUp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Logo.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StackUp.obj" \
	"$(INTDIR)\StackUp.res" \
	"$(INTDIR)\StackUpApp.obj" \
	"$(INTDIR)\StackUpWnd.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\StackUp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\StackUp.exe" "$(OUTDIR)\StackUp.bsc"

!ELSE 

ALL : "$(OUTDIR)\StackUp.exe" "$(OUTDIR)\StackUp.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Game.sbr"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Globals.sbr"
	-@erase "$(INTDIR)\Logo.obj"
	-@erase "$(INTDIR)\Logo.sbr"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Options.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StackUp.obj"
	-@erase "$(INTDIR)\StackUp.pch"
	-@erase "$(INTDIR)\StackUp.res"
	-@erase "$(INTDIR)\StackUp.sbr"
	-@erase "$(INTDIR)\StackUpApp.obj"
	-@erase "$(INTDIR)\StackUpApp.sbr"
	-@erase "$(INTDIR)\StackUpWnd.obj"
	-@erase "$(INTDIR)\StackUpWnd.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\StackUp.bsc"
	-@erase "$(OUTDIR)\StackUp.exe"
	-@erase "$(OUTDIR)\StackUp.ilk"
	-@erase "$(OUTDIR)\StackUp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StackUp.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x405 /fo"$(INTDIR)\StackUp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\StackUp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Game.sbr" \
	"$(INTDIR)\Globals.sbr" \
	"$(INTDIR)\Logo.sbr" \
	"$(INTDIR)\Options.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\StackUp.sbr" \
	"$(INTDIR)\StackUpApp.sbr" \
	"$(INTDIR)\StackUpWnd.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\StackUp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ddraw.lib dinput.lib dsound.lib dxguid.lib ole32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\StackUp.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\StackUp.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Logo.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StackUp.obj" \
	"$(INTDIR)\StackUp.res" \
	"$(INTDIR)\StackUpApp.obj" \
	"$(INTDIR)\StackUpWnd.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\StackUp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "StackUp - Win32 Release" || "$(CFG)" ==\
 "StackUp - Win32 Debug"
SOURCE=.\Game.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_GAME_=\
	".\ddutil.h"\
	".\Game.h"\
	".\GlobalsExtern.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\Game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_GAME_=\
	".\ddutil.h"\
	".\Game.h"\
	".\GlobalsExtern.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\Game.obj"	"$(INTDIR)\Game.sbr" : $(SOURCE) $(DEP_CPP_GAME_)\
 "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\Globals.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_GLOBA=\
	".\ddutil.cpp"\
	".\ddutil.h"\
	".\Globals.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\Globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_GLOBA=\
	".\ddutil.cpp"\
	".\ddutil.h"\
	".\Globals.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\Globals.obj"	"$(INTDIR)\Globals.sbr" : $(SOURCE) $(DEP_CPP_GLOBA)\
 "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\Logo.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_LOGO_=\
	".\ddutil.h"\
	".\Game.h"\
	".\GlobalsExtern.h"\
	".\Logo.h"\
	".\Options.h"\
	".\StackUp.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\Logo.obj" : $(SOURCE) $(DEP_CPP_LOGO_) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_LOGO_=\
	".\ddutil.h"\
	".\Game.h"\
	".\GlobalsExtern.h"\
	".\Logo.h"\
	".\Options.h"\
	".\StackUp.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\Logo.obj"	"$(INTDIR)\Logo.sbr" : $(SOURCE) $(DEP_CPP_LOGO_)\
 "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\Options.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_OPTIO=\
	".\Options.h"\
	

"$(INTDIR)\Options.obj" : $(SOURCE) $(DEP_CPP_OPTIO) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_OPTIO=\
	".\Options.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Options.obj"	"$(INTDIR)\Options.sbr" : $(SOURCE) $(DEP_CPP_OPTIO)\
 "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_SPLAS=\
	".\Splash.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_SPLAS=\
	".\Splash.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\StackUp.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_STACK=\
	".\Game.h"\
	".\GlobalsExtern.h"\
	".\Logo.h"\
	".\Options.h"\
	".\StackUp.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\StackUp.obj" : $(SOURCE) $(DEP_CPP_STACK) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_STACK=\
	".\Game.h"\
	".\GlobalsExtern.h"\
	".\Logo.h"\
	".\Options.h"\
	".\StackUp.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\StackUp.obj"	"$(INTDIR)\StackUp.sbr" : $(SOURCE) $(DEP_CPP_STACK)\
 "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\StackUp.rc
DEP_RSC_STACKU=\
	".\res\StackUp.bmp"\
	".\res\StackUp.ico"\
	".\res\StackUp.rc2"\
	

"$(INTDIR)\StackUp.res" : $(SOURCE) $(DEP_RSC_STACKU) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StackUpApp.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_STACKUP=\
	".\Splash.h"\
	".\StackUp.h"\
	".\StackUpApp.h"\
	".\StackUpWnd.h"\
	

"$(INTDIR)\StackUpApp.obj" : $(SOURCE) $(DEP_CPP_STACKUP) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_STACKUP=\
	".\Splash.h"\
	".\StackUp.h"\
	".\StackUpApp.h"\
	".\StackUpWnd.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\StackUpApp.obj"	"$(INTDIR)\StackUpApp.sbr" : $(SOURCE)\
 $(DEP_CPP_STACKUP) "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\StackUpWnd.cpp

!IF  "$(CFG)" == "StackUp - Win32 Release"

DEP_CPP_STACKUPW=\
	".\GlobalsExtern.h"\
	".\StackUpApp.h"\
	".\StackUpWnd.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\StackUpWnd.obj" : $(SOURCE) $(DEP_CPP_STACKUPW) "$(INTDIR)"\
 "$(INTDIR)\StackUp.pch"


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

DEP_CPP_STACKUPW=\
	".\GlobalsExtern.h"\
	".\StackUpApp.h"\
	".\StackUpWnd.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"dinput.h"\
	

"$(INTDIR)\StackUpWnd.obj"	"$(INTDIR)\StackUpWnd.sbr" : $(SOURCE)\
 $(DEP_CPP_STACKUPW) "$(INTDIR)" "$(INTDIR)\StackUp.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "StackUp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\StackUp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StackUp.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "StackUp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StackUp.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\StackUp.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

