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
	//���[�f�B���O�����ǂ����̃t���O
	CSpriteImage* back;
	std::thread LoadingThread;

	float x;
};