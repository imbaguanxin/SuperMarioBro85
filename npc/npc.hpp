#ifndef ENEMY_IS_INCLUDED
#define ENEMY_IS_INCLUDED

#include "moveable.hpp"
#include "mario.hpp"
class NPC : public Moveable
{
public:
    NPC();
    void Init();
    void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    virtual void CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff);
};

#endif