#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineSound.h>
#include "Item.h"

enum class IsaacState
{
	Idle,
	Move,
	Attack,
	Hit,
	Item,
	Die
	
	
};

// Ό³Έν :
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

	//void Idle(float _DeltaTime);
	//void Move(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void HitStart();
	void Hit(float _DeltaTime);
	void ItemStart(AItem* _Item);
	void Item(float _DeltaTime);
	void DieStart();
	void Die(float _DeltaTime);

    void Attack(float _DeltaTime);

	class USpriteRenderer* HeadRenderer = nullptr;
	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

	float DelayTime = 0.0f;

	bool CanMove = true;

	float Damage = 100.0f;
	FVector2D PrevPos;

	int Hp = 6;
	int CoinNumber = 0;
	int BombNumber = 1;
	int KeyNumber = 0;
	float HitCoolTime = 0.0f;


protected:

private:

	void HpCheck();

	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class UEngineWinImage* ColImage = nullptr;
	
	float RoomMoveCameraTime = 0.0f;

	std::string DirString = "_Right";

	class USpriteRenderer* BodyRenderer = nullptr;
	class USpriteRenderer* ShadowRenderer = nullptr;
	class USpriteRenderer* HitRenderer = nullptr;
	class USpriteRenderer* DeathRenderer = nullptr;
	class USpriteRenderer* GhostRenderer = nullptr;
	class USpriteRenderer* ItemRenderer = nullptr;

	UFSMStateManager FSM = UFSMStateManager();
	int Test = 0;
	float BulletCoolTime = 0.5f;

	float BombCoolTime = 0.0f; 
	float GhostPos = -15.0f;

	bool TheInnerEyeValue = false;

	USoundPlayer BGMPlayer;
};

