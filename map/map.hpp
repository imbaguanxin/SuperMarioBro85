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
    Map();

    void Init();
    void Collide(double timeDiff);
    void MoveOneStep(double timeDiff);
    void RunOneStep(double timeDiff);
};

#endif