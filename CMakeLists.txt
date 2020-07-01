cmake_minimum_required(VERSION 3.0.0)
project(234124_introduction_to_system_programming C CXX)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
set(CMAKE_C_STANDARD 99)

set(MTM_MAPS "Assignments/hw1/maps")
set(MTM_ELECTIONS "Assignments/hw1/elections")
set(MAPS ${MTM_MAPS}/map.h ${MTM_MAPS}/map.c ${MTM_MAPS}/node.h ${MTM_MAPS}/node.c ${MTM_MAPS}/map.c)
set(MAPS_TEST_1 ${MAPS})
set(ELECTIONS ${MTM_ELECTIONS}/election.h ${MTM_ELECTIONS}/election.c ${MTM_ELECTIONS}/util.h ${MTM_ELECTIONS}/util.c ${MTM_ELECTIONS}/entity.h ${MTM_ELECTIONS}/entity.c ${MTM_ELECTIONS}/call_result.h ${MTM_ELECTIONS}/ballotbox.h ${MTM_ELECTIONS}/ballotbox.c ${MTM_ELECTIONS}/ballot.h ${MTM_ELECTIONS}/ballot.c ${MTM_ELECTIONS}/mtm_map/map.h ${MTM_ELECTIONS}/mtm_map/map.c ${MTM_ELECTIONS}/mtm_map/node.h ${MTM_ELECTIONS}/mtm_map/node.c)
set(ELECTIONS_TEST_1 ${ELECTIONS} ${MTM_ELECTIONS}/Tests/election_test.c)
set(ELECTIONS_TEST_2 ${ELECTIONS} ${MTM_ELECTIONS}/Tests/election_tests.c ${MTM_ELECTIONS}/test_utilities.h ${MTM_ELECTIONS}/Tests/utils.c ${MTM_ELECTIONS}/Tests/utils.h)
set(MTM_HW3 "Assignments/hw3/")
set(MTM_HW3_A ${MTM_HW3}/Part\ A)


add_executable(hw0-part1 Assignments/hw0/part1.c)
add_executable(hw0-part2 Assignments/hw0/mtm_buggy.c)
add_executable(hw1-q1 Assignments/hw1/dry/q1.c Assignments/hw1/dry/q.c Assignments/hw1/dry/q.h)

add_executable(hw1-maps ${MAPS})
add_executable(hw1-maps-test ${MAPS} ${MTM_MAPS}/map_example_test.c)
# add_executable(hw1-maps-test1 ${MAPS} ${MTM_MAPS}/map.c ${MTM_MAPS}/Test_1/test_utilities.h ${MTM_MAPS}/Test_1/utils.c ${MTM_MAPS}/Test_1/utils.h)

link_directories(.)
add_executable(hw1-elections  ${ELECTIONS})
add_executable(hw1-elections-test ${ELECTIONS_TEST_1})
add_executable(hw1-elections-test2 ${ELECTIONS_TEST_2})
# target_link_libraries(hw1-elections ${MTM_ELECTIONS}/libmap.a)

add_executable(hw3-parta ${MTM_HW3_A}/IntMatrix.cpp ${MTM_HW3_A}/Auxiliaries.cpp ${MTM_HW3_A}/Tests/partA_tester.cpp)