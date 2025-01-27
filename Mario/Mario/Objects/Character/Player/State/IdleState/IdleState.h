#pragma once

#include"../PlayerStateBase.h"

class IdleState : public PlayerStateBase
{
public:
	IdleState(class Player* p);
	virtual ~IdleState();

public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float) override;
	virtual void Draw() const override;

	//ó‘Ô‚Ìæ“¾
	virtual ePlayerState GetState() const override;
};