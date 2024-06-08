cmake_minimum_required(VERSION 3.5)
project(ascii_image)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(ascii_image src/main.cpp)
target_link_libraries(ascii_image ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/fruits.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})