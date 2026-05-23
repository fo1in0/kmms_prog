#include "Map.hpp"
#include "Object.hpp"
#include <stdio.h>
#include <cmath>
#include <string.h>

Map::Map() {
    Clear();
}

Map::~Map() {}

void Map::Clear() {
    for (int i = 0; i < MAP_WIDTH; i++)
        map[0][i] = ' ';
    map[0][MAP_WIDTH] = '\0';
    for (int j = 1; j < MAP_HEIGHT; j++) {
        for (int i = 0; i <= MAP_WIDTH; i++)
            map[j][i] = map[0][i];
    }
}

void Map::Show() const {
    for (int j = 0; j < MAP_HEIGHT; j++)
        printf("%s\n", map[j]);
}

void Map::PutObject(const Object& obj) {
    int ix = (int)round(obj.GetX());
    int iy = (int)round(obj.GetY());
    int iWidth = (int)round(obj.GetWidth());
    int iHeight = (int)round(obj.GetHeight());

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.GetType();
}

bool Map::IsPosInMap(int x, int y) const {
    return (x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT);
}

void Map::PutScore(int score) {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        if (i + 5 < MAP_WIDTH)
            map[1][i + 5] = c[i];
    }
}