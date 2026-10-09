#pragma once

#include <QString>

namespace reo {
	// Описание клавиши связывает её код ОС с текстом на экранной кнопке.
	struct KeyData {
		const int code;
		const QString text;
	};
}
