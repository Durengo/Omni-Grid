# Testing

## How to build tests?

1. Make sure that in [CMakeLists.txt](../CMakeLists.txt) "MAIN_TEST" is set to "ON" -> Line 7
2. Build the specific test (in IDE) or run CPM build command to build everything ($ ./cpm build -db)

## How to run tests?

1. Each test has it's own executable and can be ran individually from within the Build or Install folder
2. Every test is integrated with CTest and when bulk testing "$ ctest --test-dir "build" -C Debug -VV" can be run from the root of the repository -> this will run all the tests (if an exe is missing it will throw an error as well)

## Checking instabilities

Not all tests are made equal. Sometimes they have a certain percentage of failure, therefore a simple PS script was created -> [TestRunner.ps1](../Tools/TestRunner.ps1). Before running it make sure that the build type within the script is identical to your build (line 17) otherwise the command will fail. E.g. if we build Release we would modify line 17 from "ctest --test-dir "build" -C Debug -VV > $null 2>&1" to "ctest --test-dir "build" -C Release -VV > $null 2>&1" and vice-versa. By default this will rerun the command 100 times, but you can adjust the value to what you need.

Note: make sure to run the script from the root of the repository

## How to write tests?

This project is the [googletest](https://github.com/google/googletest) framework. All the documentation on how to exactly write tests are there.

Additional guidelines:

* Make sure that you are creating unit tests for specific parts of code (classes, structs, etc.)
* Make sure to follow the exact conventions for CMakeList files when creating new unit tests
