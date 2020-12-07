cmake_minimum_required(VERSION 3.16)
project(OpenCV_Demo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCV_Demo main.cpp Huffman_Code.cpp Huffman_Code.h Fano_Code.cpp Fano_Code.h)

target_link_libraries(OpenCV_Demo ${OpenCV_LIBS})