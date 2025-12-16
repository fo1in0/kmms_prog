cmake_minimum_required(VERSION 3.10)
project(Menu_Task)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Menu_Task
        main.cpp
        menu_elements.cpp
        elem_func.cpp
        menu_item.h
        menu_elements.h
        elem_func.h
)