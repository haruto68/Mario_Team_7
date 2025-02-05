#pragma once

#include"../Character.h"

// プレイヤー状態
enum ePlayerState
{
	IDLE,
	RUN,
	JUMP,
	NONE
};
// パワーアップ状態
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

	ePlayerState next_state;	// 次状態
	ePowerUp power_up;			// パワーアップ状態
	bool is_star;				// スター状態
	int invincible_count;		// 無敵時間
	int get_coin;				// 獲得コイン
	int lives;					// 残機

	bool is_jump;				// ジャンプしてるか

	float screen_velocity;		// スクリーン移動量

public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

public:
	Vector2D GetScreenVelocity();
	Vector2D GetVelocity();
	void SetVelocity(Vector2D);
	void SetNextState(ePlayerState);

	int GetCoin();
	int GetLive();

	bool GetIsJump();
	void SetIsJump(bool);

	void Movement(float);
	void Animation();
};