Documentation for sgrammar

Details of the installation
===========================

This software requires the programs bison.exe and flex.exe which have been
ported to windows. The tools can be obtained at the following websiteL


http://www.monmouth.com/~wstreett/lex-yacc/lex-yacc.html

The following files need to be downloaded and installed.

  flex.exe       177 Kb    Mon Jul 15 00:00:00 1996 Binary Executable
  bison.exe      191 Kb    Mon Jul 15 00:00:00 1996 Binary Executable
  bison.hairy      6 Kb    Mon Jul 15 00:00:00 1996 
  bison.simple    17 Kb    Mon Jul 15 00:00:00 1996 

flex.exe and bison.exe must be in the path. Further, it is nessecary to define
two environmental variables BISON_HAIRY and BISON_SIMPLE which point to the
locations of the respective files  bison.hairy and  bison.simple.

The project here makes use of a file sgrammar.y which contains the 
yacc grammar (input to bison) and the sgrammar.l which contains the 
grammar used to analyse the input to the parser. These must be 
specified as resources and are compiled with:

bison -v -d sgrammar.c  generates sgrammar_tab.c and sgrammar_tab.h
flex        sgrammar.l  generates lex.yy.c

More details later, when this project works.


Purpose of the software.
=======================

Chunk parsing and the disambiguation of homophones. Some ideas are explained
in  the associated pdf file. 

All work in progress.

To run the program, use the generated executable, and run it 
in a console window, using the included example file
example.txt:

sequencegrammar.exe example.txt

This will generate two files, sgrammarsequences.c
and sgrammarsequences.h which correspond to the 
sequence definitions in example.txt.


