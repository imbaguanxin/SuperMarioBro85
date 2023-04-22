#include "base.hpp"

SMBbase::SMBbase()
{
    SetBBX(0, 0, 0, 0);
    SetBBXRatio(0.1);
}

SMBbase::SMBbase(float x, float y, float width, float height, float bbxRatio)
{
    SetBBX(x, y, width, height);
    SetBBXRatio(bbxRatio);
}

void SMBbase::SetBBX(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void SMBbase::SetBBXRatio(float bbxRatio)
{
    this->bbxRatio = bbxRatio;
}

char SMBbase::CheckCollision(SMBbase &other)
{
    char result = 0;
    float thisBbxUp[4] = {x + width * bbxRatio, y + height * (1 - bbxRatio),
                          width * (1 - 2 * bbxRatio), height * bbxRatio};
    float thisBbxDown[4] = {x + width * bbxRatio, y,
                            width * (1 - 2 * bbxRatio), height * bbxRatio};
    float thisBbxLeft[4] = {x, y + height * bbxRatio,
                            width * bbxRatio, height * (1 - 2 * bbxRatio)};
    float thisBbxRight[4] = {x + width * (1 - bbxRatio), y + height * bbxRatio,
                             width * bbxRatio, height * (1 - 2 * bbxRatio)};
    // float thisBbxLeft[4] = {x, y,
    //                         width * bbxRatio, height};
    // float thisBbxRight[4] = {x + width * (1 - bbxRatio), y,
    //                          width * bbxRatio, height};

    // up hit
    if (bbxCollisionCheck(thisBbxUp[0], thisBbxUp[1], thisBbxUp[2], thisBbxUp[3],
                          other.x, other.y, other.width, other.height))
    {
        result |= 0b0010;
    }
    // down hit
    if (bbxCollisionCheck(thisBbxDown[0], thisBbxDown[1], thisBbxDown[2], thisBbxDown[3],
                          other.x, other.y, other.width, other.height))
    {
        result |= 0b0001;
    }
    // left hit
    if (bbxCollisionCheck(thisBbxLeft[0], thisBbxLeft[1], thisBbxLeft[2], thisBbxLeft[3],
                          other.x, other.y, other.width, other.height))
    {
        result |= 0b1000;
    }
    // right hit
    if (bbxCollisionCheck(thisBbxRight[0], thisBbxRight[1], thisBbxRight[2], thisBbxRight[3],
                          other.x, other.y, other.width, other.height))
    {
        result |= 0b0100;
    }
    switch (result)
    {
    case 0b1101: // left right down -> down
        result = 0b0001;
        break;
    case 0b1110: // left right up -> up
        result = 0b0010;
        break;
    case 0b1011: // up down left -> left
        result = 0b1000;
        break;
    case 0b0111: // up down right -> right
        result = 0b0100;
        break;
    }
    // printf("result: %x\n", result);
    return result;
}

bool SMBbase::bbxCollisionCheck(float x1, float y1, float width1, float height1,
                                float x2, float y2, float width2, float height2)
{
    float left1, left2, right1, right2, top1, top2, bottom1, bottom2;
    left1 = x1;
    right1 = x1 + width1;
    top1 = y1 + height1;
    bottom1 = y1;

    left2 = x2;
    right2 = x2 + width2;
    top2 = y2 + height2;
    bottom2 = y2;
    if (bottom1 > top2 || top1 < bottom2 || right1 < left2 || left1 > right2)
        return false;
    return true;
}

bool SMBbase::IsNoHit(char collisionResult)
{
    return collisionResult == 0;
}

bool SMBbase::IsLeftHit(char collisionResult)
{
    return (collisionResult & 0x8) != 0;
}

bool SMBbase::IsRightHit(char collisionResult)
{
    return (collisionResult & 0x4) != 0;
}

bool SMBbase::IsUpHit(char collisionResult)
{
    return (collisionResult & 0x2) != 0;
}

bool SMBbase::IsDownHit(char collisionResult)
{
    return (collisionResult & 0x1) != 0;
}

char SMBbase::InverseCollision(char collisionResult)
{
    char leftup = (collisionResult & 0b1010) >> 1;
    char rightdown = (collisionResult & 0b0101) << 1;
    return leftup | rightdown;
}

void SMBbase::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    return;
}