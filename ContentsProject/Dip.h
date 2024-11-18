#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>


enum class DipState
{
    IdleRight,
	IdleLeft,
	MoveRight,
	MoveLeft,
	Die,
	DieStay
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
	void Die(float _DeltaTime);
	void DieStay(float _DeltaTime);



protected:


private:

	float Speed = 300.0f;
	FVector2D RandomDir = { 0,0 };
	
};