#include "PongGame.h"
#include "GlobalFunc.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Logo.h"
#include "MainMenu.h"
namespace ponggame
{
	FGame Game;

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



	void FGame::ResetGame()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		bIsRKeyPressed = false;
		StartTime = AEGetTime(nullptr);
		global::GameState.DeltaTime = 0.f;
		Ball.posX = 0.f;
		Ball.posY = 0.f;
		if (Ball.Mesh == nullptr)
		{
			Ball.CreateBallMesh();
		}
		float angle = static_cast<float>(rand()) / PI;
//		std::cout << angle;
		Ball.dirX = cosf(angle);
		Ball.dirY = sinf(angle);
		float Speed = 200.0f + static_cast<float>(rand()) / RAND_MAX * 300.0f;
		Ball.dirX *= Speed;
		Ball.dirY *= Speed;

		LeftActor.score = 0;
		LeftActor.posY = 0;
		LeftActor.posX = -800.f*(2.f / 3.f);
		if (LeftActor.Mesh == nullptr)
		{
			LeftActor.Mesh = global::CreateBoxMesh();
		}

		RightActor.score = 0;
		RightActor.posY = 0;
		RightActor.posX = +800.f * (2.f / 3.f);
		if (RightActor.Mesh == nullptr)
		{
			RightActor.Mesh = global::CreateBoxMesh();
		}

