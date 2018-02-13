cmake_minimum_required(VERSION 3.9)
project(EDA262_CODE)

set(CMAKE_CXX_STANDARD 11)

include_directories("E:/_Include/remote11.chalmers.se/usr/include")

add_executable(login_linux
        Lab1/login_linux.c
        Lab1/makepass.c
        Lab1/pwent.c
        Lab1/pwent.h Hacking/Computerphile/buffer_overflow_000.c)
