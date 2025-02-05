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

Player::~Player()
{

}

void Player::Initialize()
{

}

void Player::Update(float delta_seconds)
{
	////state�̕ύX����
	//if (next_state != ePlayerState::NONE)
	//{
	//	state = PlayerStateFactory::Get((*this), next_state);
	//	next_state = ePlayerState::NONE;
	//}
	////��ԕʂ̍X�V�������s��
	//state->Update(delta_seconds);

	Movement(delta_seconds);

	Animation();
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	// BoxSize�`��
	//DrawBox(location.x - (int)(D_HARF), location.y - (int)(D_HARF), location.x + (int)(D_HARF), location.y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
	// velocity.y�m�F
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
	// �ړ��X�s�[�h
	float speed = 200.0f;
	// �ړ�����
	float direction = 0.0f;

	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();


	//���͏�Ԃɂ���Č�����ύX����
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))		//���ړ�
	{
		direction = -1.0f;
		flip_flag = TRUE;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//�E�ړ�
	{
		direction = 1.0f;
		flip_flag = FALSE;
	}

	//�W�����v
	if (input->GetKeyDown(KEY_INPUT_J) && is_jump == false)
	{
		is_jump = true;

		velocity.y = -20.0f;
	}

	//�����ɂ���āA�ړ��ʂ̉������s��
	if (direction != 0.0f)
	{
		//�ō����x�𒴂��Ȃ��悤�ɂ���
		float max_speed = Abs<float>((5.0f * 0.5 * direction));
		velocity.x += 0.5 * direction;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
	}
	else
	{
		//��������
		if (velocity.x < -1e-6f)		//-1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//���ړ��̌���
			float calc_speed = velocity.x + 0.015f;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.x > 1e-6f)	//1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//�E�ړ��̌���
			float cale_spped = velocity.x - 0.015f;
			velocity.x = Max<float>(cale_spped, 0.0f);
		}
	}

	// �ړ����Ă��邩
	if (velocity.x != 0.0f)
	{
		next_state = ePlayerState::RUN;
	}
	else
	{
		next_state = ePlayerState::IDLE;
	}

	//����ʒ[
	if (location.x < (collision.box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = collision.box_size.x / 2.0f;
	}
	//��ʒ���
	if ((location.x + velocity.x) >= (D_WIN_MAX_X / 2))
	{
		//��ʈړ��ʎ擾
		screen_velocity = -velocity.x;
		velocity.x = 0.0;
	}

	//�d��
	velocity.y += 0.98f * 0.25f;

	//�n�ʔ���i���j
	if ((location.y + velocity.y) >= (D_MONO * 13 - D_HARF))
	{
		is_jump = false;
		velocity.y = 0.0f;
	}

	if (is_jump)
	{
		next_state = ePlayerState::JUMP;
	}

	//�ʒu���W�������x�����炷
	location += velocity * speed * delta_seconds;

}

void Player::Animation()
{
	switch (next_state)
	{
	case IDLE:	// �ҋ@�A�j���[�V����
		image = mario_images[0];
		break;
	case RUN:	// �ړ��A�j���[�V����
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
	case JUMP:	// �W�����v�A�j���[�V����
		image = mario_images[5];
		break;
	}

}