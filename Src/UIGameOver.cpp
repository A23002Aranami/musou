#include "UIGameOver.h"

UIGameOver::UIGameOver()
{
	SetDrawOrder(-2000);
}

UIGameOver::~UIGameOver()
{

}

void UIGameOver::Update()
{
	count++;
}

void UIGameOver::Draw()
{
	float rate = count / 90;
	float rate2 = count / 120;

	rate = min(rate, 1.0f);

	CSprite spr;
	rate2 = min(rate2, 1.0f);
	spr.DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0), rate2);

	GameDevice()->m_pFont->Draw(450, 300, _T("GameOver"), 250, RGB(255, 0, 0),rate);


	
}
