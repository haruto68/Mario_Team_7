#pragma once
#include"Singleton.h"
#include"InputManager.h"
#include"../Resource/ResourceManager.h"

class Application : public Singleton
{
private:
	float delta_seconds;
	bool is_finalize;

public:
	Application();
	~Application();

	//初期化処理
	void WakeUp();

	//実行処理
	void Run();

	//終了時処理
	void Shutdown();

private:
	void UpdateDeltaTime();
};