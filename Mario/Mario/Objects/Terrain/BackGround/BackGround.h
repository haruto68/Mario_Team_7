#pragma once

#include"../Terrain.h"

enum eBackGroundState
{
	BUSHES,		//–Î
	MOUNTAIN,	//R
	CLOUD,		//‰_
	SKY,		//‹ó
	CASTLE		//é
};

class BackGround : public Terrain
{
protected:
	eBackGroundState back_ground_state;		//”wŒiî•ñ

	int bushes_images[3];					//–Î‰æ‘œ
	int mountain_images[6];					//R‰æ‘œ
	int cloud_images[6];					//‰_‰æ‘œ
	int sky_image;							//‹ó‰æ‘œ
	int castle_image;						//é‰æ‘œ
	int image_num;							//‰æ‘œˆø”

public:
	BackGround();
	~BackGround();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

public:
	void SetBackGroundState(eBackGroundState);
	void SetImageNum(int);
};