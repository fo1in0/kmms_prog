#pragma once


namespace folin {
    struct MenuItem {
        const char *const title;
        const char *const information_link;

        const MenuItem *(*itemfunction)(const MenuItem *current);

        const MenuItem *parent;
        const MenuItem *const *children; 

        const int children_count;
    };
}