#pragma once
#include "raylib.h"
#include "Ball.h"

struct Pad
{
    Vector2 Position;
    Vector2 Size;
    int score = 0;
    int minPosition;
    int maxPosition;
};

void initPad1(Pad& pad);
void initPad2(Pad& pad);
void Limit(Pad& rectangle);
bool isColliding(Pad rectangle, Ball ball);