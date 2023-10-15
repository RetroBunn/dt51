# Microsoft Developer Studio Project File - Name="speak" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=speak - Win32 Debug High Compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "speak.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "speak.mak" CFG="speak - Win32 Debug High Compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "speak - Win32 Debug Low Compute" (based on "Win32 (x86) Application")
!MESSAGE "speak - Win32 Release Low Compute" (based on "Win32 (x86) Application")
!MESSAGE "speak - Win32 Debug High Compute" (based on "Win32 (x86) Application")
!MESSAGE "speak - Win32 Release High Compute" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "speak - Win32 Debug Low Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "speak___Win32_Debug_Low_Compute"
# PROP BASE Intermediate_Dir "speak___Win32_Debug_Low_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\build\dectalk\common\LowCompute\debug"
# PROP Intermediate_Dir "LowCompute\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\..\..\..\DAPICORE\LTS\JAPAN\CodePageConv" /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "ENGLISH_US" /D "WIN32" /D "_WINDOWS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /I "..\..\..\..\DAPICORE\LTS\CodePageConv" /I "..\..\include" /D "UNICODE" /D "_UNICODE" /D "ENGLISH_US" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "INTEGER" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "ML" /d "FRENCH"
# ADD RSC /l 0x40c /d "_DEBUG" /d "ML" /d "FRENCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /debug /debugtype:both /machine:I386
# SUBTRACT BASE LINK32 /pdb:none /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /debug /debugtype:both /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "speak - Win32 Release Low Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "speak___Win32_Release_Low_Compute"
# PROP BASE Intermediate_Dir "speak___Win32_Release_Low_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\build\dectalk\common\LowCompute\release"
# PROP Intermediate_Dir "Low_Compute\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /I "..\..\..\..\DAPICORE\LTS\JAPAN\CodePageConv" /D "NDEBUG" /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "ENGLISH_US" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Ox /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /I "..\..\..\..\DAPICORE\LTS\CodePageConv" /I "..\..\include" /D "UNICODE" /D "_UNICODE" /D "ENGLISH_US" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "INTEGER" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "ML" /d "FRENCH"
# ADD RSC /l 0x40c /d "NDEBUG" /d "ML" /d "FRENCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:yes /nodefaultlib

!ELSEIF  "$(CFG)" == "speak - Win32 Debug High Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "speak___Win32_Debug_High_Compute"
# PROP BASE Intermediate_Dir "speak___Win32_Debug_High_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\build\dectalk\common\HighCompute\debug"
# PROP Intermediate_Dir "HighCompute\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\..\..\..\DAPICORE\LTS\JAPAN\CodePageConv" /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "ENGLISH_US" /D "WIN32" /D "_WINDOWS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /I "..\..\..\..\DAPICORE\LTS\CodePageConv" /I "..\..\include" /D "UNICODE" /D "_UNICODE" /D "ENGLISH_US" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "HLSYN" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "ML" /d "FRENCH"
# ADD RSC /l 0x40c /d "_DEBUG" /d "ML" /d "FRENCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /debug /debugtype:both /machine:I386
# SUBTRACT BASE LINK32 /pdb:none /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /debug /debugtype:both /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "speak - Win32 Release High Compute"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "speak___Win32_Release_High_Compute"
# PROP BASE Intermediate_Dir "speak___Win32_Release_High_Compute"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\build\dectalk\common\HighCompute\release"
# PROP Intermediate_Dir "HighCompute\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /I "..\..\..\..\DAPICORE\LTS\JAPAN\CodePageConv" /D "NDEBUG" /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "ENGLISH_US" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Ox /I "..\..\..\..\sdk\include" /I "..\..\..\..\DAPI" /I "..\..\..\..\shared\include" /I "..\..\..\..\DAPICORE\LTS\CodePageConv" /I "..\..\include" /D "UNICODE" /D "_UNICODE" /D "ENGLISH_US" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "HLSYN" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "ML" /d "FRENCH"
# ADD RSC /l 0x40c /d "NDEBUG" /d "ML" /d "FRENCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:yes /nodefaultlib

!ENDIF 

# Begin Target

# Name "speak - Win32 Debug Low Compute"
# Name "speak - Win32 Release Low Compute"
# Name "speak - Win32 Debug High Compute"
# Name "speak - Win32 Release High Compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\..\..\dapicore\LTS\CodePageConv\CodePageConv.c
# End Source File
# Begin Source File

SOURCE=.\DevFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Speak.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\..\..\dapicore\LTS\CodePageConv\CodeConvTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\dapicore\LTS\CodePageConv\CodePageConv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\DAPI\coop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\shared\include\dectalkf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\DTFnxExStdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\shared\include\DTFnxStdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\shared\include\opatype.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\shared\include\opmmsys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\shared\include\playaudd.h
# End Source File
# Begin Source File

SOURCE=..\..\include\port.h
# End Source File
# Begin Source File

SOURCE=.\Speak.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\sdk\include\ttsapi.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Bitmaps"

# PROP Default_Filter "bmp"
# Begin Source File

SOURCE=.\PauseButton.bmp
# End Source File
# Begin Source File

SOURCE=.\PauseButtonDn.bmp
# End Source File
# Begin Source File

SOURCE=.\PlayButton.bmp
# End Source File
# Begin Source File

SOURCE=.\PlayButtonDn.bmp
# End Source File
# Begin Source File

SOURCE=.\StopButton.bmp
# End Source File
# Begin Source File

SOURCE=.\StopButtonDn.bmp
# End Source File
# Begin Source File

SOURCE=.\TTSDemo.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\speak.ico
# End Source File
# Begin Source File

SOURCE=.\speak.rc
# End Source File
# End Group
# End Target
# End Project
