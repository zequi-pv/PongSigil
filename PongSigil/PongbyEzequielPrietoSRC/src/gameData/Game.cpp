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
            ClearBackground(BLACK);
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
            ClearBackground(DARKGREEN);
            drawGame(ball, rectangle1, rectangle2, middleRectangle);
            break;
        case MULTIPLAYER:
            ClearBackground(DARKGREEN);
            drawGame(ball, rectangle1, rectangle2, middleRectangle);
            break;
        case RULES:
            ClearBackground(BLACK);
            DrawText("• Player 1 has to move the left pad up and down with the a and s keys.", 20, 20, 20, WHITE);
            DrawText("• Player 2 has to move the right pad up and down with the up and", 20, 40, 20, WHITE);
            DrawText("   down keys.", 20, 60, 20, WHITE);
            DrawText("• The first one getting five points wins.", 20, 80, 20, WHITE);
            DrawText("To return to the menu press enter.", 20, 120, 20, WHITE);
            break;
        case EXIT:
            ClearBackground(BLACK);
            DrawText("Do you want to exit? If yes press enter, if no press backspace", 20, 40, 20, WHITE);
            break;
        default:
            break;
        }

        EndDrawing();
    }

    close();
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
    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentScreen = GameScreen::MENU;
        ResetGame(rectangle1, rectangle2, ball);
    }
}


void ResetBall(Ball& ball)
{
    int direction = GetRandomValue(1,4);
    ball.Speed = { 250.0f, 250.0f };

    ball.Position.x = GetScreenWidth() / 2;
    ball.Position.y = GetScreenHeight() / 2;

    switch (direction)
    {
    case 1:
        ball.Speed.x *= 1.0f;
        ball.Speed.y *= -1.0f;
        break;
    case 2:
        ball.Speed.x *= 1.0f;
        ball.Speed.y *= 1.0f;
        break;
    case 3:
        ball.Speed.x *= -1.0f;
        ball.Speed.y *= 1.0f;
        break;
    case 4:
        ball.Speed.x *= -1.0f;
        ball.Speed.y *= -1.0f;
        break;
    default:
        break;
    }       
}

void init(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    initBall(ball);

    initPad1(rectangle1);

    initPad2(rectangle2);

    middleRectangle.Position = { (float)screenWidth - 420, (float)screenHeight / 40 };
    middleRectangle.Size = { (float)screenWidth / 30, (float)screenHeight - 20 };

}

void inputsSingle(Pad& rectangle1)
{
    if (IsKeyDown(KEY_W)) rectangle1.Position.y -= 250.0f * GetFrameTime();

    if (IsKeyDown(KEY_S)) rectangle1.Position.y += 250.0f * GetFrameTime();
}

void inputsMulti(Pad& rectangle1, Pad& rectangle2)
{
    if (IsKeyDown(KEY_W)) rectangle1.Position.y -= 250.0f * GetFrameTime();

    if (IsKeyDown(KEY_S)) rectangle1.Position.y += 250.0f * GetFrameTime();

    if (IsKeyDown(KEY_UP)) rectangle2.Position.y -= 250.0f * GetFrameTime();

    if (IsKeyDown(KEY_DOWN)) rectangle2.Position.y += 250.0f * GetFrameTime();
}

void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle)
{
    DrawText(TextFormat("%i", rectangle1.score), 140, 45, 40, RAYWHITE);

    DrawText(TextFormat("%i", rectangle2.score), 650, 45, 40, RAYWHITE);

    DrawText("Use ESC to go back to the menu ", 20.0f, 420.0f, 20.0f, RAYWHITE);

    DrawRectangleV(middleRectangle.Position, middleRectangle.Size, RAYWHITE);

    DrawRectangleGradientH(ball.Position.x, ball.Position.y, ball.Size.x, ball.Size.y, BLACK, RAYWHITE);

    DrawRectangleGradientV(rectangle1.Position.x, rectangle1.Position.y, rectangle1.Size.x, rectangle1.Size.y, RED, RAYWHITE);

    DrawRectangleGradientV(rectangle2.Position.x, rectangle2.Position.y, rectangle2.Size.x, rectangle2.Size.y, BLUE, YELLOW);
}

