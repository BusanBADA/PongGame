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

	void FMainMenu::Free()
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