#pragma once
#include "AEEngine.h"

namespace ball
{
	class FBall
	{
	public:

		AEGfxVertexList* Mesh = nullptr;
		f32 radius = 50.f;
		f32 posX;
		f32 posY;
		f32 dirX;
		f32 dirY;
		void CreateBallMesh(u32 color = 0xFFFFFFFF);

		void UpdatePosition(f32 dt, bool& bIsHitLeft, bool& bIsHitRight);
	};
}