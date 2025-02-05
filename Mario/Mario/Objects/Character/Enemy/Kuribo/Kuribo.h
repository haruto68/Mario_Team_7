#pragma once

#include"../EnemyBase.h"

class Kuribo : public EnemyBase
{
protected:
	std::vector<int> kuribo_images;

public:
	Kuribo();
	~Kuribo();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

public:
	void Movement(float);
};