void updateSingleplayer(Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints)
{
    if (!gameOver)
    {
        inputsSingle(rectangle1);

        ball.Position.x += ball.Speed.x * GetFrameTime();
        ball.Position.y += ball.Speed.y * GetFrameTime();

        if (ball.Position.y >= (GetScreenHeight() - ball.Size.y)) 
        { 
            ball.Speed.y *= -1.0f;
            ball.Position.y = GetScreenHeight() - ball.Size.y;
        }
        if (ball.Position.y < 0)
        {
            ball.Speed.y *= -1.0f;
            ball.Position.y = 0;
        }

        if (isColliding(rectangle1, ball))
        {
            ball.Position.x = rectangle1.Position.x + ball.Size.x;
            ball.Speed.x *= -1.1f;
            ball.Speed.y *= 1.1f;
        }

        if (isColliding(rectangle2, ball))
        {
            ball.Position.x = rectangle2.Position.x - ball.Size.x;
            ball.Speed.x *= -1.1f;
            ball.Speed.y *= 1.1f;
        }

        if (rectangle2.Position.y + rectangle2.Size.y / 2 > ball.Position.y)
        {
            rectangle2.Position.y -= 210.0f * GetFrameTime();
        }
        if (rectangle2.Position.y + rectangle2.Size.y / 2 <= ball.Position.y)
        {
            rectangle2.Position.y += 210.0f * GetFrameTime();
        }

        if (ball.Position.x + ball.Size.x / 2 >= GetScreenWidth())
        {
            rectangle1.score++;
            ResetBall(ball);
        }
        if (ball.Position.x - ball.Size.x / 2 <= 0)
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
        if (IsKeyPressed(KEY_ENTER))
        {
            ResetGame(rectangle1, rectangle2, ball);

            gameOver = false;
            currentScreen = GameScreen::MENU;
        }
    }

    if (rectangle2.score == winPoints)
    {
        gameOver = true;
        DrawText("The CPU has won", GetScreenWidth() - 200, 15, 20, GREEN);
        DrawText("Press enter to return to the menu", 420, 100, 20, WHITE);
        if (IsKeyPressed(KEY_ENTER))
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
        inputsMulti(rectangle1, rectangle2);

        ball.Position.x += ball.Speed.x * GetFrameTime();
        ball.Position.y += ball.Speed.y * GetFrameTime();

        if (ball.Position.y >= (GetScreenHeight() - ball.Size.y))
        {
            ball.Speed.y *= -1.0f;
            ball.Position.y = GetScreenHeight() - ball.Size.y;
        }
        if (ball.Position.y < 0)
        {
            ball.Speed.y *= -1.0f;
            ball.Position.y = 0;
        }

        if (isColliding(rectangle1, ball))
        {
            ball.Position.x = rectangle1.Position.x + ball.Size.x;
            ball.Speed.x *= -1.1f;
            ball.Speed.y *= 1.1f;
        }

        if (isColliding(rectangle2, ball))
        {
            ball.Position.x = rectangle2.Position.x - ball.Size.x;
            ball.Speed.x *= -1.1f;
            ball.Speed.y *= 1.1f;
        }

        if (ball.Position.x + ball.Size.x / 2 >= GetScreenWidth())
        {
            rectangle1.score++;
            ResetBall(ball);
        }
        if (ball.Position.x - ball.Size.x / 2 <= 0)
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
        if (IsKeyPressed(KEY_ENTER))
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
        if (IsKeyPressed(KEY_ENTER))
        {
            ResetGame(rectangle1, rectangle2, ball);

            gameOver = false;
            currentScreen = GameScreen::MENU;
        }

    }

}

void close()
{
    CloseWindow();
}