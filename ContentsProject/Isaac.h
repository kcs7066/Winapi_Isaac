#pragma once

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>



enum class IsaacState
{
	Idle,
	Move,
	Attack,
	Hit,
	Item,
	Die
};

class AIsaac : public AActor
{
public:
	// constrcuter destructer
	AIsaac();
	~AIsaac();

	// delete Function
	AIsaac(const AIsaac& _Other) = delete;
	AIsaac(AIsaac&& _Other) noexcept = delete;
	AIsaac& operator=(const AIsaac& _Other) = delete;
	AIsaac& operator=(AIsaac&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelChangeStart() override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void HitStart();
	void Hit(float _DeltaTime);
	void ItemStart(class AItem* _Item);
	void Item(float _DeltaTime);
	void DieStart();
	void Die(float _DeltaTime);
    void Attack(float _DeltaTime);

	void HpCheck();

	int Hp = 6;
	int CoinNumber = 0;
	int BombNumber = 1;
	int KeyNumber = 0;

	float Damage = 3.5f;
	float HitCoolTime = 0.0f;
	float Speed = 0.0f;	
	float DelayTime = 0.0f;

	bool CanMove = true;
	bool TheInnerEyeValue = false;

	class USpriteRenderer* HeadRenderer = nullptr;

	FVector2D PrevPos;
	FVector2D Vector = FVector2D::ZERO;


protected:

private:

	float RoomMoveCameraTime = 0.0f;
	float TearCoolTime = 0.366666f;
	float BombCoolTime = 0.0f;
	float GhostPos = -15.0f;

	class U2DCollision* CollisionComponent;
	class UEngineWinImage* ColImage = nullptr;
	class USpriteRenderer* BodyRenderer = nullptr;
	class USpriteRenderer* ShadowRenderer = nullptr;
	class USpriteRenderer* HitRenderer = nullptr;
	class USpriteRenderer* DeathRenderer = nullptr;
	class USpriteRenderer* GhostRenderer = nullptr;
	class USpriteRenderer* ItemRenderer = nullptr;

	UFSMStateManager FSM = UFSMStateManager();
	USoundPlayer BGMPlayer;
};

