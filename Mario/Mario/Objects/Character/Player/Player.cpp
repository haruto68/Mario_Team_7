#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"State/PlayerStateFactory.h"

#include"UserTemplate.h"

Player::Player() : 
	mario_images(),
	next_state(ePlayerState::NONE),
	power_up(ePowerUp::NORMAL),
	is_star(false),
	invincible_count(0),
	get_coin(0),
	lives(3),
	is_jump(false),
	screen_velocity(0.0f)
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	location = Vector2D((D_MONO * 3), (D_MONO * 13 - D_HARF));
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(D_MONO, D_MONO);
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);
	// 画像設定
	mario_images = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	image = mario_images[0];
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
}

Player::~Player()
{

}

void Player::Initialize()
{

}

void Player::Update(float delta_seconds)
{
	////stateの変更処理
	//if (next_state != ePlayerState::NONE)
	//{
	//	state = PlayerStateFactory::Get((*this), next_state);
	//	next_state = ePlayerState::NONE;
	//}
	////状態別の更新処理を行う
	//state->Update(delta_seconds);

	Movement(delta_seconds);

	Animation();
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	// BoxSize描画
	//DrawBox(location.x - (int)(D_HARF), location.y - (int)(D_HARF), location.x + (int)(D_HARF), location.y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
	// velocity.y確認
	//DrawFormatString(100, 50, 0x000000, "vel.y  %.2f", velocity.y);
}

void Player::Finalize()
{
	mario_images.clear();
}

Vector2D Player::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D Player::GetVelocity()
{
	return this->velocity;
}

void Player::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void Player::SetNextState(ePlayerState state)
{
	next_state = state;
}

int Player::GetCoin()
{
	return get_coin;
}

int Player::GetLive()
{
	return lives;
}

bool Player::GetIsJump()
{
	return is_jump;
}

void Player::SetIsJump(bool is)
{
	is_jump = is;
}

void Player::Movement(float delta_seconds)
{
	// 移動スピード
	float speed = 200.0f;
	// 移動方向
	float direction = 0.0f;

	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();


	//入力状態によって向きを変更する
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))		//左移動
	{
		direction = -1.0f;
		flip_flag = TRUE;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//右移動
	{
		direction = 1.0f;
		flip_flag = FALSE;
	}

	//ジャンプ
	if (input->GetKeyDown(KEY_INPUT_J) && is_jump == false)
	{
		is_jump = true;

		velocity.y = -20.0f;
	}

	//向きによって、移動量の加減を行う
	if (direction != 0.0f)
	{
		//最高速度を超えないようにする
		float max_speed = Abs<float>((5.0f * 0.5 * direction));
		velocity.x += 0.5 * direction;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
	}
	else
	{
		//減速する
		if (velocity.x < -1e-6f)		//-1e-6f = (0に限りなく近い負の値)
		{
			//左移動の減速
			float calc_speed = velocity.x + 0.015f;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.x > 1e-6f)	//1e-6f = (0に限りなく近い正の値)
		{
			//右移動の減速
			float cale_spped = velocity.x - 0.015f;
			velocity.x = Max<float>(cale_spped, 0.0f);
		}
	}

	// 移動しているか
	if (velocity.x != 0.0f)
	{
		next_state = ePlayerState::RUN;
	}
	else
	{
		next_state = ePlayerState::IDLE;
	}

	//左画面端
	if (location.x < (collision.box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = collision.box_size.x / 2.0f;
	}
	//画面中央
	if ((location.x + velocity.x) >= (D_WIN_MAX_X / 2))
	{
		//画面移動量取得
		screen_velocity = -velocity.x;
		velocity.x = 0.0;
	}

	//重力
	velocity.y += 0.98f * 0.25f;

	//地面判定（仮）
	if ((location.y + velocity.y) >= (D_MONO * 13 - D_HARF))
	{
		is_jump = false;
		velocity.y = 0.0f;
	}

	if (is_jump)
	{
		next_state = ePlayerState::JUMP;
	}

	//位置座標を加速度分減らす
	location += velocity * speed * delta_seconds;

}

void Player::Animation()
{
	switch (next_state)
	{
	case IDLE:	// 待機アニメーション
		image = mario_images[0];
		break;
	case RUN:	// 移動アニメーション
		anime_count++;
		if (anime_count > 60)
		{
			if (image == mario_images[1])
			{
				image = mario_images[2];
			}
			else if (image == mario_images[2])
			{
				image = mario_images[3];
			}
			else
			{
				image = mario_images[1];
			}
			anime_count = 0;
		}
		break;
	case JUMP:	// ジャンプアニメーション
		image = mario_images[5];
		break;
	}

}