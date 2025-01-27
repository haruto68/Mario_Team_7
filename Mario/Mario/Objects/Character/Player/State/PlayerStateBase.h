#pragma once
#include"../Player.h"

class PlayerStateBase
{

protected:
	//�v���C���[���
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

	//��Ԃ̎擾
	virtual ePlayerState GetState() const = 0;
};