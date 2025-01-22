#pragma once
#include "GameObject.h"

class Lerp :GameObject
{
public:
	Lerp(int time, float* vRate);
	
	void Update()override;
private:
	float time;
	float count;
	float* rate;
};