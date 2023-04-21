cmake_minimum_required(VERSION 3.8)
project(M2OEP-naltland)

set(CMAKE_CXX_STANDARD 14)

add_executable(M2OEP-naltland
        main.cpp
        marketAPI.h marketAPI.cpp
        Investment.cpp Investment.h
        Stock.cpp Stock.h
        Bond.cpp Bond.h)

add_executable(M2OEP-naltland_Testing
        marketAPITesting.cpp
        marketAPI.h
        marketAPI.cpp
        Investment.cpp Investment.h
        Stock.cpp Stock.h
        Bond.cpp Bond.h)
