#include "MainMenu.h"
#include "GlobalFunc.h"
namespace mainmenu
{
	FMainMenu MainMenu;

	void FMainMenu::Init()
	{
		ButtonA = new global::FButton("ButtonA", 300.f, 50.f, -0.5f, -0.5f);
		ButtonB = new global::FButton("ButtonB", 300.f, 50.f, 0.5f, -0.5f);
	}

	void FMainMenu::Draw()
	{
		AESysFrameStart();
		ButtonA->DrawButton();
		ButtonB->DrawButton();
		AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
		std::string Title = "PongGame";
		f32 TitleW, TitleH;
		AEGfxGetPrintSize(global::font, Title.c_str(), 1.f, &TitleW, &TitleH);
		AEGfxPrint(global::font, Title.c_str(), -TitleW / 2, 0.f, 1.f, 1, 1, 1, 1);
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			if (ButtonA->CheckButtonCollision())
			{
				global::GameState.GameStateEnum = global::EGameStateEnum::PONG_RESET;
				
			}
			else if (ButtonB->CheckButtonCollision())
			{
				global::GameState.GameStateEnum = global::EGameStateEnum::ANIMATION;
			}
		}
		AESysFrameEnd();
	}

	void FMainMenu::Exit()
	{
		if (ButtonA != nullptr)
		{
			delete ButtonA;
		}
		if (ButtonB != nullptr)
		{
			delete ButtonB;
		}
	}
}
