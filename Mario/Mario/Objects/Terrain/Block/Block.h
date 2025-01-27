#pragma once

#include"../Terrain.h"

enum eBlockState
{
	QUESTION,	//�n�e�i
	BRICK,		//�����K
	EMPTY,		//��
	HIDDEN		//����
};

enum eContentsState
{
	DEFAULT,		//��
	COIN,		//�R�C��
	COIN_10,	//10�R�C��
	RED,		//�ԃL�m�R or �t�@�C�A�t�����[
	GREEN,		//1up�L�m�R
	STAR		//�X�^�[
};

class Block : public Terrain
{
protected:
	eBlockState block_state;			//�u���b�N���
	eContentsState content_state;		//���g���

	std::vector<int> question_images;	//�n�e�i�摜
	int brick_image;					//�����K�摜
	int empty_image;					//��摜

	int question_num;					//�n�e�i�摜����

public:
	Block();
	~Block();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&) const override;
	virtual void Finalize() override;

public:
	void SetBlockState(eBlockState);
	void SetContentsState(eContentsState);
};