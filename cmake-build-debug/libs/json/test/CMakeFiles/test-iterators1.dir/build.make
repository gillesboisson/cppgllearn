# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gillesboisson/Projects/sandbox/cpp_learn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug

# Include any dependencies generated for this target.
include libs/json/test/CMakeFiles/test-iterators1.dir/depend.make

# Include the progress variables for this target.
include libs/json/test/CMakeFiles/test-iterators1.dir/progress.make

# Include the compile flags for this target's objects.
include libs/json/test/CMakeFiles/test-iterators1.dir/flags.make

libs/json/test/CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.o: libs/json/test/CMakeFiles/test-iterators1.dir/flags.make
libs/json/test/CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.o: ../libs/json/test/src/unit-iterators1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/json/test/CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.o"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.o -c /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/src/unit-iterators1.cpp

libs/json/test/CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.i"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/src/unit-iterators1.cpp > CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.i

libs/json/test/CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.s"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/src/unit-iterators1.cpp -o CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.s

# Object files for target test-iterators1
test__iterators1_OBJECTS = \
"CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.o"

# External object files for target test-iterators1
test__iterators1_EXTERNAL_OBJECTS = \
"/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o"

libs/json/test/test-iterators1: libs/json/test/CMakeFiles/test-iterators1.dir/src/unit-iterators1.cpp.o
libs/json/test/test-iterators1: libs/json/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o
libs/json/test/test-iterators1: libs/json/test/CMakeFiles/test-iterators1.dir/build.make
libs/json/test/test-iterators1: libs/json/test/CMakeFiles/test-iterators1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-iterators1"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-iterators1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/json/test/CMakeFiles/test-iterators1.dir/build: libs/json/test/test-iterators1

.PHONY : libs/json/test/CMakeFiles/test-iterators1.dir/build

libs/json/test/CMakeFiles/test-iterators1.dir/clean:
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && $(CMAKE_COMMAND) -P CMakeFiles/test-iterators1.dir/cmake_clean.cmake
.PHONY : libs/json/test/CMakeFiles/test-iterators1.dir/clean

libs/json/test/CMakeFiles/test-iterators1.dir/depend:
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gillesboisson/Projects/sandbox/cpp_learn /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test/CMakeFiles/test-iterators1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/json/test/CMakeFiles/test-iterators1.dir/depend

