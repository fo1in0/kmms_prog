@echo off
setlocal EnableDelayedExpansion

set BUILD_FOLDER=..\..\build
set NAME=kmms_prog_2023

echo Очистка предыдущей сборки...
if exist %BUILD_FOLDER% rmdir /S /Q %BUILD_FOLDER%
mkdir %BUILD_FOLDER%
cd %BUILD_FOLDER%

echo Генерация проекта...
cmake -G "MinGW Makefiles" ..\HW4\projects

echo Сборка проекта...
cmake --build .

echo Запуск тестов...
ctest --output-on-failure

pause