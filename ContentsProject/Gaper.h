#pragma once
#include "Monster.h"

enum class GaperState
{
	Move,
	Die
};

class AGaper : public AMonster
{
public:
	// constrcuter destructer
	AGaper();
	~AGaper();

	// delete Function
	AGaper(const AGaper& _Other) = delete;
	AGaper(AGaper&& _Other) noexcept = delete;
	AGaper& operator=(const AGaper& _Other) = delete;
	AGaper& operator=(AGaper&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStart();


protected:

private:
	float Speed = 150.0f;

	float SoundCoolTime = 2.0f;

	FVector2D Dir = FVector2D::DOWN;

	class USpriteRenderer* BodyRenderer = nullptr;
};