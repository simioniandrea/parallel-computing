cmake_minimum_required(VERSION 3.3)
project(Parallel_OMP_Version)

set(CMAKE_CXX_STANDARD 11)

# try also to compile and execute without: -fopenmp
# in Linux just use -fopenmp, without -lomp and -Xpreprocessor
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor -fopenmp -lomp")
# the following 2 lines are needed on macOS
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# le seguenti 2 righe per inserire openCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

#[[include_directories(/usr/local/Cellar/opencv/4.0.1/include/opencv4/opencv)
link_directories(/usr/local/Cellar/opencv/4.0.1/lib)]]


set(SOURCE_FILES main.cpp)
add_executable(Parallel_OMP_Version ${SOURCE_FILES})

#riga necessaria per OpenCV
target_link_libraries( Parallel_OMP_Version ${OpenCV_LIBS} )