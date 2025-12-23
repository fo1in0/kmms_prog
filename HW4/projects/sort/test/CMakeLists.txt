cmake_minimum_required(VERSION 3.10)
project(test_bubble)

add_executable(test_bubble
    test_bubble.cpp
)

target_include_directories(test_bubble PRIVATE ../src)

target_link_libraries(test_bubble
    bubble_sort_lib
    gtest
    gtest_main
)



add_test(NAME BubbleSortTest COMMAND test_bubble)