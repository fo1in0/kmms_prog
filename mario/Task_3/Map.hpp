#ifndef MAP_HPP
#define MAP_HPP

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

class Object;

class Map {
private:
    char map[MAP_HEIGHT][MAP_WIDTH + 1];

public:
    Map();
    ~Map();
    
    void Clear();
    void Show() const;
    void PutObject(const Object& obj);
    bool IsPosInMap(int x, int y) const;
    void PutScore(int score);
};

#endif