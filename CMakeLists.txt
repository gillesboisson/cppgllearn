cmake_minimum_required(VERSION 3.14)
project(cpp_learn)

set(SRC_DIR src)
file(GLOB SOURCE_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*/*.cpp ${SRC_DIR}/*/**/*.cpp libs/jsoncpp/dist/jsoncpp.cpp)

set(LIBS_INCLUDES libs/glad/include libs/glm libs/tinygltf-2.2.0 libs/jsoncpp/dist)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(DEBUG_GL)


add_executable(cpp_learn ${SOURCE_FILES} libs/glad/src/glad.c)

find_package(OpenGL REQUIRED)

#add_subdirectory(libs/json)

include_directories( ${OPENGL_INCLUDE_DIRS} ${LIBS_INCLUDES})

find_package(glfw3 3.3 REQUIRED)
include_directories(${GKFW_INCLUDE_DIRS})

target_link_libraries(cpp_learn ${OPENGL_LIBRARIES} glfw)
