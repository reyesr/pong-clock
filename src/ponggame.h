#ifndef PONGGAME_H
#define PONGGAME_H

#include <memory>
#include "sdlcontext.h"
#include "graphics.h"
#include <chrono>
#include "utils.h"

class PongGame
{
private:
    const int BORDER_WIDTH = 24;
    std::shared_ptr<SDLContext> context;

    int groundTop, groundBottom, groundLeft, groundRight;
    float ballx, bally;
    float ballDirX, ballDirY;
    float leftPaddleY, rightPaddleY;
    float paddleHeight;

    MILLIS lastFrameMillis;

public:
    PongGame(std::shared_ptr<SDLContext> context);

    void render();
private:

    void moveObjects();
    void drawGround(Graphics& g);
    void drawBall(Graphics&g);
    void drawPaddles(Graphics &g);

    void movePaddleToBall(float& y, int distancex, bool shouldMiss);
    void movePaddleIdle(float& y, int distancex, float moveModifier);

    template<typename X> X inline ranged(X x, X min, X max) {
        if (x < min) {
            return min;
        } else if (x > max) {
            return max;
        }
        return x;
    }
};

#endif // PONGGAME_H
