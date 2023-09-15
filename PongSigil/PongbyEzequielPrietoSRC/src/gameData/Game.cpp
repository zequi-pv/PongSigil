#include "Game.h"
//#include "raylib.h"
#include "sl.h"
#include <time.h>
#include <iostream>
#include "elements/Ball.h"
#include "elements/Pad.h"

enum GameScreen
{
    MENU,
    SINGLEPLAYER,
    MULTIPLAYER,
    RULES,
    EXIT
};

static void init(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle);
static void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle);
static void returnToMenu(GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball);
static void inputsSingle(Pad& rectangle1);
static void updateSingleplayer(Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints);
static void inputsMulti(Pad& rectangle1, Pad& rectangle2);
static void updateMultiplayer(Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints);
static void close();

void runGame()
{
    Ball ball;
    Pad rectangle1;
    Pad rectangle2;
    Pad middleRectangle;
    bool gameOver = false;
    bool Paused = false;

    init(ball, rectangle1, rectangle2, middleRectangle);

    
    int initialDirection = GetRandomValue(1, 4);
    int initialDirectionAgain = GetRandomValue(1,2);
    int currentOption = 0;
    int firstOption = SINGLEPLAYER;
    int lastOption = EXIT;
    bool isGameRunning = true;
    int winPoints = 5;

    GameScreen currentScreen = MENU;

    while (!slShouldClose() && isGameRunning)
    {
        //SetExitKey(KEY_NULL);

        if (slGetKey(SL_KEY_DOWN))
        {
            currentOption++;
            if (currentOption >= lastOption)
            {
                currentOption = lastOption;
            }
        }

        if (slGetKey(SL_KEY_UP))
        {
            currentOption--;
            if (currentOption <= firstOption)
            {
                currentOption = firstOption;
            }
        }

        switch (currentScreen)
        {
        case MENU:
            switch (currentOption)
            {
            case SINGLEPLAYER:
                if (slGetKey(SL_KEY_ENTER))
                {
                    currentScreen = GameScreen::SINGLEPLAYER;
                }
                break;
            case MULTIPLAYER:
                if (slGetKey(SL_KEY_ENTER))
                {
                    currentScreen = GameScreen::MULTIPLAYER;
                }
                break;
            case RULES:
                if (slGetKey(SL_KEY_ENTER))

                {
                    currentScreen = GameScreen::RULES;
                }

                break;
            case EXIT:
                if (slGetKey(SL_KEY_ENTER))
                {
                    currentScreen = GameScreen::EXIT;
                }
                break;
            default:
                break;
            }
            break;
        case SINGLEPLAYER:
            returnToMenu(currentScreen, rectangle1, rectangle2, ball);
            updateSingleplayer(ball, rectangle1, rectangle2,  currentScreen, gameOver,  winPoints);
            break;
        case MULTIPLAYER:
            returnToMenu(currentScreen, rectangle1, rectangle2, ball);
            updateMultiplayer(ball, rectangle1, rectangle2, currentScreen, gameOver,  winPoints);
            break;
        case RULES:
            if (slGetKey(SL_KEY_ENTER))
            {
                currentScreen = GameScreen::MENU;
            }
            break;
        case EXIT:
            if (slGetKey(SL_KEY_ENTER))
            {
                isGameRunning = false;
            }
            else if (slGetKey(SL_KEY_BACKSPACE))
            {
                currentScreen = GameScreen::MENU;
            }
            break;
        default:
            break;
        }

        //BeginDrawing();

        switch (currentScreen)
        {
        case MENU:
            slSetBackColor(0.0,0.0,0.0);
            DrawText("Made by Ezequiel Prieto", 10.0f, 430.0f, 20.0f, WHITE);
            DrawText("SUPER CHAMPION PONG", GetScreenWidth() / 2.0f - 250.0f, 50.0f, 40.0f, WHITE);
            DrawText("SINGLE PLAYER", GetScreenWidth() / 2.0f - 40.0f, 150.0f, 20.0f, WHITE);
            DrawText("MULTI PLAYER", GetScreenWidth() / 2.0f - 40.0f, 200.0f, 20.0f, WHITE);
            DrawText("RULES", GetScreenWidth() / 2.0f - 40.0f, 250.0f, 20.0f, WHITE);
            DrawText("EXIT", GetScreenWidth() / 2.0f - 40.0f, 300.0f, 20.0f, WHITE);
            DrawText("Use the up and down keys ", 450.0f, 270.0f, 20.0f, WHITE);
            DrawText("to move through the menu!", 450.0f, 300.0f, 20.0f, WHITE);
            switch (currentOption)
            {
            case SINGLEPLAYER:               
                DrawText("SINGLE PLAYER", GetScreenWidth() / 2.0f - 40.0f, 150.0f, 20.0f, RED);
                break;
            case MULTIPLAYER:               
                DrawText("MULTI PLAYER", GetScreenWidth() / 2.0f - 40.0f, 200.0f, 20.0f, RED);
                break;
            case RULES:                
                DrawText("RULES", GetScreenWidth() / 2.0f - 40.0f, 250.0f, 20.0f, RED);
                break;
            case EXIT:            
                DrawText("EXIT", GetScreenWidth() / 2.0f - 40.0f, 300.0f, 20.0f, RED);
                break;
            default:
                break;
            }
            break;
        case SINGLEPLAYER:
            slSetBackColor(0.0, 0.600, 0.0);
            drawGame(ball, rectangle1, rectangle2, middleRectangle);
            break;
        case MULTIPLAYER:
            slSetBackColor(0.0, 0.600, 0.0);
            drawGame(ball, rectangle1, rectangle2, middleRectangle);
            break;
        case RULES:
            slSetBackColor(0.0, 0.0, 0.0);
            DrawText("• Player 1 has to move the left pad up and down with the a and s keys.", 20, 20, 20, WHITE);
            DrawText("• Player 2 has to move the right pad up and down with the up and", 20, 40, 20, WHITE);
            DrawText("   down keys.", 20, 60, 20, WHITE);
            DrawText("• The first one getting five points wins.", 20, 80, 20, WHITE);
            DrawText("To return to the menu press enter.", 20, 120, 20, WHITE);
            break;
        case EXIT:
            slSetBackColor(0.0, 0.0, 0.0);
            DrawText("Do you want to exit? If yes press enter, if no press backspace", 20, 40, 20, WHITE);
            break;
        default:
            break;
        }

        EndDrawing();
    }

    close();
}

