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
	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//�ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	//�W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_J))
	{
		//��U�X�g�b�v
		player->SetIsJump(true);
		player->SetNextState(ePlayerState::JUMP);
	}
}

void IdleState::Draw() const
{
	//
	DrawFormatString(100, 100, 0x000000, "IDLE");

	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	x = (int)player->GetLocation().x;
	y = (int)player->GetLocation().y;

	//�`��
	DrawBox(x - (int)(D_HARF), y - (int)(D_HARF), x + (int)(D_HARF), y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
}

ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}