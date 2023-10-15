# Microsoft Developer Studio Project File - Name="dcc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=dcc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dcc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dcc.mak" CFG="dcc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dcc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dcc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dcc - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "dcc - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
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

# Name "dcc - Win32 Release"
# Name "dcc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\allocate.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\ByteOrder.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\ByteOrderIO.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\error.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\fnxstdlib.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\fnxWin32Exstdlib.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\GetPron.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\Graph2Phon.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\hash.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\Huffman.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\InitCloseDcc.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\llist.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\LoadRules.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\Misc.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\names.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\network.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\pool.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\ShortenPronunciation.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\word.c
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\wrdparse.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\dccread.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxAllocate.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxByteOrder.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxByteOrderIO.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxDesc.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxError.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\fnxexstdlib.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxFileIO.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxFiles.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxGenPron.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxHash.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxHuffman.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxLlist.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxMachine.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxMisc.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxNames.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxNetwork.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxPlatform.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxPool.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxStdlib.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxVocab.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\FnxWord.h
# End Source File
# Begin Source File

SOURCE=..\DecTalkDict\ExtractPron\ExtractBrief\phonetic.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
