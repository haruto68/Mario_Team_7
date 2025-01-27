#pragma once
#include"../Player.h"

class PlayerStateBase
{

protected:
	//ƒvƒŒƒCƒ„[î•ñ
	class Player* player;

public:
	PlayerStateBase(class Player* p) : player(p)
	{
	}
	virtual ~PlayerStateBase() = default;


public:
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update(float) = 0;
	virtual void Draw() const = 0;

	//ó‘Ô‚Ìæ“¾
	virtual ePlayerState GetState() const = 0;
};