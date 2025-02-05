#include "UiBarBase.h"

UiBarBase::UiBarBase(float* vRate, VECTOR2 vPosition, VECTOR2 vSize,DWORD vRgb) :
	rate(vRate),
	position(vPosition),
	maxSize(vSize),
	rgb(vRgb)
{
	//ï`âÊèáÇç≈å„Ç…
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

	//äÑçáÇÃîÕàÕÇ0Å`100%Ç…Ç∑ÇÈ
	safetyRate = min(safetyRate,1.0f);
	safetyRate = max(safetyRate, 0.0f);

	//â°ÉQÅ[ÉW
	if (maxSize.x > maxSize.y)
	{
		spr.DrawRect(position.x, position.y, maxSize.x * safetyRate, maxSize.y,rgb);
	}
	else//ècÉQÅ[ÉW
	{
		spr.DrawRect(position.x, position.y, maxSize.x , maxSize.y * safetyRate, rgb);
	}
	
}
