#include "Animation.h"
#include "GlobalFunc.h"

namespace animation
{
	void FAnimation::Init()
	{
        AEGfxMeshStart();

        const f32 sprite_uv_width = 1.f / (MaxIndex+1);
        AEGfxTriAdd(
            -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1, // bottom left
            0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, 1, // bottom right 
            -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // top left

        AEGfxTriAdd(
            0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, 1, // bottom right 
            0.5f, 0.5f, 0xFFFFFFFF, sprite_uv_width, 0.0f,   // top right
            -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // bottom left


        // Saving the mesh (list of triangles) in pMesh
        Mesh = AEGfxMeshEnd();
		IdelImage = AEGfxTextureLoad("Assets/idle_right_down.png");
		DeathImage = AEGfxTextureLoad("Assets/death_normal_right_down.png");
		JumpImage = AEGfxTextureLoad("Assets/Jump_Right_Down.png");
		WalkImage = AEGfxTextureLoad("Assets/walk_right_down.png");
        JumpAudio = AEAudioLoadMusic("Assets/jump.wav");
        CurrentImage = IdelImage;
        se = AEAudioCreateGroup();
	}
    void FAnimation::Draw()
    {
        AESysFrameStart();

        if (!bIsDead)
        {
            if (!bIsJumping && AEInputCheckCurr(AEVK_SPACE))
            {
                CurrentImage = JumpImage;
                CurrentIndex = 0;
                AnimationFrameTimer = 0.f;
                AEAudioPlay(JumpAudio, se, 1.f, 1.f, 0);
                bIsJumping = true;
            }

            bool isMoving = false;
            if (AEInputCheckCurr(AEVK_A))
            {
                if (!bIsJumping && CurrentImage == IdelImage)
                {
                    CurrentImage = WalkImage;
                    CurrentIndex = 0;
                    AnimationFrameTimer = 0.f;
                }
                bIsFacingRight = false;
                bIsAButtonPressed = true;
                bIsDButtonPressed = false;
                posX -= 5.f;
                isMoving = true;
            }
            else if (AEInputCheckCurr(AEVK_D))
            {
                if (!bIsJumping && CurrentImage == IdelImage)
                {
                    CurrentImage = WalkImage;
                    CurrentIndex = 0;
                    AnimationFrameTimer = 0.f;
                }
                bIsFacingRight = true;
                bIsAButtonPressed = false;
                bIsDButtonPressed = true;
                posX += 5.f;
                isMoving = true;
            }
            else
            {
                bIsAButtonPressed = false;
                bIsDButtonPressed = false;
            }

            if (!bIsJumping && !isMoving)
            {
                CurrentImage = IdelImage;
            }
        }
        if (AEInputCheckCurr(AEVK_K))
        {
            bIsDead = true;
            
            CurrentImage = DeathImage;
            CurrentIndex = 0;
            AnimationFrameTimer = 0.f;
            bIsAButtonPressed = false;
            bIsDButtonPressed = false;
        }

        if (bIsJumping && !bIsDead)
        {
            if (CurrentIndex == MaxIndex - 1)
            {
                bIsJumping = false;
                CurrentImage = IdelImage;
            }
        }

        if (bIsDead)
        {
            if (CurrentIndex == MaxIndex - 1)
            {
                AnimationFrameTimer = 0.f;
                RespawnTimer += global::GameState.DeltaTime;
                if (RespawnTimer > 2)
                {
                    Reset();
                }
            }
        }

        AnimationFrameTimer += global::GameState.DeltaTime;
        if (AnimationFrameTimer > AnmationFrameLimit)
        {
            CurrentIndex = ++CurrentIndex % MaxIndex;
            AnimationFrameTimer = 0.f;
        }

        f32 current_sprite_uv_offset_x = sprite_uv_width * (CurrentIndex % MaxIndex);
        f32 current_sprite_uv_offset_y = 0.f;

        AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
        AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetTransparency(1.0f);

        AEGfxTextureSet(CurrentImage, current_sprite_uv_offset_x, current_sprite_uv_offset_y);

        AEMtx33 scale, final;
        f32 scaleX = bIsFacingRight ? 400.f : -400.f;
        AEMtx33Scale(&scale, scaleX, 400.f);
        AEMtx33TransApply(&final, &scale, posX, posY);
        AEGfxSetTransform(final.m);

        AEGfxMeshDraw(Mesh, AE_GFX_MDM_TRIANGLES);
        AESysFrameEnd();
    }
    void FAnimation::Reset()
    {
        posX = 0.f;
        posY = 0.f;
        CurrentIndex = 0;
        RespawnTimer = 0.f;
        AnimationFrameTimer = 0.f;

        bIsFacingRight = true;
        bIsIdel = true;
        bIsDead = false;
        bIsJumping = false;
        bIsWalking = false;
        CurrentImage = IdelImage;
    }
    void FAnimation::Exit()
    {
        if (Mesh!=nullptr)
        {
            delete Mesh;
        }
    }
}


