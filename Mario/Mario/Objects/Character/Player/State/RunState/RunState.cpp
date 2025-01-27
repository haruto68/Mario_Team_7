#include"RunState.h"

#include"DxLib.h"
#include"../../../../../Utility/InputManager.h"
#include"../../Player.h"

RunState::RunState(class Player* p)
	: PlayerStateBase(p)
{

}

RunState::~RunState()
{

}

void RunState::Initialize()
{

}

void RunState::Finalize()
{

}

void RunState::Update(float delta_seconds)
{
	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_J))
	{
		player->SetIsJump(true);
		player->SetNextState(ePlayerState::JUMP);
	}

	//停止状態に遷移
	if (!(input->GetKey(KEY_INPUT_A)) || !(input->GetKey(KEY_INPUT_D)))
	{
		player->SetNextState(ePlayerState::IDLE);
	}

	if(player->GetLocation().y <= (D_MONO * 13 - D_HARF))
	{
	}
	Move(delta_seconds);
}

void RunState::Draw() const
{
	//
	DrawFormatString(100, 120, 0x000000, "RUN");

	//座標情報を整数値に変換
	int x = 0, y = 0;
	x = (int)player->GetLocation().x;
	y = (int)player->GetLocation().y;

	//描画
	DrawBox(x - (int)(D_HARF), y - (int)(D_HARF), x + (int)(D_HARF), y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
}

ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}

void RunState::Move(float delta_seconds)
{
	// 加速度
	Vector2D velocity = 0.0f;
	// 移動スピード
	float speed = 500.0f;

	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	// 入力情報の更新
	input->Update();

	// 右移動
	if (input->GetKey(KEY_INPUT_D))
	{
		velocity.x += 1.0f;
	}
	// 左移動
	if (input->GetKey(KEY_INPUT_A))
	{
		velocity.x -= 1.0f;
	}

	//加速度をプレイヤーにセット
	player->SetVelocity(velocity);
	velocity = 0.0f;
}