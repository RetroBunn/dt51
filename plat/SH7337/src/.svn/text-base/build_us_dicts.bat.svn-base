copy C:\dev\dtalk_464_gen\dapi\src\dic\dic_us_Casio.txt C:\dev\dtalk_464_gen\dapi\build\dtalkdic\us\Release\dic_us_Casio.txt

cd C:\dev\dtalk_464_gen\dapi\build\dtalkdic\us\Release

dic.exe dic_us_Casio.txt dtalk_us_casio.dic /t:win32
dic.exe dic_us_Casio.txt dtalk_us_casio_big.dic /t:win32 /e:other

copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\us\Release\dtalk_us_Casio_big.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_us_Casio_big.dic
copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\us\Release\dtalk_us_Casio.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_us_Casio.dic

cd C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release

convert_dict dtalk_us_Casio_big.dic maindict_us_casio_big.h
convert_dict dtalk_us_Casio.dic maindict_us_casio.h

copy maindict_us_casio_big.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_us_casio_big.h
copy maindict_us_casio.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_us_casio.h

copy maindict_us_casio_big.h C:\dev\dtalk_464\dapi\src\LTS\maindict_us_casio_big.h
copy maindict_us_casio.h C:\dev\dtalk_464\dapi\src\LTS\maindict_us_casio.h


pause