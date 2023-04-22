#include "mario.hpp"
#include <algorithm>

Mario::Mario()
{
    Init();
}

Mario::Mario(float x, float y, float width, float height,
             float bbxRatio, float vx, float vy)
{
    Moveable(x, y, width, height, bbxRatio, vx, vy);
    this->myId = SMBbase::objectId::MARIO;
}

Mario::Init()
{
    Moveable();
    this->myId = SMBbase::objectId::MARIO;
    SetBBX(5.0, 2.0, 1.0, 1.0);
}

void Mario::AccRight(double timeDiff)
{
    if (currentCanDash)
    {
        if (vx < MAX_DASHING_VX)
        {
            vx = std::min(MAX_DASHING_VX, vx + DASHING_ACC_X * float(timeDiff));
            currentVhasChanged = true;
        }
    }
    else
    {
        if (vx < MAX_WALKING_VX)
        {
            vx = std::min(MAX_WALKING_VX, vx + WALKING_ACC_X * float(timeDiff));
            currentVhasChanged = true;
        }
    }
}

void Mario::AccLeft(double timeDiff)
{
    if (currentCanDash)
    {
        if (vx > -MAX_DASHING_VX)
        {
            vx = std::max(-MAX_DASHING_VX, vx - DASHING_ACC_X * float(timeDiff));
            currentVhasChanged = true;
        }
    }
    else
    {
        if (vx > -MAX_WALKING_VX)
        {
            vx = std::max(-MAX_WALKING_VX, vx - WALKING_ACC_X * float(timeDiff));
            currentVhasChanged = true;
        }
    }
}

void Mario::Jump(double timeDiff)
{
    if (currentLocStatus == Mario::marioLocStatus::ON_GROUND)
    {
        vy += JUMP_ACC_Y * float(timeDiff);
        currentLocStatus = Mario::marioLocStatus::ON_AIR;
        timeSinceLastStatusChange = 0;
        currentVhasChanged = true;
    }
    else
    {
        if (timeSinceLastStatusChange < 200) // 200 ms
        {
            vy += JUMP_ACC_Y * float(timeDiff);
            vy = std::min(vy, MAX_VY);
            currentVhasChanged = true;
        }
    }
}

void Mario::NoInput(double timeDiff)
{
    if (currentLocStatus == marioLocStatus::ON_AIR)
    {
        vy -= GRAVITY * float(timeDiff);
        vy = std::max(vy, -MAX_VY);
    }

    if (vx > EPSILON)
    {
        vx = std::max(0.0f, vx - NO_INPUT_DEACC_X * float(timeDiff));
    }
    else if (vx < -EPSILON)
    {
        vx = std::min(0.0f, vx + NO_INPUT_DEACC_X * float(timeDiff));
    }
    else
    {
        vx = 0;
    }
}

void Mario::MoveByTime(float timeDiff)
{
    if (currentVhasChanged)
    {
        NoInput(timeDiff);
    }
    currentVhasChanged = false;
    x += vx * float(timeDiff);
    y += vy * float(timeDiff);
}

void Mario::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    if (IsNoHit(collisionResult))
    {
        return;
    }
    switch (other.myId)
    {
    case SMBbase::objectId::BLOCK:
        if (IsUpHit(collisionResult))
        {
            printf("Mario up hit\n");
            y = other.y - height;
            if (vy > 0)
            {
                vy = 0;
            }
        }
        if (IsDownHit(collisionResult))
        {
            printf("Mario down hit\n");
            if (this->currentLocStatus == marioLocStatus::ON_GROUND)
            {
                if (this->currentIsRunning)
                {
                    if (vx < EPSILON || vx > -EPSILON)
                    {
                        this->currentIsRunning = false;
                        this->timeSinceLastStatusChange = 0;
                    }
                }
                else
                {
                    if (vx > EPSILON || vx < -EPSILON)
                    {
                        this->currentIsRunning = true;
                        this->timeSinceLastStatusChange = 0;
                    }
                }
            }
            else
            {
                vy = 0;
                y = other.y + other.height * 0.99;
            }
        }
        if (IsRightHit(collisionResult))
        {
            printf("Mario right hit\n");
            if (vx > 0)
            {
                vx = 0;
            }
        }
        if (IsLeftHit(collisionResult))
        {
            printf("Mario left hit\n");
            if (vx < 0)
            {
                vx = 0;
            }
        }
        break;
    }
}
