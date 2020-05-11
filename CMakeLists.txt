cmake_minimum_required(VERSION 3.0.0)
project(234124_introduction_to_system_programming C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
set(CMAKE_C_STANDARD 99)

set(MTM_MAPS "Assignments/hw1/maps")
set(MTM_ELECTIONS "Assignments/hw1/elections")

add_executable(hw0-part1 Assignments/hw0/part1.c)
add_executable(hw0-part2 Assignments/hw0/mtm_buggy.c)
add_executable(hw1-q1 Assignments/hw1/q1.c)

add_executable(hw1-maps ${MTM_MAPS}/map.h ${MTM_MAPS}/node.h ${MTM_MAPS}/map.c)
add_executable(hw1-maps-test ${MTM_MAPS}/map_example_test.c ${MTM_MAPS}/map.h ${MTM_MAPS}/map.c ${MTM_MAPS}/node.h)
add_executable(hw1-maps-test1 ${MTM_MAPS}/Test_1/map_tests.c ${MTM_MAPS}/map.h ${MTM_MAPS}/map.c ${MTM_MAPS}/node.h ${MTM_MAPS}/Test_1/test_utilities.h ${MTM_MAPS}/Test_1/utils.c ${MTM_MAPS}/Test_1/utils.h)
link_directories(.)
add_executable(hw1-elections ${MTM_ELECTIONS}/election.h ${MTM_ELECTIONS}/election.c ${MTM_ELECTIONS}/map.h ${MTM_ELECTIONS}/area.h ${MTM_ELECTIONS}/tribe.h ${MTM_MAPS}/map.c ${MTM_ELECTIONS}/call_result.h)
# target_link_libraries(hw1-elections ${MTM_ELECTIONS}/libmap.a)