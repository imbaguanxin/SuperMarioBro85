#include "mario.hpp"
#include <algorithm>

Mario::Mario()
{
    Mario::Init();
}

void Mario::Init()
{
    Moveable::Init();
    this->myId = SMBbase::objectId::MARIO;
    SetBBX(5.0, 2.0, 1.0, 1.0);
}

Mario::Mario(float x, float y, float width, float height,
             float bbxRatio, float vx, float vy)
{
    Moveable(x, y, width, height, bbxRatio, SMBbase::objectId::MARIO, vx, vy);
}

void Mario::AccRight(double timeDiff)
{
    printf("received acc right\n");
    if (currentCanDash)
    {
        if (vx < MAX_DASHING_VX)
        {
            vx = std::min(MAX_DASHING_VX, vx + DASHING_ACC_X * float(timeDiff));
            // currentVxHasChanged = true;
        }
    }
    else
    {
        if (vx < MAX_WALKING_VX)
        {
            vx = std::min(MAX_WALKING_VX, vx + WALKING_ACC_X * float(timeDiff));
            // currentVxHasChanged = true;
        }
    }
    currentVxHasChanged = true;
    printf("current vx: %f\n", vx);
}

void Mario::AccLeft(double timeDiff)
{
    if (currentCanDash)
    {
        if (vx > -MAX_DASHING_VX)
        {
            vx = std::max(-MAX_DASHING_VX, vx - DASHING_ACC_X * float(timeDiff));
            // currentVxHasChanged = true;
        }
    }
    else
    {
        if (vx > -MAX_WALKING_VX)
        {
            vx = std::max(-MAX_WALKING_VX, vx - WALKING_ACC_X * float(timeDiff));
            // currentVxHasChanged = true;
        }
    }
    currentVxHasChanged = true;
}

void Mario::Jump(double timeDiff)
{
    printf("Receive Jump command\n");
    if (currentLocStatus == Mario::marioLocStatus::ON_GROUND)
    {
        vy += JUMP_ACC_Y * float(timeDiff);
        y += 3 * EPSILON;
        currentLocStatus = Mario::marioLocStatus::ON_AIR;
        timeSinceLastStatusChange = 0;
        // currentVxHasChanged = true;
    }
    else
    {
        if (timeSinceLastStatusChange < JUMP_TOLERANCE_SEC)
        {
            vy += JUMP_ACC_Y * float(timeDiff);
            vy = std::min(vy, MAX_VY);
            // currentVxHasChanged = true;
        }
    }
}

void Mario::NoInput(double timeDiff)
{
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

void Mario::ApplyGravity(double timeDiff)
{
    vy -= GRAVITY * float(timeDiff);
    vy = std::max(vy, -MAX_VY);
    vy = std::min(vy, MAX_VY);
}

void Mario::MoveByTime(double timeDiff)
{
    //
    if (!currentVxHasChanged)
    {
        NoInput(timeDiff);
        printf("no input\n");
    }
    currentVxHasChanged = false;

    if (currentLocStatus == marioLocStatus::ON_AIR)
    {
        ApplyGravity(timeDiff);
    }

    x += vx * float(timeDiff);
    y += vy * float(timeDiff);
    printf("mario x, y, vx, vy: %f, %f, %f, %f\n", x, y, vx, vy);
    printf("mario loc status: %d, is running: %d, can dash: %d\n", currentLocStatus, currentIsRunning, currentCanDash);
    printf("mario status last time %f\n", timeSinceLastStatusChange);
    timeSinceLastStatusChange += timeDiff;
}

void Mario::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    if (IsNoHit(collisionResult))
    {
        return;
    }
    hitResultAccumulator |= collisionResult;
    switch (other.myId)
    {
    case SMBbase::objectId::BLOCK:

        if (IsUpHit(collisionResult))
        {
            printf("Mario up hit\n");
            y = other.y - height - EPSILON;
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
                    if (vx < EPSILON && vx > -EPSILON)
                    {
                        this->currentIsRunning = false;
                        printf("stop running\n");
                        ClearTimer();
                    }
                }
                else
                {
                    if (vx > EPSILON || vx < -EPSILON)
                    {
                        this->currentIsRunning = true;
                        printf("start running\n");
                        ClearTimer();
                    }
                }
            }
            else
            {
                this->currentLocStatus = marioLocStatus::ON_GROUND;
                vy = 0;
                y = other.y + other.height - EPSILON;
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

void Mario::CollisionCheckStart()
{
    hitResultAccumulator = 0;
}

void Mario::CollisionCheckEnd()
{
    if (!IsDownHit(hitResultAccumulator))
    {
        if (currentLocStatus != marioLocStatus::ON_AIR)
        {
            currentLocStatus = marioLocStatus::ON_AIR;
            ClearTimer();
        }
    }
}

void Mario::ApplyRenderStatus()
{
    if (currentSizeStatus == Mario::marioSizeStatus::SMALL)
    {
        if (currentLocStatus == Mario::marioLocStatus::ON_AIR)
        {
            if (vx > 0)
            {
                renderer.SetRenderIsFlip(false);
            }
            else
            {
                renderer.SetRenderIsFlip(true);
            }
            renderer.SetRenderState(4);
        }
        else if (currentLocStatus == Mario::marioLocStatus::ON_GROUND)
        {
            // decide direction
            if (vx > EPSILON)
            {
                renderer.SetRenderIsFlip(false);
            }
            else if (vx < -EPSILON)
            {
                renderer.SetRenderIsFlip(true);
            }
            // decide running
            if (!currentIsRunning)
            {
                renderer.SetRenderState(0);
                printf("go to standing, vx: %f\n", vx);
            }
            else
            {
                int runningState = int(timeSinceLastStatusChange / 0.2) % 3;
                switch (runningState)
                {
                case 0:
                    renderer.SetRenderState(1);
                    break;
                case 1:
                    renderer.SetRenderState(2);
                    break;
                case 2:
                    renderer.SetRenderState(3);
                    break;
                }
            }
        }
        else
        {
            renderer.SetRenderState(0);
        }
    }
}