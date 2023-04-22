#ifndef MOVEABLE_IS_INCLUDED
#define MOVEABLE_IS_INCLUDED

#include "base.hpp"
class Moveable : public SMBbase
{
public:
    double timeSinceLastStatusChange = 0;
    float vx = 0, vy = 0;
    Moveable();
    Moveable(float x, float y, float width, float height, float bbxRatio, float vx, float vy);
    void SetV(float vx, float vy);
    void SetVX(float vx);
    void SetVY(float vy);
    virtual void MoveByTime(double timeDiff);
};
#endif