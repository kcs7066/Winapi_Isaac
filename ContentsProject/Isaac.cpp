#include "PreCompile.h"
#include "Isaac.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "Tear.h"
#include "ContentsEnum.h"
#include "PlayGameMode.h"

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
		HeadRenderer->CreateAnimation("Attack_UpHead", "Head.png", {  4, 5 }, { 0.1f,0.4f });
		HeadRenderer->CreateAnimation("Attack_RightHead", "Head.png", { 2, 3 }, { 0.1f,0.4f });
		HeadRenderer->CreateAnimation("Attack_DownHead", "Head.png", { 6, 7 }, { 0.1f,0.4f});
		HeadRenderer->CreateAnimation("Attack_LeftHead", "Head.png", { 0, 1 }, { 0.1f,0.4f });
		HeadRenderer->CreateAnimation("Run_UpHead", "Head.png", 5, 5, 0.1f);
		HeadRenderer->CreateAnimation("Run_RightHead", "Head.png", 3, 3, 0.1f);
		HeadRenderer->CreateAnimation("Run_LeftHead", "Head.png", 1, 1, 0.1f);
	}

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, -20 });
	CollisionComponent->SetComponentScale({ 50, 70 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Player);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);


	GetWorld()->CollisionGroupLink(ECollisionGroup::Player, ECollisionGroup::Monster);


	CollisionComponent->SetCollisionEnter(std::bind(&AIsaac::CollisionEnter, this, std::placeholders::_1));
	CollisionComponent->SetCollisionStay(std::bind(&AIsaac::CollisionStay, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnd(std::bind(&AIsaac::CollisionEnd, this, std::placeholders::_1));


	DebugOn();
}

void AIsaac::CollisionEnter(AActor* _ColActor)
{
	int a = 0;
}

void AIsaac::CollisionStay(AActor* _ColActor)
{
	int a = 0;
}

void AIsaac::CollisionEnd(AActor* _ColActor)
{
	int  a = 0;
}

AIsaac::~AIsaac()
{
}

void AIsaac::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SetCameraToMainPawn(false);
	

	
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
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());


	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	if (true == UEngineInput::GetInst().IsDown('B'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	if (true == UEngineInput::GetInst().IsPress(VK_UP))
	{
		HeadRenderer->ChangeAnimation("Attack_UpHead");
		Attack(FVector2D::UP);
	}
	

	if (true == UEngineInput::GetInst().IsPress(VK_RIGHT))
	{
		HeadRenderer->ChangeAnimation("Attack_RightHead");
		Attack(FVector2D::RIGHT);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_DOWN))
	{
		HeadRenderer->ChangeAnimation("Attack_DownHead");
		Attack(FVector2D::DOWN);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_LEFT))
	{
		HeadRenderer->ChangeAnimation("Attack_LeftHead");
		Attack(FVector2D::LEFT);
	}

	BulletCoolTime -= _DeltaTime;
	FSM.Update(_DeltaTime);
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

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Door);

	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (nullptr != Result)
	{
		ADoor* NewResult = dynamic_cast<ADoor*>(Result);

		
     	PlayGameMode->CurRoom = NewResult->LinkedRoom;

		switch (NewResult->Dir)
		{
		case DoorDir::UP:
			this->AddActorLocation({0,-250});
			break;
		case DoorDir::RIGHT:
			this->AddActorLocation({ 300,0 });
			break;
		case DoorDir::DOWN:
			this->AddActorLocation({ 0,250 });
			break;
		case DoorDir::LEFT:
			this->AddActorLocation({ -300,0 });
			break;

		default:
			break;
		}

	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Idle);
		return;
	}

	FVector2D Location = GetActorLocation() += Vector * _DeltaTime * Speed;

	if (PlayGameMode->CurRoom->RoomPos.X - Location.X > 338.0f ||
		PlayGameMode->CurRoom->RoomPos.X - Location.X < -338.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - Location.Y > 182.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - Location.Y < -182.0f)
	{

	}
	
	else
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
	}
}

void AIsaac::Attack(FVector2D _Dir)
{
	if (BulletCoolTime < 0.0f)
	{
		ATear* NewTear = GetWorld()->SpawnActor<ATear>();
		NewTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
		NewTear->Dir = (_Dir);
		BulletCoolTime = 0.5f;
	}
}


void AIsaac::LevelChangeStart()
{
	int a = 0;
}