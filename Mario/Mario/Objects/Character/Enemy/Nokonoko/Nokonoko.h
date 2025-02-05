#pragma once

#include"../EnemyBase.h"

class Nokonoko : public EnemyBase
{
protected:
	std::vector<int> nokonoko_images;
	std::vector<int> nokonoko_shell_images;

	bool shell_mode;

public:
	Nokonoko();
	~Nokonoko();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

public:
	void Movement(float);
};