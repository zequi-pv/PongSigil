#pragma once
#include "raylib.h"

struct Ball
{
    Vector2 Position;
    Vector2 Speed;
    Vector2 Size;
};

void initBall(Ball& ball);