#line 1 "/Users/om/Downloads/ARDUBOY/Friction/camera.h"
#pragma once

#include <stdint.h>

class Camera
{
    public:
        float x;
        float y;

        bool isLeft;
        bool isRight;

        void updateCamera();
};

extern Camera camera;
