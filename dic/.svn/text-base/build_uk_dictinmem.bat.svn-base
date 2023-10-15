
copy dic_uk.txt ..\plat\win32\build\dtalkdic\uk\Release\dic_uk.txt

cd ..\plat\win32\build\dtalkdic\uk\Release
 
dic.exe dic_uk.txt dtalk_uk.dic /t:win32
dic.exe dic_uk.txt dtalk_uk_compress.dic /t:win32 /c
dic.exe dic_uk.txt dtalk_uk_small.dic /t:win32 /p:500
dic.exe dic_uk.txt dtalk_uk_small_compress.dic /t:win32 /p:500 /c
dic.exe dic_uk.txt dtalk_uk_big.dic /t:win32 /e:other
dic.exe dic_uk.txt dtalk_uk_big_compress.dic /t:win32 /e:other /c
dic.exe dic_uk.txt dtalk_uk_small_big.dic /t:win32 /p:500 /e:other
dic.exe dic_uk.txt dtalk_uk_small_big_compress.dic /t:win32 /p:500 /e:other /c
dic.exe dic_uk.txt dtalk_uk_casio.dic /t:win32
dic.exe dic_uk.txt dtalk_uk_casio_big.dic /t:win32 /e:other

copy dtalk_uk.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk.dic
copy dtalk_uk_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_compress.dic
copy dtalk_uk_small.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_small.dic
copy dtalk_uk_small_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_small_compress.dic
copy dtalk_uk_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_big.dic
copy dtalk_uk_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_big_compress.dic
copy dtalk_uk_small_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_small_big.dic
copy dtalk_uk_small_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_small_big_compress.dic
copy dtalk_uk_casio.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_casio.dic
copy dtalk_uk_casio_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_uk_casio_big.dic

cd ..\..\..\..\apps\tools\convert_dict\Release

convert_dict dtalk_uk.dic maindict_uk_comp.h
convert_dict dtalk_uk_compress.dic maindict_uk_comp_compress.h
convert_dict dtalk_uk_small.dic maindict_uk.h
convert_dict dtalk_uk_small_compress.dic maindict_uk_compress.h
convert_dict dtalk_uk_big.dic maindict_uk_comp_big.h
convert_dict dtalk_uk_big_compress.dic maindict_uk_comp_big_compress.h
convert_dict dtalk_uk_small_big.dic maindict_uk_big.h
convert_dict dtalk_uk_small_big_compress.dic maindict_uk_big_compress.h
convert_dict dtalk_uk_casio.dic maindict_uk_casio.h
convert_dict dtalk_uk_casio_big.dic maindict_uk_casio_big.h


copy maindict_uk_comp.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_comp.h
copy maindict_uk_comp_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_comp_compress.h
copy maindict_uk.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk.h
copy maindict_uk_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_compress.h
copy maindict_uk_comp_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_comp_big.h
copy maindict_uk_comp_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_comp_big_compress.h
copy maindict_uk_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_big.h
copy maindict_uk_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_big_compress.h
copy maindict_uk_casio.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_casio.h
copy maindict_uk_casio_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_uk_casio_big.h

pause