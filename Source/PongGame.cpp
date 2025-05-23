#include "PongGame.h"
#include <iomanip>
#include <sstream>
#include <iostream>

#define PI 3.14159265358979323846f

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

	void ResolveBallBoxCollision(ponggame::FBall& ball, float boxX, float boxY, float boxW, float boxH)
	{
		// 1. 박스의 가장 가까운 점 계산 (클램핑)
		float closestX = std::fmax(boxX - boxW / 2, std::fmin(ball.posX, boxX + boxW / 2));
		float closestY = std::fmax(boxY - boxH / 2, std::fmin(ball.posY, boxY + boxH / 2));

		// 2. 벡터 차이
		float dx = ball.posX - closestX;
		float dy = ball.posY - closestY;

		float distanceSq = dx * dx + dy * dy;
		float radiusPx = ball.radius;

		if (distanceSq < radiusPx * radiusPx)
		{
			// 3. 더 큰 방향으로 반사
			if (fabs(dx) > fabs(dy))
			{
				// 좌우로 접근 → 수평 반사
				ball.dirX *= -1;
				ball.posX += (dx > 0 ? 1 : -1) * (radiusPx - fabs(dx)); // 튕겨냄
			}
			else
			{
				// 상하로 접근 → 수직 반사
				ball.dirY *= -1;
				ball.posY += (dy > 0 ? 1 : -1) * (radiusPx - fabs(dy));
			}
		}
	}


	FGame Game;

	void Init()
	{
		Game.bIsRKeyPressed = false;
		Game.StartTime = AEGetTime(nullptr);
		Game.DeltaTime = 0.f;
		Game.Ball.posX = 0.f;
		Game.Ball.posY = 0.f;
		if (Game.Ball.Mesh == nullptr)
		{
			Game.Ball.CreateBallMesh();
		}
		float angle = static_cast<float>(rand()) / RAND_MAX * PI * 2.0f;
		Game.Ball.dirX = cosf(angle);
		Game.Ball.dirY = sinf(angle);
		float Speed = 200.0f + static_cast<float>(rand()) / RAND_MAX * 300.0f;
		Game.Ball.dirX *= Speed;
		Game.Ball.dirY *= Speed;

		Game.LeftActor.score = 0;
		Game.LeftActor.posY = 0;
		Game.LeftActor.posX = 

		Game.RightActor.score = 0;

		update();
	}
	
	void update()
	{
		s8 font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
		f64 lastTime = AEGetTime(nullptr);
		while (!Game.bIsRKeyPressed)
		{
			AESysFrameStart();
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);

/*----------------DeltaTime----------------*/
			f64 currentTime = AEGetTime(nullptr);
			Game.DeltaTime = static_cast<f32>(currentTime - lastTime);
			lastTime = currentTime;
/*----------------DeltaTime----------------*/

/*----------------Draw Time----------------*/
			std::string Time = FormatTime(AEGetTime(nullptr) - Game.StartTime);
			f32 TimeW, TimeH;
			AEGfxGetPrintSize(font, Time.c_str(), 1.f, &TimeW, &TimeH);
			AEGfxPrint(font, Time.c_str(), -TimeW/2, 0.7f, 1.f, 1, 1, 1, 1);
/*----------------Draw Time----------------*/

/*----------------Restart----------------*/
			if (AEInputCheckTriggered(AEVK_R))
			{
				Game.bIsRKeyPressed = true;
				break;
			}
/*----------------Restart----------------*/

/*----------------Draw Random Box----------------*/
//remove later
			ResolveBallBoxCollision(Game.Ball, 200.f, 150.f, 100.f, 100.f);
			DrawSprite(CreateBoxMesh(), 200.f, 150.f, 100.f, 100.f, 0.f);
/*----------------Draw Random Box----------------*/

/*----------------CheckCollision----------------*/
			bool bIsHitLeft = false;
			bool bIsHitRight = false;
			Game.Ball.UpdatePosition(Game.DeltaTime, bIsHitLeft, bIsHitRight);
			if (bIsHitLeft)
			{
				Game.RightActor.score++;
				std::cout << Game.RightActor.score << std::endl;
			}
			if (bIsHitRight)
			{
				Game.LeftActor.score++;
				std::cout << Game.LeftActor.score << std::endl;
			}
/*----------------CheckCollision----------------*/

/*----------------Draw Ball----------------*/
			DrawSprite(Game.Ball.Mesh, Game.Ball.posX, Game.Ball.posY, 100.f, 100.f, 0.f);
/*----------------Draw Ball----------------*/
			
/*----------------Draw Time----------------*/
			std::string LeftScore = std::to_string(Game.LeftActor.score);
			f32 LeftScoreW, LeftScoreH;
			AEGfxGetPrintSize(font, LeftScore.c_str(), 1.f, &LeftScoreW, &LeftScoreH);
			AEGfxPrint(font, LeftScore.c_str(), -LeftScoreW / 2 - 0.5f, 0.7f, 1.f, 1, 1, 1, 1);
			std::string RightScore = std::to_string(Game.RightActor.score);
			f32 RightScoreW, RightScoreH;
			AEGfxGetPrintSize(font, RightScore.c_str(), 1.f, &RightScoreW, &RightScoreH);
			AEGfxPrint(font, RightScore.c_str(), -RightScoreW / 2 + 0.5f, 0.7f, 1.f, 1, 1, 1, 1);
/*----------------Draw Time----------------*/

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