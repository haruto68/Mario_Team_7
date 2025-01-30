#pragma once

#include"../Terrain.h"

enum eBlockState
{
	QUESTION,	//ハテナ
	BRICK,		//レンガ
	EMPTY,		//空
	HIDDEN		//透明
};

enum eContentsState
{
	DEFAULT,		//空
	COIN,		//コイン
	COIN_10,	//10コイン
	RED,		//赤キノコ or ファイアフラワー
	GREEN,		//1upキノコ
	STAR		//スター
};

class Block : public Terrain
{
protected:
	eBlockState block_state;			//ブロック情報
	eContentsState content_state;		//中身情報

	std::vector<int> question_images;	//ハテナ画像
	int brick_image;					//レンガ画像
	int empty_image;					//空画像

	int question_num;					//ハテナ画像引数

public:
	Block();
	~Block();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

public:
	void SetBlockState(eBlockState);
	void SetContentsState(eContentsState);
};