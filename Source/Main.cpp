
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "GlobalFunc.h"
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

	f64 lastTime = AEGetTime(nullptr);
	global::GameState.ChangeState(global::EGameStateEnum::SPLASH);
	while (AESysDoesWindowExist())
	{
		f64 currentTime = AEGetTime(nullptr);
		global::GameState.DeltaTime = currentTime - lastTime;
		lastTime = currentTime;
//		std::cout << 1/ ponggame::Game.DeltaTime << std::endl;

		global::GameState.Draw();
	}
	AESysExit();
	return 0;
}