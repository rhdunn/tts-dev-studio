# TTS Developer Studio

- [Dependencies](#dependencies)
  - [Debian](#debian)
  - [Windows](#windows)
- [Building](#building)
  - [Visual Studio](#visual-studio)
  - [CLion](#clion)
- [Bugs](#bugs)
- [License Information](#license-information)

----------

This project is a graphical editor for creating and editing Text-to-Speech
language and voice files.

## Dependencies

In order to build TTS Developer Studio, you need:

1.  a functional cmake system for your platform;
2.  a functional C++ compiler that supports C++11 (e.g. gcc or clang);
3.  Qt5 Widgets with cmake integration.

### Debian

On Debian-based systems such as Debian, Ubuntu and Mint, these dependencies can
be installed using the following commands:

| Dependency    | Install                            |
|---------------|------------------------------------|
| cmake         | `sudo apt-get install cmake`       |
| c++ compiler  | `sudo apt-get install g++`         |
| Qt5           | `sudo apt-get install qtbase5-dev` |

### Windows

To build and run the application on Windows, you will need:

1.  Microsoft Visual Studio 2015 build tools (C++, Windows SDK and msbuild);
2.  cmake;
3.  Qt 5.7 or later.

## Building

To build the application, run:

	cmake .
	make

### Visual Studio

To build the 32-bits application, run:

	set CMAKE_PREFIX_PATH=C:\Qt\5.8\msvc2015\lib\cmake\Qt5
	cmake -G "Visual Studio 14 2015 Win32" .
	msbuild /p:Platform=Win32 tts-dev-studio.sln

To build the 64-bits application, run:

	set CMAKE_PREFIX_PATH=C:\Qt\5.8\msvc2015_64\lib\cmake\Qt5
	cmake -G "Visual Studio 14 2015 Win64" .
	msbuild /p:Platform=x86 tts-dev-studio.sln

To run tts-dev-studio, you need Qt on the system path. For example, for 64-bit
builds run:

	set PATH=C:\Qt\5.8\msvc2015_64\bin
	src\Debug\tts-dev-studio.exe

### CLion

In the `File > Settings` dialog, select the `Build, Execution, Deployment > CMake`
tab and add the following to the `Environment:` field:

	CMAKE_PREFIX_PATH=C:\Qt\5.8\msvc2015

In the `Run > Edit Configurations` dialog, select the `tts-dev-studio` tab, or
any of the other applications you want to run, and add the following to the
`Environment variables:` field:

	PATH=%PATH%;C:\Qt\5.8\msvc2015\bin

## Bugs

Report bugs to the
[tts-dev-studio issues](https://github.com/espeak-ng/tts-dev-studio/issues)
page on GitHub.

## License Information

TTS Developer Studio is released under the [GPL version 3](COPYING) or later
license.
