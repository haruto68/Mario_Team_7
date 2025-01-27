#pragma once

#include"../PlayerStateBase.h"

class RunState : public PlayerStateBase
{
public:
	RunState(class Player* p);
	virtual ~RunState();

public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float) override;
	virtual void Draw() const override;

	//��Ԃ̎擾
	virtual ePlayerState GetState() const override;

	void Move(float);
};