echo off

set /P Casio=[Is this build for Casio (y/n)?: ]


cd ..\..\plat\win32\project
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "dic.dsw" /MAKE "BuildFileSystemDic - Win32 Debug" /REBUILD 

cd ..\..\..\dic\BuildFileSystemDic


echo Building US English dictionary
.\Debug\BuildFileSystemDic.exe -i "..\USEnglish\Dic_us.txt" -o .\Casio\dctalkus.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\USEnglish\Dic_us.txt" -o .\Win32\dtalk_us.nand.dic
.\Debug\BuildFileSystemDic.exe -i "..\USEnglish\Dic_us_Casio.txt" -o .\Casio\dctalkus_Casio.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\USEnglish\Dic_us_Casio.txt" -o .\Win32\dtalk_us_Casio.nand.dic
pause

echo Building French dictionary
.\Debug\BuildFileSystemDic.exe -i "..\French\Dic_fr.txt" -o .\Casio\dctalkfr.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\French\Dic_fr.txt" -o .\Win32\dtalk_fr.nand.dic
pause

echo Building German dictionary
.\Debug\BuildFileSystemDic.exe -i "..\German\Dic_gr.txt" -o .\Casio\dctalkgr.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\German\Dic_gr.txt" -o .\Win32\dtalk_gr.nand.dic
pause

echo Building Castillian Spanish dictionary
.\Debug\BuildFileSystemDic.exe -i "..\Spanish\Dic_sp.txt" -o .\Casio\dctalksp.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\Spanish\Dic_sp.txt" -o .\Win32\dtalk_sp.nand.dic
pause

echo Building Latin American dictionary
.\Debug\BuildFileSystemDic.exe -i "..\Spanish\Dic_la.txt" -o .\Casio\dctalkla.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\Spanish\Dic_la.txt" -o .\Win32\dtalk_la.nand.dic
pause

echo Building UK English dictionary
.\Debug\BuildFileSystemDic.exe -i "..\UKEnglish\Dic_uk.txt" -o .\Casio\dctalkuk.dic -b
.\Debug\BuildFileSystemDic.exe -i "..\UKEnglish\Dic_uk.txt" -o .\Win32\dtalk_uk.nand.dic
pause

echo Building German dictionary
dir /b/s/on "..\German\*.pho" > "..\German\filename.list"
.\Debug\BuildFileSystemDic.exe -i "..\German\filename.list" -o .\Casio\dctalkgr.dic -b -g
.\Debug\BuildFileSystemDic.exe -i "..\German\filename.list" -o .\Win32\dtalk_gr.nand.dic -g
pause

echo Building Italian dictionary
dir /b/s/on "..\Italian\*.pho" "..\Italian\*.tab" > "..\Italian\filename.list"
.\Debug\BuildFileSystemDic.exe -i "..\Italian\filename.list" -o .\Casio\dctalkit.dic -b -I
.\Debug\BuildFileSystemDic.exe -i "..\Italian\filename.list" -o .\Win32\dtalk_it.nand.dic -I
pause

echo Copying files to build folders
IF /I %Casio% EQU y ( 
xcopy Win32\dtalk_us_Casio.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_us.nand.dic /Y /D
) ELSE ( 
xcopy Win32\dtalk_us.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_us.nand.dic /Y /D
)
xcopy Win32\dtalk_us.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_us.nand.dic /Y /D
xcopy Win32\dtalk_fr.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_fr.nand.dic /Y /D
xcopy Win32\dtalk_sp.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_sp.nand.dic /Y /D
xcopy Win32\dtalk_gr.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_gr.nand.dic /Y /D
xcopy Win32\dtalk_it.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_it.nand.dic /Y /D
xcopy Win32\dtalk_la.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_la.nand.dic /Y /D
xcopy Win32\dtalk_uk.nand.dic .\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_uk.nand.dic /Y /D

IF /I %Casio% EQU y ( 
xcopy Win32\dtalk_us_Casio.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_us.nand.dic /Y /D
) ELSE ( 
xcopy Win32\dtalk_us.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_us.nand.dic /Y /D
)
xcopy Win32\dtalk_fr.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_fr.nand.dic /Y /D
xcopy Win32\dtalk_sp.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_sp.nand.dic /Y /D
xcopy Win32\dtalk_gr.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_gr.nand.dic /Y /D
xcopy Win32\dtalk_it.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_it.nand.dic /Y /D
xcopy Win32\dtalk_la.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_la.nand.dic /Y /D
xcopy Win32\dtalk_uk.nand.dic .\apps\TestTtsDtSimple\NAND_Debug_low_compute\dtalk_uk.nand.dic /Y /D

pause