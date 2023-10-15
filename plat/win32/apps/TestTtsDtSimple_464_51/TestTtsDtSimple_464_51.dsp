# Microsoft Developer Studio Project File - Name="TestTtsDtSimple_464_51" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestTtsDtSimple_464_51 - Win32 NAND Debug low compute
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestTtsDtSimple_464_51.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestTtsDtSimple_464_51.mak" CFG="TestTtsDtSimple_464_51 - Win32 NAND Debug low compute"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestTtsDtSimple_464_51 - Win32 NAND Release low compute" (based on "Win32 (x86) Application")
!MESSAGE "TestTtsDtSimple_464_51 - Win32 NAND Debug low compute" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestTtsDtSimple_464_51 - Win32 NAND Release low compute"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TestTtsDtSimple_464_51___Win32_NAND_Release_low_compute0"
# PROP BASE Intermediate_Dir "TestTtsDtSimple_464_51___Win32_NAND_Release_low_compute0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "NAND_Release_low_compute"
# PROP Intermediate_Dir "NAND_Release_low_compute"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I ".\include" /I "..\..\..\..\include" /I "..\..\..\..\sdk\include" /D "INTEGER" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "DICT_IN_MEMORY" /D "_AFXDLL" /FR /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I ".\include" /I "..\..\..\..\include" /I "..\..\..\..\sdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /D "USE_NAND" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"LIBCMT.lib"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 winmm.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"LIBCMT.lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "TestTtsDtSimple_464_51 - Win32 NAND Debug low compute"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestTtsDtSimple_464_51___Win32_NAND_Debug_low_compute0"
# PROP BASE Intermediate_Dir "TestTtsDtSimple_464_51___Win32_NAND_Debug_low_compute0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "NAND_Debug_low_compute"
# PROP Intermediate_Dir "NAND_Debug_low_compute"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I ".\include" /I "..\..\..\..\include" /I "..\..\..\..\sdk\include" /D "INTEGER" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I ".\include" /I "..\..\..\..\include" /I "..\..\..\..\sdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /D "USE_NAND" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmt.lib" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 winmm.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmt.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "TestTtsDtSimple_464_51 - Win32 NAND Release low compute"
# Name "TestTtsDtSimple_464_51 - Win32 NAND Debug low compute"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Speaker.c
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestTtsDtSimple.cpp
# End Source File
# Begin Source File

SOURCE=.\TestTtsDtSimple_464_51.rc
# End Source File
# Begin Source File

SOURCE=.\TestTtsDtSimpleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteWavFile.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestTtsDtSimple.h
# End Source File
# Begin Source File

SOURCE=.\TestTtsDtSimpleDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TestTtsDtSimple.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestTtsDtSimple.rc2
# End Source File
# Begin Source File

SOURCE=.\res\TestTtsDtSimple_464_51.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\..\lib\FonixCommon40.lib
# End Source File
# End Target
# End Project
