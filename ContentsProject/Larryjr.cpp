#include "PreCompile.h"
#include "Larryjr.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include "TrapDoor.h"
#include "Poop.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

#include <EngineCore/EngineCoreDebug.h>

ALarryjr::ALarryjr()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 130, 130 });
	MonsterRenderer->SetComponentLocation({ 0,-15 });

	MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
	MonsterRenderer->CreateAnimation("Head_Larryjr_Left", "Boss_Larryjr_Left.png", 0, 1, 0.1f);
	MonsterRenderer->CreateAnimation("Head_Larryjr_Up", "Boss_Larryjr_Left.png", 2, 3, 0.1f);
	MonsterRenderer->CreateAnimation("Head_Larryjr_Down", "Boss_Larryjr_Left.png", 4, 5, 0.1f);
	MonsterRenderer->CreateAnimation("Body_Larryjr_Left", "Boss_Larryjr_Left.png", 6, 7, 0.1f);
	MonsterRenderer->CreateAnimation("Body_Larryjr_Down", "Boss_Larryjr_Left.png", 8, 9, 0.1f);
	MonsterRenderer->CreateAnimation("Tail_Larryjr_Up", "Boss_Larryjr_Left.png", 10, 11, 0.1f);
	MonsterRenderer->CreateAnimation("Body_Larryjr_Up", "Boss_Larryjr_Left.png", 12, 13, 0.1f);
	MonsterRenderer->CreateAnimation("Die_Larryjr", "BloodPoof.png", 0, 10, 0.1f);

	MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
	
	ShadowRenderer->SetSpriteScale(0.4f);

	CollisionComponent->SetComponentScale({ 45, 45 });
	CollisionComponent->SetComponentLocation({ 0, 0 });

	DebugOn();

	SetHp(22.0f);

}

ALarryjr::~ALarryjr()
{
}

