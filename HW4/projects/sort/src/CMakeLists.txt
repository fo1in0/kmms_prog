add_library(bubble_sort_lib STATIC
    bubble_sort.cpp
    bubble_sort.hpp
)

target_include_directories(bubble_sort_lib PUBLIC .)