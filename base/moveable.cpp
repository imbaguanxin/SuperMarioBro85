#include "moveable.hpp"

Moveable::Moveable()
{
    Moveable::Init();
}

void Moveable::Init()
{
    MultiStatus::Init();
    this->vx = 0;
    this->vy = 0;
}

Moveable::Moveable(float x, float y,
                   float width, float height,
                   float bbxRatio, int myId,
                   float vx, float vy)
{
    MultiStatus(x, y, width, height, bbxRatio, myId);
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

void Moveable::MoveByTime(double timeDiff)
{
    printf("Warning, used base case movebytime!\n");
    x += vx * timeDiff;
    y += vy * timeDiff;
    AddToTimer(timeDiff);
}