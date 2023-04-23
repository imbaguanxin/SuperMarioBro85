#include "map.hpp"

Map::Map()
{
    Init();
}

void Map::Init()
{
    this->mario.Init();
    blocks.push_back(SMBbase(0, 0, 15, 2, 0.1, SMBbase::objectId::BLOCK));
    blocks.push_back(SMBbase(5, 4, 2, 1, 0.1, SMBbase::objectId::BLOCK));
    blocks.push_back(SMBbase(3, 6, 2, 1, 0.1, SMBbase::objectId::BLOCK));
    this->viewPortX = 0.0f;
    this->viewPortY = 0.0f;
    this->viewPortHeight = 15.0f;
    this->viewPortWidth = 15.0f;
    this->maxWorldX = 30.0f;
    this->maxWorldY = 15.0f;
}

float Map::GetVpHeight() const
{
    return viewPortHeight;
}

float Map::GetVpWidth() const
{
    return viewPortWidth;
}

float Map::GetVpX() const
{
    return viewPortX;
}

float Map::GetVpY() const
{
    return viewPortY;
}

void Map::UpdateViewPortWithMario()
{
    float marioPropotion = (mario.x - viewPortX) / viewPortWidth;
    printf("mario propotion: %f\n", marioPropotion);
    if (marioPropotion > VIEWPORT_MAX_RATIO)
    {
        viewPortX = mario.x - viewPortWidth * VIEWPORT_MAX_RATIO;
    }
    // teleported to underground
    // TODO
    if (viewPortX >= maxWorldX - viewPortWidth)
    {
        viewPortX = maxWorldX - viewPortWidth;
    }
}

bool Map::IsInViewPort(SMBbase &obj) const
{
    return (obj.x > viewPortX && obj.x < viewPortX + viewPortWidth &&
            obj.y > viewPortY && obj.y < viewPortY + viewPortHeight) ||
           (obj.x + obj.width > viewPortX && obj.x + obj.width < viewPortX + viewPortWidth &&
            obj.y > viewPortY && obj.y < viewPortY + viewPortHeight) ||
           (obj.x > viewPortX && obj.x < viewPortX + viewPortWidth &&
            obj.y + obj.height > viewPortY && obj.y + obj.height < viewPortY + viewPortHeight) ||
           (obj.x + obj.width > viewPortX && obj.x + obj.width < viewPortX + viewPortWidth &&
            obj.y + obj.height > viewPortY && obj.y + obj.height < viewPortY + viewPortHeight);
}

void Map::RestrictMarioX()
{
    if (mario.y > 0 && mario.x < viewPortX)
    {
        mario.x = viewPortX;
    }
}

void Map::Collide(double timeDiff)
{
    mario.CollisionCheckStart();
    for (SMBbase &b : blocks)
    {
        char res = mario.CheckCollision(b);
        printf("mario collision result: %x\n", res);
        mario.CollisionUpdateSelf(b, res, timeDiff);
    }
    mario.CollisionCheckEnd();
}

void Map::MoveOneStep(double timeDiff)
{
    mario.MoveByTime(timeDiff);
}

void Map::RunOneStep(double timeDiff)
{   
    printf("////////////////////////\n");
    Collide(timeDiff);
    MoveOneStep(timeDiff);
    UpdateViewPortWithMario();
    RestrictMarioX();
}