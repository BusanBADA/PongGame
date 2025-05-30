#pragma once
#include "AEEngine.h"
#include <string>

namespace button
{
	class FButton
	{
	public:
		FButton(std::string InText, f32 InSizeX = 30.f, f32 InSizeY = 30.f, f32 InPosX = 0.f, f32 InPosY = 0.f);
		AEGfxVertexList* Mesh = nullptr;
		std::string Text;
		f32 sizeX = 30.f;
		f32 sizeY = 30.f;
		f32 posX = 0.f;
		f32	posY = 0.f;
		void DrawButton();
		bool CheckButtonCollision();
	};
}