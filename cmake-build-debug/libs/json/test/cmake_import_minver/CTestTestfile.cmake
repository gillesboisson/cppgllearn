# CMake generated Testfile for 
# Source directory: /Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/cmake_import_minver
# Build directory: /Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json/test/cmake_import_minver
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_import_minver_configure "/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake" "-G" "Unix Makefiles" "-Dnlohmann_json_DIR=/Users/gillesboisson/Projects/sandbox/cpp_learn/cmake-build-debug/libs/json" "/Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/cmake_import_minver/project")
set_tests_properties(cmake_import_minver_configure PROPERTIES  FIXTURES_SETUP "cmake_import_minver" _BACKTRACE_TRIPLES "/Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/cmake_import_minver/CMakeLists.txt;1;add_test;/Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/cmake_import_minver/CMakeLists.txt;0;")
add_test(cmake_import_minver_build "/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake" "--build" ".")
set_tests_properties(cmake_import_minver_build PROPERTIES  FIXTURES_REQUIRED "cmake_import_minver" _BACKTRACE_TRIPLES "/Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/cmake_import_minver/CMakeLists.txt;7;add_test;/Users/gillesboisson/Projects/sandbox/cpp_learn/libs/json/test/cmake_import_minver/CMakeLists.txt;0;")
