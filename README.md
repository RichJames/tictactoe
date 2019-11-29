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

I would like to improve this to validate that mysql and googletest are already installed and, perhaps, find the appropriate directories for file and library inclusion. Again, for now, this has to be manually configured.

Given mysql and googletest are installed, you can build the tictactoe app by executing:

`make tictactoe`

from the top-level tictactoe directory (where makefile resides).

To build and run the unit tests:

`make testit`

again, from the top-level directory.

There are:

`make clean` and `make realclean`

targets to clean out extraneous files. The latter also removes
the tictactoe and testit apps.

Eventually, I would like CMake to also build for a Windows platform. I don't have a Mac, so can't test building there.

---

### Using CMake

At the moment, CMake will build the tictactoe app, but doesn't build the unit tests. I hope to add the latter soon.

On linux, to build, from the top-level directory where CMakeLists.txt resides:

```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
```

All build artifacts will be in the build directory, include the tictactoe app. You can delete this directory to completely clean the build output and then repeat the above to build again.

Again, this build process requires that mysql.h be findable. Since I use XXAMP, the `include_directories` statement in the CMakeLists.txt file adds `/opt/lampp/include` to the include search directories. CMake is smart enough to find where the libmysqlclient.so file is located, but I expect tht is because that location needs to be on your lib include path in the environment or else explicitly handled inside the CMake file.

---

### Using Bazel (to do)

---

## Note to myself

There was a tough bug that caused an infinite loop in my player move logic. It surfaced when the computer player had to make a random move. The problem ultimately was that I was using an `int` called `move` that was defined outside the `do while` loop (because it was part of a larger logic). I initialzed this int to a defined `invalid_move` value before going through the logic, so I could know if a valid move had been found or not.

The problem was that inside my `do while` loop, in my assignment of the random move to `move`, I initialized a local variable of the same name:

```c++
int move = invalid_move;
do {
  int move = RandomNumberGenerator::getRandomNumber();
while (!pBoard->mark_move(move, my_mark));
```

This hid the `move` variable defined in the outer scope. The problem this created was the while test always referenced that outer scope variable, which was initialized to `invalid_move`. In other words, my assignment inside the do while never set the `move` variable I was testing against.

The simple fix:

`move = RandomNumberGenerator::getRandomNumber();`

Yep, just don't initialize a local `move` variable.

This was frustrating, but glad I finally found it.
