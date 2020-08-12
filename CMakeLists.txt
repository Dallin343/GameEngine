cmake_minimum_required(VERSION 3.17)
project(GameEngine)

set(CMAKE_CXX_STANDARD 14)

add_library(GameEngine SHARED library.cpp library.h)