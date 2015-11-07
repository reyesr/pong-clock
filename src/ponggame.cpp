#include "ponggame.h"
#include <cstdlib>
#include <iostream>

PongGame::PongGame(std::shared_ptr<SDLContext> context)
    :context(context)
{
    lastFrameMillis = Utils::now();
    groundLeft = BORDER_WIDTH/2;
    groundTop = BORDER_WIDTH/2;
    groundRight = context->width - BORDER_WIDTH/2;
    groundBottom = context->height - BORDER_WIDTH/2;

    this->ballx = groundLeft + (groundRight-groundLeft)/2 + 5;
    this->bally = groundBottom - (groundBottom-groundTop)/2 + 5;
    this->ballDirX = (groundRight - groundLeft) / 4;
    this->ballDirY = 50;

    this->leftPaddleY = this->rightPaddleY = context->height / 2;
    this->paddleHeight = BORDER_WIDTH * 3;
}

void PongGame::render()
{
    Graphics g(context);
    drawGround(g);
    moveObjects();
    drawBall(g);
    drawPaddles(g);
}

void PongGame::moveObjects()
{
    auto currentMillis = Utils::now();
    auto millisSinceLastFrame = currentMillis - lastFrameMillis;
    float modifier = 1.0/(1000.0 / (millisSinceLastFrame>0?millisSinceLastFrame:1)); // adjustment for frame loss

    auto seconds = currentMillis / 1000;

    bool isLastSecondBeforeNextMinute = (seconds % 60) >= 58;
    bool isFirstSecond = (seconds % 60) <= 1;

    auto width = context->width - BORDER_WIDTH*2;
    width += (isLastSecondBeforeNextMinute?BORDER_WIDTH*2:0); // The last 2 seconds scrern traversal are longer because the ball does not it the left pad
    bool ballIsGoingLeft = ((seconds%4) / 2) == 0 ? false : true;
    auto millisBeforeWall = 2000 - (currentMillis % 2000);

    auto ratio = (float)millisBeforeWall / 2000.0;
    if (ballIsGoingLeft) {
        ballx =  ratio * (float)width + (isLastSecondBeforeNextMinute ? 0 : BORDER_WIDTH);
    } else {
        if (isFirstSecond) {
            ballx = (float)width/2 - ratio*(float)width/2 + BORDER_WIDTH + width/2;
        } else {
            ballx = (float)width - ratio*(float)width + BORDER_WIDTH;
        }
    }

    bally += ballDirY * modifier;
    lastFrameMillis = currentMillis;

    bally = ranged(bally, (float)groundTop, (float)groundBottom);

    if ((bally < groundTop+BORDER_WIDTH && ballDirY<0) || (bally > groundBottom-BORDER_WIDTH && ballDirY>0)) {
        ballDirY = -ballDirY;
    }

    // left paddle
    if (ballIsGoingLeft) {
        movePaddleToBall(leftPaddleY, ballx, isLastSecondBeforeNextMinute);
    } else {
        movePaddleIdle(leftPaddleY, ballx, 110);
    }

    // right paddle
    if (!ballIsGoingLeft) {
        movePaddleToBall(rightPaddleY, width - ballx, isLastSecondBeforeNextMinute);
    } else {
        movePaddleIdle(rightPaddleY, ballx, 60);
    }
}

void PongGame::drawGround(Graphics& g)
{
    static Color GROUND_COLOR(133,133,133);
    static int HALF = BORDER_WIDTH /2;
    g.setColor(GROUND_COLOR);
    g.fillRect(groundLeft - HALF, groundTop - HALF, groundRight - groundLeft + BORDER_WIDTH, BORDER_WIDTH);
    g.fillRect(groundLeft - HALF, groundBottom - HALF, groundRight - groundLeft + BORDER_WIDTH, BORDER_WIDTH);

    for (auto yi = (groundTop+BORDER_WIDTH); yi<groundBottom ; yi+= BORDER_WIDTH*2) {
        g.fillRect(groundLeft + (groundRight-groundLeft)/2 - HALF, yi, BORDER_WIDTH, BORDER_WIDTH);

    }
}

void PongGame::drawBall(Graphics &g)
{
    static Color BALL_COLOR(255,50,50);
    static int HALF = BORDER_WIDTH /2;

    g.setColor(BALL_COLOR);
    g.fillRect(ballx-HALF, bally-HALF, BORDER_WIDTH, BORDER_WIDTH);
}

void PongGame::drawPaddles(Graphics &g)
{
    static Color PAD_COLOR(255,50,50);
    g.setColor(PAD_COLOR);

    g.fillRect(0, (int)(leftPaddleY - paddleHeight/2), BORDER_WIDTH, paddleHeight);
    g.fillRect(g.width() - BORDER_WIDTH, rightPaddleY - paddleHeight/2, BORDER_WIDTH, paddleHeight);
}

void PongGame::movePaddleToBall(float &y, int distancex, bool shouldMiss)
{
    float maxMove = (context->width-distancex) / ((distancex<3?3:distancex)/3) * 5;
    // std::cout << "distance " << distancex << " - maxMove " << maxMove << " - width: " << context->width << std::endl;
    float targetY = bally;
    if (shouldMiss) {
        if (bally > context->height/2) {
            targetY -= paddleHeight;
        } else {
            targetY += paddleHeight;
        }
    }

    float distanceY = ranged((targetY - y), -maxMove, maxMove);
    y += distanceY;
    y = ranged((int)y, (int)(BORDER_WIDTH + paddleHeight/2), (int)(context->height-BORDER_WIDTH - paddleHeight/2));
}

void PongGame::movePaddleIdle(float &y, int distancex, float moveModifier)
{
    float targetY = context->height/2 - (bally - context->height / 2);
    int maxMove = ranged(distancex / moveModifier, (float)1, (float)15);
    int distanceY = ranged((int)(targetY - y), -maxMove, maxMove);
    y += distanceY;
    y = ranged((int)y, (int)(BORDER_WIDTH + paddleHeight/2), (int)(context->height-BORDER_WIDTH - paddleHeight/2));
}

