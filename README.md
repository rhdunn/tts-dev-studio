# TTS Developer Studio

- [Dependencies](#dependencies)
- [Building](#building)
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

On Debian-based systems such as Debian, Ubuntu and Mint, these dependencies can
be installed using the following commands:

| Dependency    | Install                            |
|---------------|------------------------------------|
| cmake         | `sudo apt-get install cmake`       |
| c++ compiler  | `sudo apt-get install g++`         |
| Qt5           | `sudo apt-get install qtbase5-dev` |

## Building

To build the application, run:

	cmake .
	make

## Bugs

Report bugs to the
[tts-dev-studio issues](https://github.com/espeak-ng/tts-dev-studio/issues)
page on GitHub.

## License Information

TTS Developer Studio is released under the [GPL version 3](COPYING) or later
license.
