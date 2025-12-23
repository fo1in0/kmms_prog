cmake_minimum_required(VERSION 3.10)
project(CMake_MultiProject)
enable_testing()

# Подключаем GoogleTest
add_subdirectory(lib/googletest/googletest)

# Подключаем проект меню
add_subdirectory(MenuTask)

# Подключаем библиотеку сортировки и тесты
add_subdirectory(sort/src)
add_subdirectory(sort/test)
