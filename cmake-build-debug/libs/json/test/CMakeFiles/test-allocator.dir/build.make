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
include libs/json/test/CMakeFiles/test-allocator.dir/depend.make

# Include the progress variables for this target.
include libs/json/test/CMakeFiles/test-allocator.dir/progress.make

# Include the compile flags for this target's objects.
include libs/json/test/CMakeFiles/test-allocator.dir/flags.make

libs/json/test/CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.o: libs/json/test/CMakeFiles/test-allocator.dir/flags.make
libs/json/test/CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.o: ../libs/json/test/src/unit-allocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/json/test/CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.o"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.o -c /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/src/unit-allocator.cpp

libs/json/test/CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.i"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/src/unit-allocator.cpp > CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.i

libs/json/test/CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.s"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/src/unit-allocator.cpp -o CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.s

# Object files for target test-allocator
test__allocator_OBJECTS = \
"CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.o"

# External object files for target test-allocator
test__allocator_EXTERNAL_OBJECTS = \
"/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o"

libs/json/test/test-allocator: libs/json/test/CMakeFiles/test-allocator.dir/src/unit-allocator.cpp.o
libs/json/test/test-allocator: libs/json/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o
libs/json/test/test-allocator: libs/json/test/CMakeFiles/test-allocator.dir/build.make
libs/json/test/test-allocator: libs/json/test/CMakeFiles/test-allocator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-allocator"
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-allocator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/json/test/CMakeFiles/test-allocator.dir/build: libs/json/test/test-allocator

.PHONY : libs/json/test/CMakeFiles/test-allocator.dir/build

libs/json/test/CMakeFiles/test-allocator.dir/clean:
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test && $(CMAKE_COMMAND) -P CMakeFiles/test-allocator.dir/cmake_clean.cmake
.PHONY : libs/json/test/CMakeFiles/test-allocator.dir/clean

libs/json/test/CMakeFiles/test-allocator.dir/depend:
	cd /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gillesboisson/Projects/sandbox/cpp_learn /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test/CMakeFiles/test-allocator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/json/test/CMakeFiles/test-allocator.dir/depend

