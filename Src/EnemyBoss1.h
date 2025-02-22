#pragma once
#include "Enemy.h"
#include "EnemySoldier.h"
#include "Stage.h"
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

private:
	//25.01.09 T.Aranami 追加：配下の群れ
	std::list<EnemySoldier*> flock;
};
