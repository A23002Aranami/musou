#pragma once
#include "Enemy.h"
#include "EnemySoldier.h"

class EnemySoldier;

class EnemyBoss1 : public Enemy
{
public:
	EnemyBoss1();
	~EnemyBoss1();

	void Draw()override;

	int GetState();
	VECTOR3 GetVelo();

	void AddFlock(EnemySoldier* soldier);
	std::list<EnemySoldier*>* GetFlock();

protected:
	void UpdateNormal() override;
	void UpdateChase()override;
	void UpdateFight()override;

	//25.01.09 T.Aranami í«â¡ÅFîzâ∫ÇÃåQÇÍ
	std::list<EnemySoldier*> flock;
};