void ALarryjr::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Pos = { 52.0f, 0.0f };
	FuturePos = GetActorLocation() + Pos;
	DelayTime = 1.0f;

	FSM.CreateState(LarryjrState::DirChange, std::bind(&ALarryjr::DirChange, this, std::placeholders::_1),
		[this]()
		{

		}
	);

	FSM.CreateState(LarryjrState::UpMove, std::bind(&ALarryjr::UpMove, this, std::placeholders::_1),
		[this]()
		{
			switch (Part)
			{
			case LarryjrPart::HEAD:
				MonsterRenderer->ChangeAnimation("Head_Larryjr_Up");
				break;
			case LarryjrPart::BODY:
				MonsterRenderer->ChangeAnimation("Body_Larryjr_Up");
				break;
			case LarryjrPart::TAIL:
				MonsterRenderer->ChangeAnimation("Tail_Larryjr_Up");
				break;
			default:
				break;
			}
		}
	);
	FSM.CreateState(LarryjrState::RightMove, std::bind(&ALarryjr::RightMove, this, std::placeholders::_1),
		[this]()
		{
			if (LarryjrPart::HEAD == Part)
			{
				MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
			}
			else
			{
				MonsterRenderer->ChangeAnimation("Body_Larryjr_Left");
			}
			
		}
	);
	FSM.CreateState(LarryjrState::DownMove, std::bind(&ALarryjr::DownMove, this, std::placeholders::_1),
		[this]()
		{

			if (LarryjrPart::HEAD == Part)
			{
				MonsterRenderer->ChangeAnimation("Head_Larryjr_Down");
			}
			else
			{
				MonsterRenderer->ChangeAnimation("Body_Larryjr_Down");
			}
		}
	);
	FSM.CreateState(LarryjrState::LeftMove, std::bind(&ALarryjr::LeftMove, this, std::placeholders::_1),
		[this]()
		{

			if (LarryjrPart::HEAD == Part)
			{
				MonsterRenderer->ChangeAnimation("Head_Larryjr_Left");
			}
			else
			{
				MonsterRenderer->ChangeAnimation("Body_Larryjr_Left");
			}
		}
	);

	FSM.CreateState(LarryjrState::Poop, std::bind(&ALarryjr::Poop, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(LarryjrState::Die, std::bind(&ALarryjr::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Larryjr");
		}
	);

	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->BGMPlayer.Off();
	PlayGameMode->BGMPlayer = UEngineSound::Play("basic boss fight.ogg");
	FSM.ChangeState(LarryjrState::RightMove);
}

void ALarryjr::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void ALarryjr::DirChange(float _DeltaTime)
{
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if 
		(LarryjrPart::HEAD == Part)
	{
		FVector2D ExpectPos = {std::floorf(FuturePos.X), std::floorf(FuturePos.Y) };
		FVector2D NewPos = GetActorLocation();
		FVector2D NewNewPos = { std::floorf(NewPos.X), std::floorf(NewPos.Y) };
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		FVector2D NextFuturePos = { 0,0 };

		if (ExpectPos == NewNewPos)
		{
			int RandomValue = Random.RandomInt(1, 20);

			switch (RandomValue)
			{
			case 1:
				Dir = { -(Dir.X) , -(Dir.Y) };
				break;
			case 2:
				Dir = { (Dir.Y), (Dir.X) };
				break;
			case 3:
				Dir = { -(Dir.Y), -(Dir.X) };
				break;
			default:
				break;
			}
			if (FVector2D::UP == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52);
				if (NextFuturePos.Y < PlayGameMode->CurRoom->RoomPos.Y + 52 * (-3.5f))
				{
					FuturePos -= Dir * 52;
					FSM.ChangeState(LarryjrState::DownMove);
				}
				else
				{
					FuturePos += (Dir * 52);
					FSM.ChangeState(LarryjrState::UpMove);
				}
			}
			else if (FVector2D::RIGHT == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52);
				if (NextFuturePos.X > PlayGameMode->CurRoom->RoomPos.X + 52 * (6.5f))
				{
					FuturePos -= (Dir * 52);
					FSM.ChangeState(LarryjrState::LeftMove);
				}
				else
				{
					FuturePos += (Dir * 52);
					FSM.ChangeState(LarryjrState::RightMove);
				}
			}
			else if (FVector2D::DOWN == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52);
				if (NextFuturePos.Y > PlayGameMode->CurRoom->RoomPos.Y + 52 * (3.5f))
				{
					FuturePos -= Dir * 52;
					FSM.ChangeState(LarryjrState::UpMove);
				}
				else
				{
					FuturePos += (Dir * 52);
					FSM.ChangeState(LarryjrState::DownMove);
				}
			}
			else if (FVector2D::LEFT == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52);
				if (NextFuturePos.X < PlayGameMode->CurRoom->RoomPos.X + 52 * (-6.5f))
				{
					FuturePos -= Dir * 52;
					FSM.ChangeState(LarryjrState::RightMove);
				}
				else
				{
					FuturePos += (Dir * 52);
					FSM.ChangeState(LarryjrState::LeftMove);
				}
			}

			SavePos = NewNewPos;
		}


		//int Key = Poopkey(FuturePos);
		//if (nullptr == PoopPos[Key])
		//{
		//	FVector2D NewLocation = GetActorLocation() + Dir * _DeltaTime * Speed;
		//	APlayGameMode* ABPlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

		//		AddActorLocation(Dir * _DeltaTime * Speed);

		//}

	}

	else
	{
		FuturePos = LinkedParts[LinkDir::Front]->SavePos;
		FVector2D NewDir = FuturePos - GetActorLocation();

		int a = 0;

		if (NewDir.Y < -40)
		{
			FSM.ChangeState(LarryjrState::UpMove);
		}
		else if (NewDir.X > 40)
		{
			FSM.ChangeState(LarryjrState::RightMove);
		}
		else if (NewDir.Y > 40)
		{
			FSM.ChangeState(LarryjrState::DownMove);
		}
		else if (NewDir.X < -40)
		{
			FSM.ChangeState(LarryjrState::LeftMove);
		}

		SavePos = { GetActorLocation().iX(),GetActorLocation().iY()};

		if (Part == LarryjrPart::TAIL)
		{
			if (5.0f <= DelayTime)
			{
				APoop* NewPoop = GetWorld()->SpawnActor<APoop>();
				NewPoop->SetActorLocation(SavePos);
				DelayTime = 0.0f;
			}
		}

    }

}

