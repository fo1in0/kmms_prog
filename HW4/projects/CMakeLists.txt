cmake_minimum_required(VERSION 3.10)
project(CMake_MultiProject)

# Подключаем GoogleTest
add_subdirectory(lib/googletest)

# Подключаем проект меню
add_subdirectory(MenuTask)

# Подключаем библиотеку сортировки и тесты
add_subdirectory(sort/src)
add_subdirectory(sort/test)

почему такое название project(kmms_prog_2023)