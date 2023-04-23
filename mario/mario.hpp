#ifndef MARIO_IS_INCLUDED
#define MARIO_IS_INCLUDED

#include "moveable.hpp"

class Mario : public Moveable
{
public:
    enum marioLocStatus
    {
        ON_GROUND,
        ON_AIR,
    };
    enum marioSizeStatus
    {
        SMALL,
        BIG,
        IMMORTAL,
    };
    int currentLocStatus = marioLocStatus::ON_GROUND;
    int currentSizeStatus = marioSizeStatus::SMALL;
    bool currentCanDash = false;
    bool currentVxHasChanged = false;
    bool currentIsRunning = false;
    int lives = 3;
    char hitResultAccumulator = 0;
    // m/s
    const float GRAVITY = 15;
    const float MAX_WALKING_VX = 10.0;
    const float MAX_DASHING_VX = 15.0;
    const float WALKING_ACC_X = 25.0;
    const float DASHING_ACC_X = 35.0;
    const float JUMP_ACC_Y = 40.0;
    const float NO_INPUT_DEACC_X = 20.0;
    const float MAX_VY = 25.0;
    const float JUMP_TOLERANCE_SEC = 0.3;
    const float EPSILON = 0.01;

    Mario();
    Mario(float x, float y, float width, float height, float bbxRatio, float vx, float vy);
    virtual void Init() override;
    void AccRight(double timeDiff);
    void AccLeft(double timeDiff);
    void Jump(double timeDiff);
    void NoInput(double timeDiff);
    void ApplyGravity(double timeDiff);
    virtual void MoveByTime(double timeDiff) override;
    void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    void CollisionCheckStart();
    void CollisionCheckEnd();
};

#endif