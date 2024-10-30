#pragma once
#include <filesystem>

// ���� :
class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	bool IsExists();
	void MoveParent();

	std::string GetPathToString();

	std::string GetFileName();

	std::string GetExtension();

	bool MoveParentToDirectory(std::string_view _Path);

	bool IsDirectory();

	bool IsFile();


protected:
	std::filesystem::path Path;

private:
};
