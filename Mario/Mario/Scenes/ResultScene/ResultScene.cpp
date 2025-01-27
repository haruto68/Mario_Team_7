#include"ResultScene.h"
#include"../../Utility/InputManager.h"

ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{

}

eSceneType ResultScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//�^�C�g���V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	DrawFormatString(318, 360, 0xffffff, "���U���g�V�[��");
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}