echo off
ATTRIB  -R dtalk_us.dic
echo Building US standard dictionary!
..\dic.exe dic_us.txt dtalk_us.dic /t:win32 /l:us
xcopy dtalk_us.dic ..\..\plat\win32\build\dectalk\common\HighCompute\debug /Y /D
xcopy dtalk_us.dic ..\..\plat\win32\build\dectalk\common\HighCompute\release /Y /D
xcopy dtalk_us.dic ..\..\plat\win32\build\dectalk\common\LowCompute\debug /Y /D
xcopy dtalk_us.dic ..\..\plat\win32\build\dectalk\common\LowCompute\release /Y /D

pause
