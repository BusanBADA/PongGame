
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "PongGame.h"

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

	bool bIsAnyKeyPressed = true;
	while (bIsAnyKeyPressed)
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
				bIsAnyKeyPressed = false;
				break;
			}
		}
		AESysFrameEnd();
	}
	while (AESysDoesWindowExist())
	{
		ponggame::Game.Init();
		ponggame::Game.Update();
		ponggame::Game.Exit();
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