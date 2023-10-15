<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: Dtsample - Win32 (WCE x86) Release English UK dll--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo".\build\dll\x86\uk\release\link/dtsample.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_HPC2000" /d "_X86_" /d "x86" /d "_i386_" /r "D:\work\PRODUCT\samplece\DTSAMPLE\dtsample.rc"" 
Creating temporary file "C:\DOCUME~1\build\LOCALS~1\Temp\RSP16D4.tmp" with contents
[
/nologo /W3 /GX- /I ".\..\..\dapi\src\include" /I ".\..\..\dapi\src\API" /I ".\..\..\\" /I ".\..\..\dapi\src\lts" /I ".\..\..\dapi\src\ph" /I ".\..\..\dapi\src\cmd" /I ".\..\..\dapi\src\nt" /I ".\..\..\dapi\src\kernel" /D _WIN32_WCE=300 /D "WIN32_PLATFORM_HPC2000" /D "_i386_" /D UNDER_CE=300 /D "i_386_" /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "NDEBUG" /Fp".\build\dll\x86\uk\release\link/Dtsample.pch" /YX /Fo".\build\dll\x86\uk\release\link/" /Gs8192 /MC /c 
"D:\work\PRODUCT\samplece\DTSAMPLE\dtsample.c"
]
Creating command line "cl.exe @C:\DOCUME~1\build\LOCALS~1\Temp\RSP16D4.tmp" 
Creating temporary file "C:\DOCUME~1\build\LOCALS~1\Temp\RSP16D5.tmp" with contents
[
.\..\..\dapi\build\cedll\x86\uk\release\dectalk.lib commctrl.lib coredll.lib corelibc.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMain" /incremental:no /pdb:".\build\dll\x86\uk\release/Dtsample.pdb" /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib /out:".\build\dll\x86\uk\release/Dtsample.exe" /machine:I386 /subsystem:windowsce,2.0 
.\build\dll\x86\uk\release\link\dtsample.obj
.\build\dll\x86\uk\release\link\dtsample.res
]
Creating command line "link.exe @C:\DOCUME~1\build\LOCALS~1\Temp\RSP16D5.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
Command line warning D4002 : ignoring unknown option '/MC'
dtsample.c
Linking...



<h3>Results</h3>
Dtsample.exe - 0 error(s), 1 warning(s)
</pre>
</body>
</html>
