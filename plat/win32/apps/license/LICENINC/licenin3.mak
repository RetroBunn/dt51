# Microsoft Developer Studio Generated NMAKE File, Based on licenin3.dsp
!IF "$(CFG)" == ""
CFG=licenin3 - Win32 Release
!MESSAGE No configuration specified. Defaulting to licenin3 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "licenin3 - Win32 Release" && "$(CFG)" != "licenin3 - Win32 Debug" && "$(CFG)" != "licenin3 - Win32 WP Release" && "$(CFG)" != "licenin3 - Win32 WP Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "licenin3.mak" CFG="licenin3 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "licenin3 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "licenin3 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "licenin3 - Win32 WP Release" (based on "Win32 (x86) Console Application")
!MESSAGE "licenin3 - Win32 WP Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "licenin3 - Win32 Release"

OUTDIR=.\build\licenin3\release
INTDIR=.\build\licenin3\release\link
# Begin Custom Macros
OutDir=.\build\licenin3\release
# End Custom Macros

ALL : "$(OUTDIR)\licenin3.exe"


CLEAN :
	-@erase "$(INTDIR)\Crypt2.obj"
	-@erase "$(INTDIR)\liceninc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\licenin3.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\dapi\src\api" /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D LICENSE_INCREMENT=3 /Fp"$(INTDIR)\licenin3.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\licenin3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\licenin3.pdb" /machine:I386 /out:"$(OUTDIR)\licenin3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Crypt2.obj" \
	"$(INTDIR)\liceninc.obj"

"$(OUTDIR)\licenin3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "licenin3 - Win32 Debug"

OUTDIR=.\build\licenin3\debug
INTDIR=.\build\licenin3\debug\link
# Begin Custom Macros
OutDir=.\build\licenin3\debug
# End Custom Macros

ALL : "$(OUTDIR)\licenin3.exe"


CLEAN :
	-@erase "$(INTDIR)\Crypt2.obj"
	-@erase "$(INTDIR)\liceninc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\licenin3.exe"
	-@erase "$(OUTDIR)\licenin3.ilk"
	-@erase "$(OUTDIR)\licenin3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\dapi\src\api" /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D LICENSE_INCREMENT=3 /Fp"$(INTDIR)\licenin3.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\licenin3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\licenin3.pdb" /debug /machine:I386 /out:"$(OUTDIR)\licenin3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Crypt2.obj" \
	"$(INTDIR)\liceninc.obj"

"$(OUTDIR)\licenin3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "licenin3 - Win32 WP Release"

OUTDIR=.\wbuild\licenin3\release
INTDIR=.\wbuild\licenin3\release\link
# Begin Custom Macros
OutDir=.\wbuild\licenin3\release
# End Custom Macros

ALL : "$(OUTDIR)\licenin3.exe"


CLEAN :
	-@erase "$(INTDIR)\Crypt2.obj"
	-@erase "$(INTDIR)\liceninc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\licenin3.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\dapi\src\api" /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D LICENSE_INCREMENT=3 /D "WILLOWPOND" /Fp"$(INTDIR)\licenin3.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\licenin3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\licenin3.pdb" /machine:I386 /out:"$(OUTDIR)\licenin3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Crypt2.obj" \
	"$(INTDIR)\liceninc.obj"

"$(OUTDIR)\licenin3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "licenin3 - Win32 WP Debug"

OUTDIR=.\wbuild\licenin3\debug
INTDIR=.\wbuild\licenin3\debug\link
# Begin Custom Macros
OutDir=.\wbuild\licenin3\debug
# End Custom Macros

ALL : "$(OUTDIR)\licenin3.exe"


CLEAN :
	-@erase "$(INTDIR)\Crypt2.obj"
	-@erase "$(INTDIR)\liceninc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\licenin3.exe"
	-@erase "$(OUTDIR)\licenin3.ilk"
	-@erase "$(OUTDIR)\licenin3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\\" /I "..\..\dapi\src\api" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D LICENSE_INCREMENT=3 /D "WILLOWPOND" /Fp"$(INTDIR)\licenin3.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\licenin3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\licenin3.pdb" /debug /machine:I386 /out:"$(OUTDIR)\licenin3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Crypt2.obj" \
	"$(INTDIR)\liceninc.obj"

"$(OUTDIR)\licenin3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("licenin3.dep")
!INCLUDE "licenin3.dep"
!ELSE 
!MESSAGE Warning: cannot find "licenin3.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "licenin3 - Win32 Release" || "$(CFG)" == "licenin3 - Win32 Debug" || "$(CFG)" == "licenin3 - Win32 WP Release" || "$(CFG)" == "licenin3 - Win32 WP Debug"
SOURCE=..\..\dapi\src\Api\Crypt2.c

"$(INTDIR)\Crypt2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\liceninc.c

"$(INTDIR)\liceninc.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

