#pragma once

#include "menu_item.h"

namespace MenuFunctions {
    const folin::MenuItem *show_elem_menu(const folin::MenuItem *current);
    const folin::MenuItem *show_element_with_link(const folin::MenuItem *current);
    const folin::MenuItem *show_global_menu(const folin::MenuItem *current);
}