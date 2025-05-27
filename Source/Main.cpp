
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "PongGame.h"
#include <iostream>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);



    int gGameRunning = 1;

    // Initialization of your own variables go here

    // Using custom window procedure
    AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

    // Changing the window title
    AESysSetWindowTitle("PongGame");
	s8 font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);


	f64 lastTime = AEGetTime(nullptr);
	while (AESysDoesWindowExist())
	{
		f64 currentTime = AEGetTime(nullptr);
		ponggame::Game.DeltaTime = currentTime - lastTime;
		lastTime = currentTime;
		std::cout << 1/ ponggame::Game.DeltaTime << std::endl;

		if (ponggame::GameState.bIsPreGameState)
		{
			AESysFrameStart();
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			AEGfxPrint(font, "Press Any Key To Start", -0.5f, 0.4f, 1.f, 1, 1, 1, 1);
			for (u8 key = 0x01; key <= 0xFE; ++key)
			{
				if (key == 0x15 || key == 0x19)
				{
					continue;
				}
				if (AEInputCheckTriggered(key))
				{
					ponggame::GameState.bIsPreGameState = false;
					ponggame::GameState.bShouldResetGame = true;
					break;
				}
			}
			AESysFrameEnd();
		}
		if (ponggame::GameState.bShouldResetGame)
		{
			ponggame::Game.ResetGame();
		}
		if (ponggame::GameState.bIsGameRunning)
		{
			ponggame::Game.Update();
		}
		if (ponggame::GameState.bIsGameEnded)
		{
			ponggame::Game.EndGame();
		}
	}
	if (ponggame::Game.LeftActor.Mesh != nullptr)
	{
		AEGfxMeshFree(ponggame::Game.LeftActor.Mesh);
	}
	if (ponggame::Game.RightActor.Mesh != nullptr)
	{
		AEGfxMeshFree(ponggame::Game.RightActor.Mesh);
	}
	if (ponggame::Game.Ball.Mesh != nullptr)
	{
		AEGfxMeshFree(ponggame::Game.Ball.Mesh);
	}
	AESysExit();
	return 0;
}