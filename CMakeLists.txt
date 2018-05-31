cmake_minimum_required(VERSION 3.10)
project(Vektorius)

set(CMAKE_CXX_STANDARD 11)

add_executable(Vektorius main.cpp
        mVector.h
        VogtasVector.h
       )