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
		Normal,			//待機
		Contact,		//連絡
		Chase,			//追跡
		Fight,			//戦闘
		Evasion,		//回避
		AttackLight,	//弱攻撃
		AttackHeavy,	//強攻撃
		KnockBack,		//ノックバック中
		Dead,			//死亡
		stateEnd,			//最後の要素
	};

protected:
	SphereCollider coll;
};