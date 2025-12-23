#include "elem_func.hpp"
#include "menu_elem.hpp"


namespace main_children {
    const folin::MenuItem *const children[] = {
        &folin::STUDY_PROG_LEVEL1
    };
}

namespace main_educ_children {
    const folin::MenuItem *const children[] = {
        &folin::LEARN_PROG_LANG_LEVEL2,
        &folin::ALGO_STRUCTURES_LEVEL2,
        &folin::OTHER_TECH_LEVEL2
    };
}

namespace other_tech_children {
    const folin::MenuItem *const children[] = {
        &folin::DATA_BASE_LEVEL3,
        &folin::MULTITREADED_PROG_LEVEL3,
        &folin::NET_TECH_LEVEL3
    };
}

const folin::MenuItem folin::MAIN_LEVEL0 {
    "Главное Меню",  MenuFunctions::show_elem_menu, nullptr, main_children::children, 1
};

const folin::MenuItem folin::STUDY_PROG_LEVEL1 {
    "Второй уровень меню",  MenuFunctions::show_elem_menu, &MAIN_LEVEL0, main_educ_children::children,   3    
};

const folin::MenuItem folin::LEARN_PROG_LANG_LEVEL2 {
    "Меню изучения языков программирования",  MenuFunctions::show_elem_menu, &STUDY_PROG_LEVEL1, other_tech_children::children, 0
};

const folin::MenuItem folin::ALGO_STRUCTURES_LEVEL2 {
    "Меню изучения структур и алгоритмов",  MenuFunctions::show_elem_menu, &STUDY_PROG_LEVEL1, other_tech_children::children, 0
};

const folin::MenuItem folin::OTHER_TECH_LEVEL2 {
    "Меню изучения других технологий",  MenuFunctions::show_elem_menu, &STUDY_PROG_LEVEL1, other_tech_children::children, 3
};

const folin::MenuItem folin::DATA_BASE_LEVEL3 {
    "Меню изучения баз данных",  MenuFunctions::show_elem_menu, &STUDY_PROG_LEVEL1, other_tech_children::children, 0

};

const folin::MenuItem folin::MULTITREADED_PROG_LEVEL3 {
    "Меню изучения многопоточного программирования",  MenuFunctions::show_elem_menu, &STUDY_PROG_LEVEL1, other_tech_children::children, 0
};

const folin::MenuItem folin::NET_TECH_LEVEL3 {
    "Меню изучения сетевых технологий", MenuFunctions::show_elem_menu, &STUDY_PROG_LEVEL1, other_tech_children::children, 0
};