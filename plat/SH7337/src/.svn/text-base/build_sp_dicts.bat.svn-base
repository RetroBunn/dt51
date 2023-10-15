
copy C:\dev\dtalk_464_gen\dapi\src\dic\DIC_SP.txt C:\dev\dtalk_464_gen\dapi\build\dtalkdic\sp\Release\DIC_SP.txt

cd C:\dev\dtalk_464_gen\dapi\build\dtalkdic\sp\Release

dic.exe DIC_SP.txt dtalk_sp.dic /t:win32
dic.exe DIC_SP.txt dtalk_sp_big.dic /t:win32 /e:other

copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\sp\Release\dtalk_sp.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_sp.dic
copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\sp\Release\dtalk_sp_big.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_sp_big.dic

cd C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release

convert_dict dtalk_sp_big.dic maindict_sp_comp_big.h
convert_dict dtalk_sp.dic maindict_sp.h

copy maindict_sp_comp_big.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_sp_comp_big.h
copy maindict_sp.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_sp.h

copy maindict_sp_comp_big.h C:\dev\dtalk_464\dapi\src\LTS\maindict_sp_comp_big.h
copy maindict_sp.h C:\dev\dtalk_464\dapi\src\LTS\maindict_sp.h

pause