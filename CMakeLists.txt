cmake_minimum_required(VERSION 3.8)
project(Final-Project-naltland)

set(CMAKE_CXX_STANDARD 14)

add_executable(Final-Project-naltland
        main.cpp
        marketAPI.h marketAPI.cpp
        Investment.cpp Investment.h
        Stock.cpp Stock.h
        )

add_executable(Final-Project-naltland_Testing
        marketAPITesting.cpp
        marketAPI.h marketAPI.cpp
        Investment.cpp Investment.h
        Stock.cpp Stock.h
        )
