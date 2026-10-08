#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <Windows.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
    float x,y;
    float width, height;
    float vertSpeed;
    BOOL IsFly;
    char cType;
    float horizSpeed;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;

TObject *brick = NULL;
int brickLenght;

TObject *moving = NULL;
int movingLength;

int level = 1;
int score;
int maxLvl;


void ClearMap()
{
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf( map[j], map[0]);
}

void ShowMap()
{
    for (int j = 0; j < mapHeight; j++)
        printf("%s\n", map[j]);   
}

void SetObjectPos(TObject *obj, float xPos, float yPos)
{
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void initObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) 
{
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth; 
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
    (*obj).horizSpeed = 0.2;
}

BOOL IsCollision(TObject o1, TObject o2);
void CreateLevel(int lvl);
TObject *GetNewMoving();


void PlayerDead()
{
    system("color 4F");
    Sleep(500);
    CreateLevel(level);
}

void VertMoveObject(TObject *obj)
{
    obj->IsFly = TRUE;
    obj->vertSpeed += 0.05;
    obj->y += obj->vertSpeed;

    for (int i = 0; i < brickLenght; i++)
    {
        if (IsCollision(*obj, brick[i]))
        {
            
            obj->y -= obj->vertSpeed;
            
          
            if (obj->vertSpeed > 0)
            {
                obj->IsFly = FALSE;
                obj->vertSpeed = 0;
            }
            
           
            if (obj->vertSpeed < 0 && obj == &mario)
            {
                obj->vertSpeed = 0;  
                
                if (brick[i].cType == '?')
                {
                    brick[i].cType = '-';
                    initObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
                    moving[movingLength - 1].vertSpeed = -0.7;
                }
            }
            
            
            if (brick[i].cType == '+' && obj == &mario)
            {
                level++;
                if (level > maxLvl) level = 1;

                system("color 2F");
                Sleep(500);
                CreateLevel(level);
            }
            
            break;  
        }
    }
}

void DeleteMoving(int i)
{
    movingLength--;
    moving[i] = moving[movingLength];
    moving = (TObject*)realloc(moving,sizeof(*moving)*movingLength);
}

void MarioCollision()
{
    for (int i = 0; i < movingLength;i++)
        if (IsCollision ( mario, moving[i]))
        {
            if (moving[i].cType == 'o')
            {
                if (    (mario.IsFly == TRUE)
                    &&  ( mario.vertSpeed > 0)
                    && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)
                )
                {
                    score += 50;
                    DeleteMoving(i);
                    i--;
                    continue;
                }
                else
                    PlayerDead();
            }

            if (moving[i].cType == '$')
            {
                score += 100;
                DeleteMoving(i);
                i--;
                continue;
            }
        }

}

void HorizonMoveObject(TObject *obj)
{
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < brickLenght; i++)
        if (IsCollision(obj[0], brick[i]))
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }
    if (obj[0].cType == 'o')
    {
        TObject tmp = *obj;
        VertMoveObject(&tmp);
        if (tmp.IsFly == TRUE)
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}

BOOL IsPosInMap( int x, int y)
{
    return ( ( x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight) );
}

void PutObjectOnMap(TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
            if (IsPosInMap(i,j))
                map[j][i] = obj.cType;
}

void setCur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizonMoveMap(float dx)
{
    mario.x -= dx;
    for (int i = 0; i < brickLenght; i++)
        if (IsCollision(mario, brick[i]))
        {
            mario.x += dx;
            return;
        }
    mario.x += dx;

    for (int i = 0; i < brickLenght; i++)
        brick[i].x += dx;
    for (int i = 0; i < movingLength; i++)
        moving[i].x += dx;
}

