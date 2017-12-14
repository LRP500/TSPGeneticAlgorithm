cmake_minimum_required(VERSION 3.9)
project(TSPGeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(TSPGeneticAlgorithm
        src/main.cpp
        src/City.cpp src/City.hpp
        src/TSPManager.cpp src/TSPManager.hpp
        src/Tour.cpp src/Tour.hpp
        src/Population.cpp src/Population.hpp
        src/Utils/utils.cpp src/Utils/utils.h
        src/Timer/Timer.cpp src/Timer/Timer.hpp)