#pragma once
#include "Character.h"
#include "Animator.h"
#include "Player.h"
#include "ExclEffect.h"

class Player;
class Stage;

class Enemy : public Character
{
public:
	Enemy();
	virtual ~Enemy();

	void Update()override;
	void Draw()override;

	/// <summary>
	/// �m�b�N�o�b�N�̑��x��ݒ肷��
	/// </summary>
	/// <param name="velocity"></param>
	void SetKnockBackVelo( VECTOR3 velocity );

	State state;
	VECTOR3 toPlayer;	//�v���C���[�֌������x�N�g�� 

protected:

	

	VECTOR3 velo;		//���x
	VECTOR3 veloAverage;//�S�̂̑��x�̕���

	//�m�b�N�o�b�N���̑��x
	VECTOR3 knockBackVelo;

	//�X�e�[�W�̃|�C���^
	static Stage* stage;
	static Player* player;
	static CFbxMesh* enemyMesh;
	static int num;//�G�l�~�[�̐l��

	float reactionTime;//��������
	float reactionCount;//�����̃J�E���g

	int coolTime;//�N�[���^�C��
	int coolCount;//�N�[���J�E���g
	
	enum Animation
	{
		aWalk,
		aDance,
		aAttackLight,
	};

	virtual void UpdateNormal();
	virtual void UpdateContact();
	virtual void UpdateFight();
	virtual void UpdateKnockBack();
	virtual void UpdateChase();
	virtual void UpdateAttackLight();

	//�U���͈͂̃��b�V��
	static CFbxMesh* rangeMesh;

};