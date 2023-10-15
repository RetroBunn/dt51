# Microsoft Developer Studio Project File - Name="dectalkstatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dectalkstatic - Win32 Debug Integer
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dectalkstatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dectalkstatic.mak" CFG="dectalkstatic - Win32 Debug LowCompute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dectalkstatic - Win32 Release HighCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dectalkstatic - Win32 Debug HighCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dectalkstatic - Win32 Release LowCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dectalkstatic - Win32 Debug LowCompute" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\static\HighCompute\Release"
# PROP Intermediate_Dir ".\..\build\dectalk\static\HighCompute\Release\dectalk"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DECTALK_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\sdk\include" /D "HLSYN" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "NO_INCLUDED_C_FILES" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /D "BLD_DECTALK_DLL" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\HighCompute\Release\dectalk.lib"

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\static\HighCompute\Debug"
# PROP Intermediate_Dir ".\..\build\dectalk\static\HighCompute\Debug\dectalk"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DECTALK_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\sdk\include" /D "HLSYN" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "NO_INCLUDED_C_FILES" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /D "BLD_DECTALK_DLL" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\HighCompute\Debug\dectalk.lib"

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dectalkstatic___Win32_Release_Integer"
# PROP BASE Intermediate_Dir "dectalkstatic___Win32_Release_Integer"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\static\LowCompute\Release"
# PROP Intermediate_Dir ".\..\build\dectalk\static\LowCompute\Release\dectalk"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DECTALK_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\sdk\include" /D "INTEGER" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "NO_INCLUDED_C_FILES" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /D "BLD_DECTALK_DLL" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\LowCompute\Release\dectalk.lib"

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dectalkstatic___Win32_Debug_Integer"
# PROP BASE Intermediate_Dir "dectalkstatic___Win32_Debug_Integer"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\static\LowCompute\Debug"
# PROP Intermediate_Dir ".\..\build\dectalk\static\LowCompute\Debug\dectalk"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DECTALK_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\sdk\include" /D "INTEGER" /D "ENGLISH_US" /D "ENGLISH" /D "ACNA" /D "NO_INCLUDED_C_FILES" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /D "BLD_DECTALK_DLL" /FD /GZ /c
# SUBTRACT CPP /X /Fr /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\LowCompute\Debug\dectalk.lib"

!ENDIF 

# Begin Target

# Name "dectalkstatic - Win32 Release HighCompute"
# Name "dectalkstatic - Win32 Debug HighCompute"
# Name "dectalkstatic - Win32 Release LowCompute"
# Name "dectalkstatic - Win32 Debug LowCompute"
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

SOURCE=..\..\..\dapicore\CMD\cmd_wav.c
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

SOURCE=..\..\..\dapicore\LTS\l_us_cha.c
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

SOURCE=..\..\..\dapicore\CMD\C_US_CDE.H
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

SOURCE=..\..\..\dapicore\CMD\comp_dum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\CMD\compnoun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\coop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\NT\dbgwins.h
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

SOURCE=..\..\..\shared\include\NT\mmalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\mulawi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\NT\opatype.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\NT\opmmsys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\NT\opthread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_all_ph.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_fr_rom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\PH\p_gr_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_GR_="..\..\..\dapicore\PH\gr_mal.phd"	"..\..\..\dapicore\PH\gr_fem.phd"	
# Begin Custom Build - Build p_gr_rom.h
InputPath=..\..\..\dapicore\PH\p_gr_rom.h
"..\..\..\dapicore\PH\p_gr_rom" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\gr_mal.phd ..\..\..\dapicore\PH\gr_fem.phd ..\..\..\dapicore\PH\p_gr_rom.h gr _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_GR_="..\..\..\dapicore\PH\gr_mal.phd"	"..\..\..\dapicore\PH\gr_fem.phd"	
# Begin Custom Build - Build p_gr_rom.h
InputPath=..\..\..\dapicore\PH\p_gr_rom.h
"..\..\..\dapicore\PH\p_gr_rom" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\gr_mal.phd ..\..\..\dapicore\PH\gr_fem.phd ..\..\..\dapicore\PH\p_gr_rom.h gr _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_GR_="..\..\..\dapicore\PH\gr_mal.phd"	"..\..\..\dapicore\PH\gr_fem.phd"	
# Begin Custom Build - Build p_gr_rom.h
InputPath=..\..\..\dapicore\PH\p_gr_rom.h
"..\..\..\dapicore\PH\p_gr_rom" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\gr_mal.phd ..\..\..\dapicore\PH\gr_fem.phd ..\..\..\dapicore\PH\p_gr_rom.h gr _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"
USERDEP__P_GR_="..\..\..\dapicore\PH\gr_mal.phd"	"..\..\..\dapicore\PH\gr_fem.phd"	
# Begin Custom Build - Build p_gr_rom.h
InputPath=..\..\..\dapicore\PH\p_gr_rom.h
"..\..\..\dapicore\PH\p_gr_rom" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\gr_mal.phd ..\..\..\dapicore\PH\gr_fem.phd ..\..\..\dapicore\PH\p_gr_rom.h gr _def
# End Custom Build

