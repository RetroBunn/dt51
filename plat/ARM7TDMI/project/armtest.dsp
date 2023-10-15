# Microsoft Developer Studio Project File - Name="armtest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=armtest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "armtest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "armtest.mak" CFG="armtest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "armtest - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "armtest - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "armtest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ARMTEST_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\api" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I "..\.." /I ".\hlsyn" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "BLD_DECTALK_DLL" /D "ARM7" /D "ENGLISH_US" /D "ACNA" /D "ARM7_NOSWI" /D "ENGLISH" /D "i386" /D "_MBCS" /D "NO_INCLUDED_C_FILES" /D "NEW_MULTI_LANG_ARCH" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "armtest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\build\armtest\us\debug"
# PROP Intermediate_Dir "..\build\armtest\us\debug\link"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ARMTEST_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\api" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\hlsyn" /I ".\arm7" /I "..\.." /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /I ".\..\..\..\dapicore\lts\codepageconv" /I ".\..\..\..\dapicore\lts\japan" /D "_WINDOWS" /D "_USRDLL" /D "BLD_DECTALK_DLL" /D "ARM7" /D "ENGLISH_US" /D "ACNA" /D "ARM7_NOSWI" /D "ENGLISH" /D "i386" /D "EPSON_ARM7" /D "CHEESY_DICT_COMPRESSION" /D "WIN32_TEST" /D "_MBCS" /D "NO_INCLUDED_C_FILES" /D "NEW_MULTI_LANG_ARCH" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /map:"..\build\armtest\us\debug\armtest.map" /debug /machine:I386

!ENDIF 

# Begin Target

# Name "armtest - Win32 Release"
# Name "armtest - Win32 Debug"
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

SOURCE=..\..\..\dapicore\CMD\Cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\..\win32\project\dtarm7epson.def
# End Source File
# Begin Source File

SOURCE=..\src\DTFnxExStdlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapi\epsonapi.c
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

SOURCE=..\..\..\dapicore\LTS\maindict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\hlsyn\nasalf1x.c
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

SOURCE=..\..\..\dapicore\PH\p_it_sr1.c
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

SOURCE=..\..\..\dapicore\PH\p_uk_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_uk_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_uk_sy1.c
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

SOURCE=..\..\..\dapicore\CMD\par_char.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\par_pars.c
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

SOURCE=..\..\..\dapicore\PH\ph_inton.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\Ph_inton2.c
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

SOURCE=..\..\..\dapicore\PH\ph_syntx.c
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

SOURCE=..\..\..\dapicore\KERNEL\Usa_init.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\VTM\vtmiont.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\build\armltsus\us\debug\armltsus.lib
# End Source File
# Begin Source File

SOURCE=..\build\armltssp\sp\debug\armltssp.lib
# End Source File
# Begin Source File

SOURCE=..\build\armltsgr\gr\debug\armltsgr.lib
# End Source File
# Begin Source File

SOURCE=..\build\armltsuk\uk\debug\armltsuk.lib
# End Source File
# Begin Source File

SOURCE=..\build\armltsla\la\debug\armltsla.lib
# End Source File
# Begin Source File

SOURCE=..\build\armltsfr\fr\debug\armltsfr.lib
# End Source File
# Begin Source File

SOURCE=..\build\armltsit\it\debug\armltsit.lib
# End Source File
# End Target
# End Project
