#pragma once

namespace folin {
    struct MenuItem {
        const char *const title;
        
        const MenuItem *(*itemFunction)(const MenuItem *current);
        
        const MenuItem *parent;
        const MenuItem *const *children;

        const int children_count;
    };
}
