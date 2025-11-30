#include "elem_func.h"
#include <iostream>


static void print_menu_items(const folin::MenuItem* current) {
    for (int i = 0; i < current->children_count; i++) {
        std::cout << i + 1 << " - " << current->children[i]->title << std::endl;
    }
}

static int get_user_choice(int children_count) {
    std::cout << "Выберите пункт меню: ";
    int n;
    do {
        std::cin >> n;
        if (n > children_count) {
            std::cout << "Введен неверный номер меню, попробуйте снова!" << std::endl;
        }
    } while (n > children_count);
    return n;
}

static const folin::MenuItem* handle_user_choice(const folin::MenuItem* current, int n) {
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

const folin::MenuItem *MenuFunctions::show_global_menu(const folin::MenuItem *current) {
    if (current->parent == nullptr) {
        std::cout << "0 - Пойти играть в футбол" << std::endl;
    } else if (current->parent->parent == nullptr) {
        std::cout << "0 - Выйти в главное меню" << std::endl;
    } else {
        std::cout << "0 - Выйти в предыдущее меню" << std::endl;
    }

    print_menu_items(current);

    int n = get_user_choice(current->children_count);

    return handle_user_choice(current, n);
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