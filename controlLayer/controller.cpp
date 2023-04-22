#include "controller.hpp"
#include "fssimplewindow.h"

Controller::Controller()
{
    this->Init();
}

Controller::~Controller()
{
}

void Controller::Init()
{
    viewPortInPhysicalX = 0;
    viewPortInPhysicalY = 0;
    viewPortInPhysicalHeight = 15;
    viewPortInPhysicalWidth = 15;
    screenWidth = 960;
    screenHeight = 960;
    map.mario.renderer.SetRenderColor(1, 1, 0, 1);
    for (SMBbase &b : map.blocks)
    {
        b.renderer.SetRenderColor(0, 0, 0, 1);
    }
}

bool Controller::IsTerminated(void) const
{
    return term;
}

void Controller::RunOneStep(double timeDiff)
{
    FsPollDevice();
    if (FsGetKeyState(FSKEY_ESC))
    {
        term = true;
    }

    if (FsGetKeyState(FSKEY_LEFT))
    {
        map.mario.AccLeft(timeDiff);
    }
    if (FsGetKeyState(FSKEY_RIGHT))
    {
        map.mario.AccRight(timeDiff);
    }
    if (FsGetKeyState(FSKEY_UP))
    {
        map.mario.Jump(timeDiff);
    }

    if (FsGetKeyState(FSKEY_SHIFT))
    {
        map.mario.currentCanDash = true;
    }
    else
    {
        map.mario.currentCanDash = false;
    }

    if (FsGetKeyState(FSKEY_DOWN))
    {
    }
    timePassed += timeDiff;
    map.RunOneStep(timeDiff);
}

void Controller::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float xmin, ymin, xmax, ymax;
    // mario
    xmin = W2VXRatio(map.mario.x) * screenWidth;
    ymin = W2VYRatio(map.mario.y + map.mario.height) * screenHeight;
    xmax = W2VXRatio(map.mario.x + map.mario.width) * screenWidth;
    ymax = W2VYRatio(map.mario.y) * screenHeight;
    map.mario.renderer.DrawSimple(xmin, ymin, xmax, ymax);
    printf("mario: %f, %f, %f, %f\n", xmin, ymin, xmax, ymax);
    for (SMBbase &w : map.blocks)
    {
        xmin = W2VXRatio(w.x) * screenWidth;
        ymin = W2VYRatio(w.y + w.height) * screenHeight;
        xmax = W2VXRatio(w.x + w.width) * screenWidth;
        ymax = W2VYRatio(w.y) * screenHeight;
        w.renderer.DrawSimple(xmin, ymin, xmax, ymax);
        printf("block: %f, %f, %f, %f\n", xmin, ymin, xmax, ymax);
    }
    FsSwapBuffers();
}

float Controller::W2VXRatio(float worldx) const
{
    return (worldx - viewPortInPhysicalX) / viewPortInPhysicalWidth;
}

float Controller::W2VYRatio(float worldy) const
{
    return 1 - ((worldy - viewPortInPhysicalY) / viewPortInPhysicalHeight);
}

bool Controller::IsInViewPort(SMBbase &obj) const
{
    return (obj.x > viewPortInPhysicalX && obj.x < viewPortInPhysicalX + viewPortInPhysicalWidth &&
            obj.y > viewPortInPhysicalY && obj.y < viewPortInPhysicalY + viewPortInPhysicalHeight) ||
           (obj.x + obj.width > viewPortInPhysicalX && obj.x + obj.width < viewPortInPhysicalX + viewPortInPhysicalWidth &&
            obj.y > viewPortInPhysicalY && obj.y < viewPortInPhysicalY + viewPortInPhysicalHeight) ||
           (obj.x > viewPortInPhysicalX && obj.x < viewPortInPhysicalX + viewPortInPhysicalWidth &&
            obj.y + obj.height > viewPortInPhysicalY && obj.y + obj.height < viewPortInPhysicalY + viewPortInPhysicalHeight) ||
           (obj.x + obj.width > viewPortInPhysicalX && obj.x + obj.width < viewPortInPhysicalX + viewPortInPhysicalWidth &&
            obj.y + obj.height > viewPortInPhysicalY && obj.y + obj.height < viewPortInPhysicalY + viewPortInPhysicalHeight);
}

void Controller::UpdateViewPortWithMario()
{
    float marioPropotion = (map.mario.x - viewPortInPhysicalX) / viewPortInPhysicalWidth;
    if (marioPropotion > 0.7)
    {
        viewPortInPhysicalX = map.mario.x - viewPortInPhysicalWidth * 0.7;
    }
    // teleported to underground
    if (map.mario.y < 0)
    {
        for (SMBbase &w : undergrounds)
        {
            char collision = map.mario.CheckCollision(w);
            if (!map.mario.IsNoHit(collision))
            {
                viewPortInPhysicalX = w.x;
                viewPortInPhysicalY = w.y;
                break;
            }
        }
    }
    if (viewPortInPhysicalX >= maxWorldX - viewPortInPhysicalWidth)
    {
        viewPortInPhysicalX = maxWorldX - viewPortInPhysicalWidth;
    }
}

void Controller::PassViewPortToMap()
{
    // TODO
}