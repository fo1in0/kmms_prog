@echo off
chcp 65001 >nul
setlocal

rem Использование:  build.bat [путь_к_Qt]
rem Пример:         build.bat C:\Qt\6.7.2\msvc2019_64
rem Путь к Qt можно также задать переменной окружения QT_PREFIX.

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=.

if not "%~1"=="" set "QT_PREFIX=%~1"

where cmake >nul 2>nul
if errorlevel 1 goto no_cmake

where ninja >nul 2>nul
if errorlevel 1 goto no_ninja

rem Если компилятор не найден, подключаем окружение Visual Studio через vswhere.
where cl >nul 2>nul
if not errorlevel 1 goto have_compiler
where g++ >nul 2>nul
if not errorlevel 1 goto have_compiler
call :setup_msvc
if errorlevel 1 goto no_compiler

:have_compiler
if not exist "%BUILD_FOLDER%" mkdir "%BUILD_FOLDER%"
cd "%BUILD_FOLDER%"

if defined QT_PREFIX (
	cmake -G %BUILD_TYPE% -DCMAKE_BUILD_TYPE=Release "-DCMAKE_PREFIX_PATH=%QT_PREFIX%" ..\%SOURCE_FOLDER%
) else (
	cmake -G %BUILD_TYPE% -DCMAKE_BUILD_TYPE=Release ..\%SOURCE_FOLDER%
)
if errorlevel 1 goto failed

cmake --build .
if errorlevel 1 goto failed

rem Папка img и Qt DLL копируются в build_ninja автоматически (см. CMakeLists.txt).
cd ..
echo.
echo Готово: %BUILD_FOLDER%\keyboard.exe
exit /b 0

:setup_msvc
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" exit /b 1
set "VS_PATH="
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VS_PATH=%%i"
if not defined VS_PATH exit /b 1
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
exit /b %errorlevel%

:no_cmake
echo Не найден cmake. Установите CMake и добавьте его в PATH.
exit /b 1

:no_ninja
echo Не найден ninja. Установите Ninja (или используйте cmake из Qt Creator / Visual Studio).
exit /b 1

:no_compiler
echo Не найден компилятор. Установите Visual Studio Build Tools (C++) или MinGW из комплекта Qt.
exit /b 1

:failed
cd ..
echo Сборка завершилась с ошибкой.
exit /b 1
