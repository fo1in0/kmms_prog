#include "CalculatorApp.h"
#include <iostream>
#include <stdexcept>

void CalculatorApp::run() {
    std::cout << "=== Простой калькулятор ===\n";
    
    while (true) {
        try {
            // Получаем числа и операцию
            double num1 = inputHandler.getNumber("Введите первое число: ");
            double num2 = inputHandler.getNumber("Введите второе число: ");
            char operation = inputHandler.getOperation();
            
            // Выполняем операцию
            double result = performOperation(num1, num2, operation);
            std::cout << "Результат: " << num1 << " " << operation << " " << num2 << " = " << result << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
        // Спрашиваем, продолжить ли
        if (!inputHandler.askContinue()) {
            break;
        }
    }
    
    std::cout << "Программа завершена\n";
}

double CalculatorApp::performOperation(double num1, double num2, char operation) {
    switch (operation) {
        case '+':
            return calculator.add(num1, num2);
        case '-':
            return calculator.subtract(num1, num2);
        case '*':
            return calculator.multiply(num1, num2);
        case '/':
            return calculator.divide(num1, num2);
        default:
            throw std::runtime_error("Неизвестная операция");
    }
}