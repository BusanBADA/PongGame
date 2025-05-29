#include "AEEngine.h"
#include "Ball.h"
#include <string>
#include "GlobalFunc.h"
namespace ponggame
{
	class Actor
	{
	public:
		AEGfxVertexList* Mesh = nullptr;
		f32 sizeX = 30.f;
		f32 sizeY = 150.f;
		f32 posX = 0.f;
		f32	posY = 0.f;
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
		f32 EndGameTimer = 0.f;
		void ResetGame();
		void Update();
		void EndGame();
	};

	extern FGame Game;
	
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

좌측 중앙 화면 1/3 지점는 플레이어A 오브젝트 시작 좌표.					<-- 완료

플레이어A 오브젝트의 Y좌표는 마우스를 따라 움직임.						<--  

우측 중앙 화면 1/3 지점은 플레이어B 오브젝트 시작 좌표.					<-- 완료

플레이어B 오브젝트의 Y좌표는 키보드 W,S로 움직임.						<-- 완료

공이 플레이어A, B를 맞고 튕겨나감. (직사각형 임시 객체는 지워도 무방함.) <-- 완료

먼저 11점을 획득하는 플레이어가 승리									<-- 완료

승리 화면에서 R누르면 재시작.											<-- 완료	

프로그램 시작 시 로고 Fade In/Out										<-- 완료

로고 재생이 끝나면 메인 메뉴로 이동함.									<-- 완료

메인 메뉴 화면에 버튼 두 개 있음. (Button A, Button B)					<-- 완료

Button A는 Pong 게임 실행하는 버튼.										<-- 완료

Button B는 Animation Test Level 실행하는 버튼임.						

Animation Test Level에서는 캐릭터 애니메이션을 구현 할 거임. 자세한 스펙은 아래 참조.

Note: 로고 재생 화면, 메인 메뉴, 퐁 게임, Animation Test Level에 대해서 각 별도의 .cpp/.h 파일 만들기

로고 재생 화면															<-- 완료

메인 메뉴																<-- 완료

퐁 게임																	<-- 완료

Animation Test Level													<-- 완료
*/