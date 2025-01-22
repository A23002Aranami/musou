#include "EnemyVillage.h"

EnemyVillage::EnemyVillage(VECTOR3 center, VECTOR3 size, int num)
{

	//中心とサイズから左上と右下を求める
	lu = center - size / 2;
	rd = center + size / 2;
	EnemyBoss1* boss = nullptr;

	for (int i = 0; i < num; i++)
	{
		if (i == 0)//最初の一体はボス個体
		{
			boss = new EnemyBoss1();
			boss->SetPosition(Random(lu.x, rd.x), 0, Random(lu.z, rd.z));
		}
		else
		{
			//範囲内にランダムで生成
			auto soldier = new EnemySoldier(boss);
			soldier->SetPosition(Random(lu.x, rd.x), 0, Random(lu.z, rd.z));
		}
	}
}

EnemyVillage::~EnemyVillage()
{
}

void EnemyVillage::Draw()
{
	CSprite spr;
	
	spr.DrawLine3D(lu+VECTOR3(0,0.1f,0) ,VECTOR3(lu.x, 0.1f, rd.z), RGB(255, 0, 0));
	spr.DrawLine3D(VECTOR3(rd.x, 0.1f, lu.z), rd, RGB(255, 0, 0));
	spr.DrawLine3D(lu + VECTOR3(0, 0.1f, 0), VECTOR3(rd.x, 0.1f, lu.z), RGB(255, 0, 0));
	spr.DrawLine3D(rd+VECTOR3(0,0.1f,0),VECTOR3(lu.x,0.1f,rd.z), RGB(255, 0, 0));
}