!ENDIF 
# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_it_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_IT_="..\..\..\dapicore\PH\it_mal.phd"	"..\..\..\dapicore\PH\it_fem.phd"	
# Begin Custom Build - Build p_it_rom.h
InputPath=..\..\..\dapicore\PH\p_it_rom.h

"..\..\..\dapicore\PH\p_it_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\it_mal.phd ..\..\..\dapicore\PH\it_fem.phd ..\..\..\dapicore\PH\p_it_rom.h it _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_IT_="..\..\..\dapicore\PH\it_mal.phd"	"..\..\..\dapicore\PH\it_fem.phd"	
# Begin Custom Build - Build p_it_rom.h
InputPath=..\..\..\dapicore\PH\p_it_rom.h

"..\..\..\dapicore\PH\p_it_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\it_mal.phd ..\..\..\dapicore\PH\it_fem.phd ..\..\..\dapicore\PH\p_it_rom.h it _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_IT_="..\..\..\dapicore\PH\it_mal.phd"	"..\..\..\dapicore\PH\it_fem.phd"	
# Begin Custom Build - Build p_it_rom.h
InputPath=..\..\..\dapicore\PH\p_it_rom.h

"..\..\..\dapicore\PH\p_it_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\it_mal.phd ..\..\..\dapicore\PH\it_fem.phd ..\..\..\dapicore\PH\p_it_rom.h it _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"
USERDEP__P_IT_="..\..\..\dapicore\PH\it_mal.phd"	"..\..\..\dapicore\PH\it_fem.phd"	
# Begin Custom Build - Build p_it_rom.h
InputPath=..\..\..\dapicore\PH\p_it_rom.h

"..\..\..\dapicore\PH\p_it_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\it_mal.phd ..\..\..\dapicore\PH\it_fem.phd ..\..\..\dapicore\PH\p_it_rom.h it _def
# End Custom Build
!ENDIF 
# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_ch_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_CH_="..\..\..\dapicore\PH\ch_mal.phd"	"..\..\..\dapicore\PH\ch_fem.phd"	
# Begin Custom Build - Build p_ch_rom.h
InputPath=..\..\..\dapicore\PH\p_ch_rom.h
"..\..\..\dapicore\PH\p_ch_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\ch_mal.phd ..\..\..\dapicore\PH\ch_fem.phd ..\..\..\dapicore\PH\p_ch_rom.h ch _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_CH_="..\..\..\dapicore\PH\ch_mal.phd"	"..\..\..\dapicore\PH\ch_fem.phd"	
# Begin Custom Build - Build p_ch_rom.h
InputPath=..\..\..\dapicore\PH\p_ch_rom.h
"..\..\..\dapicore\PH\p_ch_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\ch_mal.phd ..\..\..\dapicore\PH\ch_fem.phd ..\..\..\dapicore\PH\p_ch_rom.h ch _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_CH_="..\..\..\dapicore\PH\ch_mal.phd"	"..\..\..\dapicore\PH\ch_fem.phd"	
# Begin Custom Build - Build p_ch_rom.h
InputPath=..\..\..\dapicore\PH\p_ch_rom.h
"..\..\..\dapicore\PH\p_ch_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\ch_mal.phd ..\..\..\dapicore\PH\ch_fem.phd ..\..\..\dapicore\PH\p_ch_rom.h ch _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"
USERDEP__P_CH_="..\..\..\dapicore\PH\ch_mal.phd"	"..\..\..\dapicore\PH\ch_fem.phd"	
# Begin Custom Build - Build p_ch_rom.h
InputPath=..\..\..\dapicore\PH\p_ch_rom.h
"..\..\..\dapicore\PH\p_ch_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\ch_mal.phd ..\..\..\dapicore\PH\ch_fem.phd ..\..\..\dapicore\PH\p_ch_rom.h ch _def
# End Custom Build

