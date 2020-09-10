cmake_minimum_required(VERSION 3.16)
project(Sequential_Version)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )

add_executable(Sequential_Version main.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( Sequential_Version ${OpenCV_LIBS} )