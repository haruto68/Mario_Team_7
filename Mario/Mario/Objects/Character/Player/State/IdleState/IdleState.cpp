#include"IdleState.h"

#include"DxLib.h"
#include"../../../../../Utility/InputManager.h"
#include"../../Player.h"

IdleState::IdleState(class Player* p)
	: PlayerStateBase(p)
{

}

IdleState::~IdleState()
{

}

void IdleState::Initialize()
{

}

void IdleState::Finalize()
{

}

void IdleState::Update(float delta_seconds)
{
	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//移動状態に遷移
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	//ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_J))
	{
		//一旦ストップ
		player->SetIsJump(true);
		player->SetNextState(ePlayerState::JUMP);
	}
}

void IdleState::Draw() const
{
	//
	DrawFormatString(100, 100, 0x000000, "IDLE");

	//座標情報を整数値に変換
	int x = 0, y = 0;
	x = (int)player->GetLocation().x;
	y = (int)player->GetLocation().y;

	//描画
	DrawBox(x - (int)(D_HARF), y - (int)(D_HARF), x + (int)(D_HARF), y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
}

ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}