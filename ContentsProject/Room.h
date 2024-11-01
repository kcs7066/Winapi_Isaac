#pragma once
#include <EngineCore/Actor.h>

class ARoom : public AActor
{
public:
	// constrcuter destructer
	ARoom();
	~ARoom();

	// delete Function
	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

	void Link();
	
	bool IsLink()
	{
		return true;
	}

protected:

private:

};

