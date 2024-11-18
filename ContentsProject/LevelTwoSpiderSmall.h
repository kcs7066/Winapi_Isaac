#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class LevelTwoSpiderSmallState
{
	Idle,
	Move,
	Jump,
	Die,
	DieStay

};

class ALevelTwoSpiderSmall : public AMonster
{
public:
	// constrcuter destructer
	ALevelTwoSpiderSmall();
	~ALevelTwoSpiderSmall();

	// delete Function
	ALevelTwoSpiderSmall(const ALevelTwoSpiderSmall& _Other) = delete;
	ALevelTwoSpiderSmall(ALevelTwoSpiderSmall&& _Other) noexcept = delete;
	ALevelTwoSpiderSmall& operator=(const ALevelTwoSpiderSmall& _Other) = delete;
	ALevelTwoSpiderSmall& operator=(ALevelTwoSpiderSmall&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStay(float _DeltaTime);

protected:

private:

	float Speed = 300.0f;
	FVector2D Dir = { 0,0 };

};