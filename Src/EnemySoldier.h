//24.12.30 T.Aranami 新規作成： 歩兵クラス
#pragma once
#include "EnemyBoss1.h"

class EnemyBoss1;

class EnemySoldier : public Enemy
{
public:

	EnemySoldier(EnemyBoss1* vBoss);
	virtual ~EnemySoldier();

	void Update()override;

	EnemyBoss1* GetBoss();

protected:
	void UpdateNormal()override;
	void UpdateContact()override;
	void UpdateFight()override;


private:
	//ボスのアドレス
	EnemyBoss1* boss;
};