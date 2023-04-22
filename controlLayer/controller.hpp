#ifndef CONTROLLER_IS_INCLUDED
#define CONTROLLER_IS_INCLUDED

#include "textureData.hpp"
#include "base.hpp"
#include "map.hpp"
class Controller
{
public:
    bool term = false;
    double timePassed = 0;
    TextureData td;
    Map map;
    float viewPortInPhysicalHeight, viewPortInPhysicalWidth;
    float viewPortInPhysicalX, viewPortInPhysicalY; // left bottom corner
    float maxWorldX, maxWorldY;
    float screenWidth, screenHeight;
    std::vector<SMBbase> undergrounds;
    Controller();
    ~Controller();
    void Init();
    bool IsTerminated(void) const;
    void RunOneStep(double timeDiff);
    void Draw(void);

    float W2VXRatio(float worldx) const;
    float W2VYRatio(float worldy) const;

    bool IsInViewPort(SMBbase &obj) const;

    void UpdateViewPortWithMario();
    void PassViewPortToMap();
}

#endif
