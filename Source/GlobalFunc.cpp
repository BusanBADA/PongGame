#include "AEEngine.h"
#include "GlobalFunc.h"
namespace global
{
	s8 font;
	FGameState GameState;

	AEGfxVertexList* CreateBoxMesh(u32 color)
	{
		AEGfxMeshStart();

		AEGfxTriAdd(
			-0.5f, -0.5f, color, 0.0f, 1.0f,  // bottom-left
			0.5f, -0.5f, color, 1.0f, 1.0f,  // bottom-right
			-0.5f, 0.5f, color, 0.0f, 0.0f); // top-left

		AEGfxTriAdd(
			0.5f, -0.5f, color, 1.0f, 1.0f,  // bottom-right
			0.5f, 0.5f, color, 1.0f, 0.0f,  // top-right
			-0.5f, 0.5f, color, 0.0f, 0.0f); // top-left

		return AEGfxMeshEnd();
	}

	void DrawSprite(AEGfxVertexList* mesh, float posX, float posY, float scaleX, float scaleY, float rotation)
	{
		// 스케일 행렬
		AEMtx33 scaleMtx;
		AEMtx33Scale(&scaleMtx, scaleX, scaleY);

		// 회전 행렬
		AEMtx33 rotMtx;
		AEMtx33Rot(&rotMtx, rotation);

		// 이동 행렬
		AEMtx33 transMtx;
		AEMtx33Trans(&transMtx, posX, posY);

		// 최종 변환 행렬: Translate * Rotate * Scale
		AEMtx33 transform;
		AEMtx33Concat(&transform, &rotMtx, &scaleMtx);
		AEMtx33Concat(&transform, &transMtx, &transform);

		// 렌더링 세팅
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetColorToMultiply(1.f, 1.f, 1.f, 1.f);
		AEGfxSetColorToAdd(0.f, 0.f, 0.f, 0.f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransform(transform.m);

		// 그리기
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}

	void FButton::DrawButton()
	{
		float WindowW = 1600 / 2;
		float WindowH = 900 / 2;
		DrawSprite(Mesh, WindowW * posX, WindowH * posY, sizeX, sizeY, 0);
		f32 ButtonTextW, ButtonTextH;
		AEGfxGetPrintSize(font, Text.c_str(), 1.f, &ButtonTextW, &ButtonTextH);
		AEGfxPrint(font, Text.c_str(), posX - (ButtonTextW / 2), posY - (ButtonTextH / 2), 1.f, 0, 0, 0, 1);
	}
	bool FButton::CheckButtonCollision()
	{
		const f32 screenWidth = 1600.0f;
		const f32 screenHeight = 900.0f;
		s32 MX;
		s32 MY;
		AEInputGetCursorPosition(&MX, &MY);
		f32 NDCX = (static_cast<f32>(MX) / screenWidth) * 2.0f - 1.0f;
		f32 NDCY = 1.0f - (static_cast<f32>(MY) / screenHeight) * 2.0f;
		f32 MousePosX = NDCX * 800;
		f32 MousePosY = NDCY * 450;
		if ((screenWidth/2) * posX - (sizeX / 2) <= NDCX * 800 && (screenWidth / 2) * posX + (sizeX / 2) >= NDCX * 800 && (screenHeight / 2) * posY - (sizeY / 2) <= NDCY * 450 && (screenHeight / 2) * posY + (sizeY / 2) >= NDCY * 450)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}