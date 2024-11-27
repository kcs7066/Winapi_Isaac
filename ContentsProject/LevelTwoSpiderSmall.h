#pragma once
#include "Monster.h"

enum class LevelTwoSpiderSmallState
{
	Idle,
	Move,
	Jump,
	Die


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
	void DieStart();

protected:

private:

	float Speed = 300.0f;

	FVector2D Dir = { 0,0 };

};