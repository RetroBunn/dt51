echo off

if x==%1x goto SPEAKHC
if %1 == all goto CHINESE
if %1 == help goto HELP
if %1 == speak goto SPEAKHC
if %1 == hc goto SPEAKHC		rem highcompute
if %1 == lc goto SPEAKLC		rem lowcompute
if %1 == dectalk goto DECTALK
if %1 == us goto USENGLISH
if %1 == fr goto FRENCH
if %1 == gr goto GERMAN
if %1 == it goto ITALIAN
if %1 == sp goto SPANISH
if %1 == la goto LASPANISH
if %1 == uk goto UKENGLISH
if %1 == ch goto CHINESE
if %1 == jp goto JAPANESE
if %1 == kr goto KOREAN

:CHINESE
echo Building dtalk_ch.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_ch - Win32 Debug High Compute" /REBUILD 
if %1 == all goto FRENCH
goto COPY

:FRENCH
echo Building dtalk_fr.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_fr - Win32 Debug High Compute" /REBUILD 
if %1 == all goto GERMAN
goto COPY

:GERMAN
echo Building dtalk_gr.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_gr - Win32 Debug High Compute" /REBUILD 
if %1 == all goto HEBREW
goto COPY

:HEBREW
echo Building dtalk_hb.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_hb - Win32 Debug High Compute" /REBUILD 
if %1 == all goto ITALIAN
goto COPY

:ITALIAN
echo Building dtalk_it.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_it - Win32 Debug High Compute" /REBUILD 
if %1 == all goto JAPANESE
goto COPY

:JAPANESE
echo Building dtalk_jp.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_jp - Win32 Debug High Compute" /REBUILD 
if %1 == all goto KOREAN
goto COPY

:KOREAN
echo Building dtalk_kr.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_kr - Win32 Debug High Compute" /REBUILD 
if %1 == all goto LASPANISH
goto COPY

:LASPANISH
echo Building dtalk_la.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_la - Win32 Debug High Compute" /REBUILD 
if %1 == all goto SPANISH
goto COPY

:SPANISH
echo Building dtalk_sp.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_sp - Win32 Debug High Compute" /REBUILD 
if %1 == all goto UKENGLISH
goto COPY

:UKENGLISH
echo Building dtalk_uk.dll
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_uk - Win32 Debug High Compute" /REBUILD 
if %1 == all goto USENGLISH
goto COPY

:USENGLISH
echo Building dtalk_us
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dtalk_us - Win32 Debug High Compute" /REBUILD 
if %1 == all goto DECTALK
goto COPY

:DECTALK
echo Building dectalk.dll and dependencies
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "dectalk - Win32 Debug High Compute" /REBUILD
if %1 == all goto SPEAKHC
goto COPY

:SPEAKHC
echo Building Speak.exe and dependencies (High Compute)
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "speak - Win32 Debug High Compute"

goto EXIT

:SPEAKLC
echo Building Speak.exe and dependencies (Low Compute)
"C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDev.com" "speak.dsw" /MAKE "speak - Win32 Debug Low Compute"

goto EXIT

:HELP
echo Usage - BuildSpeak.bat [item]
echo	[item] - can be any one of the following
echo		hc - build high compute speak and dependent dlls
echo		lc - build low compute speak and dependent dlls
echo		dectalk - rebuild dectalk.dll and dependencies  (high compute)
echo		ch - rebuild dtalk_ch.dll (high compute)
echo		fr - rebuild dtalk_fr.dll (high compute)
echo		gr - rebuild dtalk_gr.dll (high compute)
echo		it - rebuild dtalk_it.dll (high compute)
echo		jp - rebuild dtalk_jp.dll (high compute)
echo		kr - rebuild dtalk_kr.dll (high compute)
echo		la - rebuild dtalk_la.dll (high compute)
echo		sp - rebuild dtalk_sp.dll (high compute)
echo		uk - rebuild dtalk_uk.dll (high compute)
echo		us - rebuild dtalk_us.dll (high compute)

:EXIT
