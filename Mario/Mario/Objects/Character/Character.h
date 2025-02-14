#pragma once

#include"../GameObject.h"
#include"../GameObjectManager.h"

class Character : public GameObject
{
protected:
	Vector2D velocity = 0.0f;
	int hit_point = 0;
	bool on_ground = true;

	float g_velocity = 0.0;

	int anime_count = 0;	// アニメーション用カウント

public:
	bool flip_flag = false;

};