!ENDIF 
# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_jp_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_JP_="..\..\..\dapicore\PH\jp_mal.phd"	"..\..\..\dapicore\PH\jp_fem.phd"	
# Begin Custom Build - Build p_jp_rom.h
InputPath=..\..\..\dapicore\PH\p_jp_rom.h
"..\..\..\dapicore\PH\p_jp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\jp_mal.phd ..\..\..\dapicore\PH\jp_fem.phd ..\..\..\dapicore\PH\p_jp_rom.h jp _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_JP_="..\..\..\dapicore\PH\jp_mal.phd"	"..\..\..\dapicore\PH\jp_fem.phd"	
# Begin Custom Build - Build p_jp_rom.h
InputPath=..\..\..\dapicore\PH\p_jp_rom.h
"..\..\..\dapicore\PH\p_jp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\jp_mal.phd ..\..\..\dapicore\PH\jp_fem.phd ..\..\..\dapicore\PH\p_jp_rom.h jp _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_JP_="..\..\..\dapicore\PH\jp_mal.phd"	"..\..\..\dapicore\PH\jp_fem.phd"	
# Begin Custom Build - Build p_jp_rom.h
InputPath=..\..\..\dapicore\PH\p_jp_rom.h
"..\..\..\dapicore\PH\p_jp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\jp_mal.phd ..\..\..\dapicore\PH\jp_fem.phd ..\..\..\dapicore\PH\p_jp_rom.h jp _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"

USERDEP__P_JP_="..\..\..\dapicore\PH\jp_mal.phd"	"..\..\..\dapicore\PH\jp_fem.phd"	
# Begin Custom Build - Build p_jp_rom.h
InputPath=..\..\..\dapicore\PH\p_jp_rom.h

"..\..\..\dapicore\PH\p_jp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\jp_mal.phd ..\..\..\dapicore\PH\jp_fem.phd ..\..\..\dapicore\PH\p_jp_rom.h jp _def

# End Custom Build

!ENDIF 
# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_kr_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_KR_="..\..\..\dapicore\PH\kr_mal.phd"	"..\..\..\dapicore\PH\kr_fem.phd"	
# Begin Custom Build - Build p_kr_rom.h
InputPath=..\..\..\dapicore\PH\p_kr_rom.h

"..\..\..\dapicore\PH\p_kr_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\kr_mal.phd ..\..\..\dapicore\PH\kr_fem.phd ..\..\..\dapicore\PH\p_kr_rom.h kr _def

# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_KR_="..\..\..\dapicore\PH\kr_mal.phd"	"..\..\..\dapicore\PH\kr_fem.phd"	
# Begin Custom Build - Build p_kr_rom.h
InputPath=..\..\..\dapicore\PH\p_kr_rom.h

"..\..\..\dapicore\PH\p_kr_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\kr_mal.phd ..\..\..\dapicore\PH\kr_fem.phd ..\..\..\dapicore\PH\p_kr_rom.h kr _def

# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_KR_="..\..\..\dapicore\PH\kr_mal.phd"	"..\..\..\dapicore\PH\kr_fem.phd"	
# Begin Custom Build - Build p_kr_rom.h
InputPath=..\..\..\dapicore\PH\p_kr_rom.h

"..\..\..\dapicore\PH\p_kr_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\kr_mal.phd ..\..\..\dapicore\PH\kr_fem.phd ..\..\..\dapicore\PH\p_kr_rom.h kr _def

# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"

USERDEP__P_KR_="..\..\..\dapicore\PH\kr_mal.phd"	"..\..\..\dapicore\PH\kr_fem.phd"	
# Begin Custom Build - Build p_kr_rom.h
InputPath=..\..\..\dapicore\PH\p_kr_rom.h

"..\..\..\dapicore\PH\p_kr_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\kr_mal.phd ..\..\..\dapicore\PH\kr_fem.phd ..\..\..\dapicore\PH\p_kr_rom.h kr _def

