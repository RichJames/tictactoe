### This defines the c++ standard (appends -std=c++17)

```CMake
set(CMAKE_CXX_STANDARD 17)
```

### `CMAKE_CXX_COMPILER_ID` is the general name of the compiler. We can test it and set options, like in this example:

```CMake
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
         set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
         set(warnings "/W4 /WX /EHsc")
endif()
if (NOT_CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

```

### You can set flags of various types like this (which is used by the example above):

```CMake
set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
```

### The add_executable command has two parameters: the first names the executable. Here, we use the project name. The second names the source files needed to build it.

```CMake
add_executable("${PROJECT_NAME}" main.cpp)
```

### The install command installs the executable you name in the 1st parameter to the destination in the 2nd. Here, bin is relative to `${CMAKE_INSTALL_PREFIX}`. So, the full path in our example would be `${CMAKE_INSTALL_PREFIX}/bin`. On my linux box, `${CMAKE_INSTALL_PREFIX}` defaults to **/usr/local**.

```CMake
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "main.cpp" DESTINATION src)
```

### The add_subdirectory command tells CMake to go into the named subdirectory and execute the CMakeLists.txt file in that directory.

```CMake
add_subdirectory("foo")
```

### To link external libraries to your executable:

```CMake
target_link_libraries(tictactoe mysqlclient)
```

### This will be equal to whatever was specified by the `project()` command.

```CMake
PROJECT_NAME
```

### This equals the current directory you are in. I think that means the current directory of the CMakeLists.txt file that is being processed.

```CMake
CMAKE_CURRENT_SOURCE_DIR
```

### You can define an alias to use elsewhere to reference something. Here, `Foo::Foo` is an alias for whatever `${PROJECT_NAME}` is defined as.

```CMake
add_library(Foo::Foo ALIAS "${PROJECT_NAME}")
```

### These are examples of generators:

```CMake
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
$<INSTALL_INTERFACE:include>
```

CMake has **build** requirements and **usage** requirements. If we mark something as **PRIVATE**, it is a **build** requirement.

If we mark it as **INTERFACE**, it is a **usage** requirement.

If we mark it as **PUBLIC**, it is _both_ a **build** and a **usage** requirement.

**Build** requirements are anything needed to compile a target.

**Usage** requirements are anything needed to link a target.

# Need to get a clearer understanding of:

```CMake
CMAKE_CXX_EXTENSIONS
CMAKE_BINARY_DIR
CMAKE_CURRENT_BINARY_DIR
CMAKE_INSTALL_PREFIX  # On linux, this is equal  to /usr/local by default
CMAKE_RUNTIME_OUTPUT_DIRECTORY
add_library("${PROJECT_NAME}" "")
include_directories(${TicTacToe_SOURCE_DIR}/include)
TicTacToe_SOURCE_DIR # The prepends ${PROJECT_NAME}, but what directory is this?
add_test(NAME io_redirects_test COMMAND io_redirects)

```

# CDash

### You need to include this to get CDash to work:

```CMake
enable_testing()
include(CTest)
```

### You add tests like this:

```CMake
add_test("test1" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
```

# CPack

### CPack offers slick, automated way to package your final executable for distribution. It can build .sh, .gz, .zip, etc. files. There are a lot of options for how it packages things. Include this to use CPack:

```CMake
include(CPack)
```

# Googletest

### To download and build googletest inside your project:

```CMake
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, test_main, gmock and gmock_main
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 )

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
                      "${gmock_SOURCE_DIR}/include")
endif()
```

### And the **CMakeLists.txt.in** file looks like this:

```CMake
 cmake_minimum_required(VERSION 2.8.2)

 project(googletest-download NONE)

 include(ExternalProject)
 ExternalProject_Add(googletest
   GIT_REPOSITORY    https://github.com/google/googletest.git
   GIT_TAG           master
   SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
   BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
   CONFIGURE_COMMAND ""
   BUILD_COMMAND     ""
   INSTALL_COMMAND   ""
   TEST_COMMAND      ""
 )

```

### Link in `gtest_main` to your test code:

```CMake
target_link_libraries(testcode gtest_main)
```

## Things I still need to figure out:

- How to build and use `gmock`
- How to automate running the tests
