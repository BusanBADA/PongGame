#pragma once
#include "AEEngine.h"
#include "RenderableState.h"
namespace animation
{
	
	class FAnimation : public renderablestate::FRenderableState
	{
	public:
		virtual void Init() override;
		virtual void Update() override;
		void Reset();
		virtual void Exit() override;

		f32 posX = 0.f;
		f32 posY = 0.f;
		f32 scaleX = 400.f;
		f32 scaleY = 400.f;
		u8 CurrentIndex = 0;
		const u8 MaxIndex = 8;
		const f32 sprite_uv_width = 1.f / 8.f;

		f64 RespawnTimer = 0.f;
		f64 AnimationFrameTimer = 0.f;
		const f64 AnmationFrameLimit = 0.2f;

		AEGfxVertexList* Mesh = nullptr;
		AEGfxTexture* IdelImage = nullptr;
		AEGfxTexture* DeathImage = nullptr;
		AEGfxTexture* JumpImage = nullptr;
		AEGfxTexture* WalkImage = nullptr;
		AEAudio JumpAudio;
		AEAudioGroup se;
		AEGfxTexture* CurrentImage = nullptr;

		bool bIsAButtonPressed = false;
		bool bIsDButtonPressed = false;

		bool bIsFacingRight = true;
		bool bIsIdel = true;
		bool bIsDead = false;
		bool bIsJumping = false;
		bool bIsWalking = false;
	};
}

/*
[Character Animation Spec]

ĳ���� ���¿� ���� ����Ǵ� �ִϸ��̼�						<-- �Ϸ�

�ִϸ��̼� ����: �̵�, ����, ���, ���						<-- �Ϸ�

ĳ���� ������Ʈ�� ȭ�� �߾ӿ� ��ġ�� ���·� ������.			<-- �Ϸ�

�����̽��ٸ� ������ ���� (���� �� �� �Ҹ��� ��)				<-- �Ϸ�	

�¿� ����Ű�� �ȱ�											<-- �Ϸ�

K Ű�� ������ ��� ����										<-- �Ϸ�

���� �� ���� �ð��� ���� �� �ٽ� �� ����					<-- �Ϸ�

*/