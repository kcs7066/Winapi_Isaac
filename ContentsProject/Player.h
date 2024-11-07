#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

enum class PlayerState
{
	Idle,
	Move,
	Jump,
};

class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();


protected:

private:
	float Speed = 500.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;
	PlayerState CurPlayerState = PlayerState::Idle;

	void ChangeState(PlayerState CurPlayerState);

	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);




};