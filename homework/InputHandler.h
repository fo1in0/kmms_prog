#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>

class InputHandler {
public:
    static double getNumber(const std::string& prompt);
    static char getOperation();
    static bool askContinue();
};

#endif