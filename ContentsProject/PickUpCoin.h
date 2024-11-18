#pragma once
#include "PickUp.h"

class APickUpCoin : public APickUp
{
public:
	// constrcuter destructer
	APickUpCoin();
	~APickUpCoin();

	// delete Function
	APickUpCoin(const APickUpCoin& _Other) = delete;
	APickUpCoin(APickUpCoin&& _Other) noexcept = delete;
	APickUpCoin& operator=(const APickUpCoin& _Other) = delete;
	APickUpCoin& operator=(APickUpCoin&& _Other) noexcept = delete;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};
