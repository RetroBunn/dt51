# Microsoft Developer Studio Project File - Name="FonixTtsDtSimpleFR_464" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FonixTtsDtSimpleFR_464 - Win32 NAND Debug low compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FonixTtsDtSimpleFR_464.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FonixTtsDtSimpleFR_464.mak" CFG="FonixTtsDtSimpleFR_464 - Win32 NAND Debug low compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FonixTtsDtSimpleFR_464 - Win32 NAND Release low compute" (based on "Win32 (x86) Static Library")
!MESSAGE "FonixTtsDtSimpleFR_464 - Win32 NAND Debug low compute" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FonixTtsDtSimpleFR_464 - Win32 NAND Release low compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "FonixTtsDtSimpleFR_464___Win32_NAND_Release_low_compute"
# PROP BASE Intermediate_Dir "FonixTtsDtSimpleFR_464___Win32_NAND_Release_low_compute"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "NAND_Release_low_compute"
# PROP Intermediate_Dir "NAND_Release_low_compute"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "NDEBUG" /D "DTALK_FR_EXPORTS" /D "BUILD_LTS" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "FRENCH" /D "NO_PRINTF" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\plat\ARM7TDMI\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\..\dtalk_464_casio\\" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\API" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\CMD" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\INCLUDE" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\KERNEL" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\NT" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\PH" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "NDEBUG" /D "DTALK_FR_EXPORTS" /D "BUILD_LTS" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "NO_ALIGN_8" /D "FRENCH" /D "NO_PRINTF" /D "USE_NAND" /D "USE_464" /D "CASIO_SH3" /YX /FD /c
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
PostBuild_Cmds=xcopy NAND_Release_low_compute\FonixTtsDtSimpleFR_464.lib ..\..\..\lib\ /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "FonixTtsDtSimpleFR_464 - Win32 NAND Debug low compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FonixTtsDtSimpleFR_464___Win32_NAND_Debug_low_compute"
# PROP BASE Intermediate_Dir "FonixTtsDtSimpleFR_464___Win32_NAND_Debug_low_compute"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "NAND_Debug_low_compute"
# PROP Intermediate_Dir "NAND_Debug_low_compute"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\..\ARM7TDMI\include" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I "..\..\..\..\..\dapicore\CMD" /I "..\..\..\..\..\dapicore\INCLUDE" /I "..\..\..\..\..\dapicore\KERNEL" /I "..\..\..\..\..\dapicore\LTS" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\dic" /I "..\..\..\..\..\dapicore\NT" /I "..\..\..\..\..\dapicore\PH" /I "..\..\..\..\..\dapicore\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "_DEBUG" /D "DTALK_FR_EXPORTS" /D "BUILD_LTS" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "EMB_INDEX_MARKS" /D "NO_ALIGN_8" /D "FRENCH" /D "NO_PRINTF" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\dapicore\LTS\korean" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\plat\ARM7TDMI\include" /I "..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapicore\LTS\japan" /I "..\..\..\..\..\dapicore\LTS\chinese" /I "..\..\..\..\..\..\dtalk_464_casio\\" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\API" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\CMD" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\INCLUDE" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\KERNEL" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\NT" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\PH" /I "..\..\..\..\..\..\dtalk_464_casio\dapi\src\VTM" /I "..\..\..\..\..\dic\buildfilesystemdic\win32" /I "..\..\..\..\..\dic\buildfilesystemdic" /I "..\..\..\..\..\dic\buildfilesystemtables" /I "..\..\..\..\..\dic\buildfilesystemtables\win32" /D "_DEBUG" /D "DTALK_FR_EXPORTS" /D "BUILD_LTS" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /D "_WINDOWS" /D "_MBCS" /D "ARM7" /D "BLD_DECTALK_DLL" /D "ARM7_NOSWI" /D "NO_INCLUDED_C_FILES" /D "MULTIPLE_LANGUAGES_LOADED" /D "NO_ALIGN_8" /D "FRENCH" /D "NO_PRINTF" /D "USE_NAND" /D "USE_464" /D "CASIO_SH3" /FR /YX /FD /GZ /c
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
PostBuild_Cmds=xcopy NAND_Debug_low_compute\FonixTtsDtSimpleFR_464.lib ..\..\..\lib\NAND_Debug_low_compute /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "FonixTtsDtSimpleFR_464 - Win32 NAND Release low compute"
# Name "FonixTtsDtSimpleFR_464 - Win32 NAND Debug low compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "LTS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_con.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_ma1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_pr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_rta.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_ru1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_sp1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\l_fr_suf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\loaddict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_adju.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_homo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_math.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_rule.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_rule2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_spel.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_suff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\ls_util.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\dtalk_464_casio\dapi\src\LTS\lsw_main.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
