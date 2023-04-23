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
    // viewPortInPhysicalX = 0.0f;
    // viewPortInPhysicalY = 0.0f;
    // viewPortInPhysicalHeight = 15.0f;
    // viewPortInPhysicalWidth = 15.0f;
    // maxWorldX = 30.0f;
    // maxWorldY = 15.0f;
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
    return (worldx - map.GetVpX()) / map.GetVpWidth();
}

float Controller::W2VYRatio(float worldy) const
{
    return 1 - ((worldy - map.GetVpY()) / map.GetVpHeight());
}