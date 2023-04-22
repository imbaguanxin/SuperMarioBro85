#include "map.hpp"

Map::Map()
{
    Init();
}

void Map::Init()
{
    this->mario.Init();
    blocks.push_back(SMBbase(0, 0, 15, 2, 0.1));
    blocks.push_back(SMBbase(5, 4, 2, 1, 0.1));
    blocks.push_back(SMBbase(3, 6, 2, 1, 0.1));
    blocks[0].myId = SMBbase::objectId::BLOCK;
    blocks[1].myId = SMBbase::objectId::BLOCK;
    blocks[2].myId = SMBbase::objectId::BLOCK;
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
    Collide(timeDiff);
    MoveOneStep(timeDiff);
}