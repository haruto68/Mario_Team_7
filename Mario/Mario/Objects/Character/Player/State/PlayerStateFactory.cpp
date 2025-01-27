#include"PlayerStateFactory.h"

#include"IdleState/IdleState.h"
#include"JumpState/JumpState.h"
#include"RunState/RunState.h"

#include"../Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

void PlayerStateFactory::Initialize(class Player& player)
{
	idle = new IdleState(&player);
	jump = new JumpState(&player);
	run = new RunState(&player);
}

void PlayerStateFactory::Finalize()
{
	instance->idle->Finalize();
	instance->jump->Finalize();

	delete instance->idle;
	delete instance->jump;
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	if (instance == nullptr)
	{
		instance = new PlayerStateFactory();
		instance->Initialize(player);
	}

	PlayerStateBase* ret = nullptr;

	switch (state)
	{
	case ePlayerState::IDLE:
		instance->idle->Initialize();
		ret = instance->idle;
		break;
	case ePlayerState::JUMP:
		instance->jump->Initialize();
		ret = instance->jump;
		break;
	case ePlayerState::RUN:
		instance->run->Initialize();
		ret = instance->run;
	case ePlayerState::NONE:
	default:
		break;
	}
	return ret;
}
