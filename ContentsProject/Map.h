#pragma once

// Ό³Έν :
class AMap
{
public:
	// constrcuter destructer
	AMap();
	~AMap();

	// delete Function
	AMap(const AMap& _Other) = delete;
	AMap(AMap&& _Other) noexcept = delete;
	AMap& operator=(const AMap& _Other) = delete;
	AMap& operator=(AMap&& _Other) noexcept = delete;

protected:

private:

};

