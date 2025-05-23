#include "PongGame.h"
#include <iomanip>
#include <sstream>

namespace ponggame
{
	std::string FormatTime(float seconds)
	{
		int totalSeconds = static_cast<int>(seconds);
		int minutes = totalSeconds / 60;
		int secs = totalSeconds % 60;

		std::ostringstream oss;
		oss << std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << secs;

		return oss.str();
	}

	AEGfxVertexList* CreateBoxMesh(u32 color = 0xFFFFFFFF)
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

	FGame Game;

	void Init()
	{
		Game.bIsRKeyPressed = false;
		Game.StartTime = AEGetTime(nullptr);
		Game.Ball.posX = 0.f;
		Game.Ball.posY = 0.f;
		if (Game.Ball.Mesh == nullptr)
		{
			Game.Ball.CreateBallMesh();
		}
		update();
	}
	
	void update()
	{
		s8 font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
		while (!Game.bIsRKeyPressed)
		{
			AESysFrameStart();
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			std::string Time = FormatTime(AEGetTime(nullptr) - Game.StartTime);
			f32 TimeW, TimeH;
			AEGfxGetPrintSize(font, Time.c_str(), 1.f, &TimeW, &TimeH);
			AEGfxPrint(font, Time.c_str(), -TimeW/2, 0.7f, 1.f, 1, 1, 1, 1);
			if (AEInputCheckTriggered(AEVK_R))
			{
				Game.bIsRKeyPressed = true;
				break;
			}
/*----------------Draw Random Box----------------*/
//remove later
			DrawSprite(CreateBoxMesh(), 200.f, 150.f, 100.f, 100.f, 0.f);
/*----------------Draw Random Box----------------*/
			DrawSprite(Game.Ball.Mesh, Game.Ball.posX, Game.Ball.posY, 100.f, 100.f, 0.f);
			AESysFrameEnd();
		}
		exit();
	}

	void exit()
	{
		if (Game.bIsRKeyPressed)
		{
			Init();
		}
	}
}