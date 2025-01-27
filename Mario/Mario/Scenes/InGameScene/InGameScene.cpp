#include"InGameScene.h"
#include"../../Utility/InputManager.h"

#include"../../Objects/GameObjectManager.h"

InGameScene::InGameScene() :
	object_manager(),
	player(),
	scene_objects_list()
{

}

InGameScene::~InGameScene()
{
	// �I�u�W�F�N�g���X�g����Ȃ珈�����I������
	if (scene_objects_list.empty())
	{
		return;
	}
	// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���폜����
	for (GameObject* obj : scene_objects_list)
	{
		obj->Finalize();
		delete obj;
	}
	// ���I�z��̉��
	scene_objects_list.clear();
}

void InGameScene::Initialize()
{
	//GameObjectManager�C���X�^���X�擾
	object_manager = new GameObjectManager();

	//�}���I����
	player = object_manager->CreateGameObject<Player>(Vector2D((D_MONO * 3), (D_MONO * 13 - D_HARF)));

	// �w�i����
	LoadBackGroound();
	// �n�`����
	LoadGround();
	// �u���b�N����
	LoadBlock();
}

eSceneType InGameScene::Update(const float& delta_seconds)
{
	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	// ���͏��̍X�V
	input->Update();

	// ��������I�u�W�F�N�g�̊m�F
	object_manager->CheckCreateObject();
	// �j������I�u�W�F�N�g�̊m�F
	object_manager->CheckDestroyObject();
	// ���݂̃I�u�W�F�N�g���X�g���擾
	scene_objects_list = object_manager->GetObjectList();

	// ���X�g���̃I�u�W�F�N�g���X�V����
	for (GameObject* obj : scene_objects_list)
	{
		obj->Update(delta_seconds);
	}

	//�����蔻��`�F�b�N
	for (int a = 0; a < scene_objects_list.size(); a++)
	{
		for (int b = 0; b < scene_objects_list.size(); b++)
		{
			// �Ȃ����t���[�Y����̂ŕ���i�������[�v�ł͂Ȃ��H�j
			/*object_manager->HitCheck(scene_objects_list[a], scene_objects_list[b]);
			object_manager->HitCheck(scene_objects_list[b], scene_objects_list[a]);*/
		}
	}

	// ��ʈړ��ʂ̎擾
	screen_offset += player->GetScreenVelocity();

	//���U���g�V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eResult;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	if (scene_objects_list.empty())
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(screen_offset);
	}
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

