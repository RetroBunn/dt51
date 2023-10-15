# Microsoft Developer Studio Project File - Name="FonixTtsDtSimpleJP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FonixTtsDtSimpleJP - Win32 Release low compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FonixTtsDtSimpleJP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FonixTtsDtSimpleJP.mak" CFG="FonixTtsDtSimpleJP - Win32 Release low compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FonixTtsDtSimpleJP - Win32 Release low compute" (based on "Win32 (x86) Static Library")
!MESSAGE "FonixTtsDtSimpleJP - Win32 Debug low compute" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FonixTtsDtSimpleJP - Win32 Release low compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "FonixTtsDtSimpleJP___Win32_Release_low_compute"
# PROP BASE Intermediate_Dir "FonixTtsDtSimpleJP___Win32_Release_low_compute"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_low_compute"
# PROP Intermediate_Dir "Release_low_compute"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\..\..\..\..\..\\" /I "..\..\..\..\..\API" /I "..\..\..\..\..\CMD" /I "..\..\..\..\..\INCLUDE" /I "..\..\..\..\..\KERNEL" /I "..\..\..\..\..\LTS" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\NT" /I "..\..\..\..\..\PH" /I "..\..\..\..\..\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "DICT_COMPLETE" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "JAPANESE" /D "CASIO_SH3" /D "NO_PRINTF" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\CodePageConv" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "NDEBUG" /D "DTALK_JP_EXPORTS" /D "NEW_MULTI_LANG_ARCH" /D "BUILD_LTS" /D "DTALK_IT_EXPORTS" /D "JAPANESE" /D "DUSTY" /D "INTEGER" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "NO_PRINTF" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=xcopy Release_low_compute\FonixTtsDtSimpleJp.lib ..\..\..\lib\ /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "FonixTtsDtSimpleJP - Win32 Debug low compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FonixTtsDtSimpleJP___Win32_Debug_low_compute"
# PROP BASE Intermediate_Dir "FonixTtsDtSimpleJP___Win32_Debug_low_compute"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_low_compute"
# PROP Intermediate_Dir "Debug_low_compute"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\..\..\\" /I "..\..\..\..\..\API" /I "..\..\..\..\..\CMD" /I "..\..\..\..\..\INCLUDE" /I "..\..\..\..\..\KERNEL" /I "..\..\..\..\..\LTS" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\NT" /I "..\..\..\..\..\PH" /I "..\..\..\..\..\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "DICT_COMPLETE" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "JAPANESE" /D "CASIO_SH3" /D "NO_PRINTF" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\CodePageConv" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "_DEBUG" /D "DTALK_JP_EXPORTS" /D "NEW_MULTI_LANG_ARCH" /D "BUILD_LTS" /D "DTALK_IT_EXPORTS" /D "JAPANESE" /D "DUSTY" /D "INTEGER" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "NO_PRINTF" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy Debug_low_compute\FonixTtsDtSimpleJp.lib ..\..\..\lib\Debug_low_compute /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "FonixTtsDtSimpleJP - Win32 Release low compute"
# Name "FonixTtsDtSimpleJP - Win32 Debug low compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "LTS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_000x.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_1000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_2000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_22xx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_24xx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_3000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\acc_5000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\CodePageConv\CodePageConv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\dsp_roma.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_accd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_accp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_bufc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_bunc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_data.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_dbgc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_edic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_envc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_errc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_hnkc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_idic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_jknc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_kana.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_kkhc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_mruc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_numc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_nydc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_othc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_rnsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_rtgc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_rtkc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_sskc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_stcc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_stzc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_suhc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_tdic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\ile_v5cc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_jp_ad1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_jp_con.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_jp_ma1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_jp_pr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_jp_ru1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_jp_sp1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_us_cha.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\lib_genc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\lib_shdc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\loaddict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_adju.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_homo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_math.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_rule.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_rule2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_spel.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_suff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\lsw_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\mkhatu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\japan\stdonsei.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
