#pragma once
#include "GameObject.h"

class UiBarBase :public GameObject
{
public:

	/// <summary>
	/// バーのUI
	/// </summary>
	/// <param name="vRate">表示する割合</param>
	/// <param name="size">描画サイズ</param>
	/// <param name="dir">true:横バー,false:縦バー</param>
	UiBarBase(float *vRate,VECTOR2 position,VECTOR2 size);
	virtual ~UiBarBase();

	void Draw()override;

	

private:
	//描画割合
	float *rate;

	//描画座標
	VECTOR2 position;
	//描画サイズ
	VECTOR2 maxSize;

};