#pragma once
#include "PickUp.h"

class APickUpBomb : public APickUp
{
public:
	// constrcuter destructer
	APickUpBomb();
	~APickUpBomb();

	// delete Function
	APickUpBomb(const APickUpBomb& _Other) = delete;
	APickUpBomb(APickUpBomb&& _Other) noexcept = delete;
	APickUpBomb& operator=(const APickUpBomb& _Other) = delete;
	APickUpBomb& operator=(APickUpBomb&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

