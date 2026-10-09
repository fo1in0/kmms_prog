#include "keyboard_window.hpp"
#include <iostream>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include "app_font.hpp"

using reo::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	// Фиксируем удобный размер рабочего окна и его заголовок.
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");
	// Главное окно принимает физические клавиши после кликов по виртуальной клавиатуре.
	setFocusPolicy(Qt::StrongFocus);
	
	// Верхняя часть окна показывает изображение, связанное с оформлением проекта.
	// Путь строится от папки exe, поэтому запуск двойным кликом или из другой папки тоже работает.
	QPixmap pixmap(QCoreApplication::applicationDirPath() + "/img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

	// Многострочное поле позволяет отобразить результат работы клавиши Enter.
	display = new QTextEdit();
	display->setMinimumHeight(80);
	display->setFont(app_font(40));
	display->setReadOnly(true);
	display->setFocusPolicy(Qt::NoFocus);
	display->setText("Помоги мне заработать лучше...");

	// Виртуальная клавиатура получает ту же ширину, что и основное окно.
	keyboard = new KeyBoard(keyboard_width);

	// Располагаем изображение, поле вывода и клавиатуру вертикально.
    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);

	// Сигналы виртуальных кнопок подключаются к слотам изменения текста.
	connect(keyboard, &KeyBoard::text_key_pressed, this, &KeyBoardWindow::append_text);
	connect(keyboard, &KeyBoard::backspace_pressed, this, &KeyBoardWindow::remove_last_character);
	connect(keyboard, &KeyBoard::enter_pressed, this, &KeyBoardWindow::insert_line_break);
	setFocus();
}


void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	std::cout << "нажата физическая клавиша на клавиатуре" << std::endl;
	// Сначала обрабатываем служебные клавиши, у которых нет символа в раскладке.
	if (event->key() == Qt::Key_Backspace) {
		keyboard->animate_backspace();
		return;
	}
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		keyboard->animate_enter();
		return;
	}
	if (event->key() == Qt::Key_Space) {
		keyboard->animate_space();
		return;
	}

	// На Windows nativeVirtualKey — это VK-код физической клавиши, он не зависит от
	// языка раскладки и совпадает с таблицей в keyboard_data.cpp.
	// На других платформах (macOS) коды не совпадают, поэтому там приоритет у текста события.
	const int key = event->nativeVirtualKey();
#ifdef Q_OS_WIN
	if (keyboard->is_key_allowed(key)) {
		keyboard->animate_button(key);
	} else {
		// Цифровой блок и прочие клавиши, которых нет в таблице кодов.
		keyboard->animate_button_by_text(event->text());
	}
#else
	if (!keyboard->animate_button_by_text(event->text()) && keyboard->is_key_allowed(key)) {
		keyboard->animate_button(key);
	}
#endif
}

void KeyBoardWindow::append_text(const QString& text) {
	// Всегда вставляем символ в конец, чтобы физический и мышиный ввод совпадали.
	display->moveCursor(QTextCursor::End);
	display->insertPlainText(text);
}

void KeyBoardWindow::remove_last_character() {
	// Удаляем один символ перед курсором, если поле не пустое.
	display->moveCursor(QTextCursor::End);
	QTextCursor cursor = display->textCursor();
	cursor.deletePreviousChar();
	display->setTextCursor(cursor);
}

void KeyBoardWindow::insert_line_break() {
	// Enter добавляет перевод строки в многострочное поле.
	append_text("\n");
}
