# Microsoft Developer Studio Project File - Name="armltsit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=armltsit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "armltsit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "armltsit.mak" CFG="armltsit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "armltsit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "armltsit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "armltsit - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /D "NO_INCLUDED_C_FILES" /D "NEW_MULTI_LANG_ARCH" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "armltsit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "armltsit___Win32_Debug"
# PROP BASE Intermediate_Dir "armltsit___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\build\armltsit\it\debug"
# PROP Intermediate_Dir "..\build\armltsit\it\debug\link"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\api" /I ".\cmd" /I ".\lts" /I ".\ph" /I ".\vtm" /I ".\kernel" /I ".\nt" /I ".\include" /I ".\hlsyn" /I ".\arm7" /I "..\.." /I ".\..\..\..\dapicore\lts\chinese" /I "..\include" /I ".\..\..\..\shared\include" /I "..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\hlsyn" /I "..\..\..\sdk\include" /I "..\..\..\sdk\include\win32" /I ".\..\..\..\dapicore\lts\codepageconv" /I ".\..\..\..\dapicore\lts\japan" /D "_LIB" /D "BLD_DECTALK_DLL" /D "ARM7" /D "ITALIAN" /D "ARM7_NOSWI" /D "i386" /D "EPSON_ARM7" /D "CHEESY_DICT_COMPRESSION" /D "WIN32_TEST" /D "_MBCS" /D "NO_INCLUDED_C_FILES" /D "NEW_MULTI_LANG_ARCH" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "armltsit - Win32 Release"
# Name "armltsit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\execrules.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\GtWalkerlinear.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_it_ad1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_it_con.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_it_ma1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_it_pr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_it_ru1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_it_sp1.c
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

SOURCE=..\..\..\dapicore\LTS\ls_spel.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_suff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\ls_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\LSA_ADJU.C
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_fr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_gr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_ir.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_it.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_ja.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_rtbi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_rule.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_sl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_sp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_us.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsa_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\lsw_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\maindict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\userules.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\walkerit.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
