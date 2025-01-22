#pragma once


#include "EnemySoldier.h"
class EnemyVillage : public GameObject
{
public :

	/// <summary>
	/// エネミーの集落生成
	/// </summary>
	/// <param name="center">集落の中心</param>
	/// <param name="size">集落のサイズ(x,y,z)</param>
	/// <param name="num">出現させるエネミーの数</param>
	EnemyVillage(VECTOR3 center,VECTOR3 size, int num);
	virtual ~EnemyVillage();

	void Draw()override;

private:
	VECTOR3 center;
	VECTOR3 lu, rd;
};
