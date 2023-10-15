
copy dic_fr.txt ..\plat\win32\build\dtalkdic\fr\Release\dic_fr.txt

cd ..\plat\win32\build\dtalkdic\fr\Release

dic.exe dic_fr.txt dtalk_fr.dic /t:win32
dic.exe dic_fr.txt dtalk_fr_compress.dic /t:win32 /c
dic.exe dic_fr.txt dtalk_fr_big.dic /t:win32 /e:other
dic.exe dic_fr.txt dtalk_fr_big_compress.dic /t:win32 /e:other /c
dic.exe dic_fr.txt dtalk_fr_casio.dic /t:win32
dic.exe dic_fr.txt dtalk_fr_casio_big.dic /t:win32 /e:other

copy dtalk_fr.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_fr.dic
copy dtalk_fr_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_fr_compress.dic
copy dtalk_fr_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_fr_big.dic
copy dtalk_fr_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_fr_big_compress.dic
copy dtalk_fr_casio.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_fr_casio.dic
copy dtalk_fr_casio_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_fr_casio_big.dic

cd ..\..\..\..\apps\tools\convert_dict\Release

convert_dict dtalk_fr.dic maindict_fr.h
convert_dict dtalk_fr_compress.dic maindict_fr_compress.h
convert_dict dtalk_fr_big.dic maindict_fr_big.h
convert_dict dtalk_fr_big_compress.dic maindict_fr_big_compress.h
convert_dict dtalk_fr_casio.dic maindict_fr_casio.h
convert_dict dtalk_fr_casio_big.dic maindict_fr_casio_big.h


copy maindict_fr.h ..\..\..\..\..\..\dapicore\LTS\maindict_fr.h
copy maindict_fr_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_fr_compress.h
copy maindict_fr_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_fr_big.h
copy maindict_fr_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_fr_big_compress.h
copy maindict_fr_casio.h ..\..\..\..\..\..\dapicore\LTS\maindict_fr_casio.h
copy maindict_fr_casio_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_fr_casio_big.h

pause