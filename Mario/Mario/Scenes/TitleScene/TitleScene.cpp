#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

TitleScene::TitleScene() :
	mario_images(),
	ui_coin_images(),
	symbol_images(),
	string_images(),
	back_ground_image(0),
	st_mario_image(0),
	st_world_image(0),
	st_time_image(0),
	st_top_image(0)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	//�摜�擾
	mario_images = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	ui_coin_images = rm->GetImages("Resource/Images/UI/uicoin.png", 4, 4, 1, 16, 16);
	symbol_images = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	string_images = rm->GetImages("Resource/Images/UI/string.png", 26, 26, 1, 16, 16);

	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
	st_mario_image = rm->GetImages("Resource/Images/UI/name_mario.png")[0];
	st_world_image = rm->GetImages("Resource/Images/UI/world.png")[0];
	st_time_image = rm->GetImages("Resource/Images/UI/time.png")[0];
	st_top_image = rm->GetImages("Resource/Images/UI/top.png")[0];
}

eSceneType TitleScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//�C���Q�[���V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}
	
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	// �w�i
	DrawRotaGraph(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, SIZE, 0.0, back_ground_image, TRUE);
	// �}���I
	DrawRotaGraph((D_MONO * 3), (D_MONO * 13 - D_HARF), SIZE, 0.0, mario_images[0], TRUE);
	// UI
	DrawRotaGraph(132, 60, SIZE, 0.0, st_mario_image, TRUE);
	DrawRotaGraph(492, 60, SIZE, 0.0, st_world_image, TRUE);
	DrawRotaGraph(648, 60, SIZE, 0.0, st_time_image, TRUE);
	// �X�R�A
	DrawRotaGraph((D_HARF * 4 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 5 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 6 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 7 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 8 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 9 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	// �R�C��
	DrawRotaGraph((D_HARF * 12 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, ui_coin_images[0], TRUE);
	DrawRotaGraph((D_HARF * 13 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[11], TRUE);
	DrawRotaGraph((D_HARF * 14 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 15 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	// ���[���h
	DrawRotaGraph((D_HARF * 20 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[1], TRUE);
	DrawRotaGraph((D_HARF * 21 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[10], TRUE);
	DrawRotaGraph((D_HARF * 22 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[1], TRUE);
	// START�{�^��
	int st_PLAY[4] = { 15,11,0,24 };
	for (int i = 0; i < 4; i++)
	{
		DrawRotaGraph(300 + (24 * i), 492, SIZE, 0.0, string_images[st_PLAY[i]], TRUE);
	}
	int st_GAME[4] = { 6,0,12,4 };
	for (int i = 0; i < 4; i++)
	{
		DrawRotaGraph(420 + (24 * i), 492, SIZE, 0.0, string_images[st_GAME[i]], TRUE);
	}
	// ����N
	/*int sy_C1985[5] = { 13,1,9,8,5 };
	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraph(372 + (24 * i), 420, SIZE, 0.0, symbol_images[sy_C1985[i]], TRUE);
	}
	int st_NINTENDO[8] = { 13,8,13,19,4,13,3,14 };
	for (int i = 0; i < 8; i++)
	{
		DrawRotaGraph(516 + (24 * i), 420, SIZE, 0.0, string_images[st_NINTENDO[i]], TRUE);
	}*/
	// �n�C�X�R�A
	//DrawRotaGraph(336, 564, SIZE, 0.0, st_top_image, TRUE);
}

void TitleScene::Finalize()
{
	mario_images.clear();
	ui_coin_images.clear();
	symbol_images.clear();
	string_images.clear();
}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}