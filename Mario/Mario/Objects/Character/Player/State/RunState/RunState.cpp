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
	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//�W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_J))
	{
		player->SetIsJump(true);
		player->SetNextState(ePlayerState::JUMP);
	}

	//��~��ԂɑJ��
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

	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	x = (int)player->GetLocation().x;
	y = (int)player->GetLocation().y;

	//�`��
	DrawBox(x - (int)(D_HARF), y - (int)(D_HARF), x + (int)(D_HARF), y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
}

ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}

void RunState::Move(float delta_seconds)
{
	// �����x
	Vector2D velocity = 0.0f;
	// �ړ��X�s�[�h
	float speed = 500.0f;

	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	// ���͏��̍X�V
	input->Update();

	// �E�ړ�
	if (input->GetKey(KEY_INPUT_D))
	{
		velocity.x += 1.0f;
	}
	// ���ړ�
	if (input->GetKey(KEY_INPUT_A))
	{
		velocity.x -= 1.0f;
	}

	//�����x���v���C���[�ɃZ�b�g
	player->SetVelocity(velocity);
	velocity = 0.0f;
}