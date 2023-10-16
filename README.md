# Introduction
**DECtalk** was a speech synthesizer and text-to-speech technology originally developed by DEC (Digital Equipment Corporation) in 1984, based largely on the work of Dennis Klatt.
The code in this repository pertains to version 5.1 of the synthesizer, which dates to about 2005-2006, which was owned by Fonix Corp. This appears to be a beta of what would later become the company's flagship FonixTalk text-to-speech product.
## Background
These files were originally shared by a former Fonix Corp. developer on September 15, 2023 and preserved on a server at [datajake.braillescreen.net](https://datajake.braillescreen.net/tts/DECtalk%20source%20code%20archive/).
## Building
The Win32 files in this repo are designed to be built using Visual Studio 6.0.
There is a great article on CodeProject which shows you how to install VS6.0 on modern versions of Windows. You can find it [here](https://www.codeproject.com/Articles/1191047/Install-Visual-Studio-on-Windows). If you do not want to deal with Compatibility Mode, your best bet is to use a virtual machine of a legacy version of Windows such as XP,  and install Visual Studio 6.0 from there.
To build, navigate to `plat/win32/project` and excecute `dectalk.dsw` to build the DLL files for DECtalk, including all languages and dictionaries.
Build files can be found in `plat/win32/build`.
To build the speak window, navigate to `plat/win32/demo/speak` and excecute `speak.dsw`. Build files will be found in the same folder as the DECtalk build files were, since the project also builds the files needed for the speak window to function.
## Important Note for NVDA Users
The `dectalk51.py` file expects a file called `dectalk51.dll` to be present in the `SynthDrivers` folder alongside the Python file. This was intentionally done so that you can have both DECtalk 5.1 and any other version of DECtalk installed at the same time.
To use DECtalk 5.1 with NVDA, follow these steps:
1. Copy the `nvda` folder in the root of this repository to your `addons` folder of your NVDA user configuration directory, which is located in AppData/Roaming/nvda. On portable installations, it can be found in userConfig.
2. Rename the `nvda` folder you just copied to `DECtalk 5.1`.
3. If you have not built DECtalk, follow the instructions in the **Building** section to do so. Once you're finish compiling, navigate to either the `High-Compute` or the `Low-Compute` directory (depending on which components you chose to build). Navigate to the `release` subfolder.
4. Copy `dectalk.dll`, `dtalk_us.dll`, and `dtalk_us.dic` to the `SynthDrivers` folder of the `DECtalk 5.1` directory you just made in step 2.
5. Rename `dectalk.dll` to `dectalk51.dll`.

## What about Linux?
Due to the code in this repository being out of date, it's not possible to build the synthesizer under newer Linux kernels (particularly 64-bit ones), despite there being files for a Linux version internally.
If you wish to build a version of DECtalk under newer Linux kernels, and/or build against a modern version of Visual Studio, check out the activity in [this repository](https://www.github.com/dectalk/dectalk).
## Important Notice
Even though there are source files for Unix, Linux, Palm OS 5, Symbian, ARM7TDMI, SH7337, and Windows CE platform support in the `plat` folder, I cannot guarantee those will build successfully. I have kept them here for historical purposes.