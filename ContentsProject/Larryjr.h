#pragma once
#include "Monster.h"

enum class LarryjrState
{
	DirChange,
	UpMove,
	RightMove,
	DownMove,
    LeftMove,
	Poop,
	Die
};

enum class LarryjrDir
{
	Up,
	Right,
	Down,
	Left
};

enum class LarryjrPart
{
	HEAD,
	BODY,
	TAIL

};

enum class LinkDir
{
	Front,
	Back
};

class ALarryjr : public AMonster
{
public:
	// constrcuter destructer
	ALarryjr();
	~ALarryjr();

	// delete Function
	ALarryjr(const ALarryjr& _Other) = delete;
	ALarryjr(ALarryjr&& _Other) noexcept = delete;
	ALarryjr& operator=(const ALarryjr& _Other) = delete;
	ALarryjr& operator=(ALarryjr&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirChange(float _DeltaTime);
	void UpMove(float _DeltaTime);
	void RightMove(float _DeltaTime);
	void DownMove(float _DeltaTime);
	void LeftMove(float _DeltaTime);
	void Poop(float _DeltaTime);

	void Die(float _DeltaTime);
	void DieStart();

	LarryjrPart Part = LarryjrPart::BODY;
	std::map<LinkDir, ALarryjr*> LinkedParts;

protected:

private:

	float Speed = 208.0f;

	FVector2D FuturePos = { 0.0f,0.0f };
	FVector2D SavePos = { 0.0f , 0.0f };
	FVector2D Dir = { 1,0 };
};

