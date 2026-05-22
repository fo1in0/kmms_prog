#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    BOOL IsFly;
    char cType;
    float horizSpeed;
} TObject;

void ClearMap(char map[mapHeight][mapWidth + 1]);
void CreateLevel(int lvl, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score);
void DeleteMoving(TObject** moving, int* movingLength, int i);
TObject *GetNewBrick(TObject** brick, int* brickLenght);
TObject *GetNewMoving(TObject** moving, int* movingLength);
void HorizonMoveMap(float dx, TObject* mario, TObject* brick, int brickLenght, TObject* moving, int movingLength);
void HorizonMoveObject(TObject* obj, TObject* brick, int brickLenght);
void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType);
BOOL IsCollision(TObject o1, TObject o2);
BOOL IsPosInMap(int x, int y);
void MarioCollision(TObject* mario, TObject** moving, int* movingLength, int* score, int* level, TObject** brick, int* brickLenght);
void PlayerDead(int* level, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score);
void PutObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj);
void PutScoreOnMap(char map[mapHeight][mapWidth + 1], int score);
void setCur(int x, int y);
void SetObjectPos(TObject *obj, float xPos, float yPos);
void ShowMap(char map[mapHeight][mapWidth + 1]);
void VertMoveObject(TObject* obj, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* level, BOOL isMario, int* score);

void ClearMap(char map[mapHeight][mapWidth + 1])
{
    for (int i = 0; i < mapWidth; i++)
    {
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';

    for (int j = 1; j < mapHeight; j++)
    {
        sprintf(map[j], map[0]);
    }
}

void CreateLevel(int lvl, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score)
{
    system("color 9F");

    *brickLenght = 0;
    *brick = (TObject*)realloc(*brick, 0);
    *movingLength = 0;
    *moving = (TObject*)realloc(*moving, 0);

    InitObject(mario, 39, 10, 3, 3, '@');
    *score = 0;

    if (lvl == 1)
    {
        InitObject(GetNewBrick(brick, brickLenght), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 30, 10, 5, 3, '?');
        InitObject(GetNewBrick(brick, brickLenght), 50, 10, 3, 3, '?');
        InitObject(GetNewBrick(brick, brickLenght), 60, 18, 40, 10, '#');
        InitObject(GetNewBrick(brick, brickLenght), 100, 22, 20, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 60, 5, 10, 3, '-');
        InitObject(GetNewBrick(brick, brickLenght), 70, 5, 5, 3, '?');
        InitObject(GetNewBrick(brick, brickLenght), 75, 5, 5, 3, '-');
        InitObject(GetNewBrick(brick, brickLenght), 80, 5, 5, 3, '?');
        InitObject(GetNewBrick(brick, brickLenght), 85, 5, 10, 3, '-');
        InitObject(GetNewBrick(brick, brickLenght), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(brick, brickLenght), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 210, 15, 10, 10, '+');

        InitObject(GetNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
    }

    if (lvl == 2)
    {
        InitObject(GetNewBrick(brick, brickLenght), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(brick, brickLenght), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(brick, brickLenght), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 210, 15, 10, 10, '+');

        InitObject(GetNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 65, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 160, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 175, 10, 3, 2, 'o');
    }

    if (lvl == 3)
    {
        InitObject(GetNewBrick(brick, brickLenght), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(brick, brickLenght), 80, 15, 15, 10, '#');
        InitObject(GetNewBrick(brick, brickLenght), 120, 20, 20, 10, '#');
        InitObject(GetNewBrick(brick, brickLenght), 160, 15, 10, 10, '+');

        InitObject(GetNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 50, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 90, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(moving, movingLength), 135, 10, 3, 2, 'o');
    }
}

void DeleteMoving(TObject** moving, int* movingLength, int i)
{
    (*movingLength)--;
    (*moving)[i] = (*moving)[*movingLength];
    *moving = (TObject*)realloc(*moving, sizeof(**moving) * (*movingLength));
}

TObject *GetNewBrick(TObject** brick, int* brickLenght)
{
    (*brickLenght)++;
    *brick = (TObject*)realloc(*brick, sizeof(**brick) * (*brickLenght));
    return *brick + (*brickLenght) - 1;
}

TObject *GetNewMoving(TObject** moving, int* movingLength)
{
    (*movingLength)++;
    *moving = (TObject*)realloc(*moving, sizeof(**moving) * (*movingLength));
    return *moving + (*movingLength) - 1;
}

void HorizonMoveMap(float dx, TObject* mario, TObject* brick, int brickLenght, TObject* moving, int movingLength)
{
    mario->x -= dx;

    for (int i = 0; i < brickLenght; i++)
    {
        if (IsCollision(*mario, brick[i]))
        {
            mario->x += dx;
            return;
        }
    }

    mario->x += dx;

    for (int i = 0; i < brickLenght; i++)
    {
        brick[i].x += dx;
    }

    for (int i = 0; i < movingLength; i++)
    {
        moving[i].x += dx;
    }
}

void HorizonMoveObject(TObject* obj, TObject* brick, int brickLenght)
{
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < brickLenght; i++)
    {
        if (IsCollision(obj[0], brick[i]))
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }
    }

    if (obj[0].cType == 'o')
    {
        TObject tmp = *obj;
        TObject* tmpBrick = brick;
        int tmpBrickLenght = brickLenght;
        VertMoveObject(&tmp, &tmpBrick, &tmpBrickLenght, NULL, NULL, NULL, FALSE, NULL);

        if (tmp.IsFly == TRUE)
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType)
{
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
    (*obj).horizSpeed = 0.2;
}

BOOL IsCollision(TObject o1, TObject o2)
{
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
            ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

BOOL IsPosInMap(int x, int y)
{
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void MarioCollision(TObject* mario, TObject** moving, int* movingLength, int* score, int* level, TObject** brick, int* brickLenght)
{
    for (int i = 0; i < *movingLength; i++)
    {
        if (IsCollision(*mario, (*moving)[i]))
        {
            if ((*moving)[i].cType == 'o')
            {
                if ((mario->IsFly == TRUE) && (mario->vertSpeed > 0) && (mario->y + mario->height < (*moving)[i].y + (*moving)[i].height * 0.5))
                {
                    *score += 50;
                    DeleteMoving(moving, movingLength, i);
                    i--;
                    continue;
                }
                else
                {
                    PlayerDead(level, mario, brick, brickLenght, moving, movingLength, score);
                }
            }

            if ((*moving)[i].cType == '$')
            {
                *score += 100;
                DeleteMoving(moving, movingLength, i);
                i--;
                continue;
            }
        }
    }
}

void PlayerDead(int* level, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score)
{
    system("color 4F");
    Sleep(500);
    CreateLevel(*level, mario, brick, brickLenght, moving, movingLength, score);
}

void PutObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++)
    {
        for (int j = iy; j < (iy + iHeight); j++)
        {
            if (IsPosInMap(i, j))
            {
                map[j][i] = obj.cType;
            }
        }
    }
}

void PutScoreOnMap(char map[mapHeight][mapWidth + 1], int score)
{
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);

    for (int i = 0; i < len; i++)
    {
        map[1][i + 5] = c[i];
    }
}

