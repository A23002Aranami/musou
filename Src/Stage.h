#pragma once
#include "GameObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyVillage.h"
class EnemyBoss1;

class Stage : public GameObject
{
public:
	Stage();
	virtual ~Stage();
	void Draw()override;

	void SetBoss1(EnemyBoss1* boss);
	std::list<EnemyBoss1*>* GetBoss1();
protected:
	std::vector<VECTOR3> start;	//線の開始点
	std::vector<VECTOR3> end;		//線の終点

	//すべてのボス
	std::list<EnemyBoss1*> boss1;
};
