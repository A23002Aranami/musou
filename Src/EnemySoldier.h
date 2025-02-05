//24.12.30 T.Aranami �V�K�쐬�F �����N���X
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

	//�U���͈͂܂ł̋���
	float attackLength;
	float attackRange;
	
	
	//���݂̍U���t���[��
	int attackFrame;
	
	//��U���̔����t���[��
	int startUpFrameLight;

	//��U���̎����t���[��
	int attackFrameLight;

private:
	//�{�X�̃A�h���X
	EnemyBoss1* boss;

	Transform rangeTransform;
};