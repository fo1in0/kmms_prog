#include <clocale>
#include <iostream>

#include "menu_elements.h"
#include "menu_item.h"
#include "elem_func.h"


int main() {
    std::cout << "Добро пожаловать!\n";
    const folin::MenuItem *current = &folin:: MAIN_LEVEL0;

    do {
        current = current -> itemFunction(current);
    } while (true);
}



