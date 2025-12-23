cmake_minimum_required(VERSION 3.10)
project(MenuTask)

add_executable(MenuTask
    main.cpp
    menu_item.hpp
    elem_func.cpp
    elem_func.hpp
    menu_elem.cpp
    menu_elem.hpp
)

target_include_directories(MenuTask PRIVATE .)