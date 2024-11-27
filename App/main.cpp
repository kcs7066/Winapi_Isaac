#include "PreCompile.h"

#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineRandom.h>

#include <EngineCore/EngineAPICore.h>

#include <ContentsProject/IsaacContentsCore.h>


#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	IsaacContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}