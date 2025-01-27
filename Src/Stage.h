#pragma once
#include "GameObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyVillage.h"

class Stage : public GameObject
{
public:
	Stage();
	void Draw()override;
protected:
	std::vector<VECTOR3> start;	//線の開始点
	std::vector<VECTOR3> end;		//線の終点
};
