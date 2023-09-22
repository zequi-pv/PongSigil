#include "Pad.h"
#include "Ball.h"
#include "gameData/Game.h"

void initPad1(Pad& pad)
{
	pad.x = GetScreenWidth() / 10.0f;
	pad.y = GetScreenHeight() / 3.0f;
	pad.width = GetScreenWidth() / 30.0f;
	pad.height = GetScreenHeight() / 4.0f;
	pad.minPosition = pad.height / 2;
	pad.maxPosition = GetScreenHeight() - pad.height / 2;
	Limit(pad);
}

void initPad2(Pad& pad)
{
	pad.x = GetScreenWidth() - 100.0f;
	pad.y = GetScreenHeight() / 3.0f;
	pad.width = GetScreenWidth() / 30.0f;
	pad.height = GetScreenHeight() / 4.0f;
	pad.minPosition = pad.height / 2;
	pad.maxPosition = GetScreenHeight() - pad.height / 2;
	Limit(pad);
}

void Limit(Pad& rectangle)
{
	if (rectangle.y - rectangle.height / 2 <= 0)
	{
		rectangle.y = rectangle.minPosition;
	}
	else if (rectangle.y + rectangle.height / 2 >= GetScreenHeight())
	{
		rectangle.y = rectangle.maxPosition;
	}
}

bool isColliding(Pad rectangle, Ball ball)
{
	return rectangle.x + rectangle.width / 2 >= ball.x - ball.width / 2 &&
		   rectangle.x - rectangle.width / 2 <= ball.x + ball.width / 2 &&
		   rectangle.y + rectangle.height / 2 >= ball.y - ball.height / 2 &&
		   rectangle.y - rectangle.height / 2 <= ball.y + ball.height / 2;
}

