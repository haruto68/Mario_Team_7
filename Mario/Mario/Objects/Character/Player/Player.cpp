#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"State/PlayerStateFactory.h"

Player::Player() : 
	mario_images(),
	next_state(ePlayerState::NONE),
	power_up(ePowerUp::NORMAL),
	is_star(false),
	invincible_count(0),
	get_coin(0),
	lives(0),
	is_jump(false),
	screen_velocity(0.0f)
{
	
}

Player::~Player()
{

}

void Player::Initialize()
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

void Player::Update(float delta_seconds)
{
	// 移動スピード
	float speed = 2000.0f;
	//Move(delta_seconds);

	//stateの変更処理
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//状態別の更新処理を行う
	state->Update(delta_seconds);

	
	// 左画面端チェック
	if ((location.x + velocity.x) <= D_HARF)
	{
		velocity.x = 0.0;
	}
	// 画面移動量取得
	if ((location.x + velocity.x) >= (D_WIN_MAX_X / 2))
	{
		screen_velocity = -velocity.x * speed * delta_seconds;
		velocity.x = 0.0;
	}

	screen_velocity = 0.0f;




	//重力速度の計算
	if((location.y + velocity.y) < (D_MONO * 13 - D_HARF))
	{
		velocity.y += 0.5f;
	}



	//地面判定（仮）
	if ((location.y + velocity.y) >= (D_MONO * 13 - D_HARF))
	{
		velocity.y = 0.0f;
	}
	else
	{
		is_jump = true;
	}




	//加速度を座標に加算
	location += velocity * speed * delta_seconds;
	velocity = 0.0f;

}

void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(0.0f);
	state->Draw();
	DrawFormatString(100, 50, 0x000000, "%.3f", velocity.y);

	DrawFormatString(250, 50, 0x000000, "X_%.3f", location.x);
	DrawFormatString(250, 70, 0x000000, "Y_%.3f", location.y);
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

bool Player::GetIsJump()
{
	return is_jump;
}

void Player::SetIsJump(bool is)
{
	is_jump = is;
}