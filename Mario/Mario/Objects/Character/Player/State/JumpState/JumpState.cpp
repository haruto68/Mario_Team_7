#include"JumpState.h"

#include"DxLib.h"
#include"../../../../../Utility/InputManager.h"
#include"../../Player.h"

JumpState::JumpState(class Player* p)
	: PlayerStateBase(p)
	, old_location(player->GetLocation())
	, up_acceleration(0.0f)
	, down_acceleration(0.0f)
{

}

JumpState::~JumpState()
{

}

void JumpState::Initialize()
{
	up_acceleration = -1.0f;
}

void JumpState::Finalize()
{

}

void JumpState::Update(float delta_seconds)
{
	// “ü—Í‹@”\ƒCƒ“ƒXƒ^ƒ“ƒXŽæ“¾
	InputManager* input = InputManager::GetInstance();


	//‰Á‘¬“x
	Vector2D velocity = 0.0f;
	up_acceleration += 0.01f;
	/*if (up_acceleration > 0.0f)
	{
		up_acceleration = 0.0f;
	}*/
	velocity.y += up_acceleration;


	////’n–Ê‚ÉG‚ê‚½‚ç
	//if (player->GetIsJump() == false)
	//{
	//	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	//	{
	//		//ˆÚ“®ó‘Ô‚É‘JˆÚ
	//		player->SetNextState(ePlayerState::RUN);
	//	}
	//	else
	//	{
	//		//’âŽ~ó‘Ô‚É‘JˆÚ
	//		player->SetNextState(ePlayerState::IDLE);
	//	}
	//}

	// ã¸‰Á‘¬“x‚ª0ˆÈã‚É‚È‚Á‚½‚ç
	if (up_acceleration >= 0.0f)
	{
		if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
		{
			//ˆÚ“®ó‘Ô‚É‘JˆÚ
			player->SetNextState(ePlayerState::RUN);
		}
		else
		{
			//’âŽ~ó‘Ô‚É‘JˆÚ
			player->SetNextState(ePlayerState::IDLE);
		}
	}



	//‰Á‘¬“xƒZƒbƒg
	player->SetVelocity(velocity);
	
}

void JumpState::Draw() const
{
	//
	DrawFormatString(100, 140, 0x000000, "JUMP");

	DrawFormatString(100, 300, 0x000000, "%.3f", up_acceleration);

	//À•Wî•ñ‚ð®”’l‚É•ÏŠ·
	int x = 0, y = 0;
	x = (int)player->GetLocation().x;
	y = (int)player->GetLocation().y;

	//•`‰æ
	DrawBox(x - (int)(D_HARF), y - (int)(D_HARF), x + (int)(D_HARF), y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
}

ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}