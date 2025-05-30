#pragma once
#include "AEEngine.h"
#include "RenderableState.h"
namespace logo
{
	class FLogo : public renderablestate::FRenderableState
	{
	public:
		virtual void Init() override;
		virtual void Draw() override;
		virtual void Exit() override;
		AEGfxTexture* Image = nullptr;
		AEGfxVertexList* Mesh = nullptr;
	};
}