cmake_minimum_required(VERSION 3.22)
project(Askme)

set(CMAKE_CXX_STANDARD 14)

add_executable(Askme main.cpp user.cpp user.h qustion.cpp qustion.h manager.cpp manager.h)
