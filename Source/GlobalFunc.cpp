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
		// ������ ���
		AEMtx33 scaleMtx;
		AEMtx33Scale(&scaleMtx, scaleX, scaleY);

		// ȸ�� ���
		AEMtx33 rotMtx;
		AEMtx33Rot(&rotMtx, rotation);

		// �̵� ���
		AEMtx33 transMtx;
		AEMtx33Trans(&transMtx, posX, posY);

		// ���� ��ȯ ���: Translate * Rotate * Scale
		AEMtx33 transform;
		AEMtx33Concat(&transform, &rotMtx, &scaleMtx);
		AEMtx33Concat(&transform, &transMtx, &transform);

		// ������ ����
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetColorToMultiply(1.f, 1.f, 1.f, 1.f);
		AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransform(transform.m);

		// �׸���
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}

	
	void FGameState::Draw()
	{
		switch (GameStateEnum)
		{
		case global::EGameStateEnum::SPLASH:
			Logo.Draw();
			break;
		case global::EGameStateEnum::MAIN_MENU:
			MainMenu.Draw();
			break;
		case global::EGameStateEnum::ANIMATION:
			Animation.Draw();
			break;
		case global::EGameStateEnum::PONG_RESET:
			Game.Init();
			break;
		case global::EGameStateEnum::PONG_GAME:
			Game.Draw();
			break;
		case global::EGameStateEnum::PONG_END:
			Game.EndGame();
			break;
		}
	}
	void FGameState::ChangeState(EGameStateEnum InEnum)
	{
		switch(GameStateEnum)
		{
		case global::EGameStateEnum::SPLASH:
			Logo.Exit();
			break;
		case global::EGameStateEnum::MAIN_MENU:
			MainMenu.Exit();
			break;
		case global::EGameStateEnum::ANIMATION:
			Animation.Draw();
			break;
		case global::EGameStateEnum::PONG_RESET:
			//Game.Exit();
			break;
		case global::EGameStateEnum::PONG_GAME:
			//Game.Exit();
			break;
		case global::EGameStateEnum::PONG_END:
			Game.Exit();
			break;
		}
		GameStateEnum = InEnum;
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
			Game.Draw();
			break;
		case global::EGameStateEnum::PONG_END:
			Game.EndGame();
			break;
		}
		
	}
}