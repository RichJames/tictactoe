# Tic Tac Toe

## Overview

This is a learning and demostration project to showcase a number of things:

- Writing C++ code using c++ 17 features
- Connecting to and using a database (mysql)
- Putting a Web front end on a c++ app, via a RESTful API
- Using automated unit tests (googletest)
- Managing the project through git and GitHub
- Building a project with make, CMake and Bazel
- Managing the project through a CD/CI pipeline

Most of the above has been accomplished at this point. The things that remain are to create the RESTful API and create a web front end, add unit testing for the database interfaces, and creating a Bazel build.

I also would like to refactor some of the code as I see room for improvment in the main game logic.

---

## To Build

### Using make

The makefile is a very simple one. It requires that mysql has already been installed and that mysql.h is in the include path. For now, these have to be manually configured. I am using XAMPP, so my include path is /opt/lampp/include. Also, libmysqlclient.so needs to be findable in the library include path. The makefile will build the tictactoe app. It will also build googletest unit tests, provided googletest is installed on your system.

I would like to improve this to validate that mysql and googletest are already installed.

Given mysql and googletest are installed, you can build the tictactoe app by executing:

`make tictactoe`

from the top-level tictactoe directory (where makefile resides).

To build and run the unit tests:

`make testit`

again, from the top-level directory.

There is also:

`make makeandtest`

This combines both `make tictactoe` and `make testit` into one target so you can build and test with one command.

There are:

`make clean` and `make realclean`

targets to clean out extraneous files. The latter also removes
the tictactoe and testit apps.

---

### Using CMake

CMake will build the tictactoe app and the unit tests.

On linux, to build, from the top-level directory where CMakeLists.txt resides:

```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
```

All build artifacts will be in the build directory, include the tictactoe app. You can delete this directory to completely clean the build output and then repeat the above to build again.

This build process requires that mysql.h be findable. Since I use XXAMP, the `include_directories` statement in the CMakeLists.txt file adds `/opt/lampp/include` to the include search directories. CMake is smart enough to find where the libmysqlclient.so file is located, but I expect tht is because that location needs to be on your lib include path in the environment or else explicitly handled inside the CMake file.

I would like to figure out how to bundle googletest inside the project and also compile and use gmock successfully.

**Note to self**: review the ExampleProject I have elsewhere and apply what I learn from it to this project.

Eventually, I would like CMake to also build for a Windows platform. I don't have a Mac, so can't test building there.

---

### Using Bazel (to do)
