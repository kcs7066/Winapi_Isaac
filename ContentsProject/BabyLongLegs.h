#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class BabyLongLegsState
{
	Move,
	Attack
};

class ABabyLongLegs : public AMonster
{
public:
	// constrcuter destructer
	ABabyLongLegs();
	~ABabyLongLegs();

	// delete Function
	ABabyLongLegs(const ABabyLongLegs& _Other) = delete;
	ABabyLongLegs(ABabyLongLegs&& _Other) noexcept = delete;
	ABabyLongLegs& operator=(const ABabyLongLegs& _Other) = delete;
	ABabyLongLegs& operator=(ABabyLongLegs&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Attack(float _DeltaTime);
	void Move(float _DeltaTime);

protected:

private:

	float DelayTime = 0.0f;

	UFSMStateManager FSM = UFSMStateManager();
	U2DCollision* CollisionComponent;
	float Speed = 300.0f;
	class USpriteRenderer* BabyLongLegsRenderer = nullptr;
	FVector2D Dir = { 0,0 };

	

};