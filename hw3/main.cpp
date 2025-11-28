#include <clocale>
#include <iostream>

#include "menu.h"
#include "menu_elements.h"
#include "element_functions.h"


int main() {
    std::setlocale(LC_ALL, "");
    std::cout << "Добро Пожаловать в программу обучения!\n";
    const folin::MenuItem *current = &folin::MAIN_LEVEL0;

    do {
        current = current->itemfunction(current);
    } while (true);

    return 0;
}