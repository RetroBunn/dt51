
copy dic_us.txt ..\plat\win32\build\dtalkdic\us\Release\dic_us.txt

cd ..\plat\win32\build\dtalkdic\us\Release

dic.exe dic_us.txt dtalk_us.dic /t:win32
dic.exe dic_us.txt dtalk_us_compress.dic /t:win32 /c
dic.exe dic_us.txt dtalk_us_small.dic /t:win32 /p:500
dic.exe dic_us.txt dtalk_us_small_compress.dic /t:win32 /p:500 /c
dic.exe dic_us.txt dtalk_us_big.dic /t:win32 /e:other
dic.exe dic_us.txt dtalk_us_big_compress.dic /t:win32 /e:other /c
dic.exe dic_us.txt dtalk_us_small_big.dic /t:win32 /p:500 /e:other
dic.exe dic_us.txt dtalk_us_small_big_compress.dic /t:win32 /p:500 /e:other /c
dic.exe dic_us.txt dtalk_us_casio.dic /t:win32
dic.exe dic_us.txt dtalk_us_casio_big.dic /t:win32 /e:other

copy dtalk_us.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us.dic
copy dtalk_us_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_compress.dic
copy dtalk_us_small.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_small.dic
copy dtalk_us_small_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_small_compress.dic
copy dtalk_us_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_big.dic
copy dtalk_us_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_big_compress.dic
copy dtalk_us_small_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_small_big.dic
copy dtalk_us_small_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_small_big_compress.dic
copy dtalk_us_casio.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_casio.dic
copy dtalk_us_casio_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_us_casio_big.dic

cd ..\..\..\..\apps\tools\convert_dict\Release

convert_dict dtalk_us.dic maindict_us_comp.h
convert_dict dtalk_us_compress.dic maindict_us_comp_compress.h
convert_dict dtalk_us_small.dic maindict_us.h
convert_dict dtalk_us_small_compress.dic maindict_us_compress.h
convert_dict dtalk_us_big.dic maindict_us_comp_big.h
convert_dict dtalk_us_big_compress.dic maindict_us_comp_big_compress.h
convert_dict dtalk_us_small_big.dic maindict_us_big.h
convert_dict dtalk_us_small_big_compress.dic maindict_us_big_compress.h
convert_dict dtalk_us_casio.dic maindict_us_casio.h
convert_dict dtalk_us_casio_big.dic maindict_us_casio_big.h


copy maindict_us_comp.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_comp.h
copy maindict_us_comp_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_comp_compress.h
copy maindict_us.h ..\..\..\..\..\..\dapicore\LTS\maindict_us.h
copy maindict_us_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_compress.h
copy maindict_us_comp_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_comp_big.h
copy maindict_us_comp_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_comp_big_compress.h
copy maindict_us_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_big.h
copy maindict_us_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_big_compress.h
copy maindict_us_casio.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_casio.h
copy maindict_us_casio_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_us_casio_big.h

pause