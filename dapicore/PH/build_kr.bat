c:
cd C:\Dev\ad-new\DECtalk\plat\win32\project
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "dectalk.dsw" /MAKE "dtalk_kr - Win32 Debug Integer" /REBUILD

"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "dectalk.dsw" /MAKE "dtalk_kr - Win32 Debug" /REBUILD

copy c:\dev\ad-new\DECtalk\dic\dtalk_kr.dic C:\dev\ad-new\DECtalk\plat\win32\build\dectalk\common\debug\.
copy c:\dev\ad-new\DECtalk\dic\dtalk_kr.dic C:\dev\ad-new\DECtalk\plat\win32\build\dectalk\commonint\debug\.
pause