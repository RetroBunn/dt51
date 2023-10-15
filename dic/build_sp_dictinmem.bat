
copy dic_sp.txt ..\plat\win32\build\dtalkdic\sp\Release\dic_sp.txt

cd ..\plat\win32\build\dtalkdic\sp\Release

dic.exe dic_sp.txt dtalk_sp.dic /t:win32
dic.exe dic_sp.txt dtalk_sp_compress.dic /t:win32 /c
dic.exe dic_sp.txt dtalk_sp_big.dic /t:win32 /e:other
dic.exe dic_sp.txt dtalk_sp_big_compress.dic /t:win32 /e:other /c
dic.exe dic_sp.txt dtalk_sp_casio.dic /t:win32
dic.exe dic_sp.txt dtalk_sp_casio_big.dic /t:win32 /e:other

copy dtalk_sp.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_sp.dic 
copy dtalk_sp_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_sp_compress.dic 
copy dtalk_sp_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_sp_big.dic 
copy dtalk_sp_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_sp_big_compress.dic 
copy dtalk_sp_casio.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_sp_casio.dic
copy dtalk_sp_casio_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_sp_casio_big.dic

cd ..\..\..\..\apps\tools\convert_dict\Release

convert_dict dtalk_sp.dic maindict_sp.h
convert_dict dtalk_sp_compress.dic maindict_sp_compress.h
convert_dict dtalk_sp_big.dic maindict_sp_big.h
convert_dict dtalk_sp_big_compress.dic maindict_sp_big_compress.h
convert_dict dtalk_sp_casio.dic maindict_sp_casio.h
convert_dict dtalk_sp_casio_big.dic maindict_sp_casio_big.h


copy maindict_sp.h ..\..\..\..\..\..\dapicore\LTS\maindict_sp.h 
copy maindict_sp_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_sp_compress.h
copy maindict_sp_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_sp_big.h 
copy maindict_sp_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_sp_big_compress.h 
copy maindict_sp_casio.h ..\..\..\..\..\..\dapicore\LTS\maindict_sp_casio.h 
copy maindict_sp_casio_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_sp_casio_big.h 

pause