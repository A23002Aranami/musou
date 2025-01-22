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

	//弱攻撃の攻撃範囲
	float attackRangeLight;
	//弱攻撃のノックバック
	float attackKnockBackHeightLight;

	//24.12.18 新規作成：カーソル画像
	CSpriteImage* cursolImg;

	

	CFbxMesh* sword;

	POINT currPos;

};
