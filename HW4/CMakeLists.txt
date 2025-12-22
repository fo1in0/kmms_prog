cmake_minimum_required(VERSION 3.10)

project(HW4)

add_subdirectory(MenuTask)
add_subdirectory(sort)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()