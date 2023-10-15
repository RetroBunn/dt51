# Microsoft Developer Studio Project File - Name="FonixTtsDtSimple_464_51" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FonixTtsDtSimple_464_51 - Win32 NAND Debug low compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FonixTtsDtSimple_464_51.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FonixTtsDtSimple_464_51.mak" CFG="FonixTtsDtSimple_464_51 - Win32 NAND Debug low compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FonixTtsDtSimple_464_51 - Win32 NAND Release low compute" (based on "Win32 (x86) Static Library")
!MESSAGE "FonixTtsDtSimple_464_51 - Win32 NAND Debug low compute" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FonixTtsDtSimple_464_51 - Win32 NAND Release low compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "FonixTtsDtSimple_464_51___Win32_NAND_Release_low_compute0"
# PROP BASE Intermediate_Dir "FonixTtsDtSimple_464_51___Win32_NAND_Release_low_compute0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "NAND_Release_low_compute"
# PROP Intermediate_Dir "NAND_Release_low_compute"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "NDEBUG" /D "DECTALK_EXPORTS" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /D "INLINE_FUNC_IN_FILE_USED" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "ENGLISH_US" /D "ENGLISH" /D "NO_PRINTF" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "NDEBUG" /D "INLINE_FUNC_IN_FILE_USED" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "DICT_COMPLETE" /D "NO_ALIGN_8" /D "ENGLISH_US" /D "ENGLISH" /D "CASIO_SH3" /D "NO_PRINTF" /D "NEW_MULTI_LANG_ARCH" /D "USE_NAND" /D "USE_464" /D "USE_51" /D "INTEGER" /D "UNICODE" /D "_UNICODE" /YX /FD /c
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
PostBuild_Cmds=xcopy NAND_Release_low_compute\FonixTtsDtSimple_464_51.lib ..\..\..\lib\ /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "FonixTtsDtSimple_464_51 - Win32 NAND Debug low compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FonixTtsDtSimple_464_51___Win32_NAND_Debug_low_compute"
# PROP BASE Intermediate_Dir "FonixTtsDtSimple_464_51___Win32_NAND_Debug_low_compute"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "NAND_Debug_low_compute"
# PROP Intermediate_Dir "NAND_Debug_low_compute"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gm /GX /ZI /Od /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "_DEBUG" /D "DECTALK_EXPORTS" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /D "INLINE_FUNC_IN_FILE_USED" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "ENGLISH_US" /D "ENGLISH" /D "NO_PRINTF" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /GZ /c
# ADD CPP /nologo /Gm /GX /ZI /Od /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "_DEBUG" /D "INLINE_FUNC_IN_FILE_USED" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "DICT_COMPLETE" /D "NO_ALIGN_8" /D "ENGLISH_US" /D "ENGLISH" /D "CASIO_SH3" /D "NO_PRINTF" /D "NEW_MULTI_LANG_ARCH" /D "USE_NAND" /D "USE_464" /D "USE_51" /D "INTEGER" /D "UNICODE" /D "_UNICODE" /YX /FD /GZ /c
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
PostBuild_Cmds=xcopy NAND_Debug_low_compute\FonixTtsDtSimple_464_51.lib ..\..\..\lib\NAND_Debug_low_compute\ /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "FonixTtsDtSimple_464_51 - Win32 NAND Release low compute"
# Name "FonixTtsDtSimple_464_51 - Win32 NAND Debug low compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\DAPI\FonixTTSDTSimple.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\DAPI\simpleapi.c
# End Source File
# End Group
# Begin Group "cmd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_char.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_cmd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_copt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_pars.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_phon.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_text.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cm_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\par_ambi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\par_char.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\par_dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\par_pars1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\CMD\par_rule.c
# End Source File
# End Group
# Begin Group "Kernel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\KERNEL\services.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\KERNEL\Usa_init.c
# End Source File
# End Group
# Begin Group "PH"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_ch_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_ch_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_ch_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_ch_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_fr_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_fr_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_fr_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_fr_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\P_gr_inton2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_gr_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_gr_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_gr_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_he_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_he_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_it_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_it_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_it_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_it_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_jp_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_jp_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_jp_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_jp_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_kr_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_kr_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_kr_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_kr_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_krnew_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_la_sr1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_la_st1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_la_sy1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_la_tim.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_sp_inton.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_sp_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_sp_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_sp_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_sp_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\P_UK_SR1.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_uk_st1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\P_UK_SY1.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_uk_tim.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_us_sr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_us_st1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_us_sy1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\p_us_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_aloph.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_claus.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_draw_464.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\Ph_drwt02.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\Ph_fr_inton2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\Ph_inton2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\Ph_intonnew.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_romi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_setar.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_sort.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_sort2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_sttr2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_syl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_timng.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_vdefi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\ph_vset.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\phinit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\phlog.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\PH\phprint.c
# End Source File
# End Group
# Begin Group "Vtm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\VTM\playtone.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\VTM\vtm3.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\VTM\vtmiont.c
# End Source File
# End Group
# Begin Group "shared"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\shared\src\DTfnxstdlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\shared\src\spc.c
# End Source File
# End Group
# Begin Group "dic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dic\BuildFileSystemTables\FileSystemDataHandler.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dic\BuildFileSystemDic\FileSystemDict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dic\BuildFileSystemTables\Win32\FrenchFileSystemTable.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dic\BuildFileSystemDic\Win32\GermanFileSystemDict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dic\BuildFileSystemDic\Win32\ItalianFileSystemDict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dic\BuildFileSystemTables\Win32\UsEnglishFileSystemTable.c
# End Source File
# End Group
# Begin Group "LTS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\l_us_cha.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\ls_homo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\lsw_main2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\nocashcache.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\..\dapicore\LTS\CodePageConv\CodePageConv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\ARM7TDMI\src\DTFnxExStdlib.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
