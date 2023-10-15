# Microsoft Developer Studio Project File - Name="dtalkstatic_kr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dtalkstatic_kr - Win32 Debug Integer
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dtalkstatic_kr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dtalkstatic_kr.mak" CFG="dtalkstatic_kr - Win32 Debug LowCompute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dtalkstatic_kr - Win32 Release HighCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dtalkstatic_kr - Win32 Debug HighCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dtalkstatic_kr - Win32 Release LowCompute" (based on "Win32 (x86) Static Library")
!MESSAGE "dtalkstatic_kr - Win32 Debug LowCompute" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dtalkstatic_kr - Win32 Release HighCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\static\HighCompute\Release"
# PROP Intermediate_Dir ".\..\build\dectalk\static\HighCompute\Release\kr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_KR_EXPORTS" /D "KOREAN" /D "BUILD_LTS" /D "NDEBUG" /D "HLSYN" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\HighCompute\Release\dtalk_kr.lib"

!ELSEIF  "$(CFG)" == "dtalkstatic_kr - Win32 Debug HighCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dtalkstatic_kr___Win32_Debug"
# PROP BASE Intermediate_Dir "dtalkstatic_kr___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\static\HighCompute\Debug"
# PROP Intermediate_Dir ".\..\build\dectalk\static\HighCompute\Debug\kr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_KR_EXPORTS" /D "KOREAN" /D "BUILD_LTS" /D "_DEBUG" /D "HLSYN" /D "FNX_LEAN_AND_MEAN" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\HighCompute\Debug\dtalk_kr.lib"

!ELSEIF  "$(CFG)" == "dtalkstatic_kr - Win32 Release LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Integer"
# PROP BASE Intermediate_Dir "Release Integer"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\build\dectalk\static\LowCompute\Release"
# PROP Intermediate_Dir ".\..\build\dectalk\static\LowCompute\Release\kr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_KR_EXPORTS" /D "KOREAN" /D "BUILD_LTS" /D "NDEBUG" /D "INTEGER" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /D "MULTIPLE_LANGUAGES_LOADED" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\LowCompute\Release\dtalk_kr.lib"

!ELSEIF  "$(CFG)" == "dtalkstatic_kr - Win32 Debug LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug Integer"
# PROP BASE Intermediate_Dir "Debug Integer"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\build\dectalk\static\LowCompute\Debug"
# PROP Intermediate_Dir ".\..\build\dectalk\static\LowCompute\Debug\kr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\..\include" /I ".\..\..\..\dapi" /I ".\..\..\..\dapicore\cmd" /I ".\..\..\..\dapicore\hlsyn" /I ".\..\..\..\dapicore\include" /I ".\..\..\..\dapicore\kernel" /I ".\..\..\..\dapicore\lts" /I ".\..\..\..\dapicore\lts\japan" /I ".\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\dapicore\lts\korean" /I ".\..\..\..\dapicore\ph" /I ".\..\..\..\dapicore\vtm" /I ".\..\..\..\shared\include" /I ".\..\..\..\shared\include" /I ".\..\..\..\sdk\include" /D "DTALK_KR_EXPORTS" /D "KOREAN" /D "BUILD_LTS" /D "FNX_LEAN_AND_MEAN" /D "_DEBUG" /D "INTEGER" /D "MULTIPLE_LANGUAGES_LOADED" /D "NO_INCLUDED_C_FILES" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "PRINTFDEBUG" /D "NEW_MULTI_LANG_ARCH" /D "WIN32_STATIC" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\build\dectalk\static\LowCompute\Debug\dtalk_kr.lib"

!ENDIF 

# Begin Target

# Name "dtalkstatic_kr - Win32 Release HighCompute"
# Name "dtalkstatic_kr - Win32 Debug HighCompute"
# Name "dtalkstatic_kr - Win32 Release LowCompute"
# Name "dtalkstatic_kr - Win32 Debug LowCompute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\allocate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\ByteOrder.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\ByteOrderIO.c
# End Source File
# Begin Source File

SOURCE=.\dtalk_kr.def
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\error.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\fnxstdlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\fnxWin32Exstdlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\Graph2Phon.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\hash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\Huffman.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\InitCloseDcc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\KoreanIntonation.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_kr_ad1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_kr_con.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_kr_ma1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_kr_pr1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_kr_ru1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\l_kr_sp1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\language.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\llist.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\loaddict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\LoadRules.c
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

SOURCE=..\..\..\dapicore\LTS\korean\Misc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\names.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\network.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\pool.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\SelectSinglePron.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\ShortenPronunciation.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\word.c
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\wrdparse.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\dccread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxAllocate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxByteOrder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxByteOrderIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxDesc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\fnxexstdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxFileIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxFiles.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxGenPron.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxHash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxHuffman.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxLlist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxMachine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxMisc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxNames.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxNetwork.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxPlatform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxStdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxVocab.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\FnxWord.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\language.h
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

SOURCE=..\..\..\dapicore\LTS\korean\phonetic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\dapicore\LTS\korean\SelectSinglePron.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
