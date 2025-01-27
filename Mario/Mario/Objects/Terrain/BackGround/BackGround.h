#pragma once

#include"../Terrain.h"

enum eBackGroundState
{
	BUSHES,		//��
	MOUNTAIN,	//�R
	CLOUD,		//�_
	SKY,		//��
	CASTLE		//��
};

class BackGround : public Terrain
{
protected:
	eBackGroundState back_ground_state;		//�w�i���

	int bushes_images[3];					//�Ή摜
	int mountain_images[6];					//�R�摜
	int cloud_images[6];					//�_�摜
	int sky_image;							//��摜
	int castle_image;						//��摜
	int image_num;							//�摜����

public:
	BackGround();
	~BackGround();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&) const override;
	virtual void Finalize() override;

public:
	void SetBackGroundState(eBackGroundState);
	void SetImageNum(int);
};