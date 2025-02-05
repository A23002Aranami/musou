#include "Enemy.h"
#include "Stage.h"

namespace
{
	//描画距離
	static const float ableLength = 25.0f;

}

class Stage;

Player* Enemy::player = nullptr; // 静的メンバ変数の定義

CFbxMesh* Enemy::enemyMesh = nullptr;
CFbxMesh* Enemy::rangeMesh = nullptr;

Stage* Enemy::stage = nullptr;
int Enemy::num = 0;

Enemy::Enemy():state(Normal),knockBackVelo(VECTOR3(0,0,0))
{
	num++;//人数を加算

	//クラス内共通のメンバがnullptrの時のみ設定する
	if (!player) player = ObjectManager::FindGameObject<Player>();
	if (!stage) stage = ObjectManager::FindGameObject<Stage>(); 

	if (!enemyMesh)
	{
		enemyMesh = new CFbxMesh();
		enemyMesh->Load("data/models/Enemy/Gob/Gob.mesh");
		enemyMesh->LoadAnimation(aWalk, "data/models/Enemy/Gob/Walk.anmx", true);
		enemyMesh->LoadAnimation(aDance, "data/models/Enemy/Gob/Dance.anmx", true);
		enemyMesh->LoadAnimation(aAttackLight, "data/models/Enemy/Gob/AttackLight.anmx", false);

		//攻撃範囲用のメッシュ
		rangeMesh = new CFbxMesh();
		rangeMesh->Load("data/models/Common/Range.mesh");
	}
	

	mesh = enemyMesh;
	//プレイヤーのエネミーリストに自分を追加
	player->enemys.push_back(this);


	//mesh = new CFbxMesh();
	//mesh->Load("data/models/Enemy/Enemy1.mesh");
	//mesh->LoadAnimation(0, "data/models/Enemy/Walking.anmx", true);
	//mesh->LoadAnimation(1, "data/models/Enemy/Sitting.anmx", true);


	animator = new Animator();

	animator->SetModel(mesh);

	animator->Play(aDance);
	//プレイスピードを等速で初期化
	animator->SetPlaySpeed(1.0f);

	//開始時の向きをランダムで設定
	transform.rotation = VECTOR3(0, Random(0, 180) * DegToRad, 0);
}


Enemy::~Enemy()
{
	//24.12.19 T.Aranami 追加すべての敵が共通のメッシュを参照しているのでデリートエラーが起こらないようにmeshをnullptrにしておく
	mesh = nullptr;

	if (num == 1)//リソースがデリートされていないときデリートする
	{
		delete enemyMesh;//敵全体で共通のメッシュをデリート
		player = nullptr;//プレイヤーの共通ポインタをデリート
		stage = nullptr;//ステージの共通ポインタをデリート
	}
	//アニメーターのデリート
	SAFE_DELETE(animator);
	//人数を減算
	num--;
}

void Enemy::Update()
{
	//プレイヤーへ向かうベクトルを取得
	toPlayer = player->Position() - this->Position();

	//アニメーションのアップデート
	animator->Update();

	switch (state)
	{
	case Normal:			//通常状態
		UpdateNormal();
		break;
	case Contact:			//接触状態
		UpdateContact();
		break;
	case Chase:				//追跡状態
		UpdateChase();
		break;
	case Fight:				//戦闘状態
		UpdateFight();
		break;
	case AttackLight:		//攻撃状態
		UpdateAttackLight();
		break;
	case KnockBack:			//ノックバック状態
		UpdateKnockBack();
		break;
	case Dead:				//死亡状態
		break;
	default:				//その他
		break;
	}

	if ((this->state != Dead) && (this->state != KnockBack))
	{
		//すべてのボスのすべての配下とヒット判定
		for (auto boss : *stage->GetBoss1())
		{
			for (auto node : *boss->GetFlock())
			{
				//対象が動ける状態であるとき
				if ( (node->state != Dead) &&
					 (node->state != KnockBack) &&
					 (node->state != AttackLight)
					)
				{
					auto toNode = node->Position() - this->Position();
					auto length = toNode.Length();

					//距離が一定以下のとき
					if (length < 1.0)
					{
						//当たった仲間を押し出す
						toNode = XMVector3Normalize(toNode);
						toNode.y = 0;
						node->SetPosition(node->Position() + toNode * (1.0f - length));
					}
					
				}
			}
		}
	}
}

void Enemy::Draw()
{
	//プレイヤーとの距離が描画距離以内であり、死亡状態でないとき描画する
	if ( (player && toPlayer.Length() < ableLength) && state != Dead)
	{
		Object3D::Draw();
	}
}

void Enemy::SetKnockBackVelo(VECTOR3 velocity)
{
	knockBackVelo = velocity;
	state = KnockBack;
}


void Enemy::UpdateNormal()
{

}

void Enemy::UpdateContact()
{
	
}

void Enemy::UpdateFight()
{
}

void Enemy::UpdateKnockBack()
{
	
	transform.position += knockBackVelo;

	//重力表現
	knockBackVelo.y -= 0.002;

	if (transform.position.y < 0)
	{
		transform.position.y = 0;
		state = Dead;
	}
}

void Enemy::UpdateChase()
{
}

void Enemy::UpdateAttackLight()
{
}


