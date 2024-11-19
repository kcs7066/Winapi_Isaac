#pragma once
#include "Monster.h"



enum class SpiderState
{
	Idle,
	MoveRight,
	MoveLeft,
	Die

};

class ASpider : public AMonster
{
public:
	// constrcuter destructer
	ASpider();
	~ASpider();

	// delete Function
	ASpider(const ASpider& _Other) = delete;
	ASpider(ASpider&& _Other) noexcept = delete;
	ASpider& operator=(const ASpider& _Other) = delete;
	ASpider& operator=(ASpider&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStart();

protected:

private:

	float Speed = 300.0f;
	FVector2D RandomDir = { 0,0 };
	
};