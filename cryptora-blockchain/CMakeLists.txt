cmake_minimum_required(VERSION 3.16)

project(cryptora-node)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    cryptora-node
    src/main.cpp
)
