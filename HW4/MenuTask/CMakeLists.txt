cmake_minimum_required(VERSION 3.10)

project(MenuTask)

add_executable(
	main.cpp
	el_func.cpp
	menu_el.cpp
)

target_include_directories(menu PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS menu RUNTIME DESTINATION bin)