// �w�i����
void InGameScene::LoadBackGroound()
{
	//�󐶐�
	LoadSky(1, 1, 213, 15);
	//�R����
	LoadMountain(1, 11, 5, 13);
	LoadMountain(17, 12, 19, 13);
	LoadMountain(49, 11, 53, 13);
	LoadMountain(65, 12, 67, 13);
	LoadMountain(97, 11, 101, 13);
	LoadMountain(113, 12, 115, 13);
	LoadMountain(145, 11, 149, 13);
	LoadMountain(161, 12, 163, 13);
	LoadMountain(193, 11, 197, 13);
	LoadMountain(209, 12, 211, 13);
	//�ΐ���
	LoadBushes(12, 13, 16, 13);
	LoadBushes(24, 13, 26, 13);
	LoadBushes(42, 13, 45, 13);
	LoadBushes(60, 13, 64, 13);
	LoadBushes(72, 13, 74, 13);
	LoadBushes(90, 13, 93, 13);
	LoadBushes(108, 13, 112, 13);
	LoadBushes(120, 13, 122, 13);
	LoadBushes(138, 13, 141, 13);
	LoadBushes(158, 13, 160, 13);
	LoadBushes(168, 13, 170, 13);
	LoadBushes(206, 13, 208, 13);
	//�󐶐�
	LoadCloud(9, 4, 11, 5);
	LoadCloud(0, 3, 0, 4);
	LoadCloud(20, 4, 22, 5);
	LoadCloud(28, 3, 32, 4);
	LoadCloud(37, 4, 40, 5);
	LoadCloud(57, 3, 59, 4);
	LoadCloud(68, 4, 70, 5);
	LoadCloud(76, 3, 80, 4);
	LoadCloud(85, 4, 88, 5);
	LoadCloud(105, 3, 107, 4);
	LoadCloud(116, 4, 118, 5);
	LoadCloud(124, 3, 128, 4);
	LoadCloud(133, 4, 136, 5);
	LoadCloud(153, 3, 155, 4);
	LoadCloud(164, 4, 166, 5);
	LoadCloud(172, 3, 176, 4);
	LoadCloud(181, 4, 184, 5);
	LoadCloud(201, 3, 203, 4);
	//�鐶��
	LoadCastle(203, 9, 207, 13);
}
// �ΐ���
void InGameScene::LoadBushes(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;

	//��
	x = D_MONO * x_start - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::BUSHES);
	bg->SetImageNum(0);
	//�E
	x = D_MONO * x_last - D_HARF;
	y = D_MONO * y_last - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::BUSHES);
	bg->SetImageNum(2);
	//�^��
	for (int i = x_start + 1; i <= x_last - 1; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * y_start - D_HARF;
			bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
			bg->SetBackGroundState(eBackGroundState::BUSHES);
			bg->SetImageNum(1);
		}
	}
}
// �R����
void InGameScene::LoadMountain(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;
	int i;

	//��
	x = D_MONO * ((x_start + x_last) / 2) - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
	bg->SetImageNum(0);
	//��
	for (i = 0; i < (y_last - y_start); i++)
	{
		//�X��
		x = D_MONO * (x_start + i) - D_HARF;
		y = D_MONO * (y_last - i) - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
		bg->SetImageNum(1);
		//����(�͗l����)
		x = D_MONO * (x_start + i + 1) - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
		bg->SetImageNum(5);
	}
	//�E
	for (i = 0; i < (y_last - y_start); i++)
	{
		//�X��
		x = D_MONO * (x_last - i) - D_HARF;
		y = D_MONO * (y_last - i) - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
		bg->SetImageNum(2);

		if (i > 0)
		{
			//����(�͗l����)
			x = D_MONO * (x_last - i) - D_HARF;
			y = D_MONO * (y_last - i + 1) - D_HARF;
			bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
			bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
			bg->SetImageNum(4);
			//����(�͗l�Ȃ�)
			x = D_MONO * (x_last - i - 1) - D_HARF;
			bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
			bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
			bg->SetImageNum(3);
		}
	}
}
// �_����
void InGameScene::LoadCloud(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;

	//��
	x = D_MONO * x_start - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CLOUD);
	bg->SetImageNum(0);
	y = D_MONO * y_last - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CLOUD);
	bg->SetImageNum(3);
	//�^��
	for (int i = x_start + 1; i <= x_last - 1; i++)
	{
		x = D_MONO * i - D_HARF;
		y = D_MONO * y_start - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::CLOUD);
		bg->SetImageNum(1);
		y = D_MONO * y_last - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::CLOUD);
		bg->SetImageNum(4);
	}
	//�E
	x = D_MONO * x_last - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CLOUD);
	bg->SetImageNum(2);
	y = D_MONO * y_last - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CLOUD);
	bg->SetImageNum(5);
}
// �󐶐�
void InGameScene::LoadSky(int x_start, int y_start, int x_last, int y_last)
{
	//�n�ʐ���
	BackGround* bg;
	float x;
	float y;

	for (int i = x_start; i <= x_last; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * j - D_HARF;
			bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
			bg->SetBackGroundState(eBackGroundState::SKY);
		}
	}
}
// �鐶��
void InGameScene::LoadCastle(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;

	x = D_MONO * ((x_start + x_last) / 2) - D_HARF;
	y = D_MONO * ((y_start + y_last) / 2) - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CASTLE);
}
// �n�`����
void InGameScene::LoadGround()
{
	//�n�ʐ���
	LoadFloor(1, 14, 69, 15);
	LoadFloor(72, 14, 86, 15);
	LoadFloor(90, 14, 153, 15);
	LoadFloor(156, 14, 213, 15);
	//�K�i����
	LoadStairs(135, 13, 138, 13);
	LoadStairs(136, 12, 138, 12);
	LoadStairs(137, 11, 138, 11);
	LoadStairs(138, 10, 138, 10);
	LoadStairs(141, 10, 141, 10);
	LoadStairs(141, 11, 142, 11);
	LoadStairs(141, 12, 143, 12);
	LoadStairs(141, 13, 144, 13);
	LoadStairs(149, 13, 153, 13);
	LoadStairs(150, 12, 153, 12);
	LoadStairs(151, 11, 153, 11);
	LoadStairs(152, 10, 153, 10);
	LoadStairs(156, 10, 156, 10);
	LoadStairs(156, 11, 157, 11);
	LoadStairs(156, 12, 158, 12);
	LoadStairs(156, 13, 159, 13);
	LoadStairs(182, 13, 190, 13);
	LoadStairs(183, 12, 190, 12);
	LoadStairs(184, 11, 190, 11);
	LoadStairs(185, 10, 190, 10);
	LoadStairs(186, 9, 190, 9);
	LoadStairs(187, 8, 190, 8);
	LoadStairs(188, 7, 190, 7);
	LoadStairs(189, 6, 190, 6);
	LoadStairs(199, 13, 199, 13);
	//�y�ǐ���
	LoadPipe(29, 12, 30, 13);
	LoadPipe(39, 11, 40, 13);
	LoadPipe(47, 10, 48, 13);
	LoadPipe(58, 10, 59, 13);
	LoadPipe(164, 12, 165, 13);
	LoadPipe(180, 12, 181, 13);
}
// �n�ʐ���
void InGameScene::LoadFloor(int x_start, int y_start, int x_last, int y_last)
{
	Ground* g;
	float x;
	float y;

	for (int i = x_start; i <= x_last; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * j - D_HARF;
			g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
			g->SetGroundState(eGroundState::FLOOR);
		}
	}
}
// �K�i����
void InGameScene::LoadStairs(int x_start, int y_start, int x_last, int y_last)
{
	Ground* g;
	float x;
	float y;

	for (int i = x_start; i <= x_last; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * j - D_HARF;
			g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
			g->SetGroundState(eGroundState::STAIRS);
		}
	}
}
// �y�ǐ���
void InGameScene::LoadPipe(int x_start, int y_start, int x_last, int y_last)
{
	Ground* g;
	float x;							//x���W
	float y;							//y���W
	int height = (y_last - y_start);	//����
	int n = 0;							//�摜����

	//����
	x = D_MONO * (x_start++) - D_HARF;
	y = D_MONO * (y_start)-D_HARF;
	g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
	g->SetGroundState(eGroundState::PIPE);
	g->SetPipeNum(n++);
	//�E��
	x = D_MONO * (x_start--) - D_HARF;
	y = D_MONO * (y_start++) - D_HARF;
	g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
	g->SetGroundState(eGroundState::PIPE);
	g->SetPipeNum(n++);

	//��
	for (int j = 0; j < height; j++)
	{
		//��
		x = D_MONO * (x_start++) - D_HARF;
		y = D_MONO * (y_start)-D_HARF;
		g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
		g->SetGroundState(eGroundState::PIPE);
		g->SetPipeNum(n++);
		//�E
		x = D_MONO * (x_start--) - D_HARF;
		y = D_MONO * (y_start++) - D_HARF;
		g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
		g->SetGroundState(eGroundState::PIPE);
		g->SetPipeNum(n--);
	}
}
// �u���b�N����
void InGameScene::LoadBlock()
{
	//�n�e�i�u���b�N����
	LoadQuestion(17, 10, 17, 10, COIN);
	LoadQuestion(22, 10, 22, 10, RED);
	LoadQuestion(23, 6, 23, 6, COIN);
	LoadQuestion(24, 10, 24, 10, COIN);
	LoadQuestion(79, 10, 79, 10, RED);
	LoadQuestion(95, 6, 95, 6, COIN);
	LoadQuestion(107, 10, 107, 10, COIN);
	LoadQuestion(110, 6, 110, 6, RED);
	LoadQuestion(110, 10, 110, 10, COIN);
	LoadQuestion(113, 10, 113, 10, COIN);
	LoadQuestion(130, 6, 130, 6, COIN);
	LoadQuestion(131, 6, 131, 6, COIN);
	LoadQuestion(171, 10, 171, 10, COIN);
	//�����K�u���b�N����
	LoadBrick(21, 10, 21, 10, DEFAULT);
	LoadBrick(23, 10, 23, 10, DEFAULT);
	LoadBrick(25, 10, 25, 10, DEFAULT);
	LoadBrick(78, 10, 78, 10, DEFAULT);
	LoadBrick(80, 10, 80, 10, DEFAULT);
	LoadBrick(81, 6, 88, 6, DEFAULT);
	LoadBrick(92, 6, 94, 6, DEFAULT);
	LoadBrick(95, 10, 95, 10, COIN_10);
	LoadBrick(101, 10, 101, 10, DEFAULT);
	LoadBrick(102, 10, 102, 10, STAR);
	LoadBrick(119, 10, 119, 10, DEFAULT);
	LoadBrick(122, 6, 124, 6, DEFAULT);
	LoadBrick(129, 6, 129, 6, DEFAULT);
	LoadBrick(130, 10, 131, 10, DEFAULT);
	LoadBrick(132, 6, 132, 6, DEFAULT);
	LoadBrick(169, 10, 170, 10, DEFAULT);
	LoadBrick(172, 10, 172, 10, DEFAULT);
	//�����u���b�N����
	LoadHidden(65, 9, 65, 9, GREEN);
}
// �n�e�i�u���b�N����
void InGameScene::LoadQuestion(int x_start, int y_start, int x_last, int y_last, eContentsState state)
{
	Block* b;
	float x;
	float y;

	for (int i = x_start; i <= x_last; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * j - D_HARF;
			b = object_manager->CreateGameObject<Block>(Vector2D(x, y));
			b->SetBlockState(eBlockState::QUESTION);
			b->SetContentsState(state);
		}
	}
}
// �����K�u���b�N����
void InGameScene::LoadBrick(int x_start, int y_start, int x_last, int y_last, eContentsState state)
{
	Block* b;
	float x;
	float y;

	for (int i = x_start; i <= x_last; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * j - D_HARF;
			b = object_manager->CreateGameObject<Block>(Vector2D(x, y));
			b->SetBlockState(eBlockState::BRICK);
			b->SetContentsState(state);
		}
	}
}
// �����u���b�N����
void InGameScene::LoadHidden(int x_start, int y_start, int x_last, int y_last, eContentsState state)
{
	Block* b;
	float x;
	float y;

	for (int i = x_start; i <= x_last; i++)
	{
		for (int j = y_start; j <= y_last; j++)
		{
			x = D_MONO * i - D_HARF;
			y = D_MONO * j - D_HARF;
			b = object_manager->CreateGameObject<Block>(Vector2D(x, y));
			b->SetBlockState(eBlockState::HIDDEN);
			b->SetContentsState(state);
		}
	}
}