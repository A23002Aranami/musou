#include "UiBarBase.h"

UiBarBase::UiBarBase(float* vRate, VECTOR2 vPosition, VECTOR2 vSize) :
	rate(vRate),
	position(vPosition),
	maxSize(vSize)
{
	//�`�揇���Ō��
	SetDrawOrder(-2000);
}

UiBarBase::~UiBarBase()
{
}

void UiBarBase::Draw()
{
	CSprite spr;
	spr.DrawRect(position.x, position.y, maxSize.x, maxSize.y, RGB(100, 100, 100));

	float safetyRate = *rate;

	//�����͈̔͂�0�`100%�ɂ���
	safetyRate = min(safetyRate,1.0f);
	safetyRate = max(safetyRate, 0.0f);

	//���Q�[�W
	if (maxSize.x > maxSize.y)
	{
		spr.DrawRect(position.x, position.y, maxSize.x * safetyRate, maxSize.y, RGB(255, 255, 0));
	}
	else//�c�Q�[�W
	{
		spr.DrawRect(position.x, position.y, maxSize.x , maxSize.y * safetyRate, RGB(255, 255, 0));
	}
	
}
