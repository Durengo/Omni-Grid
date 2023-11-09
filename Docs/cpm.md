# CPM

CMake Project Generator.

## Project Setup

This part reduces the amount of time needed for developers to get and setup all the dependencies.

1. Make sure you cd into the repository and not run the script from anywhere else.
2. Strawberry Perl and Python __must__ be installed to allow the script to execute.
3. First, the CPM submodule has to be initialized. The following command runs through a dependency check and creates a new script within the root directory of the repository which is an entrypoint for the CPM submodule.
4. >$ perl .\Tools\CPM\init.pl
5. Now cpm.pl and cpm.bat will appear in the root directory.
6. Now there are 3 choices to continue:

   * I have a local VCPKG install and I have added it to my path
   * >$ ./cpm setup -n
   * I have a local VCPKG install but I have not added it to my path
   * >$ ./cpm setup -l "path/to/vcpkg"
   * I do not have a local VCPKG install
   * >$ ./cpm setup -n
   * The above command will download vcpkg into Vendor/vcpkg. If you never downloaded these packages it will a very long time (depending on your machine). It should be noted that it is better to have a local vcpkg installation somewhere, because if you accidentally delete the repository it will take an excruciating amount of time to rebuild and rerun everything. 
7. Make sure that you have enough space on your disk, as all the libraries take at least 15 Gb of space.

Notes:

1. If you delete the whole repository on accident then init.pl won't have to re-download all the dependencies as they are not stored in the repository.
2. ./cpm setup -n or ./cpm setup -l has been run at least once, the configuration of specific packages can be skipped with "--spc" flag, e.g. "$ ./cpm setup -l "c:/dev/vcpkg" --spc". This will save some time if you accidentally delete the repository. Do take note that it might cause some issues with building or generating the CMake project, so you should usually run without the "--spc" flag.

## Project Generation

The next part generates the skeleton CMake Project which will be used to build all the source code.

1. Make sure you cd into the repository and not run the script from anywhere else.
2. Before generating the project choose what kind of build you will need - either Release (-r) or Debug (-d)
3. Choose which compiler you will use. Currently only msvc is supported.
4. >$ ./cpm build -d --pg "nt/msvc"
5. Once you have chosen a compiler it will be cached and you will never need to rerun this command unless you delete the CPM submodule folder or the whole repository.

That's it! It's simple as that, just one command. And better yet, once you delete the build folder you still won't have to rerun the above command as the CPM submodule is streamlined in such a way that it will be very fast to rebuild everything in a simple command.

## Project Build

The build part has been through many iteration at it has become quite intuitive and easy to use.

First of all, before even running any build commands you must generate the project at least once.

Before running pretty much any of the commands you will need to make sure that you provide a build type - either Release (-r) or Debug (-d). This is mandatory before -b (Build) and -i (Install) flags.

Once you have done that here are simple use scenarios:

I want to build the project in Debug.
> $ ./cpm build -db

I want to build the project in Release.
> $ ./cpm build -rb

I want to build the project in Debug and also generate the Install folder.
> $ ./cpm build -dbi

I want to delete the Build and the Install directories.
> $ ./cpm build -c

I want to delete the Build and the Install directories then I want to build the project in Debug and also generate the Install folder.
> $ ./cpm build -cdbi

Hopefully you can see the pattern and how easy it is to use the build command.

Remember, even though the build folder is deleted after using the "-c" option, it still regenerates the CMake project because it saved your previous compiler option. Yey!

It's important to note that if you build with '-db' and then try to run '-ri' it will most likely fail and if it doesn't there will be a lot of problems during runtime (mostly unexpected behavior since the Debug .dlls are not meant to be used for Release executables or vice-versa).
