#ifndef CALCULATORAPP_H
#define CALCULATORAPP_H

#include "Calculator.h"
#include "InputHandler.h"

class CalculatorApp {
private:
    Calculator calculator;
    InputHandler inputHandler;
    
    double performOperation(double num1, double num2, char operation);

public:
    void run();
};

#endif