		RightActor.score = 0;
		global::GameState.bIsGameEnded = false;
		global::GameState.bIsGameRunning = true;
		global::GameState.bShouldResetGame = false;
	}
	
	void FGame::Update()
	{
		if (!bIsRKeyPressed && AESysDoesWindowExist())
		{
			AESysFrameStart();
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);

			s32 MX;
			s32 MY;
			AEInputGetCursorPosition(&MX, &MY);
			const f32 screenWidth = 1600.0f;
			const f32 screenHeight = 900.0f;

			// screen → Normalized Device Coordinate 변환
			f32 NDCX = (static_cast<f32>(MX) / screenWidth) * 2.0f - 1.0f;
			f32 NDCY = 1.0f - (static_cast<f32>(MY) / screenHeight) * 2.0f; // y inverse
			//f32 NDCY = (static_cast<f32>(MY) / screenHeight) * 2.0f - 1.0f;
//			std::cout << "MouseCoord : " << NDCY * 400 <<" RightActorCoord : " << RightActor.posY<< std::endl;
			//if (RightActor.posY < NDCY * 400)
			//{
			//	if (NDCY * 400 - RightActor.posY < 10.0f)
			//	{
			//		RightActor.posY -= NDCY * 400 - RightActor.posY;
			//	}
			//	else
			//	{
			//		RightActor.posY -= 10.f;
			//	}
			//}
			//else if (RightActor.posY > NDCY * 400)
			//{
			//	if (RightActor.posY - NDCY * 400 < 10.0f)
			//	{
			//		RightActor.posY += RightActor.posY - NDCY * 400;
			//	}
			//	else
			//	{
			//		RightActor.posY += 10.f;
			//	}
			//}
			RightActor.posY = NDCY *400;
			if (RightActor.posY < -450 + RightActor.sizeY / 2)//clamp
			{
				RightActor.posY = -450 + RightActor.sizeY / 2;
			}
			else if (RightActor.posY > 450 - RightActor.sizeY / 2)
			{
				RightActor.posY = 450 - RightActor.sizeY / 2;
			}

			if (AEInputCheckCurr(AEVK_W))
			{
				LeftActor.posY += 20.0f;
			}
			else if (AEInputCheckCurr(AEVK_S))
			{
				LeftActor.posY -= 20.0f;
			}
			if (LeftActor.posY < -450 + LeftActor.sizeY / 2)//clamp
			{
				LeftActor.posY = -450 + LeftActor.sizeY / 2;
			}
			else if (LeftActor.posY > 450 - LeftActor.sizeY / 2)
			{
				LeftActor.posY = 450 - LeftActor.sizeY / 2;
			}

/*----------------Restart----------------*/
			if (AEInputCheckTriggered(AEVK_R))
			{
				bIsRKeyPressed = true;
			}
/*----------------Restart----------------*/


/*----------------Draw Time----------------*/
			std::string Time = FormatTime(AEGetTime(nullptr) - StartTime);
			f32 TimeW, TimeH;
			AEGfxGetPrintSize(global::font, Time.c_str(), 1.f, &TimeW, &TimeH);
			AEGfxPrint(global::font, Time.c_str(), -TimeW/2, 0.7f, 1.f, 1, 1, 1, 1);
/*----------------Draw Time----------------*/

/*----------------Draw Box----------------*/
//remove later
			ResolveBallBoxCollision(Ball, LeftActor.posX, LeftActor.posY, LeftActor.sizeX, LeftActor.sizeY);
			ResolveBallBoxCollision(Ball, RightActor.posX, RightActor.posY, RightActor.sizeX, RightActor.sizeY);
			global::DrawSprite(LeftActor.Mesh, LeftActor.posX, LeftActor.posY, LeftActor.sizeX, LeftActor.sizeY, 0.f);
			global::DrawSprite(RightActor.Mesh, RightActor.posX, RightActor.posY, RightActor.sizeX, RightActor.sizeY, 0.f);
/*----------------Draw Box----------------*/

/*----------------Draw Random Box----------------*/
			//DrawSprite(global::CreateBoxMesh(), 200.f, 150.f, 100.f, 100.f, 0.f);
/*----------------Draw Random Box----------------*/

/*----------------CheckCollision----------------*/
			bool bIsHitLeft = false;
			bool bIsHitRight = false;
			Ball.UpdatePosition(global::GameState.DeltaTime, bIsHitLeft, bIsHitRight);
			if (bIsHitLeft)
			{
				RightActor.score++;
				if (RightActor.score > 10)
				{
					global::GameState.bIsGameRunning = false;
					global::GameState.bIsGameEnded = true;
				}
			}
			if (bIsHitRight)
			{
				LeftActor.score++;
				if (LeftActor.score > 10)
				{
					global::GameState.bIsGameRunning = false;
					global::GameState.bIsGameEnded = true;
				}
			}
/*----------------CheckCollision----------------*/

/*----------------Draw Ball----------------*/
			global::DrawSprite(Ball.Mesh, Ball.posX, Ball.posY, 100.f, 100.f, 0.f);
/*----------------Draw Ball----------------*/
			
/*----------------Draw Time----------------*/
			std::string LeftScore = std::to_string(LeftActor.score);
			f32 LeftScoreW, LeftScoreH;
			AEGfxGetPrintSize(global::font, LeftScore.c_str(), 1.f, &LeftScoreW, &LeftScoreH);
			AEGfxPrint(global::font, LeftScore.c_str(), -LeftScoreW / 2 - 0.5f, 0.7f, 1.f, 1, 1, 1, 1);
			std::string RightScore = std::to_string(RightActor.score);
			f32 RightScoreW, RightScoreH;
			AEGfxGetPrintSize(global::font, RightScore.c_str(), 1.f, &RightScoreW, &RightScoreH);
			AEGfxPrint(global::font, RightScore.c_str(), -RightScoreW / 2 + 0.5f, 0.7f, 1.f, 1, 1, 1, 1);
/*----------------Draw Time----------------*/

			AESysFrameEnd();
		}
		else if (bIsRKeyPressed)
		{
			global::GameState.bShouldResetGame = true;
		}
	}

	void FGame::EndGame()
	{
		if (!bIsRKeyPressed && AESysDoesWindowExist())
		{
			AESysFrameStart();
			EndGameTimer += global::GameState.DeltaTime;
			if (EndGameTimer > 3.f)
			{
				global::GameState.bIsMainMenu = true;
				global::GameState.bIsGameEnded = false;
				EndGameTimer = 0.f;
			}
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			if (LeftActor.score > 10)
			{
				std::string str = "Left Player Wins";
				f32 strW, strH;
				AEGfxGetPrintSize(global::font, str.c_str(), 1.f, &strW, &strH);
				AEGfxPrint(global::font, str.c_str(), -(strW / 2), 0.7f, 1.f, 1, 1, 1, 1);
			}
			else
			{
				std::string str = "Right Player Wins";
				f32 strW, strH;
				AEGfxGetPrintSize(global::font, str.c_str(), 1.f, &strW, &strH);
				AEGfxPrint(global::font, str.c_str(), -(strW / 2), 0.7f, 1.f, 1, 1, 1, 1);
			}
			if (AEInputCheckTriggered(AEVK_R))
			{
				bIsRKeyPressed = true;
			}
			AESysFrameEnd();
		}
		if (bIsRKeyPressed)
		{
			global::GameState.bShouldResetGame = true;
		}
	}

}