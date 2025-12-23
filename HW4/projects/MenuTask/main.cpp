#include <clocale>
#include <iostream>

#include "menu_elem.hpp"
#include "elem_func.hpp"
#include "menu_item.hpp"


int main() {
    std::cout << "Добро пожаловать!\n";
    const folin::MenuItem *current = &folin:: MAIN_LEVEL0;

    do {
        current = current -> itemFunction(current);
    } while (true);
}



