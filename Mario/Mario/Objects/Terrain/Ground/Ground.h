#pragma once

#include"../Terrain.h"

enum eGroundState
{
	FLOOR,		//�n��
	STAIRS,		//�K�i
	PIPE		//�y��
};

class Ground : public Terrain
{
protected:
	eGroundState ground_state;		//�n�ʏ��

	int floor_image;				//�n�ʉ摜
	int stairs_image;				//�K�i�摜
	int pipe_images[4];				//�y�ǉ摜
	int pipe_num;					//�y�ǉ摜����

public:
	Ground();
	~Ground();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&) const override;
	virtual void Finalize() override;

public:
	void SetGroundState(eGroundState);
	void SetPipeNum(int);
};