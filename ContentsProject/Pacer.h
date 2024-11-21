#pragma once
#include "Monster.h"


enum class PacerState
{
	Move,
	Die

};

class APacer : public AMonster
{
public:
	// constrcuter destructer
	APacer();
	~APacer();

	// delete Function
	APacer(const APacer& _Other) = delete;
	APacer(APacer&& _Other) noexcept = delete;
	APacer& operator=(const APacer& _Other) = delete;
	APacer& operator=(APacer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStart();


protected:

private:
	float Speed = 75.0f;
	class USpriteRenderer* BodyRenderer = nullptr;
	FVector2D RandomDir = FVector2D::DOWN;

};