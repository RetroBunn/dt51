
copy C:\dev\dtalk_464_gen\dapi\src\dic\dic_gr.txt C:\dev\dtalk_464_gen\dapi\build\dtalkdic\gr\Release\dic_gr.txt

cd C:\dev\dtalk_464_gen\dapi\build\dtalkdic\gr\Release

dic.exe dic_gr.txt dtalk_gr.dic /t:win32
dic.exe dic_gr.txt dtalk_gr_big.dic /t:win32 /e:other

copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\gr\Release\dtalk_gr.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_gr.dic
copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\gr\Release\dtalk_gr_big.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_gr_big.dic

cd C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release

convert_dict dtalk_gr_big.dic maindict_gr_comp_big.h
convert_dict dtalk_gr.dic maindict_gr.h

copy maindict_gr_comp_big.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_gr_comp_big.h
copy maindict_gr.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_gr.h

copy maindict_gr_comp_big.h C:\dev\dtalk_464\dapi\src\LTS\maindict_gr_comp_big.h
copy maindict_gr.h C:\dev\dtalk_464\dapi\src\LTS\maindict_gr.h

pause