void ALarryjr::UpMove(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if (LarryjrPart::HEAD == Part)
	{
		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);
		if (nullptr != Result)
		{
			AStructure* ResultStructure = dynamic_cast<AStructure*>(Result);
			APoop* ResultPoop = dynamic_cast<APoop*>(ResultStructure);
			ResultPoop->Hp = 0;
			ResultPoop->StructureRenderer->ChangeAnimation("Poop0");
			ResultPoop->CollisionComponent->SetActive(false);
		}
	}

	    float ExpectPos = std::floorf(FuturePos.Y);
		FVector2D NewPos = GetActorLocation();
		float NewNewPos = std::floorf(NewPos.Y);
		if (ExpectPos == NewNewPos) 
		{
			FSM.ChangeState(LarryjrState::DirChange);
		}
		else
		{
			Dir = { 0,-1 };
			AddActorLocation(Dir * _DeltaTime * Speed);
		}


}
void ALarryjr::RightMove(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if (LarryjrPart::HEAD == Part)
	{
		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);
		if (nullptr != Result)
		{
			AStructure* ResultStructure = dynamic_cast<AStructure*>(Result);
			APoop* ResultPoop = dynamic_cast<APoop*>(ResultStructure);
			ResultPoop->Hp = 0;
			ResultPoop->StructureRenderer->ChangeAnimation("Poop0");
			ResultPoop->CollisionComponent->SetActive(false);
		}
	}

	float ExpectPos = std::floorf(FuturePos.X);
	FVector2D NewPos = GetActorLocation();
	float NewNewPos = std::floorf(NewPos.X);
	if (ExpectPos == NewNewPos)
	{
		FSM.ChangeState(LarryjrState::DirChange);
	}
	else
	{
		Dir = { 1,0 };
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

}
void ALarryjr::DownMove(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if (LarryjrPart::HEAD == Part)
	{
		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);
		if (nullptr != Result)
		{
			AStructure* ResultStructure = dynamic_cast<AStructure*>(Result);
			APoop* ResultPoop = dynamic_cast<APoop*>(ResultStructure);
			ResultPoop->Hp = 0;
			ResultPoop->StructureRenderer->ChangeAnimation("Poop0");
			ResultPoop->CollisionComponent->SetActive(false);
		}
	}

	float ExpectPos = std::floorf(FuturePos.Y);
	FVector2D NewPos = GetActorLocation();
	float NewNewPos = std::floorf(NewPos.Y);
	if (ExpectPos == NewNewPos)
	{
		FSM.ChangeState(LarryjrState::DirChange);
	}
	else
	{
		Dir = { 0,1 };
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

}
void ALarryjr::LeftMove(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if (LarryjrPart::HEAD == Part)
	{
		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);
		if (nullptr != Result)
		{
			AStructure* ResultStructure = dynamic_cast<AStructure*>(Result);
			APoop* ResultPoop = dynamic_cast<APoop*>(ResultStructure);
			ResultPoop->Hp = 0;
			ResultPoop->StructureRenderer->ChangeAnimation("Poop0");
			ResultPoop->CollisionComponent->SetActive(false);
		}
	}

	float ExpectPos = std::floorf(FuturePos.X);
	FVector2D NewPos = GetActorLocation();
	float NewNewPos = std::floorf(NewPos.X);
	if (ExpectPos == NewNewPos)
	{
		FSM.ChangeState(LarryjrState::DirChange);
	}
	else
	{
		Dir = { -1,0 };
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

}


void ALarryjr::Poop(float _DeltaTime)
{
	
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if (LarryjrPart::TAIL == this->Part)
	{
		APoop* NewPoop = GetWorld()->SpawnActor<APoop>();
		NewPoop->SetActorLocation(GetActorLocation());
	}

}


void ALarryjr::DieStart()
{
	CollisionComponent->SetActive(false);


	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->CurRoom->MonsterNumber--;
	if (0 == PlayGameMode->CurRoom->MonsterNumber)
	{
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		EffectPlayer = UEngineSound::Play("death burst large.wav");
	}

	if (nullptr != LinkedParts[LinkDir::Front])
	{
		LinkedParts[LinkDir::Front]->Part = LarryjrPart::TAIL;
		LinkedParts[LinkDir::Front]->LinkedParts.erase(LinkDir::Back);
	}
	if (nullptr != LinkedParts[LinkDir::Back])
	{
		LinkedParts[LinkDir::Back]->Part = LarryjrPart::HEAD;
		LinkedParts[LinkDir::Back]->MonsterRenderer->SetComponentLocation({ 0,-25 });
		LinkedParts[LinkDir::Back]->ShadowRenderer->SetSpriteScale(0.5f);
		LinkedParts[LinkDir::Back]->LinkedParts.erase(LinkDir::Front);
	}

	DelayTime = 0.0f;
	FSM.ChangeState(LarryjrState::Die);
}

void ALarryjr::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}