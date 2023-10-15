# Introduction
**DECtalk** was a speech synthesizer and text-to-speech technology originally developed by DEC (Digital Equipment Corporation) in 1984, based largely on the work of Dennis Klatt.
The code in this repository pertains to version 5.1 of the synthesizer, which dates to about 2005-2006, which was owned by Fonix Corp. This appears to be a beta of what would later become the company's flagship FonixTalk text-to-speech product.
## Background
These files were originally shared by a former Fonix Corp. developer on September 15, 2023 and preserved on a server at [datajake.braillescreen.net](https://datajake.braillescreen.net/tts/DECtalk%20source%20code%20archive/).
## Building
The files in this repo are designed to be built using Visual Studio 6.0 on Windows. There is a great article on CodeProject which shows you how to install VS6.0 on newer versions of Windows. You can find it [here](https://www.codeproject.com/Articles/1191047/Install-Visual-Studio-on-Windows). If you do not want to deal with Compatibility Mode on newer versions of Windows, your best bet is to use a virtual machine of an older version of Windows such as XP,  and install Visual Studio 6.0 from there.
Navigate to `plat/win32/projec` and excecute `dectalk.dsw` to build all components of DECtalk.
Due to the code in this repository being out of date, it's not possible to build the synthesizer under newer Linux kernels, despite there being files for a Linux version internally.
If you wish to build a version of DECtalk under newer Linux kernels, and/or build against a modern version of Visual Studio, check out the activity in [this repository](https://www.github.com/dectalk/dectalk).
## Important
Even though there are files for Unix, Linux, Palm OS, Symbian, ARM7TDMI, SH7337, and Windows CE platform support in the `plat` folder, I cannot guarantee those will build successfully. I have kept them here for historical purposes.
