cmake_minimum_required(VERSION 3.5)
project(ascii_image)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

set(DEPENDENCIES "${PROJECT_SOURCE_DIR}/libs")
if(NOT EXISTS ${DEPENDENCIES})
    file(MAKE_DIRECTORY ${DEPENDENCIES})
endif ()

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.h)

file(GLOB_RECURSE LIBS_SRCS libs/*.cpp)
file(GLOB_RECURSE LIBS_HDRS libs/*.h)

add_executable(ascii_image ${SRCS} ${HDRS} ${LIBS_SRCS} ${LIBS_HDRS})
target_link_libraries(ascii_image ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/fruits.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/mike.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/shades.gif
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})