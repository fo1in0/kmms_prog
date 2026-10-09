#pragma once

#include <QFont>

namespace reo {
	// Шрифт интерфейса: на Windows Roboto обычно не установлен, поэтому берём системный Segoe UI.
	inline QFont app_font(const int point_size) {
#ifdef Q_OS_WIN
		return QFont("Segoe UI", point_size);
#else
		return QFont("Roboto", point_size);
#endif
	}

}
