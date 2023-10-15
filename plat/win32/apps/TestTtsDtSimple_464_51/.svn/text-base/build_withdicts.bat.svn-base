cd ..\..\..\..\dic
call build_all_dictinmem.bat

cd ..\..\..\..\..\..\dic\BuildFileSystemDic
call BuildNandDicts.bat

cd ..\BuildFileSystemTables
call BuildFileSystemTables.bat

cd ..\..\plat\win32\apps\TestTtsDtSimple_464_51

"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "TestTtsDtSimple_464_51.dsw" /MAKE "TestTtsDtSimple - NAND Release low compute" /REBUILD

pause
@echo off

