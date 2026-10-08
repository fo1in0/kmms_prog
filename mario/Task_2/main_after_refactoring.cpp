#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25

const char EMPTY_SYMBOL = ' ';
const char MARIO_SYMBOL = '@';
const char BRICK_SYMBOL = '#';
const char QUESTION_BRICK_SYMBOL = '?';
const char EMPTY_BRICK_SYMBOL = '-';
const char EXIT_SYMBOL = '+';
const char ENEMY_SYMBOL = 'o';
const char COIN_SYMBOL = '$';

typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    BOOL IsFly;
    char cType;
    float horizSpeed;
} TObject;

void clearMap(char map[mapHeight][mapWidth + 1]);
void createLevel(int lvl, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score);
void deleteMoving(TObject** moving, int* movingLength, int i);
TObject *getNewBrick(TObject** brick, int* brickLenght);
TObject *getNewMoving(TObject** moving, int* movingLength);
void horizonMoveMap(float dx, TObject* mario, TObject* brick, int brickLenght, TObject* moving, int movingLength);
void horizonMoveObject(TObject* obj, TObject* brick, int brickLenght);
void initObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType);
BOOL isCollision(TObject o1, TObject o2);
BOOL isPosInMap(int x, int y);
void marioCollision(TObject* mario, TObject** moving, int* movingLength, int* score, int* level, TObject** brick, int* brickLenght);
void playerDead(int* level, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score);
void putObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj);
void putScoreOnMap(char map[mapHeight][mapWidth + 1], int score);
void setCur(int x, int y);
void setObjectPos(TObject *obj, float xPos, float yPos);
void showMap(char map[mapHeight][mapWidth + 1]);
void vertMoveObject(TObject* obj, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* level, BOOL isMario, int* score);

void clearMap(char map[mapHeight][mapWidth + 1])
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

void createLevel(int lvl, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score)
{
    system("color 9F");

    *brickLenght = 0;
    *brick = (TObject*)realloc(*brick, 0);
    *movingLength = 0;
    *moving = (TObject*)realloc(*moving, 0);

    initObject(mario, 39, 10, 3, 3, MARIO_SYMBOL);
    *score = 0;


    switch (lvl) {
        case 1:
            initObject(getNewBrick(brick, brickLenght), 20, 20, 40, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 50, 10, 5, 3, QUESTION_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 60, 15, 40, 10, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 60, 5, 10, 3, EMPTY_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 70, 5, 5, 3, QUESTION_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 30, 10, 5, 3, QUESTION_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 75, 5, 5, 3, EMPTY_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 80, 5, 5, 3, QUESTION_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 85, 5, 10, 3, QUESTION_BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 100, 20, 20, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 120, 15, 10, 10, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 150, 20, 40, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 210, 15, 10, 10, EXIT_SYMBOL);

			initObject(getNewMoving(moving, movingLength), 25, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 80, 10, 3, 2, ENEMY_SYMBOL);
			break;

			
			initObject(getNewBrick(brick, brickLenght), 20, 20, 40, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 60, 15, 10, 10, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 80, 20, 20, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 120, 15, 10, 10, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 150, 20, 40, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 210, 15, 10, 10, EXIT_SYMBOL);

			initObject(getNewMoving(moving, movingLength), 25, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 80, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 65, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 120, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 160, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 175, 10, 3, 2, ENEMY_SYMBOL);
			break;

		case 3:
			initObject(getNewBrick(brick, brickLenght), 20, 20, 40, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 80, 20, 15, 5, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 120, 15, 15, 10, BRICK_SYMBOL);
			initObject(getNewBrick(brick, brickLenght), 160, 10, 15, 15, EXIT_SYMBOL);

			initObject(getNewMoving(moving, movingLength), 25, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 50, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 80, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 90, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 120, 10, 3, 2, ENEMY_SYMBOL);
			initObject(getNewMoving(moving, movingLength), 130, 10, 3, 2, ENEMY_SYMBOL);
			break;

        default:
            break;
        }
}

void deleteMoving(TObject** moving, int* movingLength, int i)
{
    (*movingLength)--;
    (*moving)[i] = (*moving)[*movingLength];
    *moving = (TObject*)realloc(*moving, sizeof(**moving) * (*movingLength));
}

TObject *getNewBrick(TObject** brick, int* brickLenght)
{
    (*brickLenght)++;
    *brick = (TObject*)realloc(*brick, sizeof(**brick) * (*brickLenght));
    return *brick + (*brickLenght) - 1;
}

TObject *getNewMoving(TObject** moving, int* movingLength)
{
    (*movingLength)++;
    *moving = (TObject*)realloc(*moving, sizeof(**moving) * (*movingLength));
    return *moving + (*movingLength) - 1;
}

