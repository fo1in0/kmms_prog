#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory)
    : GameLevel(ui_factory) {
    init_data();
}

bool ThirdLevel::is_final() const noexcept {
    return true;
}

biv::GameLevel* ThirdLevel::get_next() {
    return next;
}

// --------------------------------------------------
//                    PROTECTED
// --------------------------------------------------
// Финальный уровень: несколько участков пути, разрывы,
// плавающие платформы и разные типы врагов. Маршрут
// сложный, но все препятствия можно пройти прыжком.
void ThirdLevel::init_data() {
    ui_factory->create_mario({39, 10}, 3, 3);

    // Основной маршрут с небольшими разрывами.
    ui_factory->create_ship({20, 25}, 35, 2);
    ui_factory->create_ship({60, 23}, 25, 2);
    ui_factory->create_ship({95, 25}, 25, 2);
    ui_factory->create_ship({130, 22}, 25, 2);
    ui_factory->create_ship({165, 25}, 25, 2);

    // Плавающие платформы помогают пройти разрывы и требуют
    // контроля прыжка и положения Марио.
    ui_factory->create_floating_platform({48, 18}, 8, 2);
    ui_factory->create_floating_platform({82, 17}, 8, 2);
    ui_factory->create_floating_platform({118, 16}, 8, 2);
    ui_factory->create_floating_platform({153, 18}, 8, 2);

    // Наземные враги на разных участках.
    ui_factory->create_enemy({35, 5}, 3, 2);
    ui_factory->create_enemy({67, 5}, 3, 2);
    ui_factory->create_enemy({101, 5}, 3, 2);
    ui_factory->create_enemy({137, 5}, 3, 2);
    ui_factory->create_enemy({173, 5}, 3, 2);

    // Прыгающие враги добавляют препятствия на маршруте.
    ui_factory->create_jumping_enemy({52, 10}, 3, 2);
    ui_factory->create_jumping_enemy({110, 10}, 3, 2);
    ui_factory->create_jumping_enemy({158, 10}, 3, 2);

    // Летающие враги перекрывают верхнюю часть маршрута.
    ui_factory->create_flying_enemy({75, 12}, 3, 2);
    ui_factory->create_flying_enemy({125, 12}, 3, 2);
    ui_factory->create_flying_enemy({170, 12}, 3, 2);

    // Последний статический объект — финиш.
    // Столкновение с ним завершает финальный уровень.
    ui_factory->create_ship({195, 23}, 5, 2);
}
