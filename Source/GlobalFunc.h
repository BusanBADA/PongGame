#pragma once
#include "AEEngine.h"
#include "string"
#include "Logo.h"
#include "Animation.h"
#include "MainMenu.h"
#include "PongGame.h"
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
		void Draw();
		void ChangeState(EGameStateEnum InEnum);

		f64 PreGameTimer = 0.f;
		f64 DeltaTime = 0.f;
		
	private:
		EGameStateEnum GameStateEnum;
		logo::FLogo Logo;
		animation::FAnimation Animation;
		mainmenu::FMainMenu MainMenu;
		ponggame::FGame Game;
	};

	

	extern s8 font;
	extern FGameState GameState;
}