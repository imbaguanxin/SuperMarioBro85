#include "map.hpp"

Map::Map()
{
    Init();
}

void Map::Init()
{
    this->mario.Init();
    blocks.push_back(SMBbase(0, 0, 15, 2, 0.1));
    blocks.push_back(SMBbase(5, 2, 2, 1, 0.1));
    blocks.push_back(SMBbase(3, 3, 2, 1, 0.1));
}

void Map::Collide(double timeDiff)
{
    for (SMBbase &b : blocks)
    {
        char res = mario.CheckCollision(b);
        mario.CollisionUpdateSelf(b, res, timeDiff);
    }
}

void Map::MoveOneStep(double timeDiff)
{
    mario.MoveByTime(timeDiff);
}

void Map::RunOneStep(double timeDiff)
{
    Collide(timeDiff);
    MoveOneStep(timeDiff);
}