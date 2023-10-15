# Microsoft Developer Studio Project File - Name="TuneCheck" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TuneCheck - Win32 Debug LowCompute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TuneCheck.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TuneCheck.mak" CFG="TuneCheck - Win32 Debug LowCompute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TuneCheck - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TuneCheck - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "TuneCheck - Win32 Release LowCompute" (based on "Win32 (x86) Console Application")
!MESSAGE "TuneCheck - Win32 Debug LowCompute" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TuneCheck - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\dapi\build\dectalk\common\HighCompute\release\"
# PROP Intermediate_Dir ".\us\release\link"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\plat\win32\include" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I ".\..\..\..\..\..\shared\include\\" /D "NDEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "BLD_DECTALK_DLL" /D "HLSYN" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\..\dapi\build\dectalk\common\release\dectalk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\..\..\dapi\build\dectalk\common\release\TuneCheck.exe .\..\..\dapi\build\dectalk\commonint\release\TuneCheck.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TuneCheck - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\..\build\dectalk\common\HighCompute\debug\"
# PROP Intermediate_Dir ".\us\debug\link"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\lts\chinese" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\plat\win32\include" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I ".\..\..\..\..\..\shared\include\\" /D "_DEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "BLD_DECTALK_DLL" /D "NEW_MULTI_LANG_ARCH" /D "HLSYN" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\..\..\..\build\dectalk\common\debug\TuneCheck.exe .\..\..\..\build\dectalk\commonint\debug\TuneCheck.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TuneCheck - Win32 Release LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TuneCheck___Win32_Release_LowCompute"
# PROP BASE Intermediate_Dir "TuneCheck___Win32_Release_LowCompute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\dapi\build\dectalk\common\LowCompute\release\"
# PROP Intermediate_Dir ".\us\releaselow\link"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\plat\win32\include" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I ".\..\..\..\..\..\shared\include\\" /D "NDEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "BLD_DECTALK_DLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\plat\win32\include" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I ".\..\..\..\..\..\shared\include\\" /D "NDEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "BLD_DECTALK_DLL" /D "INTEGER" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\dapi\build\dectalk\common\release\dectalk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\..\dapi\build\dectalk\common\release\dectalk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\..\..\dapi\build\dectalk\common\release\TuneCheck.exe .\..\..\dapi\build\dectalk\commonint\release\TuneCheck.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TuneCheck - Win32 Debug LowCompute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TuneCheck___Win32_Debug_LowCompute"
# PROP BASE Intermediate_Dir "TuneCheck___Win32_Debug_LowCompute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\..\build\dectalk\common\LowCompute\debug\"
# PROP Intermediate_Dir ".\us\debuglow\link"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\plat\win32\include" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I ".\..\..\..\..\..\shared\include\\" /D "_DEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "BLD_DECTALK_DLL" /D "NEW_MULTI_LANG_ARCH" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\plat\win32\include" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I ".\..\..\..\..\..\shared\include\\" /D "_DEBUG" /D "ENGLISH_US" /D "ENGLISH" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "BLD_DECTALK_DLL" /D "NEW_MULTI_LANG_ARCH" /D "INTEGER" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\..\..\..\build\dectalk\common\debug\TuneCheck.exe .\..\..\..\build\dectalk\commonint\debug\TuneCheck.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TuneCheck - Win32 Release"
# Name "TuneCheck - Win32 Debug"
# Name "TuneCheck - Win32 Release LowCompute"
# Name "TuneCheck - Win32 Debug LowCompute"
# Begin Source File

SOURCE=..\..\..\..\..\shared\src\opthread.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\port.h
# End Source File
# Begin Source File

SOURCE=.\Tunecheck.c
# End Source File
# Begin Source File

SOURCE=..\..\..\build\dectalk\common\debug\dectalk.lib
# End Source File
# End Target
# End Project
