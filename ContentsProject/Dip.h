#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class DipState
{
    IdleRight,
	IdleLeft,
	MoveRight,
	MoveLeft
};

class ADip : public AMonster
{
public:
	// constrcuter destructer
	ADip();
	~ADip();

	// delete Function
	ADip(const ADip& _Other) = delete;
	ADip(ADip&& _Other) noexcept = delete;
	ADip& operator=(const ADip& _Other) = delete;
	ADip& operator=(ADip&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);


protected:
	void TimeEvent();

private:

	float DelayTime = 0.0f;

	UFSMStateManager FSM = UFSMStateManager();
	U2DCollision* CollisionComponent;
	float Speed = 300.0f;
	class USpriteRenderer* DipRenderer = nullptr;
	FVector2D RandomDir = { 0,0 };

	UEngineRandom Random;

};