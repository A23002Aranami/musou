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
	std::vector<VECTOR3> start;	//���̊J�n�_
	std::vector<VECTOR3> end;		//���̏I�_
};
