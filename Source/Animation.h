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

캐릭터 상태에 따라 재생되는 애니메이션						<-- 완료

애니메이션 상태: 이동, 점프, 사망, 대기						<-- 완료

캐릭터 오브젝트가 화면 중앙에 배치된 상태로 시작함.			<-- 완료

스페이스바를 누르면 점프 (점프 할 때 소리도 남)				<-- 완료	

좌우 방향키로 걷기											<-- 완료

K 키를 누르면 즉시 죽음										<-- 완료

죽음 후 일정 시간이 지난 후 다시 재 시작					<-- 완료

*/