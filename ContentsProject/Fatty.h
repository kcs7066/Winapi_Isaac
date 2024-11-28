#pragma once
#include "Monster.h"

enum class FattyState
{
	Move,
	Attack,
	Die
};

class AFatty : public AMonster
{
public:
	// constrcuter destructer
	AFatty();
	~AFatty();

	// delete Function
	AFatty(const AFatty& _Other) = delete;
	AFatty(AFatty&& _Other) noexcept = delete;
	AFatty& operator=(const AFatty& _Other) = delete;
	AFatty& operator=(AFatty&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);

	void Die(float _DeltaTime);
	void DieStart();


protected:

private:

	float Speed = 100.0f;
	float SoundCoolTime = 2.0f;
	FVector2D Dir = FVector2D::DOWN;

	class USpriteRenderer* BodyRenderer = nullptr;
	class USpriteRenderer* NewPoofRenderer = nullptr;
};