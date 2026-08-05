cmake_minimum_required(VERSION 3.16)
project(CafeManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(cafe_management_system
    src/main.cpp
    src/Menu.cpp
    src/Staff.cpp
    src/Finance.cpp
)
