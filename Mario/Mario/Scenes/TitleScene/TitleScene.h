#pragma once
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
protected:
	std::vector<int> mario_images;
	std::vector<int> ui_coin_images;
	std::vector<int> symbol_images;
	std::vector<int> string_images;
	int back_ground_image;
	int st_mario_image;
	int st_world_image;
	int st_time_image;
	int st_top_image;

public:
	TitleScene();
	~TitleScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};