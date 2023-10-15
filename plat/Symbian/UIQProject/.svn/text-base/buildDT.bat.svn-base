rem building US English
cd FnxDtSimpleUs
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building Chinese
cd..\FnxDtSimpleCh
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building French
cd..\FnxDtSimpleFr
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building German
cd..\FnxDtSimpleGr
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building Italian
cd..\FnxDtSimpleIt
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building Japanese
cd..\FnxDtSimpleJp
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building Korean
cd..\FnxDtSimpleKr
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building LA Spanish
cd..\FnxDtSimpleLa
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building Spanish
cd..\FnxDtSimpleSp
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

rem building UK English
cd..\FnxDtSimpleUk
call bldmake bldfiles
call abld clean
rem call abld build wins udeb
call abld build winscw urel
call abld build thumb urel

cd..

IF NOT EXIST ..\..\..\SDK\lib\Symbian\UIQ2.0\winscw\*.dll mkdir ..\..\..\SDK\lib\Symbian\UIQ2.0\winscw
IF NOT EXIST ..\..\..\SDK\lib\Symbian\UIQ2.0\THUMB\*.dll mkdir ..\..\..\SDK\lib\Symbian\UIQ2.0\THUMB

copy C:\Symbian\UIQ_21\epoc32\release\winscw\urel\FnxDtSimple??.dll ..\..\..\SDK\lib\Symbian\UIQ2.0\winscw\FnxDtSimple??.dll
copy C:\Symbian\UIQ_21\epoc32\release\winscw\udeb\FnxDtSimple??.lib ..\..\..\SDK\lib\Symbian\UIQ2.0\winscw\FnxDtSimple??.lib
copy C:\Symbian\UIQ_21\epoc32\release\thumb\urel\FnxDtSimple??.dll ..\..\..\SDK\lib\Symbian\UIQ2.0\THUMB\FnxDtSimple??.dll
copy C:\Symbian\UIQ_21\epoc32\release\thumb\urel\FnxDtSimple??.lib ..\..\..\SDK\lib\Symbian\UIQ2.0\THUMB\FnxDtSimple??.lib

rem FINISHED