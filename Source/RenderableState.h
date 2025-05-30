#pragma once

namespace renderablestate
{
	class FRenderableState
	{
		virtual void Init(){}
		virtual void Draw(){}
		virtual void Exit(){}
	};
}