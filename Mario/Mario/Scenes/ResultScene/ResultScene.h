#pragma once
#include"../SceneBase.h"

class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};