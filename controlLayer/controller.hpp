#ifndef CONTROLLER_IS_INCLUDED
#define CONTROLLER_IS_INCLUDED

#include "textureData.hpp"
#include "backgroundRenderer.hpp"
#include "base.hpp"
#include "map.hpp"
class Controller
{
public:
    bool term = false;
    double timePassed = 0;
    TextureData td;
    Map map;
    float screenWidth, screenHeight;
    BackgroundRenderer bgRenderer;
    Controller();
    ~Controller();
    void Init();
    void InitTexture();
    bool IsTerminated(void) const;
    void RunOneStep(double timeDiff);

    void Draw(void);
    void DrawBackground();
    float W2VXRatio(float worldx) const;
    float W2VYRatio(float worldy) const;
};

#endif
