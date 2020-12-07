cmake_minimum_required(VERSION 3.16)
project(elgamal)

set(CMAKE_CXX_STANDARD 14)

add_executable(elgamal main.cpp md5.cpp md5.h elgamal.cpp elgamal.h)