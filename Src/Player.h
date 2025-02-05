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

	//攻撃されたときの処理
	void Damage(float damage);

	void Update()override;
	void Draw()override;
	
	void SetMesh(const TCHAR* file);

	MoveTarget* target;


	//アニメーション用列挙型
	enum Animation
	{
		aWalk,
		aRoll,
		aIdle,
		aAttackLight,
		aEnd,
	};

	//エネミーのリスト
	std::list<Enemy*> enemys;

private:
	void UpdateNormal();
	void UpdateAttackLight();
	void UpdateEvation();

	float time;
	float count;

	float hp;
	float maxHp;
	float hpRate;

	State state;

	//カメラクラス
	CameraPlayScene* cam;
	float toRot;
	float startRot;
	float rot;
	float doubleTapCount;//長押し時間
	float doubleTapTime;//ダブルタップの許容時間

	float invincibleTime;//無敵時間
	float invincibleCount;//無敵時間カウント

	VECTOR3 GetCursolPos();

	//攻撃発生からのフレーム
	int countAttackFrame;

	//弱攻撃の攻撃範囲(距離)
	float attackRangeLight;
	//弱攻撃の攻撃範囲(角度)
	float attackAngleLight;
	//弱攻撃の攻撃フレーム
	int attackFrameLight;

	//弱攻撃のノックバック
	float attackKnockBackHeightLight;

	//24.12.18 新規作成：カーソル画像
	CSpriteImage* cursolImg;

	

	CFbxMesh* sword;

	POINT currPos;

};
