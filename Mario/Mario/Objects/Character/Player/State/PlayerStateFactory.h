#pragma once

#include"PlayerStateBase.h"

class PlayerStateFactory
{
	//シングルトーン用 ここから
private:
	static PlayerStateFactory* instance;

private:
	PlayerStateFactory() = default;
	PlayerStateFactory(const PlayerStateFactory&) = default;
	PlayerStateFactory& operator=(const PlayerStateFactory&) = default;
	//シングルトーン用 ここまで

private:
	class IdleState* idle;
	class JumpState* jump;
	class RunState* run;

private:
	void Initialize(class Player& player);

public:
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	static void Finalize();
};