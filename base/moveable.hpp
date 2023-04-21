#ifndef MOVEABLE_IS_INCLUDED
#define MOVEABLE_IS_INCLUDED

#include "base.hpp"
class Moveable : SMBbase
{
public:
    float vx, vy;
    Moveable();
    Moveable(float x, float y, float width, float height, float bbxRatio, float vx, float vy);
    void SetV(float vx, float vy);
    void SetVX(float vx);
    void SetVY(float vy);
    void MoveByTime(float timeDiff);
};
#endif