
rem building US English
cd FnxDtSimpleUs
call bldmake bldfiles
call abld makefile vc6

rem building Chinese
cd..\FnxDtSimpleCh
call bldmake bldfiles
call abld makefile vc6

rem building French
cd..\FnxDtSimpleFr
call bldmake bldfiles
call abld makefile vc6

rem building German
cd..\FnxDtSimpleGr
call bldmake bldfiles
call abld makefile vc6

rem building Italian
cd..\FnxDtSimpleIt
call bldmake bldfiles
call abld makefile vc6

rem building Japanese
cd..\FnxDtSimpleJp
call bldmake bldfiles
call abld makefile vc6

rem building Korean
cd..\FnxDtSimpleKr
call bldmake bldfiles
call abld makefile vc6

rem building LA Spanish
cd..\FnxDtSimpleLa
call bldmake bldfiles
call abld makefile vc6

rem building Spanish
cd..\FnxDtSimpleSp
call bldmake bldfiles
call abld makefile vc6

rem building UK English
cd..\FnxDtSimpleUk
call bldmake bldfiles
call abld makefile vc6

cd..

