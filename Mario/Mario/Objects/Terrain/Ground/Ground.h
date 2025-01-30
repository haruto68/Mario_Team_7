#pragma once

#include"../Terrain.h"

enum eGroundState
{
	FLOOR,		//’n–Ê
	STAIRS,		//ŠK’i
	PIPE		//“yŠÇ
};

class Ground : public Terrain
{
protected:
	eGroundState ground_state;		//’n–Êî•ñ

	int floor_image;				//’n–Ê‰æ‘œ
	int stairs_image;				//ŠK’i‰æ‘œ
	int pipe_images[4];				//“yŠÇ‰æ‘œ
	int pipe_num;					//“yŠÇ‰æ‘œˆø”

public:
	Ground();
	~Ground();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

public:
	void SetGroundState(eGroundState);
	void SetPipeNum(int);
};