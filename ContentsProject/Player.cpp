#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"

APlayer::APlayer()
{

	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{

	UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));



}

void APlayer::MoveFunction(FVector2D _Dir)
{


	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);
}
void APlayer::Tick(float _DeltaTime)
{

	if (3.0f < UEngineInput::GetInst().IsPreeTime(VK_LBUTTON))
	{
		ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
		Ptr->SetActorLocation(GetActorLocation());
	}

}