#include "keyboard_button.hpp"

#include <QSizePolicy>

#include "app_font.hpp"
#include <iostream>
using reo::KeyBoardButton;

KeyBoardButton::KeyBoardButton(const QString& text, QWidget* parent)
    : QPushButton(parent) {
	// Все клавиши используют одинаковый шрифт и растягиваются внутри layout.
	setFont(app_font(20));
	setText(text);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	// Фокус остаётся у главного окна, чтобы физические клавиши обрабатывались им.
	setFocusPolicy(Qt::NoFocus);
}
