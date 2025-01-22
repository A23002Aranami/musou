#include "Lerp.h"

Lerp::Lerp(int time, float* vRate):count(0.0f),time(time),rate(vRate)
{
}

void Lerp::Update()
{
	//���ԉ��Z
	count++;
	float ret = count / time;
	if (ret > 1.0f)ret = 1.0f;
	*rate = ret;

	if (ret > 1.0f)
	{
		DestroyMe();
	}
}

