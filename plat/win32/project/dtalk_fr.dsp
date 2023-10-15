# Microsoft Developer Studio Project File - Name="dtalk_fr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dtalk_fr - Win32 Debug High Compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dtalk_fr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dtalk_fr.mak" CFG="dtalk_fr - Win32 Debug High Compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dtalk_fr - Win32 Debug Low Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dtalk_fr - Win32 Release Low Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dtalk_fr - Win32 Debug High Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dtalk_fr - Win32 Release High Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dtalk_fr - Win32 Debug Low Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dtalk_fr___Win32_Debug_Low_Compute"
# PROP BASE Intermediate_Dir "dtalk_fr___Win32_Debug_Low_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\common\LowCompute\debug"
# PROP Intermediate_Dir ".\..\build\dectalk\common\LowCompute\debug\fr"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\..\..\shared\include\\" /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include\NT" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "_DEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\..\..\shared\include\\" /I ".\..\..\..\shared\include\NT" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "INTEGER" /D "_DEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy ..\..\..\dic\french\dtalk_fr.dic "..\build\dectalk\common\LowCompute\debug" /Y /D
# End Special Build Tool

!ELSEIF  "$(CFG)" == "dtalk_fr - Win32 Release Low Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dtalk_fr___Win32_Release_Low_Compute"
# PROP BASE Intermediate_Dir "dtalk_fr___Win32_Release_Low_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\common\LowCompute\release"
# PROP Intermediate_Dir ".\..\build\dectalk\common\LowCompute\release\fr"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include\NT" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "NDEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I ".\..\..\..\shared\include\NT" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "INTEGER" /D "NDEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy ..\..\..\dic\french\dtalk_fr.dic "..\build\dectalk\common\LowCompute\release" /Y /D
# End Special Build Tool

!ELSEIF  "$(CFG)" == "dtalk_fr - Win32 Debug High Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dtalk_fr___Win32_Debug_High_Compute"
# PROP BASE Intermediate_Dir "dtalk_fr___Win32_Debug_High_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\common\HighCompute\debug"
# PROP Intermediate_Dir ".\..\build\dectalk\common\HighCompute\debug\fr"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\..\..\shared\include\\" /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include\NT" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "_DEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\..\..\..\shared\include\\" /I ".\..\..\..\shared\include\NT" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "HLSYN" /D "_DEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy ..\..\..\dic\french\dtalk_fr.dic "..\build\dectalk\common\HighCompute\debug" /Y /D
# End Special Build Tool

!ELSEIF  "$(CFG)" == "dtalk_fr - Win32 Release High Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dtalk_fr___Win32_Release_High_Compute"
# PROP BASE Intermediate_Dir "dtalk_fr___Win32_Release_High_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\common\HighCompute\release"
# PROP Intermediate_Dir ".\..\build\dectalk\common\HighCompute\release\fr"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include\NT" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "NDEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I ".\..\..\..\shared\include\NT" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DTALK_FR_EXPORTS" /D "FRENCH" /D "BUILD_LTS" /D "HLSYN" /D "NDEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy ..\..\..\dic\French\dtalk_fr.dic "..\build\dectalk\common\HighCompute\release" /Y /D
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "dtalk_fr - Win32 Debug Low Compute"
# Name "dtalk_fr - Win32 Release Low Compute"
# Name "dtalk_fr - Win32 Debug High Compute"
# Name "dtalk_fr - Win32 Release High Compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dtalk_fr.def
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_con.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_ma1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_pr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_rta.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_ru1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_sp1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_fr_suf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_us_cha.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\loaddict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_adju.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_homo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_math.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_rule.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_rule2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_spel.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_suff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsw_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\mmalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\opthread.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_char.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_cons.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_dict.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_homo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_rule.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
