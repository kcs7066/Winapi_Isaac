#pragma once

#include <EngineBase/FSMStateManager.h>
#include <EngineBase/EngineRandom.h>

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/Actor.h>

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
	
	float TearSpeed = 500.0f;

	FVector2D Dir = FVector2D::ZERO;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Fly(float _DeltaTime);
	void Poof(float _DeltaTime);

private:

	float DelayTime = 0.0f;
	float DropPos = 0.0f;

	class USpriteRenderer* TearRenderer;
	class USpriteRenderer* ShadowRenderer;
	class U2DCollision* CollisionComponent;

	UFSMStateManager FSM;
	USoundPlayer BGMPlayer;
	UEngineRandom Random;
};