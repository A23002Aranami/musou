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
	void Draw()override;

	EnemyBoss1* GetBoss();

protected:
	void UpdateNormal()override;
	void UpdateContact()override;
	void UpdateFight()override;
	void UpdateAttackLight()override;
	void Boids();

	//攻撃範囲までの距離
	float attackLength;
	float attackRange;
	
	
	//現在の攻撃フレーム
	int attackFrame;
	
	//弱攻撃の発生フレーム
	int startUpFrameLight;

	//弱攻撃の持続フレーム
	int attackFrameLight;

private:
	//ボスのアドレス
	EnemyBoss1* boss;

	Transform rangeTransform;
};