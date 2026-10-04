#include "second_level.hpp"
#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
    init_data();
}

bool SecondLevel::is_final() const noexcept {
    return false;
}

biv::GameLevel* SecondLevel::get_next() {
    if (!next) {
        clear_data();
        next = new biv::ThirdLevel(ui_factory);
    }
    return next;
}

// ----------------------------------------------------------------------------
//                                  PROTECTED
// ----------------------------------------------------------------------------
// Тестовый уровень: здесь удобно проверить новые типы врагов
// и плавающую платформу без сложного маршрута.
void SecondLevel::init_data() {
    ui_factory->create_mario({39, 10}, 3, 3);

    // Простая безопасная поверхность для начала уровня.
    ui_factory->create_ship({20, 25}, 55, 2);
    ui_factory->create_ship({75, 22}, 35, 2);

    // Плавающая платформа для проверки движения вместе с ней.
    // Она НЕ должна быть последним static_obj,
    // поэтому после неё создаём финальный корабль.
    ui_factory->create_floating_platform({65, 17}, 8, 2);

    // Последний корабль является концом второго уровня.
    ui_factory->create_ship({115, 25}, 45, 2);

    // По одному врагу каждого нового типа.
    ui_factory->create_enemy({48, 5}, 3, 2);
    ui_factory->create_jumping_enemy({90, 5}, 3, 2);
    ui_factory->create_flying_enemy({115, 12}, 3, 2);
}