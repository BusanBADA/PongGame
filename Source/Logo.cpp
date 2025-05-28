#include "Logo.h"
#include "GlobalFunc.h"
namespace logo
{
	FLogo Logo;

	void FLogo::Init()
	{
		Image = AEGfxTextureLoad("Assets/Logo.png");
		Mesh = global::CreateBoxMesh();
	}

}