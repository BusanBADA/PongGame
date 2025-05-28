#pragma once
#include "AEEngine.h"

namespace logo
{
	class FLogo
	{
	public:
		void Init();
		AEGfxTexture* Image = nullptr;
		AEGfxVertexList* Mesh = nullptr;
	};

	extern FLogo Logo;
}