int GetScreenWidth()
{
    const int screenWidth = 800;
    return screenWidth;
}

int GetScreenHeight()
{
    const int screenHeight = 450;
    return screenHeight;
}

void ResetGame(Pad& rectangle1, Pad& rectangle2, Ball& ball)
{
    rectangle1.score = 0;
    rectangle2.score = 0;
    initBall(ball);
    initPad1(rectangle1);
    initPad2(rectangle2);
}

void returnToMenu(GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball)
{
    if (slGetKey(SL_KEY_ESCAPE))
    {
        currentScreen = GameScreen::MENU;
        ResetGame(rectangle1, rectangle2, ball);
    }
}


void ResetBall(Ball& ball)
{
    int direction = GetRandomValue(1,4);
    ball.speedX = 250.0f;
    ball.speedY = 250.0f;

    ball.x = GetScreenWidth() / 2;
    ball.y = GetScreenHeight() / 2;

    switch (direction)
    {
    case 1:
        ball.speedX *= 1.0f;
        ball.speedY *= -1.0f;
        break;
    case 2:
        ball.speedX *= 1.0f;
        ball.speedY *= 1.0f;
        break;
    case 3:
        ball.speedX *= -1.0f;
        ball.speedY *= 1.0f;
        break;
    case 4:
        ball.speedX *= -1.0f;
        ball.speedY *= -1.0f;
        break;
    default:
        break;
    }       
}

void init(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    slWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    initBall(ball);

    initPad1(rectangle1);

    initPad2(rectangle2);

    middleRectangle.x = (float)screenWidth - 420;
    middleRectangle.y = (float)screenHeight / 40;
    middleRectangle.width = (float)screenWidth / 30;
    middleRectangle.height = (float)screenHeight - 20;

}

void inputsSingle(Pad& rectangle1)
{
    if (slGetKey('W')) rectangle1.y -= 250.0f * slGetDeltaTime();

    if (slGetKey('S')) rectangle1.y += 250.0f * slGetDeltaTime();
}

void inputsMulti(Pad& rectangle1, Pad& rectangle2)
{
    if (slGetKey('W')) rectangle1.y -= 250.0f * slGetDeltaTime();

    if (slGetKey('S')) rectangle1.y += 250.0f * slGetDeltaTime();

    if (slGetKey(SL_KEY_UP)) rectangle2.y -= 250.0f * slGetDeltaTime();

    if (slGetKey(SL_KEY_DOWN)) rectangle2.y += 250.0f * slGetDeltaTime();
}

void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle)
{
    slSetForeColor(1, 1, 1, 1);
    slSetFont(slLoadFont("fonts/arial.ttf"), 20);
    slSetTextAlign(SL_ALIGN_LEFT);
    slSetFontSize(40);
    slText(400, 420, const char*(rectangle1.score));
    DrawText(TextFormat("%i", rectangle1.score), 140, 45, 40, RAYWHITE);

    DrawText(TextFormat("%i", rectangle2.score), 650, 45, 40, RAYWHITE);

    DrawText("Use ESC to go back to the menu ", 20.0f, 420.0f, 20.0f, RAYWHITE);

    slSetForeColor(1, 1, 1, 1);
    slRectangleFill(middleRectangle.x, middleRectangle.y, middleRectangle.width, middleRectangle.height);

    slSetForeColor(1, 1, 1, 1);
    slRectangleFill(ball.x, ball.y, ball.width, ball.height);

    slSetForeColor(1, 0, 0, 1);
    slRectangleFill(rectangle1.x, rectangle1.y, rectangle1.width, rectangle1.height);

    slSetForeColor(1, 1, 0, 0);
    slRectangleFill(rectangle2.x, rectangle2.y, rectangle2.width, rectangle2.height);

    slRender();
}

