#pragma once
#include "GameObject.h"

class UIGameOver :public GameObject
{
public:
	UIGameOver();
	virtual ~UIGameOver();

	void Update();
	void Draw();

private:
	//CSpriteImage* img;

	float count;

};