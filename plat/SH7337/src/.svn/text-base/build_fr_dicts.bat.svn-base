
copy C:\dev\dtalk_464_gen\dapi\src\dic\dic_fr.txt C:\dev\dtalk_464_gen\dapi\build\dtalkdic\fr\Release\dic_fr.txt

cd C:\dev\dtalk_464_gen\dapi\build\dtalkdic\fr\Release

dic.exe dic_fr.txt dtalk_fr.dic /t:win32
dic.exe dic_fr.txt dtalk_fr_big.dic /t:win32 /e:other

copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\fr\Release\dtalk_fr.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_fr.dic
copy C:\dev\dtalk_464_gen\dapi\build\dtalkdic\fr\Release\dtalk_fr_big.dic C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release\dtalk_fr_big.dic

cd C:\dev\ad\dectalk\plat\win32\apps\tools\convert_dict\Release

convert_dict dtalk_fr_big.dic maindict_fr_comp_big.h
convert_dict dtalk_fr.dic maindict_fr.h

copy maindict_fr_comp_big.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_fr_comp_big.h
copy maindict_fr.h C:\dev\dtalk_464_gen\dapi\src\LTS\maindict_fr.h

copy maindict_fr_comp_big.h C:\dev\dtalk_464\dapi\src\LTS\maindict_fr_comp_big.h
copy maindict_fr.h C:\dev\dtalk_464\dapi\src\LTS\maindict_fr.h

pause