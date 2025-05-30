#pragma once
#include "AEEngine.h"
#include "GlobalFunc.h"
#include "RenderableState.h"
namespace mainmenu
{
	class FMainMenu : public renderablestate::FRenderableState
	{
	public:
		virtual void Init() override;
		virtual void Draw() override;
		virtual void Exit() override;

		global::FButton* ButtonA = nullptr;
		global::FButton* ButtonB = nullptr;

	};

	extern FMainMenu MainMenu;
}