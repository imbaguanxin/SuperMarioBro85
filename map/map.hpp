#ifndef MAP_IS_INCLUDED
#define MAP_IS_INCLUDED

#include <vector>
#include "base.hpp"
#include "mario.hpp"

class Map
{
public:
    std::vector<SMBbase> blocks; // all the blocks that could move

    Mario mario;

    std::vector<SMBbase> undergrounds; // undergrounds

    float viewPortHeight, viewPortWidth;
    float viewPortX, viewPortY; // left bottom corner
    float maxWorldX, maxWorldY;

    const float VIEWPORT_MAX_RATIO = 0.6f;

    Map();

    float GetVpHeight() const;
    float GetVpWidth() const;
    float GetVpX() const;
    float GetVpY() const;
    float GetMaxWorldX() const;
    float GetMaxWorldY() const;

    void Init();
    void UpdateViewPortWithMario();
    bool IsInViewPort(SMBbase &obj) const;
    void RestrictMarioX();

    void Collide(double timeDiff);
    void MoveOneStep(double timeDiff);
    void RunOneStep(double timeDiff);
};

#endif