project(MenuTask)

# Просто перечислите файлы БЕЗ полных путей
add_executable(MenuTask
    main.cpp
    menu_elem.cpp
    elem_func.cpp
    
)

# И заголовки (если нужно)
target_sources(MenuTask PRIVATE
    menu_elem.hpp
    menu_item.hpp
    elem_func.hpp
)

target_include_directories(MenuTask PRIVATE .)

# Проверка
message(STATUS "MenuTask will be built from files in: ${CMAKE_CURRENT_SOURCE_DIR}")