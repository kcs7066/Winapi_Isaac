#pragma once
#include "PickUp.h"

class APickUpKey : public APickUp
{
public:
	// constrcuter destructer
	APickUpKey();
	~APickUpKey();

	// delete Function
	APickUpKey(const APickUpKey& _Other) = delete;
	APickUpKey(APickUpKey&& _Other) noexcept = delete;
	APickUpKey& operator=(const APickUpKey& _Other) = delete;
	APickUpKey& operator=(APickUpKey&& _Other) noexcept = delete;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};
