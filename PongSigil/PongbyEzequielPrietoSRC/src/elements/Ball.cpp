#include "Ball.h"

void initBall(Ball& ball)
{
    ball.Position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    ball.Speed = { 250.0f, 250.0f };
    ball.Size = {30.0f, 30.0f};
}