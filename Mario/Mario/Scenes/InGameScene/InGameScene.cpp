#include"InGameScene.h"
#include"../../Utility/InputManager.h"

#include"../../Objects/GameObjectManager.h"

InGameScene::InGameScene() :
	ui_coin_images(),
	symbol_images(),
	string_images(),
	st_mario_image(0),
	st_world_image(0),
	st_time_image(0),
	st_top_image(0),
	object_manager(),
	player(),
	scene_objects_list()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像取得
	ui_coin_images = rm->GetImages("Resource/Images/UI/uicoin.png", 4, 4, 1, 16, 16);
	symbol_images = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	string_images = rm->GetImages("Resource/Images/UI/string.png", 26, 26, 1, 16, 16);
	st_mario_image = rm->GetImages("Resource/Images/UI/name_mario.png")[0];
	st_world_image = rm->GetImages("Resource/Images/UI/world.png")[0];
	st_time_image = rm->GetImages("Resource/Images/UI/time.png")[0];
	st_top_image = rm->GetImages("Resource/Images/UI/top.png")[0];
}

InGameScene::~InGameScene()
{
	// オブジェクトリストが空なら処理を終了する
	if (scene_objects_list.empty())
	{
		return;
	}
	// オブジェクトリスト内のオブジェクトを削除する
	for (GameObject* obj : scene_objects_list)
	{
		obj->Finalize();
		delete obj;
	}
	// 動的配列の解放
	scene_objects_list.clear();
}

void InGameScene::Initialize()
{
	//GameObjectManagerインスタンス取得
	object_manager = new GameObjectManager();

	//マリオ生成
	player = object_manager->CreateGameObject<Player>(Vector2D((D_MONO * 3), (D_MONO * 13 - D_HARF)));

	// 背景生成
	LoadBackGroound();
	// 地形生成
	LoadGround();
	// ブロック生成
	LoadBlock();

	
	// 敵生成
	LoadEnemy();
}

eSceneType InGameScene::Update(const float& delta_seconds)
{
	//test
	if (screen_offset.x >= 5.0 * D_MONO)
	{
		object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 21), (D_MONO * 13 - D_HARF)));
	}
	//test


	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	// 入力情報の更新
	input->Update();

	// 生成するオブジェクトの確認
	object_manager->CheckCreateObject();
	// 破棄するオブジェクトの確認
	object_manager->CheckDestroyObject();
	// 現在のオブジェクトリストを取得
	scene_objects_list = object_manager->GetObjectList();

	// リスト内のオブジェクトを更新する
	for (GameObject* obj : scene_objects_list)
	{
		obj->Update(delta_seconds);
	}

	//当たり判定チェック
	for (int a = 0; a < scene_objects_list.size(); a++)
	{
		for (int b = 0; b < scene_objects_list.size(); b++)
		{
			// なぜかフリーズするので封印（無限ループではない？）
			/*object_manager->HitCheck(scene_objects_list[a], scene_objects_list[b]);
			object_manager->HitCheck(scene_objects_list[b], scene_objects_list[a]);*/
		}
	}

	// 画面移動量の取得
	screen_offset += player->GetScreenVelocity();

	//リザルトシーンへ遷移
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eResult;
	}

	//ゲームを終了
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
	// 空描画
	DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(92, 148, 252), TRUE);

	// オブジェクト描画
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(screen_offset, false);
	}

	DrawUI();
}

void InGameScene::Finalize()
{
	ui_coin_images.clear();
	symbol_images.clear();
	string_images.clear();
}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

