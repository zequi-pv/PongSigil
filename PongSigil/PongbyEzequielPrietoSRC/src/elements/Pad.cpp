#include "Pad.h"
#include "Ball.h"

void initPad1(Pad& pad)
{
	pad.Position = { GetScreenWidth() / 10.0f, GetScreenHeight() / 3.0f };
	pad.Size = { GetScreenWidth() / 30.0f, GetScreenHeight() / 4.0f };
	pad.minPosition = 0;
	pad.maxPosition = GetScreenHeight() - pad.Size.y;
	Limit(pad);
}

void initPad2(Pad& pad)
{
	pad.Position = { GetScreenWidth() - 100.0f, GetScreenHeight() / 3.0f };
	pad.Size = { GetScreenWidth() / 30.0f, GetScreenHeight() / 4.0f };
	pad.minPosition = 0;
	pad.maxPosition = GetScreenHeight() - pad.Size.y;
	Limit(pad);
}

void Limit(Pad& rectangle)
{
	if (rectangle.Position.y <= 0)
	{
		rectangle.Position.y = rectangle.minPosition;
	}
	else if (rectangle.Position.y + rectangle.Size.y >= GetScreenHeight())
	{
		rectangle.Position.y = rectangle.maxPosition;
	}
}

bool isColliding(Pad rectangle, Ball ball)
{
	return rectangle.Position.x + rectangle.Size.x >= ball.Position.x &&
		rectangle.Position.x <= ball.Position.x + ball.Size.x &&
		rectangle.Position.y + rectangle.Size.y >= ball.Position.y &&
		rectangle.Position.y <= ball.Position.y + ball.Size.y;
}

