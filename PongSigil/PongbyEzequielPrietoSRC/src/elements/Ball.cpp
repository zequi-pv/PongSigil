#include "Ball.h"
#include "gameData/Game.h"
#include "sl.h"

void initBall(Ball& ball)
{
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.speedX = 250.0f;
    ball.speedY = 250.0f;
    ball.width = 30.0f;
    ball.height = 30.0f;
}