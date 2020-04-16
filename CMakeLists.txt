cmake_minimum_required(VERSION 3.15)
project(234124_introduction_to_system_programming C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
set(CMAKE_C_STANDARD 99)

add_executable(234124_introduction_to_system_programming main.c Assignments/hw0/part1.c Assignments/hw0/mtm_buggy.c)