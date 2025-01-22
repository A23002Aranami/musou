#include "ExclEffect.h"

CSpriteImage* ExclEffect::exclImg = nullptr;

int ExclEffect::num = 0;

ExclEffect::ExclEffect(Object3D* vobj):
	obj(vobj),
	timer(0),
	destroyTime(60)
{
	//画像がロードされていなければロードする
	if (!exclImg) exclImg = new CSpriteImage("data/images/Effect/Excl.png");
	num++;
}

ExclEffect::~ExclEffect()
{
	obj = nullptr;

	if (num == 1)//自分が最後の一つだった場合
	{
		if (exclImg)
		{
			delete exclImg;
			exclImg = nullptr;
		}
	}
	num--;
}

void ExclEffect::Update()
{
	timer++;
	transform.position = obj->Position();

	if (timer > destroyTime)
	{
		DestroyMe();
	}
}

void ExclEffect::Draw()
{
	CSprite spr;
	spr.Draw3D(exclImg, transform.position + VECTOR3(0, 2.0f, 0), VECTOR2(0.5f, 0.5f), VECTOR2(0, 0), VECTOR2(128, 128), 1.0f);
}
