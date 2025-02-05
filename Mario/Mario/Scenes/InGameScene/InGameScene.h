#pragma once
#include"../SceneBase.h"
#include"../../Objects/GameObject.h"


#include"../../Objects/Character/Player/Player.h"
#include"../../Objects/Character/Enemy/Kuribo/Kuribo.h"
#include"../../Objects/Character/Enemy/Nokonoko/Nokonoko.h"
#include"../../Objects/Terrain/Block/Block.h"
#include"../../Objects/Terrain/Ground/Ground.h"
#include"../../Objects/Terrain/BackGround/BackGround.h"

class InGameScene : public SceneBase
{
protected:
	// UIâÊëú
	std::vector<int> ui_coin_images;
	std::vector<int> symbol_images;
	std::vector<int> string_images;
	int st_mario_image;
	int st_world_image;
	int st_time_image;
	int st_top_image;

public:
	class GameObjectManager* object_manager;
	class Player* player;

	std::vector<GameObject*> scene_objects_list;

public:
	InGameScene();
	~InGameScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

public:
	// UIï`âÊ
	void DrawUI() const;

	// îwåiê∂ê¨
	void LoadBackGroound();
	void LoadBushes(int, int, int, int);
	void LoadMountain(int, int, int, int);
	void LoadCloud(int, int, int, int);
	void LoadSky(int, int, int, int);
	void LoadCastle(int, int, int, int);
	// ínå`ê∂ê¨
	void LoadGround();
	void LoadFloor(int, int, int, int);
	void LoadStairs(int, int, int, int);
	void LoadPipe(int, int, int, int);
	// ÉuÉçÉbÉNê∂ê¨
	void LoadBlock();
	void LoadQuestion(int, int, int, int, eContentsState);
	void LoadBrick(int, int, int, int, eContentsState);
	void LoadHidden(int, int, int, int, eContentsState);


	// ìGê∂ê¨
	void LoadEnemy();

};