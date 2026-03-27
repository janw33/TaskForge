cmake_minimum_required(VERSION 3.10)
project(TaskForge)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaskForge
    Account.cpp
    AccountManager.cpp
    Interface.cpp
    TaskForge.cpp
)