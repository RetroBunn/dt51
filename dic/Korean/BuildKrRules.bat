echo off
xcopy c:\dictionary\Korean\KoreanRulesFBF.txt . /D /Y
..\FnxLtsRules2Code.exe ".\KoreanRulesFBF.txt" "..\..\dapicore\LTS\korean\FnxKrLtsRules.c" Kr
pause