// UI描画
void InGameScene::DrawUI() const
{
	int coin = player->GetCoin();
	int live = player->GetLive();

	// UI
	// 残機
	DrawRotaGraph(132, 60, SIZE, 0.0, st_mario_image, TRUE);
	// スコア
	DrawRotaGraph((D_HARF * 4 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 5 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 6 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 7 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 8 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	DrawRotaGraph((D_HARF * 9 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[0], TRUE);
	// コイン
	DrawRotaGraph((D_HARF * 12 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, ui_coin_images[0], TRUE);
	DrawRotaGraph((D_HARF * 13 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[11], TRUE);
	DrawRotaGraph((D_HARF * 14 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[coin / 10], TRUE);
	DrawRotaGraph((D_HARF * 15 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[coin % 10], TRUE);
	// ワールド
	DrawRotaGraph(492, 60, SIZE, 0.0, st_world_image, TRUE);
	DrawRotaGraph((D_HARF * 20 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[1], TRUE);
	DrawRotaGraph((D_HARF * 21 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[10], TRUE);
	DrawRotaGraph((D_HARF * 22 - D_QUARTER), (D_HARF * 4 - D_QUARTER), SIZE, 0.0, symbol_images[1], TRUE);
	// 制限時間
	DrawRotaGraph(648, 60, SIZE, 0.0, st_time_image, TRUE);
}

// 背景生成
void InGameScene::LoadBackGroound()
{
	//空生成
	//LoadSky(1, 1, 213, 15);
	//山生成
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
	//茂生成
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
	//雲生成
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
	//城生成
	LoadCastle(203, 9, 207, 13);
}
// 茂生成
void InGameScene::LoadBushes(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;

	//左
	x = D_MONO * x_start - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::BUSHES);
	bg->SetImageNum(0);
	//右
	x = D_MONO * x_last - D_HARF;
	y = D_MONO * y_last - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::BUSHES);
	bg->SetImageNum(2);
	//真ん中
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
// 山生成
void InGameScene::LoadMountain(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;
	int i;

	//頂
	x = D_MONO * ((x_start + x_last) / 2) - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
	bg->SetImageNum(0);
	//左
	for (i = 0; i < (y_last - y_start); i++)
	{
		//傾斜
		x = D_MONO * (x_start + i) - D_HARF;
		y = D_MONO * (y_last - i) - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
		bg->SetImageNum(1);
		//中央(模様あり)
		x = D_MONO * (x_start + i + 1) - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
		bg->SetImageNum(5);
	}
	//右
	for (i = 0; i < (y_last - y_start); i++)
	{
		//傾斜
		x = D_MONO * (x_last - i) - D_HARF;
		y = D_MONO * (y_last - i) - D_HARF;
		bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
		bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
		bg->SetImageNum(2);

		if (i > 0)
		{
			//中央(模様あり)
			x = D_MONO * (x_last - i) - D_HARF;
			y = D_MONO * (y_last - i + 1) - D_HARF;
			bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
			bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
			bg->SetImageNum(4);
			//中央(模様なし)
			x = D_MONO * (x_last - i - 1) - D_HARF;
			bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
			bg->SetBackGroundState(eBackGroundState::MOUNTAIN);
			bg->SetImageNum(3);
		}
	}
}
// 雲生成
void InGameScene::LoadCloud(int x_start, int y_start, int x_last, int y_last)
{
	BackGround* bg;
	float x;
	float y;

	//左
	x = D_MONO * x_start - D_HARF;
	y = D_MONO * y_start - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CLOUD);
	bg->SetImageNum(0);
	y = D_MONO * y_last - D_HARF;
	bg = object_manager->CreateGameObject<BackGround>(Vector2D(x, y));
	bg->SetBackGroundState(eBackGroundState::CLOUD);
	bg->SetImageNum(3);
	//真ん中
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
	//右
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
// 空生成
void InGameScene::LoadSky(int x_start, int y_start, int x_last, int y_last)
{
	//地面生成
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
// 城生成
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
// 地形生成
void InGameScene::LoadGround()
{
	//地面生成
	LoadFloor(1, 14, 69, 15);
	LoadFloor(72, 14, 86, 15);
	LoadFloor(90, 14, 153, 15);
	LoadFloor(156, 14, 213, 15);
	//階段生成
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
	//土管生成
	LoadPipe(29, 12, 30, 13);
	LoadPipe(39, 11, 40, 13);
	LoadPipe(47, 10, 48, 13);
	LoadPipe(58, 10, 59, 13);
	LoadPipe(164, 12, 165, 13);
	LoadPipe(180, 12, 181, 13);
}
// 地面生成
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
// 階段生成
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
// 土管生成
void InGameScene::LoadPipe(int x_start, int y_start, int x_last, int y_last)
{
	Ground* g;
	float x;							//x座標
	float y;							//y座標
	int height = (y_last - y_start);	//高さ
	int n = 0;							//画像引数

	//左上
	x = D_MONO * (x_start++) - D_HARF;
	y = D_MONO * (y_start)-D_HARF;
	g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
	g->SetGroundState(eGroundState::PIPE);
	g->SetPipeNum(n++);
	//右上
	x = D_MONO * (x_start--) - D_HARF;
	y = D_MONO * (y_start++) - D_HARF;
	g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
	g->SetGroundState(eGroundState::PIPE);
	g->SetPipeNum(n++);

	//下
	for (int j = 0; j < height; j++)
	{
		//左
		x = D_MONO * (x_start++) - D_HARF;
		y = D_MONO * (y_start)-D_HARF;
		g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
		g->SetGroundState(eGroundState::PIPE);
		g->SetPipeNum(n++);
		//右
		x = D_MONO * (x_start--) - D_HARF;
		y = D_MONO * (y_start++) - D_HARF;
		g = object_manager->CreateGameObject<Ground>(Vector2D(x, y));
		g->SetGroundState(eGroundState::PIPE);
		g->SetPipeNum(n--);
	}
}
// ブロック生成
void InGameScene::LoadBlock()
{
	//ハテナブロック生成
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
	//レンガブロック生成
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
	//透明ブロック生成
	LoadHidden(65, 9, 65, 9, GREEN);
}
// ハテナブロック生成
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
// レンガブロック生成
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
// 透明ブロック生成
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


// 敵生成
void InGameScene::LoadEnemy()
{
	// クリボー仮
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 21), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 44), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 53), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 54), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 79), (D_MONO * 9 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 81), (D_MONO * 5 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 97), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 98), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 112), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 113), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 124), (D_MONO * 13 - D_HARF)));
	object_manager->CreateGameObject<Kuribo>(Vector2D((D_MONO * 125), (D_MONO * 13 - D_HARF)));

	// ノコノコ仮
	object_manager->CreateGameObject<Nokonoko>(Vector2D((D_MONO * 103), (D_MONO * 13 - D_HARF)));
}