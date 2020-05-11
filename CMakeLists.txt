cmake_minimum_required(VERSION 3.0.0)
project(234124_introduction_to_system_programming C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
set(CMAKE_C_STANDARD 99)

add_executable(hw0-part1 Assignments/hw0/part1.c)
add_executable(hw0-part2 Assignments/hw0/mtm_buggy.c)
add_executable(hw1-q1 Assignments/hw1/q1.c)

add_executable(hw1-maps Assignments/hw1/maps/map.h Assignments/hw1/maps/node.h Assignments/hw1/maps/map.c)
add_executable(hw1-maps-test Assignments/hw1/maps/map_example_test.c Assignments/hw1/maps/map.h Assignments/hw1/maps/map.c Assignments/hw1/maps/node.h)
# link_directories(Assignments)
# add_executable(hw1-elections Assignments/hw1/elections/election.h)
# target_link_libraries(hw1-elections Assignments/hw1/elections/libmap.a)