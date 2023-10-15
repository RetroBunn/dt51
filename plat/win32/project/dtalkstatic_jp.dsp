# Microsoft Developer Studio Project File - Name="dtalkstatic_jp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dtalkstatic_jp - Win32 Debug Integer
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dtalkstatic_jp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dtalkstatic_jp.mak" CFG="dtalkstatic_jp - Win32 Debug LowCompute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dtalkstatic_jp - Win32 Release HighCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dtalkstatic_jp - Win32 Debug HighCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dtalkstatic_jp - Win32 Release LowCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dtalkstatic_jp - Win32 Debug LowCompute" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dtalkstatic_jp - Win32 Release HighCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\static\HighCompute\Release"
# PROP Intermediate_Dir ".\..\build\dectalk\static\HighCompute\Release\jp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\japan\CodePageConv" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_JP_EXPORS" /D "JAPANESE" /D "BUILD_LTS" /D "NDEBUG" /D "HLSYN" /D "DUSTY" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\HighCompute\Release\dtalk_jp.lib"

!ELSEIF  "$(CFG)" == "dtalkstatic_jp - Win32 Debug HighCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dtalkstatic_jp___Win32_Debug"
# PROP BASE Intermediate_Dir "dtalkstatic_jp___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\static\HighCompute\Debug"
# PROP Intermediate_Dir ".\..\build\dectalk\static\HighCompute\Debug\jp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\japan\CodePageConv" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_JP_EXPORTS" /D "JAPANESE" /D "BUILD_LTS" /D "DUSTY" /D "_DEBUG" /D "HLSYN" /D "FNX_LEAN_AND_MEAN" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\HighCompute\Debug\dtalk_jp.lib"

!ELSEIF  "$(CFG)" == "dtalkstatic_jp - Win32 Release LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Integer"
# PROP BASE Intermediate_Dir "Release Integer"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\static\LowCompute\Release"
# PROP Intermediate_Dir ".\..\build\dectalk\static\LowCompute\Release\jp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\japan\CodePageConv" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_JP_EXPORTS" /D "JAPANESE" /D "BUILD_LTS" /D "NDEBUG" /D "DUSTY" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\LowCompute\Release\dtalk_jp.lib"

!ELSEIF  "$(CFG)" == "dtalkstatic_jp - Win32 Debug LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug Integer"
# PROP BASE Intermediate_Dir "Debug Integer"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\static\LowCompute\Debug"
# PROP Intermediate_Dir ".\..\build\dectalk\static\LowCompute\Debug\jp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\japan\CodePageConv" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_JP_EXPORTS" /D "JAPANESE" /D "BUILD_LTS" /D "DUSTY" /D "_DEBUG" /D "INTEGER" /D "MULTIPLE_LANGUAGES_LOADED" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\LowCompute\Debug\dtalk_jp.lib"

!ENDIF 

# Begin Target

# Name "dtalkstatic_jp - Win32 Release HighCompute"
# Name "dtalkstatic_jp - Win32 Debug HighCompute"
# Name "dtalkstatic_jp - Win32 Release LowCompute"
# Name "dtalkstatic_jp - Win32 Debug LowCompute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_000x.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_1000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_2000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_22xx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_24xx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_3000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\acc_5000.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\CodePageConv\CodePageConv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\dsp_roma.c
# End Source File
# Begin Source File

SOURCE=.\dtalk_jp.def
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_accd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_accp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_bufc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_bunc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_data.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_dbgc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_edic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_envc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_errc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_hnkc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_idic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_jknc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_kana.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_kkhc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_mruc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_numc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_nydc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_othc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_rnsc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_rtgc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_rtkc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_sskc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_stcc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_stzc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_suhc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_tdic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_v5cc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_jp_ad1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_jp_con.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_jp_ma1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_jp_pr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_jp_ru1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_jp_sp1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\lib_genc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\lib_shdc.c
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

SOURCE=..\..\..\dapicore\LTS\japan\mkhatu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\stdonsei.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\DAPICORE\LTS\JAPAN\CodePageConv\CodePageConv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\dustytypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\entrypt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_accd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_acch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_bunh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_dbgh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_edic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_envh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_errh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_fddh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_func.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_idic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_jknh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_kkhh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_mjzh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_mruh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_nydh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_rnsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_shdh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_sskh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_stch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_stzh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_tdic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\ile_v5ch.h
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

SOURCE=..\..\..\dapicore\LTS\ls_homo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_rule.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DAPICORE\LTS\JAPAN\CodePageConv\MergedCodeTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\onsei.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\onsei_s.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\onseiapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\japan\pkind.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
