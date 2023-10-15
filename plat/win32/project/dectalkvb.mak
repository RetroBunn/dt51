# Microsoft Developer Studio Generated NMAKE File, Based on dectalkvb.dsp
!IF "$(CFG)" == ""
CFG=dectalkvb - Win32 Debug
!MESSAGE No configuration specified. Defaulting to dectalkvb - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dectalkvb - Win32 Release" && "$(CFG)" != "dectalkvb - Win32 Debug" && "$(CFG)" != "dectalkvb - Win32 Release Spanish" && "$(CFG)" != "dectalkvb - Win32 Release German" && "$(CFG)" != "dectalkvb - Win32 Release Latin American" && "$(CFG)" != "dectalkvb - Win32 Release French" && "$(CFG)" != "dectalkvb - Win32 Release United Kingdom" && "$(CFG)" != "dectalkvb - Win32 Release Italian"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dectalkvb.mak" CFG="dectalkvb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dectalkvb - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Release Spanish" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Release German" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Release Latin American" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Release French" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Release United Kingdom" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalkvb - Win32 Release Italian" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dectalkvb - Win32 Release"

OUTDIR=.\..\build\dectalkvb\us\release
INTDIR=.\..\build\dectalkvb\us\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\us\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\us\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Debug"

OUTDIR=.\..\build\dectalkvb\us\debug
INTDIR=.\..\build\dectalkvb\us\debug\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\us\debug
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.ilk"
	-@erase "$(OUTDIR)\dectalkvb.lib"
	-@erase "$(OUTDIR)\dectalkvb.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "PRINTFDEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\dectalkvb.pdb" /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" /pdbtype:sept 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\us\debug\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Release Spanish"

OUTDIR=.\..\build\dectalkvb\sp\release
INTDIR=.\..\build\dectalkvb\sp\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\sp\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "SPANISH_SP" /D "SPANISH" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\sp\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Release German"

OUTDIR=.\..\build\dectalkvb\gr\release
INTDIR=.\..\build\dectalkvb\gr\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\gr\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /Ox /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "GERMAN" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Zm200 /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\gr\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Release Latin American"

OUTDIR=.\..\build\dectalkvb\la\release
INTDIR=.\..\build\dectalkvb\la\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\la\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "SPANISH_LA" /D "SPANISH" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\la\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Release French"

OUTDIR=.\..\build\dectalkvb\fr\release
INTDIR=.\..\build\dectalkvb\fr\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\fr\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "FRENCH" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\fr\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Release United Kingdom"

OUTDIR=.\..\build\dectalkvb\uk\release
INTDIR=.\..\build\dectalkvb\uk\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\uk\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "ENGLISH_UK" /D "ENGLISH" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\uk\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dectalkvb - Win32 Release Italian"

OUTDIR=.\..\build\dectalkvb\it\release
INTDIR=.\..\build\dectalkvb\it\release\link
# Begin Custom Macros
OutDir=.\..\build\dectalkvb\it\release
# End Custom Macros

ALL : "$(OUTDIR)\dectalkvb.dll"


CLEAN :
	-@erase "$(INTDIR)\dectalkvb.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dectalkvb.dll"
	-@erase "$(OUTDIR)\dectalkvb.exp"
	-@erase "$(OUTDIR)\dectalkvb.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /Ox /I ".\api" /I ".\acna" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\protos" /I "..\.." /I "..\hlsyn" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "i386" /D "BLD_DECTALK_DLL" /D "ITALIAN" /Fp"$(INTDIR)\dectalkvb.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Zm200 /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dectalkvb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\dectalkvb.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\vb\dectalkvb.def" /out:"$(OUTDIR)\dectalkvb.dll" /implib:"$(OUTDIR)\dectalkvb.lib" 
DEF_FILE= \
	".\vb\dectalkvb.def"
LINK32_OBJS= \
	"$(INTDIR)\dectalkvb.obj" \
	"..\build\dtstatic\it\release\dtstatic.lib"

"$(OUTDIR)\dectalkvb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("dectalkvb.dep")
!INCLUDE "dectalkvb.dep"
!ELSE 
!MESSAGE Warning: cannot find "dectalkvb.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dectalkvb - Win32 Release" || "$(CFG)" == "dectalkvb - Win32 Debug" || "$(CFG)" == "dectalkvb - Win32 Release Spanish" || "$(CFG)" == "dectalkvb - Win32 Release German" || "$(CFG)" == "dectalkvb - Win32 Release Latin American" || "$(CFG)" == "dectalkvb - Win32 Release French" || "$(CFG)" == "dectalkvb - Win32 Release United Kingdom" || "$(CFG)" == "dectalkvb - Win32 Release Italian"
SOURCE=.\vb\dectalkvb.c

"$(INTDIR)\dectalkvb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