void setCur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetObjectPos(TObject *obj, float xPos, float yPos)
{
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void ShowMap(char map[mapHeight][mapWidth + 1])
{
    for (int j = 0; j < mapHeight; j++)
    {
        printf("%s\n", map[j]);
    }
}

void VertMoveObject(TObject* obj, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* level, BOOL isMario, int* score)
{
    obj->IsFly = TRUE;
    obj->vertSpeed += 0.05;
    obj->y += obj->vertSpeed;

    for (int i = 0; i < *brickLenght; i++)
    {
        if (IsCollision(*obj, (*brick)[i]))
        {
            obj->y -= obj->vertSpeed;

            if (obj->vertSpeed > 0)
            {
                obj->IsFly = FALSE;
                obj->vertSpeed = 0;
            }

            if (obj->vertSpeed < 0 && isMario)
            {
                obj->vertSpeed = 0;

                if ((*brick)[i].cType == '?')
                {
                    (*brick)[i].cType = '-';
                    InitObject(GetNewMoving(moving, movingLength), (*brick)[i].x, (*brick)[i].y - 3, 3, 2, '$');
                    (*moving)[*movingLength - 1].vertSpeed = -0.7;
                }
            }

            if ((*brick)[i].cType == '+' && isMario)
            {
                (*level)++;
                if (*level > 3) *level = 1;

                system("color 2F");
                Sleep(500);
                CreateLevel(*level, obj, brick, brickLenght, moving, movingLength, score);
            }

            break;
        }
    }
}

int main()
{
    char map[mapHeight][mapWidth + 1];
    TObject mario;
    TObject* brick = NULL;
    int brickLenght = 0;
    TObject* moving = NULL;
    int movingLength = 0;
    int level = 1;
    int score = 0;

    CreateLevel(level, &mario, &brick, &brickLenght, &moving, &movingLength, &score);

    do
    {
        ClearMap(map);

        if ((mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0))
        {
            mario.vertSpeed = -1.2;
        }

        if (GetKeyState('A') < 0)
        {
            HorizonMoveMap(1, &mario, brick, brickLenght, moving, movingLength);
        }

        if (GetKeyState('D') < 0)
        {
            HorizonMoveMap(-1, &mario, brick, brickLenght, moving, movingLength);
        }

        if (mario.y > mapHeight)
        {
            PlayerDead(&level, &mario, &brick, &brickLenght, &moving, &movingLength, &score);
        }

        VertMoveObject(&mario, &brick, &brickLenght, &moving, &movingLength, &level, TRUE, &score);
        MarioCollision(&mario, &moving, &movingLength, &score, &level, &brick, &brickLenght);

        for (int i = 0; i < brickLenght; i++)
        {
            PutObjectOnMap(map, brick[i]);
        }

        for (int i = 0; i < movingLength; i++)
        {
            VertMoveObject(&moving[i], &brick, &brickLenght, &moving, &movingLength, &level, FALSE, &score);
            HorizonMoveObject(&moving[i], brick, brickLenght);

            if (moving[i].y > mapHeight)
            {
                DeleteMoving(&moving, &movingLength, i);
                i--;
                continue;
            }

            PutObjectOnMap(map, moving[i]);
        }

        PutObjectOnMap(map, mario);
        PutScoreOnMap(map, score);

        setCur(0, 0);
        ShowMap(map);

        Sleep(16);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}