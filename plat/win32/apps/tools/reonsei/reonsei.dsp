# Microsoft Developer Studio Project File - Name="reonsei" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=reonsei - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "reonsei.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "reonsei.mak" CFG="reonsei - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "reonsei - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "reonsei - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "reonsei - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\..\..\..\..\..\dapicore\lts\korean" /I ".\..\..\..\..\..\shared\include\\" /I ".\..\..\..\..\..\dapicore\lts\japan" /I ".\..\..\..\..\..\shared\include\NT" /I ".\..\..\..\..\..\shared\include\nt" /I "..\..\..\..\..\dapicore\LTS\japan\CodePageConv" /I ".\..\..\..\..\..\dapicore\lts\chinese" /I "..\..\..\include" /I ".\..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\sdk\include\win32" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "JAPANESE" /D "BUILD_LTS" /D "DUSTY" /D "HLSYN" /D "NO_INCLUDED_C_FILES" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "NEW_MULTI_LANG_ARCH" /D "_WINDOWS" /D "O_TALKONLY" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "reonsei - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\..\..\..\..\..\dapicore\lts\korean" /I ".\..\..\..\..\..\shared\include\\" /I ".\..\..\..\..\..\dapicore\lts\japan" /I ".\..\..\..\..\..\shared\include\NT" /I ".\..\..\..\..\..\shared\include\nt" /I "..\..\..\..\..\dapicore\LTS\japan\CodePageConv" /I ".\..\..\..\..\..\dapicore\lts\chinese" /I "..\..\..\include" /I ".\..\..\..\..\..\shared\include" /I "..\..\..\..\..\dapi" /I ".\..\..\..\..\..\dapicore\cmd" /I ".\..\..\..\..\..\dapicore\lts" /I ".\..\..\..\..\..\dapicore\ph" /I ".\..\..\..\..\..\dapicore\vtm" /I ".\..\..\..\..\..\dapicore\kernel" /I ".\..\..\..\..\..\dapicore\include" /I ".\..\..\..\..\..\dapicore\hlsyn" /I "..\..\..\..\..\sdk\include" /I "..\..\..\..\..\sdk\include\win32" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "JAPANESE" /D "BUILD_LTS" /D "DUSTY" /D "HLSYN" /D "NO_INCLUDED_C_FILES" /D "_USRDLL" /D "i386" /D "BLD_DECTALK_DLL" /D "NEW_MULTI_LANG_ARCH" /D "_WINDOWS" /D "O_TALKONLY" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "reonsei - Win32 Release"
# Name "reonsei - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\reonsei.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
