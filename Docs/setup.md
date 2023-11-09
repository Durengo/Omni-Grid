# setup.pl

This is a very handy script to reduce the amount of time needed on the developers side to get all the dependencies if they don't have them already or never used vcpkg.

## Running

1. Make sure you cd into the repository and not run the script from anywhere else.
2. Strawberry Perl __must__ be installed to allow the script to execute.
3. On windows from Powershell the script can be ran with ``./setup`` (this just executes setup.bat which is an entrypoint into setup.pl)
4. > $ ./setup --help
5. If you have a local vcpkg installation then run the following command
6. > ./setup --vcpkg-location "location/to/vcpkg_root/"
7. Make sure that the provided location is the exact root of where vcpkg.exe is located
8. Otherwise run the following command:
9. > ./setup
10. This will download vcpkg into vendor/vcpkg, download and install all the libraries, as well as execute some Boost library generation code. If you never downloaded these packages it will a very long time (depending on your machine).
11. Also make sure that you have enough space on your disk, as all the libraries take at least 15 Gb of space.
12. The script also interacts with [build.py](build.py.md) - which is the internal script for generating CMake build files on any platform (of course the code has to be platform/compiler compatible beforehand).