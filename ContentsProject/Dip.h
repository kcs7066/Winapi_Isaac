#pragma once
#include "Monster.h"

enum class DipState
{
    IdleRight,
	IdleLeft,
	MoveRight,
	MoveLeft,
	Die
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
	void DirChange();
	void DieStart();

protected:


private:

	float Speed = 300.0f;
	FVector2D PrevPos;
	FVector2D RandomDir = { 0,0 };
};