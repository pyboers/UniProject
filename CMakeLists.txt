cmake_minimum_required(VERSION 3.8)
project(UniProject CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${UniProject_SOURCE_DIR}/cmake_modules")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(UniProject ${SOURCE_FILES})

find_package(GLEW REQUIRED)
find_package(OpenGl REQUIRED)
find_package(OpenAL REQUIRED)

find_package(SDL2 REQUIRED)

include_directories(
        # purposfully ommited openGL dir bc it
        # should only be accessed through glew
        ${GLEW_INCLUDE_DIRS}
        ${OPENAL_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR})
target_link_libraries(UniProject
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${SDL2_LIBRARY}
        m # link math library
        )
