
copy dic_la.txt ..\plat\win32\build\dtalkdic\la\Release\dic_la.txt

cd ..\plat\win32\build\dtalkdic\la\Release

dic.exe dic_la.txt dtalk_la.dic /t:win32
dic.exe dic_la.txt dtalk_la_compress.dic /t:win32 /c
dic.exe dic_la.txt dtalk_la_big.dic /t:win32 /e:other
dic.exe dic_la.txt dtalk_la_big_compress.dic /t:win32 /e:other /c
dic.exe dic_la.txt dtalk_la_casio.dic /t:win32
dic.exe dic_la.txt dtalk_la_casio_big.dic /t:win32 /e:other

copy dtalk_la.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_la.dic 
copy dtalk_la_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_la_compress.dic 
copy dtalk_la_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_la_big.dic 
copy dtalk_la_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_la_big_compress.dic 
copy dtalk_la_casio.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_la_casio.dic
copy dtalk_la_casio_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_la_casio_big.dic

cd ..\..\..\..\apps\tools\convert_dict\Release

convert_dict dtalk_la.dic maindict_la.h
convert_dict dtalk_la_compress.dic maindict_la_compress.h
convert_dict dtalk_la_big.dic maindict_la_big.h
convert_dict dtalk_la_big_compress.dic maindict_la_big_compress.h
convert_dict dtalk_la_casio.dic maindict_la_casio.h
convert_dict dtalk_la_casio_big.dic maindict_la_casio_big.h


copy maindict_la.h ..\..\..\..\..\..\dapicore\LTS\maindict_la.h 
copy maindict_la_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_la_compress.h
copy maindict_la_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_la_big.h 
copy maindict_la_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_la_big_compress.h 
copy maindict_la_casio.h ..\..\..\..\..\..\dapicore\LTS\maindict_la_casio.h 
copy maindict_la_casio_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_la_casio_big.h 

pause