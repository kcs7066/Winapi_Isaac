#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{


}

UEngineFile::~UEngineFile()
{
	// 소멸자를 이용해서 자연스럽게 파괴되도록 만드는게 좋다.
	Close();
}

void UEngineFile::FileOpen(const char* _Mode)
{
	fopen_s(&File, Path, _Mode);

	// 방어코드
	// 파일을 열지 못했다.
	if (nullptr == File)
	{
		// char [] Arr0
		// char [] Arr1
		// Arr0 + Arr1

		MSGASSERT(Path /*+ "파일 오픈에 실패했습니다"*/);
	}
}


void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("크기가 0인 데이터를 쓸수는 없습니다.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 사용하려고 했습니다.");
	}

	// w일 경우에 대한 예외처리
	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
		return;
	}

	fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("크기가 0인 데이터를 읽을수는 없습니다.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 읽으려고 했습니다.");
	}

	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
		return;
	}

	fread(_Ptr, _Size, 1, File);
}

// 인라인은 구현과 선언을분리하면 인라인을 하기 힘듭니다.
bool UEngineFile::IsExits()
{
	int Result = _access(Path, 00);

	// 0이면 있는것 0 이외의 값이면 없는 것
	return 0 == Result;
}



// 보통 파일 혹은 플랫폼 기능들은 언제나 한쌍이다.
// 시작한다.
// 사용한다.
// 끝낸다
void UEngineFile::Close()
{
	// 방어코드
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

