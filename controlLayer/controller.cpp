#include "controller.hpp"
#include "fssimplewindow.h"
#include "textureRegister.h"
Controller::Controller()
{
    this->Init();
}

Controller::~Controller()
{
}

void Controller::Init()
{
    screenWidth = 960;
    screenHeight = 960;
    map.mario.renderer.SetRenderColor(1, 1, 1, 1);
    for (SMBbase &b : map.blocks)
    {
        b.renderer.SetRenderColor(1, 1, 1, 1);
    }
    InitTexture();
}

void Controller::InitTexture()
{ // 1 means 1 texture file
    td.resize(2);
    // must use absolute path and I don't know why
    int res = td.decoders[0].Decode("/Users/gx/repo/24783_cpp/ArcadeAvenger/assets/world1-1.png");
    if (YSERR == res)
    {
        printf("======\ndecode map failed\n======\n");
    }
    else
    {
        printf("======\ndecode map success\n======\n");
    }

    res = td.decoders[1].Decode("/Users/gx/repo/24783_cpp/ArcadeAvenger/assets/tileset.png");
    if (YSERR == res)
    {
        printf("======\ndecode tileset failed\n======\n");
    }
    else
    {
        printf("======\ndecode tileset success\n======\n");
    }
    // color means the background color. using white here
    float color[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    td.setRGBA(color);

    // register texture to opengl.
    // using for loop since might have multiple textures.
    int rgba_idx = 0;
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < td.size; ++i)
    {
        rgba_idx = i * 4;
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(td.rgba[rgba_idx],
                  td.rgba[rgba_idx + 1],
                  td.rgba[rgba_idx + 2],
                  td.rgba[rgba_idx + 3]);
        glGenTextures(1, &td.texIds[i]);
        glBindTexture(GL_TEXTURE_2D, td.texIds[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     td.decoders[i].wid,
                     td.decoders[i].hei,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     td.decoders[i].rgba);
    }
    TextureRegister tr;
    map.mario.renderer.AddRenderState(0, TextureCoord(tr.SMALL_MARIO_STAND));
    map.mario.renderer.AddRenderState(1, TextureCoord(tr.SMALL_MARIO_WALK_0));
    map.mario.renderer.AddRenderState(2, TextureCoord(tr.SMALL_MARIO_WALK_1));
    map.mario.renderer.AddRenderState(3, TextureCoord(tr.SMALL_MARIO_WALK_2));
    map.mario.renderer.AddRenderState(4, TextureCoord(tr.SMALL_MARIO_JUMP));
    map.mario.renderer.AddRenderState(5, TextureCoord(tr.SMALL_MARIO_GG));
    map.mario.renderer.SetRenderState(0);
    map.mario.renderer.SetRenderTextureId(1); // second texture
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float xmin, ymin, xmax, ymax;
    // mario
    xmin = W2VXRatio(map.mario.x) * screenWidth;
    ymin = W2VYRatio(map.mario.y + map.mario.height) * screenHeight;
    xmax = W2VXRatio(map.mario.x + map.mario.width) * screenWidth;
    ymax = W2VYRatio(map.mario.y) * screenHeight;
    map.mario.renderer.Draw(td, xmin, ymin, xmax, ymax);
    printf("mario: %f, %f, %f, %f\n", xmin, ymin, xmax, ymax);
    glDisable(GL_BLEND);
    for (SMBbase &w : map.blocks)
    {
        xmin = W2VXRatio(w.x) * screenWidth;
        ymin = W2VYRatio(w.y + w.height) * screenHeight;
        xmax = W2VXRatio(w.x + w.width) * screenWidth;
        ymax = W2VYRatio(w.y) * screenHeight;
        w.renderer.DrawSimple(xmin, ymin, xmax, ymax);
        printf("block color: %f, %f, %f, %f\n", w.renderer.color[0], w.renderer.color[1],
               w.renderer.color[2], w.renderer.color[3]);
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