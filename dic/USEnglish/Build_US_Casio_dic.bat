echo off
ATTRIB  -R dtalk_us.dic
echo Building US Casio dictionary!
..\dic.exe dic_us_Casio.txt dtalk_us_Casio.dic /t:win32 /l:us
xcopy dtalk_us_Casio.dic ..\..\plat\win32\build\dectalk\common\HighCompute\debug\dtalk_us.dic /Y /D
xcopy dtalk_us_Casio.dic ..\..\plat\win32\build\dectalk\common\HighCompute\release\dtalk_us.dic /Y /D
xcopy dtalk_us_Casio.dic ..\..\plat\win32\build\dectalk\common\LowCompute\debug\dtalk_us.dic /Y /D
xcopy dtalk_us_Casio.dic ..\..\plat\win32\build\dectalk\common\LowCompute\release\dtalk_us.dic /Y /D
pause
