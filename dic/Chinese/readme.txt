To modify the chinese-to-pinyin process you can edit the following files:

To add or subtract from the list of possible pinyin+tone edit the table PinyinTableWithTones in the file ...\dapicore\lts\chinese\CJK2PinyinTables.c.
Note:  Do not try to edit the table CJKUnicodeOffsetToPinyinTable.  This table must be built by BuildCJK2PinyinTables.exe

To modify the pinyin+tone for a specific chinese character, modify the file CJK.txt in this folder.  Only chinese unicode characters 0x4E00 through 0x9FA5
are allowed.
Note:  The use of tabs in this file is important.

To modify a polyphone chinese character, edit the file dtalk_ch.cjk.  
Note:  The use of tabs in this file is important!