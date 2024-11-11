#include "PreCompile.h"
#include <ContentsProject/IsaacContentsCore.h>

#include <EngineCore/EngineAPICore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")

#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineRandom.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	IsaacContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}