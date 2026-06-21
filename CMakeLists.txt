cmake_minimum_required(VERSION 4.2)
project(connect4)

set(CMAKE_CXX_STANDARD 20)

add_executable(connect4 main.cpp
               fonctionsUtilitaires.cpp
               fonctionsUtilitaires.h)
