#include "PreCompile.h"
#include "Larryjr.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include "TrapDoor.h"
#include "Poop.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>


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

	CollisionComponent->SetComponentScale({ 50, 50 });
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



//void ALarryjr::Move(float _DeltaTime)
//{
//	
//	DelayTime += _DeltaTime;
//
//	if (this->Hp <= 0.0f)
//	{
//		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
//		PlayGameMode->CurRoom->MonsterNumber--;	
//		EffectPlayer = UEngineSound::Play("death burst large.wav");
//		FSM.ChangeState(LarryjrState::Die);
//	}
//	if (LarryjrPart::HEAD == Part)
//	{
//		FVector2D ExpectPos = { HeadFuturePos.iX(), HeadFuturePos.iY() };
//		FVector2D NewPos = GetActorLocation();
//		FVector2D NewNewPos = { NewPos.iX(), NewPos.iY() };
//		if (ExpectPos == NewNewPos)
//		{
//			int RandomValue = Random.RandomInt(1, 4);
//
//			switch (RandomValue)
//			{
//			case 1:
//				Dir = { 0,-1 };
//				switch (Part)
//				{
//				case LarryjrPart::HEAD:
//					MonsterRenderer->ChangeAnimation("Head_Larryjr_Up");
//					break;
//				case LarryjrPart::BODY:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Up");
//					break;
//				case LarryjrPart::TAIL:
//					MonsterRenderer->ChangeAnimation("Tail_Larryjr_Up");
//					break;
//				default:
//					break;
//				}
//				break;
//			case 2:
//				Dir = { 1,0 };
//				switch (Part)
//				{
//				case LarryjrPart::HEAD:
//					MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
//					break;
//				case LarryjrPart::BODY:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Left");
//					break;
//				case LarryjrPart::TAIL:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Left");
//					break;
//				default:
//					break;
//				}
//
//				break;
//			case 3:
//				Dir = { 0,1 };
//				switch (Part)
//				{
//				case LarryjrPart::HEAD:
//					MonsterRenderer->ChangeAnimation("Head_Larryjr_Down");
//					break;
//				case LarryjrPart::BODY:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Down");
//					break;
//				case LarryjrPart::TAIL:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Down");
//					break;
//				default:
//					break;
//				}
//
//				break;
//			default:
//				Dir = { -1,0 };
//				switch (Part)
//				{
//				case LarryjrPart::HEAD:
//					MonsterRenderer->ChangeAnimation("Head_Larryjr_Left");
//					break;
//				case LarryjrPart::BODY:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Left");
//					break;
//				case LarryjrPart::TAIL:
//					MonsterRenderer->ChangeAnimation("Body_Larryjr_Left");
//					break;
//				default:
//					break;
//				}
//
//				break;
//			}
//			APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
//			FVector2D NextFuturePos = HeadFuturePos + (Dir * 52.0f);
//			if (NextFuturePos.X > PlayGameMode->CurRoom->RoomPos.X + (52.0f * 6.5f))
//			{
//				HeadFuturePos = HeadFuturePos - (Dir * 52.0f);
//				Dir = Dir * (-1.0f); 
//			}
//			else if(NextFuturePos.X < PlayGameMode->CurRoom->RoomPos.X + (52.0f * (- 6.5f)))
//			{
//				HeadFuturePos -= Dir * 52.0f;
//				Dir = Dir * (-1.0f);
//			}
//			else if (NextFuturePos.Y > PlayGameMode->CurRoom->RoomPos.Y + (52.0f * 3.5f))
//			{
//				HeadFuturePos -= Dir * 52.0f;
//				Dir = Dir * (-1.0f);
//			}
//			else if (NextFuturePos.Y < PlayGameMode->CurRoom->RoomPos.Y + (52.0f * (-3.5f)))
//			{
//				HeadFuturePos -= Dir * 52.0f;
//				Dir = Dir * (-1.0f);
//			}
//			else
//			{
//				HeadFuturePos += (Dir * (52.0f));
//			}
//		}
//
//		int Key = Poopkey(HeadFuturePos);
//		if (nullptr == PoopPos[Key])
//		{
//			FVector2D NewLocation = GetActorLocation() + Dir * _DeltaTime * Speed;
//			APlayGameMode* ABPlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
//
//				AddActorLocation(Dir * _DeltaTime * Speed);
//
//		}
//		
//
//		
//	}
//
//	else
//	{
//		//FVector2D FollowDir = LinkedParts[Dir::Front]->GetActorLocation() - GetActorLocation();
//		//FollowDir.Normalize();
//		if (DelayTime > 0.3f)
//		{
//			BodyFuturePos = LinkedParts[Dir::Front]->GetActorLocation();
//			DelayTime = 0;
//		}
//		Dir = BodyFuturePos - GetActorLocation();
//		Dir.Normalize();
//		AddActorLocation(Dir * _DeltaTime* Speed);
//	}
//
//	// ¶ËÃ¼·Â°¨¼Ò
//}
void ALarryjr::DirChange(float _DeltaTime)
{
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	if 
		(LarryjrPart::HEAD == Part)
	{
		FVector2D ExpectPos = { FuturePos.iX(), FuturePos.iY() };
		FVector2D NewPos = GetActorLocation();
		FVector2D NewNewPos = { NewPos.iX(), NewPos.iY() };
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
				NextFuturePos = FuturePos + (Dir * 52.0f);
				if (NextFuturePos.Y < PlayGameMode->CurRoom->RoomPos.Y + (52.0f * (-3.5f)))
				{
					FuturePos -= Dir * 52.0f;
					FSM.ChangeState(LarryjrState::DownMove);
				}
				else
				{
					FuturePos += (Dir * (52.0f));
					FSM.ChangeState(LarryjrState::UpMove);
				}
			}
			else if (FVector2D::RIGHT == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52.0f);
				if (NextFuturePos.X > PlayGameMode->CurRoom->RoomPos.X + (52.0f * (6.5f)))
				{
					FuturePos -= (Dir * 52.0f);
					FSM.ChangeState(LarryjrState::LeftMove);
				}
				else
				{
					FuturePos += (Dir * (52.0f));
					FSM.ChangeState(LarryjrState::RightMove);
				}
			}
			else if (FVector2D::DOWN == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52.0f);
				if (NextFuturePos.Y > PlayGameMode->CurRoom->RoomPos.Y + (52.0f * (3.5f)))
				{
					FuturePos -= Dir * 52.0f;
					FSM.ChangeState(LarryjrState::UpMove);
				}
				else
				{
					FuturePos += (Dir * (52.0f));
					FSM.ChangeState(LarryjrState::DownMove);
				}
			}
			else if (FVector2D::LEFT == Dir)
			{
				NextFuturePos = FuturePos + (Dir * 52.0f);
				if (NextFuturePos.X < PlayGameMode->CurRoom->RoomPos.X + (52.0f * (-6.5f)))
				{
					FuturePos -= Dir * 52.0f;
					FSM.ChangeState(LarryjrState::RightMove);
				}
				else
				{
					FuturePos += (Dir * (52.0f));
					FSM.ChangeState(LarryjrState::LeftMove);
				}
			}

			
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
		FuturePos = LinkedParts[LinkDir::Front]->GetActorLocation();
		FVector2D NewDir = FuturePos - GetActorLocation();

		int a = 0;

		if (NewDir.Y < -40.0f)
		{
			FSM.ChangeState(LarryjrState::UpMove);
		}
		else if (NewDir.X > 40.0f)
		{
			FSM.ChangeState(LarryjrState::RightMove);
		}
		else if (NewDir.Y > 40.0f)
		{
			FSM.ChangeState(LarryjrState::DownMove);
		}
		else if (NewDir.X < -40.0f)
		{
			FSM.ChangeState(LarryjrState::LeftMove);
		}

    }

}

void ALarryjr::UpMove(float _DeltaTime)
{

	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	    float ExpectPos = FuturePos.iY(); 
		FVector2D NewPos = GetActorLocation();
		float NewNewPos = NewPos.iY();
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
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	float ExpectPos = FuturePos.iX();
	FVector2D NewPos = GetActorLocation();
	float NewNewPos = NewPos.iX();
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
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	float ExpectPos = FuturePos.iY();
	FVector2D NewPos = GetActorLocation();
	float NewNewPos = NewPos.iY();
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
	if (this->Hp <= 0.0f || true == LinkedParts.empty())
	{
		DieStart();
	}

	float ExpectPos = FuturePos.iX();
	FVector2D NewPos = GetActorLocation();
	float NewNewPos = NewPos.iX();
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

		//FSM.ChangeState(LarryjrState::Move);

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