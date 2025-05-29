#include "Logo.h"
#include "GlobalFunc.h"
#include "PongGame.h"
namespace logo
{
	FLogo Logo;

	void FLogo::Init()
	{
		Image = AEGfxTextureLoad("Assets/Logo.png");
		Mesh = global::CreateBoxMesh();
	}

	void FLogo::Draw()
	{
		AESysFrameStart();
		global::GameState.PreGameTimer += global::GameState.DeltaTime;
		if (global::GameState.PreGameTimer <= 1.f)
		{
			//fade in
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			AEMtx33 scale = { 0 };
			AEMtx33Scale(&scale, 500.f, 500.f);
			AEMtx33 rotate = { 0 };
			AEMtx33Rot(&rotate, 0);
			AEMtx33 translate = { 0 };
			AEMtx33Trans(&translate, 0, 0);
			AEMtx33 transform = { 0 };
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxTextureSet(logo::Logo.Image, 0, 0);
			AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, global::GameState.PreGameTimer);
			AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetTransparency(1.0f);
			AEGfxTextureSet(logo::Logo.Image, 0, 0);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(logo::Logo.Mesh, AE_GFX_MDM_TRIANGLES);
			//std::string Title = "PongGame";
			//f32 TitleW, TitleH;
			//AEGfxGetPrintSize(font, Title.c_str(), 1.f, &TitleW, &TitleH);
			//AEGfxPrint(font, Title.c_str(), -TitleW / 2, 0.f, 1.f, 1, 1, 1, GameState.PreGameTimer);
		}
		else if (global::GameState.PreGameTimer <= 2.f)
		{
			//fade out
			AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			AEMtx33 scale = { 0 };
			AEMtx33Scale(&scale, 500.f, 500.f);
			AEMtx33 rotate = { 0 };
			AEMtx33Rot(&rotate, 0);
			AEMtx33 translate = { 0 };
			AEMtx33Trans(&translate, 0, 0);
			AEMtx33 transform = { 0 };
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxTextureSet(logo::Logo.Image, 0, 0);
			AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1 - (global::GameState.PreGameTimer - 1));
			AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetTransparency(1.0f);
			AEGfxTextureSet(logo::Logo.Image, 0, 0);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(logo::Logo.Mesh, AE_GFX_MDM_TRIANGLES);
			//AEGfxSetBackgroundColor(0.1f, 0.1f, 0.1f);
			//std::string Title = "PongGame";
			//f32 TitleW, TitleH;
			//AEGfxGetPrintSize(font, Title.c_str(), 1.f, &TitleW, &TitleH);
			//AEGfxPrint(font, Title.c_str(), -TitleW / 2, 0.f, 1.f, 1, 1, 1, 1 - (GameState.PreGameTimer - 1));
		}
		else
		{
			global::GameState.bIsPreGameState = false;
			global::GameState.bIsMainMenu = true;
		}

		for (u8 key = 0x01; key <= 0xFE; ++key)
		{
			if (key == 0x15 || key == 0x19)
			{
				continue;
			}
			if (AEInputCheckTriggered(key))
			{
				global::GameState.bIsPreGameState = false;
				global::GameState.bIsMainMenu = true;
				break;
			}
		}
		AESysFrameEnd();
	}

}