#include "Enemy.h"

namespace
{
	//描画距離
	static const float ableLength = 25.0f;

}

Player* Enemy::player = nullptr; // 静的メンバ変数の定義

CFbxMesh* Enemy::enemyMesh = nullptr;
int Enemy::num = 0;

Enemy::Enemy():state(Normal),knockBackVelo(VECTOR3(0,0,0))
{
	num++;//人数を加算

	//クラス内共通のメンバがnullptrの時のみ設定する
	if (!player) player = ObjectManager::FindGameObject<Player>();

	if (!enemyMesh)
	{
		enemyMesh = new CFbxMesh();
		enemyMesh->Load("data/models/Enemy/Gob/Gob.mesh");
		enemyMesh->LoadAnimation(Walk, "data/models/Enemy/Gob/Walk.anmx", true);
		enemyMesh->LoadAnimation(Dance, "data/models/Enemy/Gob/Dance.anmx", true);

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

	animator->Play(Dance);
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
		delete enemyMesh;
		player = nullptr;
	}
	//人数を減算
	num--;
}

void Enemy::Update()
{
	//プレイヤーへ向かうベクトルを取得
	toPlayer = player->Position() - this->Position();

	switch (state)
	{
	case Normal:
		UpdateNormal();
		break;
	case Contact:
		UpdateContact();
		break;
	case Chase:
		UpdateChase();
		break;
	case Fight:
		UpdateFight();
		break;
	case KnockBack:
		UpdateKnockBack();
		break;
	case Dead:
		break;
	default:
		break;
	}

}

void Enemy::Draw()
{
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


