Fonix Dectalk 4.6.3 SDK for Palm OS5

This SDK used the Fonix DECtalk Simple API set.
See the DTKSimple_RG_4_6_3.pdf file located in the \DECtalk 4.63\FnxSimpleAPI\help directory
for help on the API set.

This SDK is built using Palm OS5 and CodeWarrior.

This SDK was tested on the Palm Tungsten T3 and Palm Tungsten C devices.

Audio requirements:
This SDK used the Palm OS5 Sampled Sound API set

Devices Supported:
Palm Tungsten T3
Palm Tungsten C

Languages supported:
US. English
Castillian Spanish
Latin American Spanish

***Note that you can only run a program with one language at a time.
You have to make a separate program for each language like the demos included
with this SDK reflect.***

Features not supported:
This SDK does not support tone mode.

Voices supported:
all 9 DECtalk voices are supported

Directory Structure:
DECtalk 4.63
	FnxSimpleAPI
		help
		include
		PalmOS5
			LA
			SP
			US	
		Samples
			PalmOS5
				FnxTtsDtExStreamLA
				FnxTtsDtExStreamSP
				FnxTtsDtExStreamUS

Requirements:

To build applications you must have at least the Palm OS Garnet SDK (68K) R3 available from PalmSource:
http://www.palmos.com

To build applications you must have at least the CodeWarrior(R) Development Studio for Palm OS(R) Version 9
available from Metrowerks:
www.metrowerks.com

You must have a Palm OS5 device with streaming audio out capabilities
such as a Tungsten T3 or Tungsten C.

Running the us english example:

To download the us english example directly to your Palm Device:
Download the dictionary file and example program file to your device:

doubleclick on the "dtalk_us_dic.pdb" file located in the \DECtalk 4.63\FnxSimpleAPI\PalmOS5\Us directory
doubleclick on the "FnxTtsDtExStreamUS.prc" file located
in the \DECtalk 4.63\FnxSimpleAPI\Samples\PalmOS5\FnxTtsDtExStreamUS\Release directory

Hotsync to your Palm Device and then doubleclick on the FnxTtsDtExStreamUS icon on the device
to begin the example.

The example has two buttons on the interface:
Speak
Clear Text

Press the speak button to hear the text spoken that is displayed in the text box above.
The default text is "This is a demonstration of the Fonix Dectalk Text To Speech engine".
Press the clear text button to clear the text and then you may type in the text you wish to hear.

To change voices:
Click on the top of the screen somewhere on the "FnxTtsDtExStreamUS" tab at the top.
A menu bar will appear with two options, "Edit" and "Change Voice".
Select the "Change Voice" menu. 
Select which voice you want from this menu.
Press the "Speak" Button again to hear the text spoken in the new voice.
You can also use the shortcuts for each name that are listed in the menu.
(Note that Paul's shortcut is "A", Ursula's is "V" and Kits shortcut is "I"
due to conflicts with the default edit menu)
Paul is the default voice.

To change the text:
Either use the keyboard from the "Edit" menu or use graffiti to change the default text.

The LA and SP examples work similarly.

Sample Rate:
8KHz

Code Model:
The libraries and example program are built using the "Large" code model.

Struct Alignment:
The libraries and example program are built using the 68K 4-byte struct alignment.

Data Storage:
The libraries and example program are built with the PC Relative Strings and PC Constant
Data flags both on.

Prefix File
You must include the following prefix file in your settings:
palmconfig_dectalkla.h - to run Latin American Spanish
palmconfig_dectalksp.h - to run Castillian Spanish
palmconfig_dectalkus.h - to run US English

These files are located in the \DECtalk 4.63\FnxSimpleAPI\PalmOS5\Us La or Sp directories.
These files have all the necessary MACRO definitions to run DEctalk on PalmOS5.

To build your own program:
Your example must have at least 9 segments with each library in a different segment as
in the example programs.
The following library files are required:

Latin American Spanish
FnxTtsDtSimpleLA_1.lib
FnxTtsDtSimpleLA_2.lib
FnxTtsDtSimpleLA_3.lib
FnxTtsDtSimpleLA_4.lib
FnxTtsDtSimpleLA_5.lib
FnxTtsDtSimpleLA_6.lib
FnxTtsDtSimpleLA_7.lib
FnxTtsDtSimpleLA_8.lib

Castillian Spanish
FnxTtsDtSimpleSP_1.lib
FnxTtsDtSimpleSP_2.lib
FnxTtsDtSimpleSP_3.lib
FnxTtsDtSimpleSP_4.lib
FnxTtsDtSimpleSP_5.lib
FnxTtsDtSimpleSP_6.lib
FnxTtsDtSimpleSP_7.lib
FnxTtsDtSimpleSP_8.lib

US English
FnxTtsDtSimpleUS_1.lib
FnxTtsDtSimpleUS_2.lib
FnxTtsDtSimpleUS_3.lib
FnxTtsDtSimpleUS_4.lib
FnxTtsDtSimpleUS_5.lib
FnxTtsDtSimpleUS_6.lib
FnxTtsDtSimpleUS_7.lib
FnxTtsDtSimpleUS_8.lib


they are located in the \DECtalk 4.63\FnxSimpleAPI\PalmOS5\Us LA or SP directories

You must link MathLib to your project and include Mathlib.c as in the example.

You must use the prefix files:
palmconfig_dectalkla.h or
palmconfig_dectalksp.h or
palmconfig_dectalkus.h

FnxTtsDtExStreamLA.c
FnxTtsDtExStreamSP.c
FnxTtsDtExStreamUs.c
have all the required APIs you need to run DECtalk TTS.

See the "Speak Button" calls in these files for the APIs used.