void updateSingleplayer(Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints)
{
    if (!gameOver)
    {
        inputsSingle(rectangle1);

        ball.x += ball.speedX * slGetDeltaTime();
        ball.y += ball.speedY * slGetDeltaTime();

        if (ball.y >= (GetScreenHeight() - ball.height)) 
        { 
            ball.speedY *= -1.0f;
            ball.y = GetScreenHeight() - ball.height;
        }
        if (ball.y < 0)
        {
            ball.speedY *= -1.0f;
            ball.y = 0;
        }

        if (isColliding(rectangle1, ball))
        {
            ball.x = rectangle1.x + ball.width;
            ball.speedX *= -1.1f;
            ball.speedY *= 1.1f;
        }

        if (isColliding(rectangle2, ball))
        {
            ball.x = rectangle2.x - ball.width;
            ball.speedX *= -1.1f;
            ball.speedY *= 1.1f;
        }

        if (rectangle2.y + rectangle2.height / 2 > ball.y)
        {
            rectangle2.y -= 210.0f * slGetDeltaTime();
        }
        if (rectangle2.y + rectangle2.height / 2 <= ball.y)
        {
            rectangle2.y += 210.0f * slGetDeltaTime();
        }

        if (ball.x + ball.width / 2 >= slGetDeltaTime())
        {
            rectangle1.score++;
            ResetBall(ball);
        }
        if (ball.x - ball.width / 2 <= 0)
        {
            rectangle2.score++;
            ResetBall(ball);
        }

        Limit(rectangle1);
        Limit(rectangle2);

    }

    if (rectangle1.score == winPoints)
    {
        gameOver = true;
        slSetTextAlign(SL_ALIGN_LEFT);
        slSetForeColor(0,1,0,1);
        slSetFontSize(20);
        slText(20, 420, "Player 1 has won");
        slSetForeColor(1, 1, 1, 1);
        slText(20, 400, "Press enter to return to the menu");
        if (slGetKey(SL_KEY_ENTER))
        {
            ResetGame(rectangle1, rectangle2, ball);

            gameOver = false;
            currentScreen = GameScreen::MENU;
        }
    }

    if (rectangle2.score == winPoints)
    {
        gameOver = true;
        slSetTextAlign(SL_ALIGN_RIGHT);
        slSetForeColor(0, 1, 0, 1);
        slSetFontSize(20);
        slText(600, 420, "The CPU has won");
        slSetForeColor(1, 1, 1, 1);
        slText(550, 400, "Press enter to return to the menu");
        if (slGetKey(SL_KEY_ENTER))
        {
            ResetGame(rectangle1, rectangle2, ball);

            gameOver = false;
            currentScreen = GameScreen::MENU;
        }

    }

}

void updateMultiplayer(Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints)
{
   if (!gameOver)
    {
        inputsSingle(rectangle1);

        ball.x += ball.speedX * slGetDeltaTime();
        ball.y += ball.speedY * slGetDeltaTime();

        if (ball.y >= (GetScreenHeight() - ball.height)) 
        { 
            ball.speedY *= -1.0f;
            ball.y = GetScreenHeight() - ball.height;
        }
        if (ball.y < 0)
        {
            ball.speedY *= -1.0f;
            ball.y = 0;
        }

        if (isColliding(rectangle1, ball))
        {
            ball.x = rectangle1.x + ball.width;
            ball.speedX *= -1.1f;
            ball.speedY *= 1.1f;
        }

        if (isColliding(rectangle2, ball))
        {
            ball.x = rectangle2.x - ball.width;
            ball.speedX *= -1.1f;
            ball.speedY *= 1.1f;
        }

        if (rectangle2.y + rectangle2.height / 2 > ball.y)
        {
            rectangle2.y -= 210.0f * slGetDeltaTime();
        }
        if (rectangle2.y + rectangle2.height / 2 <= ball.y)
        {
            rectangle2.y += 210.0f * slGetDeltaTime();
        }

        if (ball.x + ball.width / 2 >= slGetDeltaTime())
        {
            rectangle1.score++;
            ResetBall(ball);
        }
        if (ball.x - ball.width / 2 <= 0)
        {
            rectangle2.score++;
            ResetBall(ball);
        }

        Limit(rectangle1);
        Limit(rectangle2);

    }

    if (rectangle1.score == winPoints)
    {
        gameOver = true;
        DrawText("Player 1 has won", 20, 15, 20, GREEN);
        DrawText("Press enter to return to the menu", 420, 100, 20, WHITE);
        if (slGetKey(SL_KEY_ENTER))
        {
            ResetGame(rectangle1, rectangle2, ball);

            gameOver = false;
            currentScreen = GameScreen::MENU;
        }
    }

    if (rectangle2.score == winPoints)
    {
        gameOver = true;
        DrawText("Player 2 has won", GetScreenWidth() - 200, 15, 20, GREEN);
        DrawText("Press enter to return to the menu", 420, 100, 20, WHITE);
        if (slGetKey(SL_KEY_ENTER))
        {
            ResetGame(rectangle1, rectangle2, ball);

            gameOver = false;
            currentScreen = GameScreen::MENU;
        }

    }

}

void close()
{
    slClose();
}