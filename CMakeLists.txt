cmake_minimum_required(VERSION 3.16)
project(OOP_Project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(OOP_Project
        main.cpp
        studentas.cpp
        failai.cpp
        utils.cpp
        results.cpp
        results.h
)