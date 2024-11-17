#include "PreCompile.h"
#include "Larryjr.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include "TrapDoor.h"
#include "Poop.h"


ALarryjr::ALarryjr()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

		MonsterRenderer->SetComponentScale({ 100, 100 });
		MonsterRenderer->SetComponentLocation({ 0,-20 });

		MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Head_Larryjr_Left", "Boss_Larryjr_Left.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Head_Larryjr_Up", "Boss_Larryjr_Left.png", 2, 3, 0.1f);
		MonsterRenderer->CreateAnimation("Head_Larryjr_Down", "Boss_Larryjr_Left.png", 4, 5, 0.1f);
		MonsterRenderer->CreateAnimation("Body_Larryjr_Left", "Boss_Larryjr_Left.png", 6, 7, 0.1f);
		MonsterRenderer->CreateAnimation("Body_Larryjr_Down", "Boss_Larryjr_Left.png", 8, 9, 0.1f);
		MonsterRenderer->CreateAnimation("Tail_Larryjr_Up", "Boss_Larryjr_Left.png", 10, 11, 0.1f);
		MonsterRenderer->CreateAnimation("Body_Larryjr_Up", "Boss_Larryjr_Left.png", 12, 13, 0.1f);
		MonsterRenderer->CreateAnimation("Die_Larryjr", "BloodPoof.png", 12, 13, 0.1f);

		MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
	}

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetSpriteScale(0.5f);


	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 100, 100 });
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	DebugOn();

	SetHp(250.0f);

}

ALarryjr::~ALarryjr()
{
}

void ALarryjr::BeginPlay()
{
	Super::BeginPlay();

	HeadFuturePos = GetActorLocation();
	DelayTime = 1.0f;

	FSM.CreateState(LarryjrState::Move, std::bind(&ALarryjr::Move, this, std::placeholders::_1),
		[this]()
		{

			MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
		}
	);

	FSM.CreateState(LarryjrState::Poop, std::bind(&ALarryjr::Poop, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(LarryjrState::Separate, std::bind(&ALarryjr::Separate, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(LarryjrState::Die, std::bind(&ALarryjr::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
		}
	);


	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->BGMPlayer.Off();
	PlayGameMode->BGMPlayer = UEngineSound::Play("basic boss fight.ogg");
	FSM.ChangeState(LarryjrState::Move);
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
void ALarryjr::UpMove(float _DeltaTime)
{
	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(LarryjrState::Die);
	}

	FVector2D Pos = { 0.0f,-1.0f };
	AddActorLocation( Pos * _DeltaTime * Speed);

}

void ALarryjr::Poop(float _DeltaTime)
{
	

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(LarryjrState::Die);
	}

	if (LarryjrPart::TAIL == this->Part)
	{
		APoop* NewPoop = GetWorld()->SpawnActor<APoop>();
		NewPoop->SetActorLocation(GetActorLocation());
	}

		FSM.ChangeState(LarryjrState::Move);

}

void ALarryjr::Separate(float _DeltaTime)
{
	

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		
		DelayTime = 0.0f;

		LinkedParts[Dir::Front]->Part = LarryjrPart::TAIL;
		LinkedParts[Dir::Back]->Part = LarryjrPart::HEAD;

		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(LarryjrState::Die);

	}

       FSM.ChangeState(LarryjrState::Move);

}

void ALarryjr::Die(float _DeltaTime)
{
	DeathValue = true;
	DelayTime += _DeltaTime;



	if (DelayTime > 1.1f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->BGMPlayer.Off();
		PlayGameMode->BGMPlayer = UEngineSound::Play("secret to everyone.ogg");
		Destroy();
	}
}