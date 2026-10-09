cmake_minimum_required(VERSION 3.16)

project(keyboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
	src/main.cpp
	src/keyboard.cpp
	src/keyboard_button.cpp
	src/keyboard_data.cpp
	src/keyboard_window.cpp
	src/welcome_window.cpp
)

qt_add_executable(${PROJECT_NAME}
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Без GUI-подсистемы консольное окно не появляется (на Windows нужен WinMain, Qt подключает его сам).
#set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

if(MSVC)
	# Исходники в UTF-8 (русские строки): без /utf-8 MSVC читает их в кодовой странице ОС и ломает кириллицу.
	target_compile_options(${PROJECT_NAME} PRIVATE /utf-8 /W3)
endif()

# Картинка кладётся рядом с exe, приложение ищет её относительно exe, а не текущей папки.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/img"
		"$<TARGET_FILE_DIR:${PROJECT_NAME}>/img"
)

if(WIN32)
	# windeployqt копирует Qt DLL и плагины платформы (qwindows.dll), чтобы exe запускался без установленного Qt в PATH.
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt
		HINTS "${Qt${QT_VERSION_MAJOR}_DIR}/../../../bin"
	)
	if(WINDEPLOYQT_EXECUTABLE)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations "$<TARGET_FILE:${PROJECT_NAME}>"
		)
	else()
		message(WARNING "windeployqt не найден: для запуска exe добавьте папку bin комплекта Qt в PATH.")
	endif()
endif()

qt_finalize_executable(${PROJECT_NAME})
