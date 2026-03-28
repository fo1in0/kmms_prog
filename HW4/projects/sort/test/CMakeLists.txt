project(test_bubble)

add_executable(test_bubble
    test_bubble.cpp
)




target_link_libraries(test_bubble
    ${BUBBLE_SORT_LIB_NAME}  
    gtest
    gtest_main
)



add_test(NAME BubbleSortTest COMMAND test_bubble)
