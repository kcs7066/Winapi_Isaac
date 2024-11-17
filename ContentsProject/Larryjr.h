#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class LarryjrState
{

	Move,
	Poop,
	Separate,
	Die

};

enum class LarryjrPart
{
	HEAD,
	BODY,
	TAIL

};

enum class Dir
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

	void Move(float _DeltaTime);
	void Poop(float _DeltaTime);
	void Separate(float _DeltaTime);
	void Die(float _DeltaTime);

	LarryjrPart Part = LarryjrPart::BODY;

	std::map<Dir, ALarryjr*> LinkedParts;

protected:

private:
	float Speed = 300.0f;
	FVector2D Dir;

};

