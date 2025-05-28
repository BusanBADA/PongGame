#pragma once
#include "AEEngine.h"
#include "GlobalFunc.h"
namespace mainmenu
{
	class FMainMenu
	{
	public:
		void Init();
		void Free();

		global::FButton* ButtonA = nullptr;
		global::FButton* ButtonB = nullptr;

	};

	extern FMainMenu MainMenu;
}