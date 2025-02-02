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
	std::vector<VECTOR3> start;	//���̊J�n�_
	std::vector<VECTOR3> end;		//���̏I�_

	//���ׂẴ{�X
	std::list<EnemyBoss1*> boss1;
};
