#pragma once

#include"../PlayerStateBase.h"

class JumpState : public PlayerStateBase
{
private:
	Vector2D old_location;

	float up_acceleration;
	float down_acceleration;

public:
	JumpState(class Player* p);
	virtual ~JumpState();

public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float) override;
	virtual void Draw() const override;

	//ó‘Ô‚Ìæ“¾
	virtual ePlayerState GetState() const override;
};