# End Custom Build

!ENDIF 
# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_la_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_LA_="..\..\..\dapicore\PH\la_mal.phd"	"..\..\..\dapicore\PH\la_fem.phd"	
# Begin Custom Build - Build p_la_rom.h
InputPath=..\..\..\dapicore\PH\p_la_rom.h

"..\..\..\dapicore\PH\p_la_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\la_mal.phd ..\..\..\dapicore\PH\la_fem.phd ..\..\..\dapicore\PH\p_la_rom.h la _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_LA_="..\..\..\dapicore\PH\la_mal.phd"	"..\..\..\dapicore\PH\la_fem.phd"	
# Begin Custom Build - Build p_la_rom.h
InputPath=..\..\..\dapicore\PH\p_la_rom.h

"..\..\..\dapicore\PH\p_la_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\la_mal.phd ..\..\..\dapicore\PH\la_fem.phd ..\..\..\dapicore\PH\p_la_rom.h la _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_LA_="..\..\..\dapicore\PH\la_mal.phd"	"..\..\..\dapicore\PH\la_fem.phd"	
# Begin Custom Build - Build p_la_rom.h
InputPath=..\..\..\dapicore\PH\p_la_rom.h

"..\..\..\dapicore\PH\p_la_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\la_mal.phd ..\..\..\dapicore\PH\la_fem.phd ..\..\..\dapicore\PH\p_la_rom.h la _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"

USERDEP__P_LA_="..\..\..\dapicore\PH\la_mal.phd"	"..\..\..\dapicore\PH\la_fem.phd"	
# Begin Custom Build - Build p_la_rom.h
InputPath=..\..\..\dapicore\PH\p_la_rom.h

"..\..\..\dapicore\PH\p_la_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\la_mal.phd ..\..\..\dapicore\PH\la_fem.phd ..\..\..\dapicore\PH\p_la_rom.h la _def
# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_sp_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_SP_="..\..\..\dapicore\PH\sp_mal.phd"	"..\..\..\dapicore\PH\sp_fem.phd"	
# Begin Custom Build - Build p_sp_rom.h
InputPath=..\..\..\dapicore\PH\p_sp_rom.h

"..\..\..\dapicore\PH\p_sp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\sp_mal.phd ..\..\..\dapicore\PH\sp_fem.phd ..\..\..\dapicore\PH\p_sp_rom.h sp _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_SP_="..\..\..\dapicore\PH\sp_mal.phd"	"..\..\..\dapicore\PH\sp_fem.phd"	
# Begin Custom Build - Build p_sp_rom.h
InputPath=..\..\..\dapicore\PH\p_sp_rom.h

"..\..\..\dapicore\PH\p_sp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\sp_mal.phd ..\..\..\dapicore\PH\sp_fem.phd ..\..\..\dapicore\PH\p_sp_rom.h sp _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_SP_="..\..\..\dapicore\PH\sp_mal.phd"	"..\..\..\dapicore\PH\sp_fem.phd"	
# Begin Custom Build - Build p_sp_rom.h
InputPath=..\..\..\dapicore\PH\p_sp_rom.h

"..\..\..\dapicore\PH\p_sp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\sp_mal.phd ..\..\..\dapicore\PH\sp_fem.phd ..\..\..\dapicore\PH\p_sp_rom.h sp _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"
USERDEP__P_SP_="..\..\..\dapicore\PH\sp_mal.phd"	"..\..\..\dapicore\PH\sp_fem.phd"	
# Begin Custom Build - Build p_sp_rom.h
InputPath=..\..\..\dapicore\PH\p_sp_rom.h

