#pragma once
#include "Monster.h"
#include "Poop.h"


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


	int Poopkey(FVector2D _Pos)
	{
		std::map<int, FVector2D>::iterator StartIter = PoopBind.begin();
		std::map<int, FVector2D>::iterator EndIter = PoopBind.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second == _Pos)
				return StartIter->first;
		}

	}

	LarryjrPart Part = LarryjrPart::BODY;

	std::map<LinkDir, ALarryjr*> LinkedParts;

	//ALarryjr* LinkedFront = nullptr;
	//ALarryjr* LinkedBack = nullptr;

	std::map<int, FVector2D> PoopBind;
	std::map<int, APoop*> PoopPos;
	FVector2D FuturePos = { 0.0f,0.0f };
	FVector2D SavePos = { 0.0f , 0.0f };
	//FVector2D BodyFuturePos = { 0.0f,0.0f };
	float Speed = 208.0f;
	FVector2D Dir = { 1,0 };

protected:

private:


};

