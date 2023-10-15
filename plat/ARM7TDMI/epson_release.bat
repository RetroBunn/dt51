mkdir %1
cd %1
mkdir lib
mkdir src

cd lib
mkdir base
mkdir us
mkdir uk
mkdir gr
mkdir sp
mkdir fr
mkdir la
mkdir it
mkdir jp
mkdir ch
mkdir kr
mkdir base_thumb
mkdir us_thumb
mkdir uk_thumb
mkdir gr_thumb
mkdir sp_thumb
mkdir fr_thumb
mkdir la_thumb
mkdir it_thumb
mkdir jp_thumb
mkdir ch_thumb
mkdir kr_thumb

xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7\epsonarm7_data\debugrelepson\* base
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7\epsonarm7_data\debugrelepson\* base_thumb

rem xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonChineseLts\* ch
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonEnglishLts\* us
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonEngUKLts\* uk
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonFrenchLts\* fr
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonGermanLts\* gr
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonItalianLts\* it
rem xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonJapaneseLts\* jp
rem xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonKoreanLts\* kr
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonLatinAmLts\* la
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonSpanishLts\* sp

rem xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonChineseLtsThu\* ch_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonEnglishLtsThu\* us_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonEngUKLtsThumb\* uk_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonFrenchLtsThum\* fr_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonGermanLtsThum\* gr_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonItalianLtsThu\* it_thumb
rem xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonJapaneseLtsTh\* jp_thumb
rem xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonKoreanLtsThum\* kr_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonLatinAmLtsThu\* la_thumb
xcopy /s /y ..\..\..\ad-new\dectalk\plat\ARM7TDMI\project\epsonarm7lts\epsonarm7lts_data\DebugRelEpsonSpanishLtsThu\* sp_thumb


xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonEnglishDummy\* us
xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonEngUKDummy\* uk
xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonFrenchDummy\* fr
xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonGermanDummy\* gr
xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonItalianDummy\* it
xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonLatinDummy\* la
xcopy /s /y ..\..\..\ad-new\DECtalk\plat\ARM7TDMI\project\epsonltsdummy\epsonltsdummy_Data\DebugRelEpsonSpanishDummy\* sp

cd ..
cd src

mkdir api
mkdir cmd
mkdir lts
mkdir ph
mkdir vtm
mkdir include
mkdir kernel
mkdir hlsyn
mkdir asian_inc

copy c:\work\ad-new\dectalk\dapi\*.h api
copy c:\work\ad-new\dectalk\dapi\epsonapi.c api
copy c:\work\ad-new\dectalk\plat\ARM7TDMI\include\*  api
copy c:\work\ad-new\dectalk\plat\ARM7TDMI\src\*  api

copy c:\work\ad-new\dectalk\dapicore\cmd\*.c cmd 
copy c:\work\ad-new\dectalk\dapicore\cmd\*.h cmd 
cd cmd
del co_gr_dict.h
del co_gr_dict_big.h
del port_old.h
cd ..
copy c:\work\ad-new\dectalk\dapicore\lts\*.h lts
copy c:\work\ad-new\dectalk\dapicore\lts\ls_dict.c lts
copy c:\work\ad-new\dectalk\dapicore\lts\lts_dummy*.c lts
copy c:\work\ad-new\dectalk\dapicore\lts\*.h lts

copy c:\work\ad-new\dectalk\dapicore\ph\*.h ph
copy c:\work\ad-new\dectalk\dapicore\ph\ph_vdefi.c ph
copy c:\work\ad-new\dectalk\dapicore\ph\ph_vset.c ph
cd ph
del p_*rom*.h
del p_us_ali.h
del p_us_ed.h
del p_us_ken.h
del p_us_sue.h
del p_us_ali.h
cd ..

copy c:\work\ad-new\dectalk\dapicore\vtm\*.h vtm
copy c:\work\ad-new\dectalk\dapicore\vtm\vtm3.c vtm
copy c:\work\ad-new\dectalk\dapicore\vtm\vtm.c vtm
copy c:\work\ad-new\dectalk\dapicore\vtm\playtone.c vtm
copy c:\work\ad-new\dectalk\dapicore\vtm\vtmiont.c vtm
copy c:\work\ad-new\dectalk\dapicore\include\*.h include 
copy c:\work\ad-new\dectalk\dapicore\include\*.tab include 
copy c:\work\ad-new\dectalk\dapicore\kernel\*.h kernel
copy c:\work\ad-new\dectalk\dapicore\kernel\*.c kernel
copy c:\work\ad-new\dectalk\dapicore\hlsyn\*.h hlsyn
copy c:\work\ad-new\dectalk\dapicore\hlsyn\log10table.c hlsyn
copy c:\work\ad-new\dectalk\dapicore\hlsyn\sqrttable.c hlsyn
copy c:\work\ad-new\dectalk\plat\ARM7TDMI\include\*.h include
copy c:\work\ad-new\dectalk\shared\include\*.h include
copy c:\work\ad-new\dectalk\sdk\include\*.h api
cd api
del simpleapi.h
del fonixttsdtsimple.h
cd ..
cd include
del dectalkf_old.h
del port_old.h
cd ..
copy c:\work\ad-new\dectalk\dapicore\lts\japan\*.h asian_inc
copy c:\work\ad-new\dectalk\dapicore\lts\chinese\*.h asian_inc
copy c:\work\ad-new\dectalk\dapicore\lts\korean\*.h asian_inc

cd ..
cd ..

