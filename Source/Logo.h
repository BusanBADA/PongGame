#pragma once
#include "AEEngine.h"

namespace logo
{
	class FLogo
	{
	public:
		void Init();
		void Draw();
		AEGfxTexture* Image = nullptr;
		AEGfxVertexList* Mesh = nullptr;
	};

	extern FLogo Logo;
}