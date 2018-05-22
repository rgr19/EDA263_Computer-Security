cmake_minimum_required(VERSION 3.9)
project(EDA262_CODE)

set(CMAKE_CXX_STANDARD 11)

include_directories("E:/_Include/remote11.chalmers.se/usr/include")

add_executable(login_linux
        Lab1/uid_tests/uid_drop_test.c
        )
