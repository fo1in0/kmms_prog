#!/bin/bash

CPP_FILES="main.cpp Calculator.cpp InputHandler.cpp CalculatorApp.cpp"
APP="calculator"

if [ -f $APP ]; then rm $APP; fi

g++ -std=c++11 $CPP_FILES -o $APP

./$APP