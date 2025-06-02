#include "AEEngine.h"
#include "GlobalFunc.h"
#include "PongGame.h"
#include "Logo.h"
#include "MainMenu.h"
#include "Animation.h"
namespace global
{
	s8 font;
	FGameState GameState;

	AEGfxVertexList* CreateBoxMesh(u32 color)
	{
		AEGfxMeshStart();

		AEGfxTriAdd(
			-0.5f, -0.5f, color, 0.0f, 1.0f,  // bottom-left
			0.5f, -0.5f, color, 1.0f, 1.0f,  // bottom-right
			-0.5f, 0.5f, color, 0.0f, 0.0f); // top-left

		AEGfxTriAdd(
			0.5f, -0.5f, color, 1.0f, 1.0f,  // bottom-right
			0.5f, 0.5f, color, 1.0f, 0.0f,  // top-right
			-0.5f, 0.5f, color, 0.0f, 0.0f); // top-left

		return AEGfxMeshEnd();
	}

	void DrawSprite(AEGfxVertexList* mesh, float posX, float posY, float scaleX, float scaleY, float rotation)
	{
		// 스케일 행렬
		AEMtx33 scaleMtx;
		AEMtx33Scale(&scaleMtx, scaleX, scaleY);

		// 회전 행렬
		AEMtx33 rotMtx;
		AEMtx33Rot(&rotMtx, rotation);

		// 이동 행렬
		AEMtx33 transMtx;
		AEMtx33Trans(&transMtx, posX, posY);

		// 최종 변환 행렬: Translate * Rotate * Scale
		AEMtx33 transform;
		AEMtx33Concat(&transform, &rotMtx, &scaleMtx);
		AEMtx33Concat(&transform, &transMtx, &transform);

		// 렌더링 세팅
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetColorToMultiply(1.f, 1.f, 1.f, 1.f);
		AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransform(transform.m);

		// 그리기
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}

	
	void FGameState::Update()
	{
		if (GameStateEnum != PrevGameStateEnum)
		{
			switch (GameStateEnum)
			{
			case global::EGameStateEnum::SPLASH:
				Logo.Exit();
				break;
			case global::EGameStateEnum::MAIN_MENU:
				MainMenu.Exit();
				break;
			case global::EGameStateEnum::ANIMATION:
				Animation.Exit();
				break;
			case global::EGameStateEnum::PONG_RESET:
				break;
			case global::EGameStateEnum::PONG_GAME:
				break;
			case global::EGameStateEnum::PONG_END:
				Game.Exit();
				break;
			}
			GameStateEnum = PrevGameStateEnum;
			switch (GameStateEnum)
			{
			case global::EGameStateEnum::SPLASH:
				Logo.Init();
				break;
			case global::EGameStateEnum::MAIN_MENU:
				MainMenu.Init();
				break;
			case global::EGameStateEnum::ANIMATION:
				Animation.Init();
				break;
			case global::EGameStateEnum::PONG_RESET:
				Game.Init();
				break;
			case global::EGameStateEnum::PONG_GAME:
				Game.Update();
				break;
			case global::EGameStateEnum::PONG_END:
				Game.UpdateEndGame();
				break;
			}
		}
		switch (GameStateEnum)
		{
		case global::EGameStateEnum::SPLASH:
			Logo.Update();
			break;
		case global::EGameStateEnum::MAIN_MENU:
			MainMenu.Update();
			break;
		case global::EGameStateEnum::ANIMATION:
			Animation.Update();
			break;
		case global::EGameStateEnum::PONG_RESET:
			Game.ResetGame();
			break;
		case global::EGameStateEnum::PONG_GAME:
			Game.Update();
			break;
		case global::EGameStateEnum::PONG_END:
			Game.UpdateEndGame();
			break;
		}
	}
	void FGameState::ChangeState(EGameStateEnum InEnum)
	{
		PrevGameStateEnum = InEnum;
	}
}