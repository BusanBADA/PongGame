#include "AEEngine.h"
namespace ponggame
{
	class FBall
	{
	public:
		FBall();

		AEGfxVertexList* Mesh = nullptr;
		f32 posX;
		f32 posY;
		void CreateBallMesh(u32 color = 0xFFFFFFFF);
	};
}