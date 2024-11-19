#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/FSMStateManager.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineBase/EngineRandom.h>

enum class MonsterTearState
{
	Fly,
	Poof
};

class AMonsterTear : public AActor
{
public:
	// constrcuter destructer
	AMonsterTear();
	~AMonsterTear();

	// delete Function
	AMonsterTear(const AMonsterTear& _Other) = delete;
	AMonsterTear(AMonsterTear&& _Other) noexcept = delete;
	AMonsterTear& operator=(const AMonsterTear& _Other) = delete;
	AMonsterTear& operator=(AMonsterTear&& _Other) noexcept = delete;
	FVector2D Dir = FVector2D::ZERO;
	float TearSpeed = 500.0f;

	float DelayTime = 0.0f;
	float DropPos = 0.0f;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Fly(float _DeltaTime);
	void Poof(float _DeltaTime);

private:

	class USpriteRenderer* TearRenderer;
	class USpriteRenderer* ShadowRenderer;
	U2DCollision* CollisionComponent;

	UFSMStateManager FSM = UFSMStateManager();
	USoundPlayer BGMPlayer;
	UEngineRandom Random;
};