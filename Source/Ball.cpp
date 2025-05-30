#include <math.h> // sin, cos
#include "Ball.h"
#include <iostream>

namespace ball
{
    void FBall::CreateBallMesh(u32 color)
    {
        const int sides = 32;


        AEGfxMeshStart();

        for (int i = 0; i < sides; ++i)
        {
            float angle1 = (2.0f * PI * i) / sides;
            float angle2 = (2.0f * PI * (i + 1)) / sides;

            float x0 = 0.0f, y0 = 0.0f;
            float x1 = cosf(angle1) * (radius / 100);
            float y1 = sinf(angle1) * (radius / 100);
            float x2 = cosf(angle2) * (radius / 100);
            float y2 = sinf(angle2) * (radius / 100);

            AEGfxTriAdd(
                x0, y0, color, 0.0f, 0.0f,
                x1, y1, color, 0.0f, 0.0f,
                x2, y2, color, 0.0f, 0.0f
            );
        }

        Mesh = AEGfxMeshEnd();
    }

    void FBall::UpdatePosition(f32 dt, bool& bIsHitLeft, bool& bIsHitRight)
    {
        posX += dirX * dt;
        posY += dirY * dt;
        if (posX < -800.f + radius)
        {
            dirX *= -1;
            bIsHitLeft = true;
        }
        if (posX > 800 - radius)
        {
            dirX *= -1;
            bIsHitRight = true;
        }
        if (posY < -450.f + radius || posY > 450 - radius)
        {
            dirY *= -1;
        }
        //      debug
        //    std::cout << "Ball X : " << posX << " Y : " << posY << std::endl;
    }

}
