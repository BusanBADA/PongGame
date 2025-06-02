#pragma once
#include "AEEngine.h"
#include "Button.h"
#include "RenderableState.h"
namespace mainmenu
{
	class FMainMenu : public renderablestate::FRenderableState
	{
	public:
		virtual void Init() override;
		virtual void Update() override;
		virtual void Exit() override;

		button::FButton* ButtonA = nullptr;
		button::FButton* ButtonB = nullptr;

	};
}