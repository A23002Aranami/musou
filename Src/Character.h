#pragma once
#include "Object3D.h"
#include "Animator.h"

class Character : public Object3D
{
public:
	Character();
	virtual ~Character();
	void SetMesh( TCHAR* file);
	void Update();

	enum State
	{
		Normal,			//�ҋ@
		Contact,		//�A��
		Chase,			//�ǐ�
		Fight,			//�퓬
		Evasion,		//���
		AttackLight,	//��U��
		AttackHeavy,	//���U��
		KnockBack,		//�m�b�N�o�b�N��
		Dead,			//���S
		stateEnd,			//�Ō�̗v�f
	};

protected:
	SphereCollider coll;
};