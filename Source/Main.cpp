
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "PongGame.h"
#include "Logo.h"
#include "MainMenu.h"
#include "Animation.h"
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
	global::font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);

	mainmenu::MainMenu.Init();
	logo::Logo.Init();
	animation::Animation.Init();
	f64 lastTime = AEGetTime(nullptr);
	while (AESysDoesWindowExist())
	{
		f64 currentTime = AEGetTime(nullptr);
		global::GameState.DeltaTime = currentTime - lastTime;
		lastTime = currentTime;
//		std::cout << 1/ ponggame::Game.DeltaTime << std::endl;

		if (global::GameState.bIsPreGameState)
		{
			logo::Logo.Draw();
		}
		if (global::GameState.bIsMainMenu)
		{
			mainmenu::MainMenu.Draw();
		}
		if (global::GameState.bIsAnimation)
		{
			animation::Animation.Draw();
		}
		if (global::GameState.bShouldResetGame)
		{
			ponggame::Game.ResetGame();
		}
		if (global::GameState.bIsGameRunning)
		{
			ponggame::Game.Update();
		}
		if (global::GameState.bIsGameEnded)
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
	mainmenu::MainMenu.Free();
	AESysExit();
	return 0;
}