#pragma once
#include "AEEngine.h"
#include "string"
namespace global
{
	AEGfxVertexList* CreateBoxMesh(u32 color = 0xFFFFFFFF);
	void DrawSprite(AEGfxVertexList* mesh, float posX, float posY, float scaleX, float scaleY, float rotation);

	enum EGameStateEnum
	{
		SPLASH,
		MAIN_MENU,
		ANIMATION,
		PONG_GAME,
		PONG_END,
		PONG_RESET//TODO : remove later
	};

	class FGameState
	{
	public:
		EGameStateEnum GameStateEnum = EGameStateEnum::SPLASH;

		f64 PreGameTimer = 0.f;
		f64 DeltaTime = 0.f;
	};

	

	class FButton
	{
	public:
		FButton(std::string InText, f32 InSizeX = 30.f, f32 InSizeY = 30.f, f32 InPosX = 0.f, f32 InPosY = 0.f)
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
		AEGfxVertexList* Mesh = nullptr;
		std::string Text;
		f32 sizeX = 30.f;
		f32 sizeY = 30.f;
		f32 posX = 0.f;
		f32	posY = 0.f;
		void DrawButton();
		bool CheckButtonCollision();
	};

	extern s8 font;
	extern FGameState GameState;
}