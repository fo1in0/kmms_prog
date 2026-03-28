# vector test
add_executable(vector_tests 
    test_vector.cpp
    templates_vector.cpp          # добавляем
)

target_link_libraries(vector_tests 
    ${CONTAINERS_LIB}
    gtest
    gtest_main
)

target_include_directories(vector_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME vector_tests COMMAND vector_tests)

# doubly linked list test
add_executable(doubly_linked_list_tests 
    test_doubly_linked_list.cpp
    templates_doubly_linked_list.cpp   # добавляем
)

target_link_libraries(doubly_linked_list_tests 
    ${CONTAINERS_LIB}
    gtest
    gtest_main
)

target_include_directories(doubly_linked_list_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME doubly_linked_list_tests COMMAND doubly_linked_list_tests)