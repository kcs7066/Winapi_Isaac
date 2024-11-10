#include "PreCompile.h"
#include "Isaac.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

AIsaac::AIsaac()
{
	SetActorLocation({ 0, 0 });

	{
		BodyRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BodyRenderer->SetSprite("Body.png");
		BodyRenderer->SetComponentScale({ 70, 70 });
		BodyRenderer->CreateAnimation("Idle_Body", "Body.png", 29, 29, 0.1f);
		BodyRenderer->CreateAnimation("Run_RightBody", "Body.png", 10, 19, 0.1f);
		BodyRenderer->CreateAnimation("Run_DownBody", "Body.png", 20, 29, 0.1f);
		BodyRenderer->CreateAnimation("Run_LeftBody", "Body.png", 0, 9, 0.1f);
	}

	{
		HeadRenderer = CreateDefaultSubObject<USpriteRenderer>();
		HeadRenderer->SetSprite("Head.png");
		HeadRenderer->SetComponentScale({ 70, 70 });
		HeadRenderer->SetComponentLocation({ 0,-30 });


		HeadRenderer->CreateAnimation("Idle_Head", "Head.png", 7, 7, 0.1f);
		HeadRenderer->CreateAnimation("Run_UpHead", "Head.png", 5, 5, 0.1f);
		HeadRenderer->CreateAnimation("Run_RightHead", "Head.png", 3, 3, 0.1f);
		HeadRenderer->CreateAnimation("Run_LeftHead", "Head.png", 1, 1, 0.1f);
	}

}

AIsaac::~AIsaac()
{
}

void AIsaac::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SetCameraToMainPawn(true);
	

	
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
	
	FSM.CreateState(NewPlayerState::Idle, std::bind(&AIsaac::Idle, this, std::placeholders::_1),
		[this]()
		{
			HeadRenderer->ChangeAnimation("Idle_Head");
			BodyRenderer->ChangeAnimation("Idle_Body");
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&AIsaac::Move, this, std::placeholders::_1),
		[this]()
		{
			HeadRenderer->ChangeAnimation("Idle_Head");
			BodyRenderer->ChangeAnimation("Run_DownBody");
		}
	);



	FSM.ChangeState(NewPlayerState::Idle);
	
}

void AIsaac::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());


	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}
}



void AIsaac::Idle(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}




void AIsaac::Move(float _DeltaTime)
{
	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		HeadRenderer->ChangeAnimation("Run_RightHead");
		BodyRenderer->ChangeAnimation("Run_RightBody");
		Vector += FVector2D::RIGHT;
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		HeadRenderer->ChangeAnimation("Run_LeftHead");
		BodyRenderer->ChangeAnimation("Run_LeftBody");
		Vector += FVector2D::LEFT;
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		HeadRenderer->ChangeAnimation("Idle_Head");
		BodyRenderer->ChangeAnimation("Run_DownBody");
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		HeadRenderer->ChangeAnimation("Run_UpHead");
		BodyRenderer->ChangeAnimation("Run_DownBody");
		Vector += FVector2D::UP;
	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Idle);
		return;
	}
	AddActorLocation(Vector * _DeltaTime * Speed);

}



void AIsaac::LevelChangeStart()
{
	int a = 0;
}