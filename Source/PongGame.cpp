#include "PongGame.h"
#include <iomanip>
#include <sstream>

namespace ponggame
{
	std::string FormatTime(float seconds)
	{
		int totalSeconds = static_cast<int>(seconds);
		int minutes = totalSeconds / 60;
		int secs = totalSeconds % 60;

		std::ostringstream oss;
		oss << std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << secs;

		return oss.str();
	}

	FGame Game;

	void Init()
	{
		Game.bIsRKeyPressed = false;
		Game.StartTime = AEGetTime(nullptr);
		update();
	}
	
	void update()
	{
		s8 font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
		while (!Game.bIsRKeyPressed)
		{
			AESysFrameStart();
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			std::string Time = FormatTime(AEGetTime(nullptr) - Game.StartTime);
			f32 TimeW, TimeH;
			AEGfxGetPrintSize(font, Time.c_str(), 1.f, &TimeW, &TimeH);
			AEGfxPrint(font, Time.c_str(), -TimeW/2, 0.7f, 1.f, 1, 1, 1, 1);
			if (AEInputCheckTriggered(AEVK_R))
			{
				Game.bIsRKeyPressed = true;
				break;
			}
			AESysFrameEnd();
		}
		exit();
	}

	void exit()
	{
		if (Game.bIsRKeyPressed)
		{
			Init();
		}
	}
}