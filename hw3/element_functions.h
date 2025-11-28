#pragma once

#include "menu.h"


namespace MenuFunctions{

    const folin::MenuItem *show_element_menu(const folin::MenuItem *current);

    const folin::MenuItem *show_element_with_link_menu(const folin::MenuItem *current);

    const folin::MenuItem *show_global_menu(const folin::MenuItem *current);

}