BOOL IsCollision(TObject o1, TObject o2)
{
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
            ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

TObject *GetNewBrick()
{
    brickLenght++;
    brick = (TObject*)realloc(brick,sizeof(*brick)*brickLenght);
    return brick + brickLenght - 1;
}

TObject *GetNewMoving()
{
    movingLength++;
    moving = (TObject*)realloc(moving,sizeof(*moving)*movingLength);
    return moving + movingLength - 1;
}

void PutScoreOnMap()
{
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
    {
        map[1][i+5] = c[i];
    }
}
void CreateLevel(int lvl)
{
    system("color 9F");

    brickLenght = 0;
    brick = (TObject*)realloc(brick,0);
    movingLength = 0;
    moving = (TObject*)realloc(moving,0);

    initObject(&mario, 39, 10, 3, 3, '@');
    score = 0;

    if (lvl == 1)
    {
        if (lvl == 1)
    {
        initObject(getNewBrick(),  0, 21, 207, 4, '#');

            initObject(getNewBrick(), 48, 13, 3, 2, '?');
            initObject(getNewBrick(), 60, 13, 3, 2, '#');
            initObject(getNewBrick(), 63, 13, 3, 2, '?');
            initObject(getNewBrick(), 66, 13, 3, 2, '#');
            initObject(getNewBrick(), 69, 13, 3, 2, '?');
            initObject(getNewBrick(), 72, 13, 3, 2, '#');
            initObject(getNewBrick(), 66, 5, 3, 2, '?');

        initObject(getNewBrick(), 84, 17, 6, 2, '#');
        initObject(getNewBrick(), 85, 19, 4, 2, '#');

        initObject(getNewBrick(), 114, 15, 6, 2, '#');
        initObject(getNewBrick(), 115, 17, 4, 4, '#');

        initObject(getNewBrick(), 138, 13, 6, 2, '#');
        initObject(getNewBrick(), 139, 15, 4, 6, '#');

        initObject(getNewBrick(), 171, 13, 6, 2, '#');
        initObject(getNewBrick(), 172, 15, 4, 6, '#');
        // --
        initObject(getNewBrick(),  213, 21, 45, 4, '#');
            initObject(getNewBrick(), 231, 13, 3, 2, '#');
            initObject(getNewBrick(), 234, 13, 3, 2, '?');
            initObject(getNewBrick(), 237, 13, 3, 2, '#');
                initObject(getNewBrick(), 240, 5, 24, 2, '#');
        // --
        initObject(getNewBrick(),  267, 21, 192, 4, '#');
                initObject(getNewBrick(), 273, 5, 9, 2, '#');
                initObject(getNewBrick(), 282, 5, 3, 2, '?');
            initObject(getNewBrick(), 282, 13, 3, 2, '?');
            initObject(getNewBrick(), 300, 13, 6, 2, '#');
            initObject(getNewBrick(), 318, 13, 3, 2, '?');
            initObject(getNewBrick(), 327, 13, 3, 2, '?');
                initObject(getNewBrick(), 327, 5, 3, 2, '?');
            initObject(getNewBrick(), 336, 13, 3, 2, '?');
            initObject(getNewBrick(), 354, 13, 3, 2, '#');
                initObject(getNewBrick(), 363, 5, 9, 2, '#');
                initObject(getNewBrick(), 384, 5, 3, 2, '#');
                initObject(getNewBrick(), 387, 5, 3, 2, '?');
                initObject(getNewBrick(), 390, 5, 3, 2, '?');
                initObject(getNewBrick(), 393, 5, 3, 2, '#');
            initObject(getNewBrick(), 387, 13, 6, 2, '#');
            //лестница
            initObject(getNewBrick(), 402, 19, 12, 2, '#');
            initObject(getNewBrick(), 405, 17, 9, 2, '#');
            initObject(getNewBrick(), 408, 15, 6, 2, '#');
            initObject(getNewBrick(), 411, 13, 3, 2, '#');

            initObject(getNewBrick(), 420, 13, 3, 2, '#');
            initObject(getNewBrick(), 420, 15, 6, 2, '#');
            initObject(getNewBrick(), 420, 17, 9, 2, '#');
            initObject(getNewBrick(), 420, 19, 12, 2, '#');

            initObject(getNewBrick(), 444, 19, 15, 2, '#');
            initObject(getNewBrick(), 447, 17, 12, 2, '#');
            initObject(getNewBrick(), 450, 15, 9, 2, '#');
            initObject(getNewBrick(), 453, 13, 6, 2, '#');
        // --
        initObject(getNewBrick(), 465, 21, 165, 4, '#');
            initObject(getNewBrick(), 465, 13, 3, 2, '#');
            initObject(getNewBrick(), 465, 15, 6, 2, '#');
            initObject(getNewBrick(), 465, 17, 9, 2, '#');
            initObject(getNewBrick(), 465, 19, 12, 2, '#');

            initObject(getNewBrick(), 489, 17, 6, 2, '#');
            initObject(getNewBrick(), 490, 19, 4, 2, '#');

            initObject(getNewBrick(), 504, 13, 6, 2, '#');
            initObject(getNewBrick(), 510, 13, 3, 2, '?');
            initObject(getNewBrick(), 513, 13, 3, 2, '#');

            initObject(getNewBrick(), 537, 17, 6, 2, '#');
            initObject(getNewBrick(), 538, 19, 4, 2, '#');
            // лестница большая
            initObject(getNewBrick(), 543, 19, 27, 2, '#');
            initObject(getNewBrick(), 546, 17, 24, 2, '#');
            initObject(getNewBrick(), 549, 15, 21, 2, '#');
            initObject(getNewBrick(), 552, 13, 18, 2, '#');
            initObject(getNewBrick(), 555, 11, 15, 2, '#');
            initObject(getNewBrick(), 558,  9, 12, 2, '#');
            initObject

    maxLvl = 3;
}


int main() 
{
    CreateLevel(level);

    do 
    {
        ClearMap();

        if((mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0 ) ) mario.vertSpeed = -1.2;
        if (GetKeyState('A') < 0 ) HorizonMoveMap(1);
        if (GetKeyState('D') < 0 ) HorizonMoveMap(-1);

        if (mario.y > mapHeight) PlayerDead();
        
        VertMoveObject(&mario);
        MarioCollision();

        for (int i = 0; i < brickLenght; i++){       
            PutObjectOnMap(brick[i]);
        }
        for (int i = 0; i < movingLength; i++)
        {       
            VertMoveObject(moving + i);
            HorizonMoveObject(moving + i);
            if (moving[i].y > mapHeight)
            {
                DeleteMoving(i);
                i--;
                continue;
            }
            PutObjectOnMap(moving[i]);
        }
        PutObjectOnMap(mario);
        PutScoreOnMap();

        setCur(0,0);
        ShowMap();

        Sleep(16);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
} 
