
rem building US English
cd FnxDtSimpleUs
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building Chinese
cd..\FnxDtSimpleCh
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building French
cd ..\FnxDtSimpleFr
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building German
cd..\FnxDtSimpleGr
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building Italian
cd..\FnxDtSimpleIt
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building Japanese
cd..\FnxDtSimpleJp
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building Korean
cd..\FnxDtSimpleKr
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building LA Spanish
cd..\FnxDtSimpleLa
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building Spanish
cd..\FnxDtSimpleSp
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

rem building UK English
cd..\FnxDtSimpleUk
call bldmake bldfiles
call abld clean
call abld build wins udeb
call abld build wins urel
call abld build thumb urel

cd..

IF NOT EXIST ..\..\..\SDK\lib\Symbian\Series60_2.0\WINS\*.dll mkdir ..\..\..\SDK\lib\Symbian\Series60_2.0\WINS
IF NOT EXIST ..\..\..\SDK\lib\Symbian\Series60_2.0\THUMB\*.dll mkdir ..\..\..\SDK\lib\Symbian\Series60_2.0\THUMB

copy C:\Symbian\7.0s\Series60_v20\epoc32\release\WINS\urel\FnxDtSimple??.dll ..\..\..\SDK\lib\Symbian\Series60_2.0\WINS\FnxDtSimple??.dll
copy C:\Symbian\7.0s\Series60_v20\epoc32\release\WINS\udeb\FnxDtSimple??.lib ..\..\..\SDK\lib\Symbian\Series60_2.0\WINS\FnxDtSimple??.lib
copy C:\Symbian\7.0s\Series60_v20\epoc32\release\thumb\urel\FnxDtSimple??.dll ..\..\..\SDK\lib\Symbian\Series60_2.0\THUMB\FnxDtSimple??.dll
copy C:\Symbian\7.0s\Series60_v20\epoc32\release\thumb\urel\FnxDtSimple??.lib ..\..\..\SDK\lib\Symbian\Series60_2.0\THUMB\FnxDtSimple??.lib

rem FINISHED