"..\..\..\dapicore\PH\p_sp_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\sp_mal.phd ..\..\..\dapicore\PH\sp_fem.phd ..\..\..\dapicore\PH\p_sp_rom.h sp _def
# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_uk_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_UK_="..\..\..\dapicore\PH\uk_mal.phd"	"..\..\..\dapicore\PH\uk_fem.phd"	
# Begin Custom Build - Build p_uk_rom.h
InputPath=..\..\..\dapicore\PH\p_uk_rom.h
"..\..\..\dapicore\PH\p_uk_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\uk_mal.phd ..\..\..\dapicore\PH\uk_fem.phd ..\..\..\dapicore\PH\p_uk_rom.h uk _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_UK_="..\..\..\dapicore\PH\uk_mal.phd"	"..\..\..\dapicore\PH\uk_fem.phd"	
# Begin Custom Build - Build p_uk_rom.h
InputPath=..\..\..\dapicore\PH\p_uk_rom.h
"..\..\..\dapicore\PH\p_uk_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\uk_mal.phd ..\..\..\dapicore\PH\uk_fem.phd ..\..\..\dapicore\PH\p_uk_rom.h uk _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_UK_="..\..\..\dapicore\PH\uk_mal.phd"	"..\..\..\dapicore\PH\uk_fem.phd"	
# Begin Custom Build - Build p_uk_rom.h
InputPath=..\..\..\dapicore\PH\p_uk_rom.h
"..\..\..\dapicore\PH\p_uk_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\uk_mal.phd ..\..\..\dapicore\PH\uk_fem.phd ..\..\..\dapicore\PH\p_uk_rom.h uk _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"
USERDEP__P_UK_="..\..\..\dapicore\PH\uk_mal.phd"	"..\..\..\dapicore\PH\uk_fem.phd"	
# Begin Custom Build - Build p_uk_rom.h
InputPath=..\..\..\dapicore\PH\p_uk_rom.h
"..\..\..\dapicore\PH\p_uk_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\uk_mal.phd ..\..\..\dapicore\PH\uk_fem.phd ..\..\..\dapicore\PH\p_uk_rom.h uk _def
# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\p_us_rom.h

!IF  "$(CFG)" == "dectalkstatic - Win32 Release LowCompute"
USERDEP__P_US_="..\..\..\dapicore\ph\us_mal.phd"	"..\..\..\dapicore\ph\us_fem.phd"	
# Begin Custom Build - Build p_us_rom.h
InputPath=..\..\..\dapicore\PH\p_us_rom.h
"..\..\..\dapicore\PH\p_us_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\us_mal.phd ..\..\..\dapicore\PH\us_fem.phd ..\..\..\dapicore\PH\p_us_rom.h us _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug LowCompute"
USERDEP__P_US_="..\..\..\dapicore\ph\us_mal.phd"	"..\..\..\dapicore\ph\us_fem.phd"	
# Begin Custom Build - Build p_us_rom.h
InputPath=..\..\..\dapicore\PH\p_us_rom.h
"..\..\..\dapicore\PH\p_us_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\us_mal.phd ..\..\..\dapicore\PH\us_fem.phd ..\..\..\dapicore\PH\p_us_rom.h us _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Release HighCompute"
USERDEP__P_US_="..\..\..\dapicore\ph\us_mal.phd"	"..\..\..\dapicore\ph\us_fem.phd"	
# Begin Custom Build - Build p_us_rom.h
InputPath=..\..\..\dapicore\PH\p_us_rom.h
"..\..\..\dapicore\PH\p_us_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\us_mal.phd ..\..\..\dapicore\PH\us_fem.phd ..\..\..\dapicore\PH\p_us_rom.h us _def
# End Custom Build

!ELSEIF  "$(CFG)" == "dectalkstatic - Win32 Debug HighCompute"
USERDEP__P_US_="..\..\..\dapicore\ph\us_mal.phd"	"..\..\..\dapicore\ph\us_fem.phd"	
# Begin Custom Build - Build p_us_rom.h
InputPath=..\..\..\dapicore\PH\p_us_rom.h
"..\..\..\dapicore\PH\p_us_rom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\..\dapicore\PH\phc ..\..\..\dapicore\PH\us_mal.phd ..\..\..\dapicore\PH\us_fem.phd ..\..\..\dapicore\PH\p_us_rom.h us _def
# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\..\..\dapicore\PH\P_us_vdf1.h
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

SOURCE=..\..\..\shared\include\NT\playaud.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\NT\playaudd.h
# End Source File
# Begin Source File

SOURCE=..\include\port.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\INCLUDE\samprate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\shared\include\NT\shmalloc.h
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

SOURCE=..\..\..\DAPI\Tts.h
# End Source File
# Begin Source File

SOURCE=..\..\..\sdk\include\ttsapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\ttserr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPI\ttsfeat.h
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
