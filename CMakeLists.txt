cmake_minimum_required(VERSION 3.26)
project(CPP3_calc_plus)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/Controller)
include_directories(src/Model)

add_executable(CPP3_calc_plus
        src/Controller/Controller.cc
        src/Controller/Controller.h
        src/Model/Model.cc
        src/Model/Model.h
)

