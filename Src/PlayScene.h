#pragma once
#include "SceneBase.h"
#include <thread>
#include <atomic>

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
	std::atomic<bool> loading;

private:
	//ローディング中かどうかのフラグ
	CSpriteImage* back;
	std::thread LoadingThread;

	float x;
};