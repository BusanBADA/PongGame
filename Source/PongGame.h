#include "AEEngine.h"
#include "Ball.h"
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
		bool bFontLoadFlag = false;
		s8 font;
		f64 Time = 0.f;
		f64 StartTime = 0.f;
		Actor LeftActor;
		Actor RightActor;
		FBall Ball;
		bool bIsRKeyPressed = false;
		f32 DeltaTime = 0.f;
		void ResetGame();
		void Update();
		void EndGame();
	};

	class FGameState
	{
	public:
		bool bIsPreGameState = true;
		bool bShouldResetGame = false;
		bool bIsGameRunning = false;
		bool bIsGameEnded = false;
	};

	extern FGame Game;
	extern FGameState GameState;
	
}

/* TODO LIST
�ƹ� Ű�� ������ ������ ������.											<-- �Ϸ�

R ������ ���� �� ����.													<-- �Ϸ�

���� ���ۺ��� �귯�� �ð��� ���� ȭ�� �߾� ��ܿ� ��µ�.				<-- �Ϸ�

�ӽ÷� ���簢�� ������Ʈ�� ���� ȭ�� �ƹ� ��ǥ���� ������.				<-- �Ϸ�

�� ������Ʈ�� ȭ�� �� �߾ӿ��� ������.									<-- �Ϸ�

������ �����ϸ�, ���� ������ �ʱ� �ӵ��� ������ �����̱� ������.		<-- �Ϸ�

�ӽ� ��ü�� ���簢�� ������Ʈ�� ���� �°� ƨ�� ��.						<-- �Ϸ�

���� �����¿� ȭ�� ���� �°� ƨ�� ��.									<-- �Ϸ�

���� ���� ���� �°� ƨ��� �÷��̾�A ���ھ� 1 ȹ��.						<-- �Ϸ�

ȭ�� ���� ��ܿ� �÷��̾�A ���ھ� ���.									<-- �Ϸ�

ȭ�� ���� ���� �°� ƨ��� �÷��̾�B ���ھ� 1 ȹ��.						<-- �Ϸ�

ȭ�� ���� ��ܿ� �÷��̾�B ���ھ� ���.									<-- �Ϸ�

���� �߾� ȭ�� 1/3 ������ �÷��̾�A ������Ʈ ���� ��ǥ.					<-- �Ϸ�

�÷��̾�A ������Ʈ�� Y��ǥ�� ���콺�� ���� ������.						<-- �Ϸ�

���� �߾� ȭ�� 1/3 ������ �÷��̾�B ������Ʈ ���� ��ǥ.					<-- �Ϸ�

�÷��̾�B ������Ʈ�� Y��ǥ�� Ű���� W,S�� ������.						<-- �Ϸ�

���� �÷��̾�A, B�� �°� ƨ�ܳ���. (���簢�� �ӽ� ��ü�� ������ ������.) <-- �Ϸ�

���� 11���� ȹ���ϴ� �÷��̾ �¸�									<-- �Ϸ�

�¸� ȭ�鿡�� R������ �����.											<-- �Ϸ�	
*/