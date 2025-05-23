#include "AEEngine.h"
#include "Ball.h"
namespace ponggame
{
	class Actor
	{
	public:
		f32 sizeX;
		f32 sizeY;
		f32 posX;
		f32	posY;
		int score = 0;
	};
	
	
	
	class FGame
	{
	public:
		f64 Time = 0.f;
		f64 StartTime = 0.f;
		Actor LeftActor;
		Actor RightActor;
		FBall Ball;
		bool bIsRKeyPressed = false;
		f32 DeltaTime = 0.f;
	};



	void Init();
	void update();
	void exit();
}

/* TODO LIST
아무 키나 누르면 게임이 시작함.											<-- 완료

R 누르면 게임 재 시작.													<-- 완료

게임 시작부터 흘러간 시간이 게임 화면 중앙 상단에 출력됨.				<-- 완료

임시로 직사각형 오브젝트가 게임 화면 아무 좌표에서 시작함.				<-- 완료

공 오브젝트는 화면 정 중앙에서 시작함.									<-- 완료

게임이 시작하면, 공이 랜덤한 초기 속도를 가지고 움직이기 시작함.		<-- 완료

임시 객체인 직사각형 오브젝트에 공이 맞고 튕겨 남.						<-- 완료

공이 상하좌우 화면 벽을 맞고 튕겨 남.									<-- 완료

공이 우측 벽을 맞고 튕기면 플레이어A 스코어 1 획득.						<-- 완료

화면 좌측 상단에 플레이어A 스코어 출력.									<-- 완료

화면 좌측 벽을 맞고 튕기면 플레이어B 스코어 1 획득.						<-- 완료

화면 우측 상단에 플레이어B 스코어 출력.									<-- 완료

좌측 중앙 화면 1/3 지점는 플레이어A 오브젝트 시작 좌표.					<-- 

플레이어A 오브젝트의 Y좌표는 마우스를 따라 움직임.

우측 중앙 화면 1/3 지점은 플레이어B 오브젝트 시작 좌표.

플레이어B 오브젝트의 Y좌표는 키보드 W,S로 움직임.

공이 플레이어A, B를 맞고 튕겨나감. (직사각형 임시 객체는 지워도 무방함.)

먼저 11점을 획득하는 플레이어가 승리

승리 화면에서 R누르면 재시작.
*/