#include "elem_func.h"
#include <iostream>


const folin::MenuItem *MenuFunctions::show_global_menu(const folin::MenuItem *current) {
    if (current->parent == nullptr) {
        std::cout << "0 - Пойти играть в футбол" << std::endl;
    } else if (current->parent->parent == nullptr) {
        std::cout << "0 - Выйти в главное меню" << std::endl;
    } else {
        std::cout << "0 - Выйти в предыдущее меню" << std::endl;
    }

    for (int i = 0; i < current->children_count; i++) {
        std::cout << i + 1 << " - " << current->children[i]->title << std::endl;
    }

    std::cout << "Выберите пункт меню: ";
    int n;
    do {
        std::cin >> n;
        if (n > current->children_count) std::cout << "Введен неверный номер меню, попробуйте снова!" << std::endl;
    } while (n > current->children_count);

    if (n == 0) {
        if (current->parent == nullptr) {
            std::cout << "Завершение программы!" << std::endl;
            std::exit(0); 
        } else {
            std::cout << "Выйти в главное меню" << std::endl << std::endl;
            return current->parent;
        }
    }
    std::cout << std::endl;

    return current->children[n - 1];
}

const folin::MenuItem *MenuFunctions::show_elem_menu(const folin::MenuItem *current) {
    std::cout << current->title << ": " << std::endl;

    return show_global_menu(current);
};

const folin::MenuItem *MenuFunctions::show_element_with_link(const folin::MenuItem *current) {
    std::cout << current->title << ": " << std::endl;
    std::cout << "Наслаждайтесь!" << std::endl << std::endl;
    return show_global_menu(current);
};