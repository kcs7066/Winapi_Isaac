#pragma once
#include <string>

class UObject
{
public:
	// constrcuter destructer
	UObject();

	virtual ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	//이름을 얻어주는 함수
	std::string GetName() const
	{
		return Name;
	}

	// ??
	std::string_view GetNameView() const
	{
		return Name.c_str();
	}

	// ??
	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

protected:

private:
	std::string Name;

};
