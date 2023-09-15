#include "Pad.h"
#include "Ball.h"
#include "gameData/Game.h"

void initPad1(Pad& pad)
{
	pad.x = GetScreenWidth() / 10.0f;
	pad.y = GetScreenHeight() / 3.0f;
	pad.width = GetScreenWidth() / 30.0f;
	pad.height = GetScreenHeight() / 4.0f;
	pad.minPosition = 0;
	pad.maxPosition = GetScreenHeight() - pad.height;
	Limit(pad);
}

void initPad2(Pad& pad)
{
	pad.x = GetScreenWidth() - 100.0f;
	pad.y = GetScreenHeight() / 3.0f;
	pad.width = GetScreenWidth() / 30.0f;
	pad.height = GetScreenHeight() / 4.0f;
	pad.minPosition = 0;
	pad.maxPosition = GetScreenHeight() - pad.height;
	Limit(pad);
}

void Limit(Pad& rectangle)
{
	if (rectangle.y <= 0)
	{
		rectangle.y = rectangle.minPosition;
	}
	else if (rectangle.y + rectangle.height >= GetScreenHeight())
	{
		rectangle.y = rectangle.maxPosition;
	}
}

bool isColliding(Pad rectangle, Ball ball)
{
	return rectangle.x + rectangle.width >= ball.x &&
		rectangle.x <= ball.x + ball.width &&
		rectangle.y + rectangle.height >= ball.y &&
		rectangle.y <= ball.y + ball.height;
}

