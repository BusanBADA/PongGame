#include "Button.h"
#include "GlobalFunc.h"
namespace button
{
	FButton::FButton(std::string InText, f32 InSizeX, f32 InSizeY, f32 InPosX, f32 InPosY)
	{
		if (Mesh == nullptr)
		{
			Mesh = global::CreateBoxMesh();
		}
		Text = InText;
		sizeX = InSizeX;
		sizeY = InSizeY;
		posX = InPosX;
		posY = InPosY;
	}
	void FButton::DrawButton()
	{
		float WindowW = 1600 / 2;
		float WindowH = 900 / 2;
		global::DrawSprite(Mesh, WindowW * posX, WindowH * posY, sizeX, sizeY, 0);
		f32 ButtonTextW, ButtonTextH;
		AEGfxGetPrintSize(global::font, Text.c_str(), 1.f, &ButtonTextW, &ButtonTextH);
		AEGfxPrint(global::font, Text.c_str(), posX - (ButtonTextW / 2), posY - (ButtonTextH / 2), 1.f, 0, 0, 0, 1);
	}
	bool FButton::CheckButtonCollision()
	{
		const f32 screenWidth = 1600.0f;
		const f32 screenHeight = 900.0f;
		s32 MX;
		s32 MY;
		AEInputGetCursorPosition(&MX, &MY);
		f32 NDCX = (static_cast<f32>(MX) / screenWidth) * 2.0f - 1.0f;
		f32 NDCY = 1.0f - (static_cast<f32>(MY) / screenHeight) * 2.0f;
		f32 MousePosX = NDCX * 800;
		f32 MousePosY = NDCY * 450;
		if ((screenWidth / 2) * posX - (sizeX / 2) <= NDCX * 800 && (screenWidth / 2) * posX + (sizeX / 2) >= NDCX * 800 && (screenHeight / 2) * posY - (sizeY / 2) <= NDCY * 450 && (screenHeight / 2) * posY + (sizeY / 2) >= NDCY * 450)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}