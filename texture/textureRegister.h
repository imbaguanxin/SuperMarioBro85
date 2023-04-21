#ifndef TEXTURE_REGISTER_IS_INCLUDED
#define TEXTURE_REGISTER_IS_INCLUDED

const static float TEX_COL_LEN = 1. / 23.;
const static float TEX_ROW_LEN = 1. / 13.;
const static float TEX_X_PIX_CNT = 220.;
const static float TEX_Y_PIX_CNT = 384.;

class TextureRegister
{
public:
    // all data: {xmin ymin xmax ymax}
    // mario
    const float SMALL_MARIO_STAND[4] = {0 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 16 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_WALK_0[4] = {17 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 33 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_WALK_1[4] = {34 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 50 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_WALK_2[4] = {51 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 67 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_JUMP[4] = {85 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 101 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_GG[4] = {102 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 118 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};

    const float LARGE_MARIO_STAND[4] = {0 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 16 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_WALK_0[4] = {17 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 33 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_WALK_1[4] = {34 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 50 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_WALK_2[4] = {51 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 67 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_JUMP[4] = {85 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 101 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_GG[4] = {102 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 118 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
};

#endif