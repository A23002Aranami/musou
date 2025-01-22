#pragma once

#include "Character.h"
#include "CameraPlayScene.h"
#include "MoveTarget.h"
#include "Enemy.h"

class CameraPlayScene;
class MoveTarget;
class Enemy;

class Player : public Character
{
public:

	Player();
	virtual ~Player();

	void Update()override;
	void Draw()override;
	
	void SetMesh(const TCHAR* file);

	MoveTarget* target;


	//�A�j���[�V�����p�񋓌^
	enum Animation
	{
		aWalk,
		aRoll,
		aIdle,
		aAttackLight,
		aEnd,
	};

	//�G�l�~�[�̃��X�g
	std::list<Enemy*> enemys;

private:
	void UpdateNormal();
	void UpdateAttackLight();
	void UpdateEvation();

	float time;
	float count;


	State state;

	//�J�����N���X
	CameraPlayScene* cam;
	float toRot;
	float startRot;
	float rot;
	float doubleTapCount;//����������
	float doubleTapTime;//�_�u���^�b�v�̋��e����

	float invincibleTime;//���G����
	float invincibleCount;//���G���ԃJ�E���g

	VECTOR3 GetCursolPos();

	//��U���̍U���͈�
	float attackRangeLight;
	//��U���̃m�b�N�o�b�N
	float attackKnockBackHeightLight;

	//24.12.18 �V�K�쐬�F�J�[�\���摜
	CSpriteImage* cursolImg;

	

	CFbxMesh* sword;

	POINT currPos;

};
