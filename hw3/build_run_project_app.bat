@echo off
chcp 1251 > nul

set CPP_FILES=main.cpp element_functions.cpp menu_elements.cpp 
set EXE=project.exe
set CHARSET=-finput-charset=UTF-8 -fexec-charset=windows-1251

if exist %EXE% del %EXE%

g++ %CHARSET% -std=c++11 %CPP_FILES% -o %EXE%

%EXE%
pause