void horizonMoveMap(float dx, TObject* mario, TObject* brick, int brickLenght, TObject* moving, int movingLength)
{
    mario->x -= dx;

    for (int i = 0; i < brickLenght; i++)
    {
        if (isCollision(*mario, brick[i]))
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

void horizonMoveObject(TObject* obj, TObject* brick, int brickLenght)
{
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < brickLenght; i++)
    {
        if (isCollision(obj[0], brick[i]))
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
        vertMoveObject(&tmp, &tmpBrick, &tmpBrickLenght, NULL, NULL, NULL, FALSE, NULL);

        if (tmp.IsFly == TRUE)
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}

void initObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType)
{
    setObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
    (*obj).horizSpeed = 0.2;
}

BOOL isCollision(TObject o1, TObject o2)
{
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
            ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

BOOL isPosInMap(int x, int y)
{
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void marioCollision(TObject* mario, TObject** moving, int* movingLength, int* score, int* level, TObject** brick, int* brickLenght)
{
    for (int i = 0; i < *movingLength; i++)
    {
        if (isCollision(*mario, (*moving)[i]))
        {
            if ((*moving)[i].cType == 'o')
            {
                if ((mario->IsFly == TRUE) && (mario->vertSpeed > 0) && (mario->y + mario->height < (*moving)[i].y + (*moving)[i].height * 0.5))
                {
                    *score += 50;
                    deleteMoving(moving, movingLength, i);
                    i--;
                    continue;
                }
                else
                {
                    playerDead(level, mario, brick, brickLenght, moving, movingLength, score);
                }
            }

            if ((*moving)[i].cType == '$')
            {
                *score += 100;
                deleteMoving(moving, movingLength, i);
                i--;
                continue;
            }
        }
    }
}

void playerDead(int* level, TObject* mario, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* score)
{
    system("color 4F");
    Sleep(500);
    createLevel(*level, mario, brick, brickLenght, moving, movingLength, score);
}

void putObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++)
    {
        for (int j = iy; j < (iy + iHeight); j++)
        {
            if (isPosInMap(i, j))
            {
                map[j][i] = obj.cType;
            }
        }
    }
}

void putScoreOnMap(char map[mapHeight][mapWidth + 1], int score)
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

void setObjectPos(TObject *obj, float xPos, float yPos)
{
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void showMap(char map[mapHeight][mapWidth + 1])
{
    for (int j = 0; j < mapHeight; j++)
    {
        printf("%s\n", map[j]);
    }
}

void vertMoveObject(TObject* obj, TObject** brick, int* brickLenght, TObject** moving, int* movingLength, int* level, BOOL isMario, int* score)
{
    obj->IsFly = TRUE;
    obj->vertSpeed += 0.05;
    obj->y += obj->vertSpeed;

    for (int i = 0; i < *brickLenght; i++)
    {
        if (isCollision(*obj, (*brick)[i]))
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
                    initObject(getNewMoving(moving, movingLength), (*brick)[i].x, (*brick)[i].y - 3, 3, 2, '$');
                    (*moving)[*movingLength - 1].vertSpeed = -0.7;
                }
            }

            if ((*brick)[i].cType == '+' && isMario)
            {
                (*level)++;
                if (*level > 3) *level = 1;

                system("color 2F");
                Sleep(500);
                createLevel(*level, obj, brick, brickLenght, moving, movingLength, score);
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

    createLevel(level, &mario, &brick, &brickLenght, &moving, &movingLength, &score);

    do
    {
        clearMap(map);

        if ((mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0))
        {
            mario.vertSpeed = -1.2;
        }

        if (GetKeyState('A') < 0)
        {
            horizonMoveMap(1, &mario, brick, brickLenght, moving, movingLength);
        }

        if (GetKeyState('D') < 0)
        {
            horizonMoveMap(-1, &mario, brick, brickLenght, moving, movingLength);
        }

        if (mario.y > mapHeight)
        {
            playerDead(&level, &mario, &brick, &brickLenght, &moving, &movingLength, &score);
        }

        vertMoveObject(&mario, &brick, &brickLenght, &moving, &movingLength, &level, TRUE, &score);
        marioCollision(&mario, &moving, &movingLength, &score, &level, &brick, &brickLenght);

        for (int i = 0; i < brickLenght; i++)
        {
            putObjectOnMap(map, brick[i]);
        }

        for (int i = 0; i < movingLength; i++)
        {
            vertMoveObject(&moving[i], &brick, &brickLenght, &moving, &movingLength, &level, FALSE, &score);
            horizonMoveObject(&moving[i], brick, brickLenght);

            if (moving[i].y > mapHeight)
            {
                deleteMoving(&moving, &movingLength, i);
                i--;
                continue;
            }

            putObjectOnMap(map, moving[i]);
        }

        putObjectOnMap(map, mario);
        putScoreOnMap(map, score);

        setCur(0, 0);
        showMap(map);

        Sleep(16);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}