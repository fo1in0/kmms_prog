#include "InputHandler.h"
#include <iostream>
#include <string>
#include <limits>

double InputHandler::getNumber(const std::string& prompt) {
    double number;
    while (true) {
        std::cout << prompt;
        if (std::cin >> number) {
            break;
        } else {
            std::cout << "Ошибка: введите число\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return number;
}

char InputHandler::getOperation() {
    char operation;
    while (true) {
        std::cout << "Выберите операцию (+, -, *, /): ";
        std::cin >> operation;
        
        // Очищаем буфер ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
            break;
        } else {
            std::cout << "Ошибка: выберите одну из операций: +, -, *, /\n";
        }
    }
    return operation;
}

bool InputHandler::askContinue() {
    char answer;
    while (true) {
        std::cout << "\nПродолжить? (y/n): ";
        std::cin >> answer;
        
        // Очищаем буфер ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (answer == 'y' || answer == 'Y') {
            return true;
        } else if (answer == 'n' || answer == 'N') {
            return false;
        } else {
            std::cout << "Введите 'y' или 'n'\n";
        }
    }
}