#pragma once

namespace renderablestate
{
	class FRenderableState
	{
		virtual void Init(){}
		virtual void Update(){}
		virtual void Exit(){}
	};
}