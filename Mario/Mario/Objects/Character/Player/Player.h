#pragma once

#include"../Character.h"

// �v���C���[���
enum ePlayerState
{
	IDLE,
	RUN,
	JUMP,
	NONE
};
// �p���[�A�b�v���
enum ePowerUp
{
	NORMAL,
	BIG,
	FIRE
};

class Player : public Character
{
protected:
	std::vector<int> mario_images;

private:
	class PlayerStateBase* state = nullptr;

	ePlayerState next_state;	// �����
	ePowerUp power_up;			// �p���[�A�b�v���
	bool is_star;				// �X�^�[���
	int invincible_count;		// ���G����
	int get_coin;				// �l���R�C��
	int lives;					// �c�@

	bool is_jump;				// �W�����v���Ă邩

	float screen_velocity;		// �X�N���[���ړ���

public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&) const override;
	virtual void Finalize() override;

public:
	Vector2D GetScreenVelocity();
	Vector2D GetVelocity();
	void SetVelocity(Vector2D);
	void SetNextState(ePlayerState);

	bool GetIsJump();
	void SetIsJump(bool);
};