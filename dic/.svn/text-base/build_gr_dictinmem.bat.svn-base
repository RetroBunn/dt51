
copy dic_gr.txt ..\plat\win32\build\dtalkdic\gr\Release\dic_gr.txt

cd ..\plat\win32\build\dtalkdic\gr\Release

dic.exe dic_gr.txt dtalk_gr.dic /t:win32
dic.exe dic_gr.txt dtalk_gr_compress.dic /t:win32 /c
dic.exe dic_gr.txt dtalk_gr_big.dic /t:win32 /e:other
dic.exe dic_gr.txt dtalk_gr_big_compress.dic /t:win32 /e:other /c
dic.exe dic_gr.txt dtalk_gr_casio.dic /t:win32
dic.exe dic_gr.txt dtalk_gr_casio_big.dic /t:win32 /e:other

copy dtalk_gr.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_gr.dic 
copy dtalk_gr_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_gr_compress.dic 
copy dtalk_gr_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_gr_big.dic 
copy dtalk_gr_big_compress.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_gr_big_compress.dic 
copy dtalk_gr_casio.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_gr_casio.dic
copy dtalk_gr_casio_big.dic ..\..\..\..\apps\tools\convert_dict\Release\dtalk_gr_casio_big.dic

cd ..\..\..\..\apps\tools\convert_dict\Release

convert_dict dtalk_gr.dic maindict_gr.h
convert_dict dtalk_gr_compress.dic maindict_gr_compress.h
convert_dict dtalk_gr_big.dic maindict_gr_big.h
convert_dict dtalk_gr_big_compress.dic maindict_gr_big_compress.h
convert_dict dtalk_gr_casio.dic maindict_gr_casio.h
convert_dict dtalk_gr_casio_big.dic maindict_gr_casio_big.h


copy maindict_gr.h ..\..\..\..\..\..\dapicore\LTS\maindict_gr.h 
copy maindict_gr_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_gr_compress.h
copy maindict_gr_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_gr_big.h 
copy maindict_gr_big_compress.h ..\..\..\..\..\..\dapicore\LTS\maindict_gr_big_compress.h 
copy maindict_gr_casio.h ..\..\..\..\..\..\dapicore\LTS\maindict_gr_casio.h 
copy maindict_gr_casio_big.h ..\..\..\..\..\..\dapicore\LTS\maindict_gr_casio_big.h 

pause