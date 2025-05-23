#include <math.h> // sin, cos
#include "Ball.h"
#include <iostream>
#define PI 3.14159265358979323846f
float radius = 0.5f;
ponggame::FBall::FBall()
{

}

void ponggame::FBall::CreateBallMesh(u32 color)
{
    const int sides = 32;


    AEGfxMeshStart();

    for (int i = 0; i < sides; ++i)
    {
        float angle1 = (2.0f * PI * i) / sides;
        float angle2 = (2.0f * PI * (i + 1)) / sides;

        float x0 = 0.0f, y0 = 0.0f;
        float x1 = cosf(angle1) * radius;
        float y1 = sinf(angle1) * radius;
        float x2 = cosf(angle2) * radius;
        float y2 = sinf(angle2) * radius;

        AEGfxTriAdd(
            x0, y0, color, 0.0f, 0.0f,
            x1, y1, color, 0.0f, 0.0f,
            x2, y2, color, 0.0f, 0.0f
        );
    }

    Mesh = AEGfxMeshEnd();
}

void ponggame::FBall::UpdatePosition(f32 dt)
{
    posX += dirX * dt;
    posY += dirY * dt;
    if (posX < -800.f + radius * 100 || posX > 800 - radius * 100)
    {
        dirX *= -1;
    }
        
    if (posY < -450.f + radius * 100 || posY > 450 - radius * 100)
    {
        dirY *= -1;
    }
    std::cout << "Ball X : " << posX << " Y : " << posY << std::endl;
}
