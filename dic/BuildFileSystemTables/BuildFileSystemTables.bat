.\Debug\BuildFileSystemTables.exe -i .\French.list -o .\Win32\French.nand.tab
.\Debug\BuildFileSystemTables.exe -i .\French.list -o .\Casio\French.nand.tab -B

.\Debug\BuildFileSystemTables.exe -i .\UsEnglish.list -o .\Win32\UsEnglish.nand.tab 
.\Debug\BuildFileSystemTables.exe -i .\UsEnglish.list -o .\Casio\UsEnglish.nand.tab -B

.\Debug\BuildFileSystemTables.exe -i .\dectalk.list -o .\Win32\Dectalk.nand.tab 
.\Debug\BuildFileSystemTables.exe -i .\dectalk.list -o .\Casio\Dectalk.nand.tab -B

REM .\Debug\BuildFileSystemTables.exe -i .\German.list -o .\Win32\German.nand.tab
REM .\Debug\BuildFileSystemTables.exe -i .\German.list -o .\Casio\German.nand.tab -B

REM -i .\replacerules.list -o .\Win32\replacerules.nand.tab -t


copy .\Win32\French.nand.tab ..\..\plat\win32\apps\TestTtsDtSimple\NAND_Release_low_compute\French.nand.tab
copy .\Win32\UsEnglish.nand.tab ..\..\plat\win32\apps\TestTtsDtSimple\NAND_Release_low_compute\UsEnglish.nand.tab
REM copy .\Win32\German.nand.tab ..\..\plat\win32\apps\TestTtsDtSimple\NAND_Release_low_compute\dtalk_sp.nand.dic


copy .\Win32\French.nand.tab ..\..\plat\win32\apps\TestTtsDtSimple\NAND_Debug_low_compute\French.nand.tab
copy .\Win32\UsEnglish.nand.tab ..\..\plat\win32\apps\TestTtsDtSimple\NAND_Debug_low_compute\UsEnglish.nand.tab
REM copy .\Win32\German.nand.tab ..\..\plat\win32\apps\TestTtsDtSimple\NAND_Debug_low_compute\German.nand.tab

pause
