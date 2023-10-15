# Microsoft Developer Studio Project File - Name="dectalk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dectalk - Win32 Debug High Compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dectalk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dectalk.mak" CFG="dectalk - Win32 Debug High Compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dectalk - Win32 Release Low Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalk - Win32 Debug Low Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalk - Win32 Release High Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dectalk - Win32 Debug High Compute" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dectalk - Win32 Release Low Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dectalk___Win32_Release_Low_Compute"
# PROP BASE Intermediate_Dir "dectalk___Win32_Release_Low_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\common\LowCompute\release"
# PROP Intermediate_Dir ".\..\build\dectalk\common\LowCompute\release\dectalk"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include\NT" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "HLSYN" /D "NDEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I ".\..\..\..\shared\include\NT" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /I ".\..\..\..\dapicore\lts\codepageconv" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "INTEGER" /D "NDEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "dectalk - Win32 Debug Low Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dectalk___Win32_Debug_Low_Compute"
# PROP BASE Intermediate_Dir "dectalk___Win32_Debug_Low_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\common\LowCompute\debug"
# PROP Intermediate_Dir ".\..\build\dectalk\common\LowCompute\debug\dectalk"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "_DEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /FR /FD /GZ /c
# SUBTRACT BASE CPP /X /YX
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\..\..\dapicore\lts\codepageconv" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "INTEGER" /D "_DEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "dectalk - Win32 Release High Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dectalk___Win32_Release_High_Compute"
# PROP BASE Intermediate_Dir "dectalk___Win32_Release_High_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\common\HighCompute\release"
# PROP Intermediate_Dir ".\..\build\dectalk\common\HighCompute\release\dectalk"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include\NT" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "HLSYN" /D "NDEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\..\..\shared\include\\" /I ".\..\..\..\shared\include\NT" /I ".\..\..\..\shared\include\nt" /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /I ".\..\..\..\dapicore\lts\codepageconv" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "HLSYN" /D "NDEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "dectalk - Win32 Debug High Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dectalk___Win32_Debug_High_Compute"
# PROP BASE Intermediate_Dir "dectalk___Win32_Debug_High_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\common\HighCompute\debug"
# PROP Intermediate_Dir ".\..\build\dectalk\common\HighCompute\debug\dectalk"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "_DEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /FR /FD /GZ /c
# SUBTRACT BASE CPP /X /YX
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /I ".\..\..\..\dapicore\lts\codepageconv" /D "DECTALK_EXPORTS" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "HLSYN" /D "_DEBUG" /D "NO_INCLUDED_C_FILES" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32" /D "_WINDOWS" /D "O_TALKONLY" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "dectalk - Win32 Release Low Compute"
# Name "dectalk - Win32 Debug Low Compute"
# Name "dectalk - Win32 Release High Compute"
# Name "dectalk - Win32 Debug High Compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\acxf1c.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\brent.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\circuit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_char.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_cmd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_copt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_pars.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_phon.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_text.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cmd_wav.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\CodePageConv\CodePageConv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\CRYPT2.C
# End Source File
# Begin Source File

SOURCE=..\src\dbgwins.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\DECSTD97.C
# End Source File
# Begin Source File

SOURCE=.\dectalk.def
# End Source File
# Begin Source File

SOURCE=..\src\DTFnxExStdlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\hlframe.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\inithl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\log10table.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\mmalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\nasalf1x.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\opthread.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_ch_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_ch_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_ch_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_ch_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_fr_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_fr_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_fr_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_fr_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\P_gr_inton2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_gr_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_gr_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_gr_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_he_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_he_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_it_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_it_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_it_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_jp_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_jp_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_jp_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_jp_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_kr_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_kr_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_kr_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_kr_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_krnew_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_la_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_la_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_la_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_la_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_sp_inton.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_sp_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_sp_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_sp_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_sp_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\P_UK_SR1.C
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_uk_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\P_UK_SY1.C
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_uk_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_us_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_us_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_us_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_us_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_ambi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_char.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_pars1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_rule.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_aloph.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_claus.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\Ph_drwt02.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\Ph_fr_inton2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\Ph_inton2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\Ph_intonnew.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_romi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_setar.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_sort.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_sort2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_sttr2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_syl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_timng.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_vdefi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_vset.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\phinit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\phlog.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\phprint.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\pipe.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\playaud.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\playtone.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\KERNEL\services.c
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\src\spc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\sqrttable.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\sync.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\ttsapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\KERNEL\Usa_init.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtm3.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtmiont.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\186.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\c_us_cde.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_cdef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_cmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_cons.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_copt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_phon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_text.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\cm_util.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\cmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\CodePageConv\CodeConvTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\CodePageConv\CodePageConv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\comp_dum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\compnoun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\coop.h
# End Source File
# Begin Source File

SOURCE=..\include\dbgwins.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\dectalk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\dectalkf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\defs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\dt_abort.h
# End Source File
# Begin Source File

SOURCE=..\include\DTFnxExStdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\DTFnxStdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\esc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\flavor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\fr_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\ger_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\hlsyn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\hlsynapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\iso_char.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\it_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\jp_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\kernel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\l_all_ph.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\l_com_ph.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\la_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_acna.h
# End Source File
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

SOURCE=..\..\..\dapicore\LTS\ls_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_cons.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\mmalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\mulawi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\opatype.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\opmmsys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\opthread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_all_ph.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_ch_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_fr_rom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_gr_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_hb_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_it_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_jp_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_kr_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_la_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_sp_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_uk_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_us_rom.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_us_vdf1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_def1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_rule2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\pcport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\ph_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\phonlist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\pipe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\playaud.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\playaudd.h
# End Source File
# Begin Source File

SOURCE=..\include\port.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\samprate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\setltslanguage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\shmalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\sinetab.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\spa_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\spc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\syncmain.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\tts.h
# End Source File
# Begin Source File

SOURCE=..\..\..\sdk\include\ttsapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\ttserr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\sdk\include\ttsfeat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\tunecheck.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\uk_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\usa_def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtmfunc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtminst.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtmtable.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
