#include "Player.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "CameraPlayScene.h"
#include "MoveTarget.h"
#include "Lerp.h"
#include "MeshCollider.h"

Player::Player() :
	cam(nullptr),
	target(nullptr),
	doubleTapCount(10),
	doubleTapTime(10),
	invincibleCount(0),
	invincibleTime(60),
	attackRangeLight(3.0f),
	attackKnockBackHeightLight(0.1f)
{
	//描画順を遅くする
	ObjectManager::SetDrawOrder(this, -1000);

	GameDevice()->m_pDI->ShowMouseCursor(false);
	animator = nullptr;
	cam = ObjectManager::FindGameObject<CameraPlayScene>();
	toRot = transform.rotation.y;
	//カーソル画像ロード
	cursolImg = new CSpriteImage("data/images/ui/Cursol.png");
	sword = new CFbxMesh();
	sword->Load("data/models/chara/Night/Sword.mesh");
}

Player::~Player()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(cursolImg);
	SAFE_DELETE(sword);
	GameDevice()->m_pDI->ShowMouseCursor(true);
}

void Player::Update()
{
	//マウスカーソル座標取得
	currPos = GameDevice()->m_pDI->GetMousePos();
	switch (state)
	{
	case Player::Normal:
		UpdateNormal();
		break;

	case Player::Evasion:
		UpdateEvation();
		break;

	case AttackLight:
		UpdateAttackLight();
		break;

	case Player::Dead:
		break;

	default:
		break;
	}

	animator->Update();
}

void Player::Draw()
{
	Object3D::Draw();//プレイヤーモデルの描画
	CSprite spr;//スプライト描画クラス
	
	Transform swordTransform;

	swordTransform.rotation = VECTOR3(0, 0, -90);
	MATRIX4X4 swordMat = swordTransform.matrix();

	MATRIX4X4 bone = mesh->GetFrameMatrices(animator,14,1);
	sword->Render(swordMat * bone* transform.matrix());
	

	//カーソル描画
	spr.Draw(
		cursolImg,
		currPos.x - cursolImg->m_dwImageWidth/2,
		currPos.y - cursolImg->m_dwImageHeight,
		0,0,cursolImg->m_dwImageWidth,cursolImg->m_dwImageHeight);
}


void Player::SetMesh(const TCHAR* file)
{
	animator = new Animator();

	mesh = new CFbxMesh();
	mesh->Load("data/models/chara/Night.mesh");

	
	animator->SetModel(mesh);
	mesh->LoadAnimation(0, "data/models/chara/Walking.anmx", true);
	mesh->LoadAnimation(1, "data/models/chara/Roll.anmx", false);
	mesh->LoadAnimation(2, "data/models/chara/Idle.anmx", true);
	mesh->LoadAnimation(3, "data/models/chara/Night/AttackLight.anmx", false);
	animator->Play(aWalk);
	animator->SetPlaySpeed(1.0f);
}

void Player::UpdateNormal()
{
	auto di = GameDevice()->m_pDI;//入力

	float rotRate = 1.0f;

	doubleTapCount++;

	if (di->CheckMouse(KD_DAT, DIM_LBUTTON))//クリックしている間
	{
		VECTOR3 cursolPos = GetCursolPos();
		
		if (doubleTapCount <= doubleTapTime)//ダブルタップ時の処理
		{
			invincibleCount = 0;
			animator->MergePlay(aRoll);
			state = Evasion;
			return;
		}
		else
		{
			
			if ((cursolPos - this->Position()).Length() > 1.1f)
			{
				if (!target) {//ターゲットが存在しなかったらインスタンス生成
					target = new MoveTarget(cursolPos, this);
				}
				else
				{
					target->SetPosition(cursolPos);
				}

			}
			
			VECTOR3 toTarget = cursolPos - this->Position();


			toRot = atan2(toTarget.x, toTarget.z);
			count = 0;
			time = 30;
			startRot = transform.rotation.y;
			rot = toRot - startRot;
		}

	}

	if (di->CheckMouse(KD_UTRG, DIM_LBUTTON))//クリックをやめたら
	{
		doubleTapCount = 0;
	}

	count++;
	rotRate = count / time;
	if (rotRate > 1.0f)
	{
		rotRate = 1.0f;
	}
	else
	{
		transform.rotation.y = rot * rotRate + startRot;

	}

	if (target) {

		if (animator->PlayingID() != 0)
		{
			animator->MergePlay(aWalk);
		}

		//Todo[Aranami]:ここが重い処理かもしれないので、修正する
		VECTOR3 toTarget = target->Position() - this->Position();
		toTarget = XMVector3Normalize(toTarget);
		toTarget *= 0.05;
		transform.position += toTarget;
	}
	else
	{
		if (animator->PlayingID() != 2)
		{
			animator->MergePlay(aIdle);
		}
		
	}

	//右クリック(攻撃)
	if (di->CheckMouse(KD_TRG, DIM_RBUTTON))
	{
		VECTOR3 cursolPos = GetCursolPos();

		VECTOR3 toCursolPos = cursolPos - this->Position();
		transform.rotation.y  = atan2(toCursolPos.x, toCursolPos.z);
		
		

		animator->MergePlay(aAttackLight);
		state = AttackLight;//攻撃状態にする
		
		//移動先ターゲットを消す
		if (target)
		{
			target->DestroyMe();
			target = nullptr;
		}
	}
	
}

