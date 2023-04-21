#include "moveable.hpp"

Moveable::Moveable()
{
    SMBbase();
    vx = 0;
    vy = 0;
}

Moveable::Moveable(float x, float y,
                   float width, float height, float bbxRatio,
                   float vx, float vy)
{
    SMBbase(x, y, width, height, bbxRatio);
    this->vx = vx;
    this->vy = vy;
}

void Moveable::SetV(float vx, float vy)
{
    this->vx = vx;
    this->vy = vy;
}

void Moveable::SetVX(float vx)
{
    this->vx = vx;
}

void Moveable::SetVY(float vy)
{
    this->vy = vy;
}

void Moveable::MoveByTime(float timeDiff)
{
    x += vx * timeDiff;
    y += vy * timeDiff;
}