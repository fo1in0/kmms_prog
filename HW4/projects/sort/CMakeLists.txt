set(SORT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE PATH "Path to sort sources")
set(BUBBLE_SORT_LIB_NAME "bubble_sort_lib444" CACHE INTERNAL "Bubble sort library target name")

add_subdirectory(src)
add_subdirectory(test)