void Player::UpdateAttackLight()
{
	
	if (!enemys.empty())
	{
		for (auto enemy : enemys)
		{
			if (enemy->toPlayer.Length() <= attackRangeLight)
			{
				//敵のステート
				int eState = enemy->state;
				//敵がノックバックしても死んでもいないとき
				if ( (eState != KnockBack) && (eState != Dead))
				{
					VECTOR3 KnockBack;
					KnockBack = XMVector3Normalize(-(enemy->toPlayer))*0.02;
					KnockBack.y = attackKnockBackHeightLight;
					enemy->SetKnockBackVelo( KnockBack );
				}
			}
			
		}
	}
	
	
	//アニメーションが終わったら通常に戻す
	if (animator->Finished())
	{
		state = Normal;

	}
	
}

void Player::UpdateEvation()
{
	invincibleCount++;//無敵時間カウント
	doubleTapCount = doubleTapTime + 1;
	
	auto target = ObjectManager::FindGameObject<MoveTarget>();
	if (target) {
		VECTOR3 toTarget = target->Position() - this->Position();
		toTarget = XMVector3Normalize(toTarget);//ベクトル正規化

		transform.rotation.y = atan2(toTarget.x, toTarget.z);//クリックした方向へ向く

		transform.position += toTarget*0.07;

	}

	if (invincibleTime <= invincibleCount)
	{
		count = time;
		animator->MergePlay(aWalk);
		state = Normal;
	}
	

}

VECTOR3 Player::GetCursolPos()
{

	MeshCollider::CollInfo targetInfo;
	targetInfo.hitPosition = this->Position();//ターゲットを自分の位置で初期化

	VECTOR3 start = cam->Position();

	//カーソルの座標をワールド座標に変換したものを判定の終わりの座標にする
	start = XMVector3Unproject(
		VECTOR3(currPos.x, currPos.y, 0.0),
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		GameDevice()->m_mProj, GameDevice()->m_mView, XMMatrixIdentity()
	);
	VECTOR3 end = XMVector3Unproject(
		VECTOR3(currPos.x, currPos.y, 1.0),
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		GameDevice()->m_mProj, GameDevice()->m_mView, XMMatrixIdentity()
	);


	//ターゲットポジションを初期化
	ObjectManager::FindGameObject<StaticObject>()->HitLineToMesh(start, end, &targetInfo);

	//距離の初期化
	float minLength = (targetInfo.hitPosition - this->Position()).LengthSquare();


	auto objs = ObjectManager::FindGameObjects<StaticObject>();
	for (auto obj : objs)
	{

		MeshCollider::CollInfo hit;//カメラからのRayとオブジェクトの接触位置
		if (obj->HitLineToMesh(start, end, &hit)) {
			float length = (hit.hitPosition - this->Position()).LengthSquare();
			//求めたキャラクターからの距離が最短だったらターゲットポジション書き換え
			if (minLength > length)
			{
				targetInfo.hitPosition = hit.hitPosition;
			}
		}
	}


	return targetInfo.hitPosition;
}
