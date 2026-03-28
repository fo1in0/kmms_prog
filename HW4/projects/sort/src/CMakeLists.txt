add_library(${BUBBLE_SORT_LIB_NAME} STATIC
    bubble_sort.cpp
    bubble_sort.hpp
)

set_target_properties(${BUBBLE_SORT_LIB_NAME} PROPERTIES
    OUTPUT_NAME "${BUBBLE_SORT_LIB_FILE_NAME}"
    PREFIX "lib"
    SUFFIX ".a"
)

target_include_directories(${BUBBLE_SORT_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

