#include "Game.hpp"
#include <stdio.h>
#include <Windows.h>
#include <string.h>

Game::Game() : bricks(nullptr), brickLength(0), level(1), score(0), maxLevel(3) {
    CreateLevel(level);
}

Game::~Game() {
    for (int i = 0; i < brickLength; i++)
        delete bricks[i];
    delete[] bricks;
}

Brick* Game::GetNewBrick() {
    Brick** newBricks = new Brick*[brickLength + 1];
    for (int i = 0; i < brickLength; i++)
        newBricks[i] = bricks[i];
    
    delete[] bricks;
    bricks = newBricks;
    bricks[brickLength] = new Brick();
    return bricks[brickLength++];
}

void Game::CreateBrick(float x, float y, float w, float h, char type) {
    Brick* b = GetNewBrick();
    *b = Brick(x, y, w, h, type);
}

void Game::CreateLevel(int lvl) {
    system("color 9F");
    
    for (int i = 0; i < brickLength; i++)
        delete bricks[i];
    delete[] bricks;
    bricks = nullptr;
    brickLength = 0;
    movingManager.Clear();
    
    mario.Reset();
    score = 0;
    
    if (lvl == 1) {
        CreateBrick(20, 20, 40, 5, '#');
        CreateBrick(30, 10, 5, 3, '?');
        CreateBrick(50, 10, 3, 3, '?');
        CreateBrick(60, 18, 40, 10, '#');
        CreateBrick(100, 22, 20, 5, '#');
        CreateBrick(60, 5, 10, 3, '-');
        CreateBrick(70, 5, 5, 3, '?');
        CreateBrick(75, 5, 5, 3, '-');
        CreateBrick(80, 5, 5, 3, '?');
        CreateBrick(85, 5, 10, 3, '-');
        CreateBrick(120, 15, 10, 10, '#');
        CreateBrick(150, 20, 40, 5, '#');
        CreateBrick(210, 15, 10, 10, '+');
        
        movingManager.AddMovingObject(25, 10, 3, 2, 'o');
        movingManager.AddMovingObject(80, 10, 3, 2, 'o');
    }
    else if (lvl == 2) {
        CreateBrick(20, 20, 40, 5, '#');
        CreateBrick(60, 15, 10, 10, '#');
        CreateBrick(80, 20, 20, 5, '#');
        CreateBrick(120, 15, 10, 10, '#');
        CreateBrick(150, 20, 40, 5, '#');
        CreateBrick(210, 15, 10, 10, '+');
        
        movingManager.AddMovingObject(25, 10, 3, 2, 'o');
        movingManager.AddMovingObject(80, 10, 3, 2, 'o');
        movingManager.AddMovingObject(65, 10, 3, 2, 'o');
        movingManager.AddMovingObject(120, 10, 3, 2, 'o');
        movingManager.AddMovingObject(160, 10, 3, 2, 'o');
        movingManager.AddMovingObject(175, 10, 3, 2, 'o');
    }
    else if (lvl == 3) {
        CreateBrick(20, 20, 40, 5, '#');
        CreateBrick(80, 15, 15, 10, '#');
        CreateBrick(120, 20, 20, 10, '#');
        CreateBrick(160, 15, 10, 10, '+');
        
        movingManager.AddMovingObject(25, 10, 3, 2, 'o');
        movingManager.AddMovingObject(50, 10, 3, 2, 'o');
        movingManager.AddMovingObject(80, 10, 3, 2, 'o');
        movingManager.AddMovingObject(90, 10, 3, 2, 'o');
        movingManager.AddMovingObject(120, 10, 3, 2, 'o');
        movingManager.AddMovingObject(135, 10, 3, 2, 'o');
    }
}

void Game::PlayerDead() {
    system("color 4F");
    Sleep(500);
    CreateLevel(level);
}

// ИСПРАВЛЕННЫЙ HorizonMoveMap
void Game::HorizonMoveMap(float dx) {
    float oldX = mario.GetX();
    mario.SetPosition(mario.GetX() - dx, mario.GetY());
    
    for (int i = 0; i < brickLength; i++) {
        if (bricks[i] && Object::IsCollision(mario, *bricks[i])) {
            mario.SetPosition(oldX, mario.GetY());
            return;
        }
    }
    
    mario.SetPosition(oldX, mario.GetY());
    
    for (int i = 0; i < brickLength; i++)
        bricks[i]->SetPosition(bricks[i]->GetX() + dx, bricks[i]->GetY());
    
    for (int i = 0; i < movingManager.GetLength(); i++) {
        MovingObject* obj = movingManager.Get(i);
        if (obj)
            obj->SetPosition(obj->GetX() + dx, obj->GetY());
    }
}

void Game::MarioCollision() {
    for (int i = 0; i < movingManager.GetLength(); i++) {
        MovingObject* movingObj = movingManager.Get(i);
        if (movingObj && Object::IsCollision(mario, *movingObj)) {
            if (movingObj->GetType() == 'o') {
                if (mario.IsFly() && mario.GetVertSpeed() > 0 &&
                    mario.GetY() + mario.GetHeight() < movingObj->GetY() + movingObj->GetHeight() * 0.5) {
                    score += 50;
                    movingManager.DeleteMoving(i);
                    i--;
                    continue;
                } else {
                    PlayerDead();
                }
            }
            else if (movingObj->GetType() == '$') {
                score += 100;
                movingManager.DeleteMoving(i);
                i--;
                continue;
            }
        }
    }
}

void Game::ProcessInput() {
    if ((mario.IsFly() == FALSE) && (GetKeyState(VK_SPACE) < 0))
        mario.SetVertSpeed(-3.0f);
    if (GetKeyState('A') < 0)
        HorizonMoveMap(1);
    if (GetKeyState('D') < 0)
        HorizonMoveMap(-1);
}

void Game::Update() {
    if (mario.GetY() > MAP_HEIGHT)
        PlayerDead();
    
    mario.SetIsFly(TRUE);
    mario.SetVertSpeed(mario.GetVertSpeed() + 0.05f);
    float newY = mario.GetY() + mario.GetVertSpeed();
    mario.SetPosition(mario.GetX(), newY);
    
    for (int i = 0; i < brickLength; i++) {
        if (bricks[i] && Object::IsCollision(mario, *bricks[i])) {
            mario.SetPosition(mario.GetX(), newY - mario.GetVertSpeed());
            
            if (mario.GetVertSpeed() > 0) {
                mario.SetIsFly(FALSE);
                mario.SetVertSpeed(0);
            }
            
            if (mario.GetVertSpeed() < 0 && bricks[i]->GetType() == '?') {
                bricks[i]->SetType('-');
                movingManager.AddMovingObject(bricks[i]->GetX(), bricks[i]->GetY() - 3, 3, 2, '$');
                if (movingManager.GetLength() > 0) {
                    movingManager.Get(movingManager.GetLength() - 1)->SetVertSpeed(-0.7f);
                }
            }
            
            if (bricks[i]->GetType() == '+') {
                level++;
                if (level > maxLevel) level = 1;
                system("color 2F");
                Sleep(500);
                CreateLevel(level);
            }
            break;
        }
    }
    
    movingManager.UpdateAll((Object**)bricks, brickLength, MAP_HEIGHT);
    MarioCollision();
}

void Game::Render() {
    map.Clear();
    
    for (int i = 0; i < brickLength; i++)
        if (bricks[i])
            map.PutObject(*bricks[i]);
    
    movingManager.DrawAll(map);
    map.PutObject(mario);
    map.PutScore(score);
    
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    map.Show();
}

void Game::Run() {
    do {
        ProcessInput();
        Update();
        Render();
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
}