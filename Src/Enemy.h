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
	/// ノックバックの速度を設定する
	/// </summary>
	/// <param name="velocity"></param>
	void SetKnockBackVelo( VECTOR3 velocity );

	State state;
	VECTOR3 toPlayer;	//プレイヤーへ向かうベクトル 

protected:

	bool isHitAttack;

	VECTOR3 velo;		//速度
	VECTOR3 veloAverage;//全体の速度の平均

	//ノックバック時の速度
	VECTOR3 knockBackVelo;

	//ステージのポインタ
	static Stage* stage;
	static Player* player;
	static CFbxMesh* enemyMesh;
	static int num;//エネミーの人数

	float reactionTime;//反応時間
	float reactionCount;//反応のカウント

	int coolTime;//クールタイム
	int coolCount;//クールカウント
	
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

	//攻撃範囲のメッシュ
	static CFbxMesh* rangeMesh;
	static CFbxMesh* circleMesh;

};