# Working with source

## Prerequisites

### Hard dependencies:

* [Git 2.41](https://git-scm.com/download/win)
* [Cmake 3.27.1](https://cmake.org/download/)
* [Strawberry Perl 5.32.1](https://strawberryperl.com/)
* *a* [Python 3.11.4](https://www.python.org/downloads/)
* *b* *c* [MSVC v143 compiler](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
* *d* _(Optional)_ [vcpkg](https://vcpkg.io/en/getting-started)

*a* - Make sure to select Windows 64-bit; add python.exe to PATH; also do a custom installation and make sure to select *ALL* the options.

*b* - Can be acquired with [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) install. Select "Desktop development with C++".

*c* - Make sure to add MSVC x64 compiler to your environmental path. If you have visual studio installed the default location will be ``C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64``.

*c* - To add this path to your environmental path on Windows 11:

1. Start
2. In search type: "edit environment"
3. Select "Edit environment variables for your account"
4. At the bottom select "Environment Variables"
5. In the "System variables" category locate "Path" and double click it
6. Select "New"
7. Paste in the path
8. "OK"
9. "OK"
10. "OK"
11. Make sure to restart your TERMINAL/SHELL
12. Open terminal
13. > $ cl
14. > Microsoft (R) C/C++ Optimizing Compiler Version 19.37.32822 for x64 Copyright (C) Microsoft Corporation.  All rights reserved.

*b* - (*[CPM](cpm.md) HANDLES THIS AUTOMATICALLY SO NO NEED TO INSTALL THESE BEFOREHAND*) local vcpkg installation can be used, otherwise the setup script will download and setup vcpkg in the repository (Vendor/vcpkg). If using a local vcpkg install, the following packages must be installed with the x64-windows triplet (just add ``--triplet=x64-windows`` flag at the end of the command, i.e. ``vcpkg install fmt --triplet=x64-windows``) OR they can be automatically installed by running the ``setup.bat --vcpkg-location "path/to/vcpkg"`` script:

1. [fmt](https://github.com/fmtlib/fmt)
2. [spdlog](https://github.com/gabime/spdlog)
3. [stb](https://github.com/nothings/stb)
4. [pkgconfig](https://github.com/pkgconf/pkgconf)
5. [raylib](https://github.com/raysan5/raylib)
6. [gtest](https://github.com/google/googletest)
7. [boost](https://github.com/boostorg/boost)
8. [boost-python[python3]](https://github.com/boostorg/python)
9. [gtkmm](https://github.com/GNOME/gtkmm)
10. [opengl](https://www.opengl.org/)

* Make sure to install pkgconfig modules with
  > $ vcpkg install vcpkg-pkgconfig-get-modules
* Make sure to install vcpkg to ``C:/vcpkg`` or ``C:/dev/vcpkg`` - long filepaths may cause errors on Windows

Note: It is better if you setup vcpkg somewhere close to the root drive otherwise there might be issue with building the libraries (on the vcpkg side).

## Building the source

Before proceeding *make absolutely sure* you cd into the root repository directory and run the following command:

> $ git submodule update --init --recursive

This will download any submodules the repository has.
It will download the CPM module which will be located in Tools/CPM.

~~There are a few scripts available that should streamline all project generation, building, and installing~~

Everything has been moved to a single submodule - [CPM](cpm.md)

## CMakeLists.txt structure/debbuging

Learning and understanding CMake can be an extremely tedious chore, that's why any developer-error should be reduced to near zero if the following guidelines are followed.

Pay extremely close attention as to how some CMakeLists.txt files are prepared for specific executables, especially the ones that use libraries without the main OMNI-GRID framework. It will save *a lot* of time if the exact structure is used in new CMakeLists.txt files.

If you have closely followed the CMakeLists.txt structure and are still getting errors for missing .dll files, then firstly check the executable with:

> $ dumpbin /dependents [exe]

This will show which .dll files are missing. These files can be found in the vcpkg root folder, but that's why ``${VCPKG_CORE}`` variable is present in the root CMakeLists.txt. Add the specific file to the install command as such:

> install(FILES ${VCPKG_CORE}/bin/some.dll DESTINATION path/in/install)

Do not forget that debug .dll files are stored in ${VCPKG_CORE}/debug/bin and release .dll files are stored in ${VCPKG_CORE}/bin.

Whenever CMakeLists.txt files are edited, it is highly recommended to do ``./cpm -cdb`` as just regenerating the project and rebuilding the source from an already existing file-base can cause a lot of conflicts. My advice would be to keep using ``./cpm -db`` while iterating on the code, and if something doesn't compile or the code execution just doesn't seem right, then use the ol' ``./cpm -cdb``.

Remember! If you add a file it will not be automatically detected by CMake (not always at least). You will either need to provide an additional .cpp or .h filepath in the CMakeLists.txt. After you do that sometimes ``./cpm -db`` might not identify that changes were made to the CMakeLists.txt, therefore it might be necessary to use ``./cpm -cdb``.

## Additional Information

There are a few issues with how vcpkg distributes some packages, specifically with Boost and Python libraries. When all the sources are built, some executables that link these libraries will have missing .dll files. Therefore, after building the cmake --install should be used (this is automatically handled by [CPM](build.md)).

Tested IDEs:
VSCode, Visual Studio

Notes for IDEs:

* VSCode doesn't always show includes -> this has been fixed with the inclusion of the .vscode workspace folder.
* Visual Studio - building the project with the built-in tools should work completely fine ~~(but again, sources may have missing .dll files therefore using [install] executable option should resolve any issues), but in case something fails, try doing a clear rebuild with [build.bat](build.md)~~. It is important to note that CPM project setup must be done as well as generating the project once with CPM before using this IDE, this needs to be done to save all cache-able variables that are required for CMake to operate.
TLDR: Things will break if you don't use CPM at least once.
