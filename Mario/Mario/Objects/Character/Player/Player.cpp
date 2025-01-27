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
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// ���W
	location = Vector2D((D_MONO * 3), (D_MONO * 13 - D_HARF));
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(D_MONO, D_MONO);
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);
	// �摜�ݒ�
	mario_images = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	image = mario_images[0];
	// ���C���[�ݒ�
	z_layer = 2;
	// �����ݒ�
	is_mobility = true;


	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
}

void Player::Update(float delta_seconds)
{
	// �ړ��X�s�[�h
	float speed = 2000.0f;
	//Move(delta_seconds);

	//state�̕ύX����
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//��ԕʂ̍X�V�������s��
	state->Update(delta_seconds);

	
	// ����ʒ[�`�F�b�N
	if ((location.x + velocity.x) <= D_HARF)
	{
		velocity.x = 0.0;
	}
	// ��ʈړ��ʎ擾
	if ((location.x + velocity.x) >= (D_WIN_MAX_X / 2))
	{
		screen_velocity = -velocity.x * speed * delta_seconds;
		velocity.x = 0.0;
	}






	//�d�͑��x�̌v�Z
	if((location.y + velocity.y) < (D_MONO * 13 - D_HARF))
	{
		velocity.y += 0.5f;
	}



	//�n�ʔ���i���j
	if ((location.y + velocity.y) >= (D_MONO * 13 - D_HARF))
	{
		velocity.y = 0.0f;
	}
	else
	{
		is_jump = true;
	}




	//�����x�����W�ɉ��Z
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