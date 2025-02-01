#include "EnemySoldier.h"

EnemySoldier::EnemySoldier(EnemyBoss1* vBoss):Enemy()
{
	reactionCount = 0;
	reactionTime = Random(10,20);
	state = Normal;
	boss = vBoss;
	velo = VECTOR3(0, 0, 0);

	boss->AddFlock(this);
}

EnemySoldier::~EnemySoldier()
{
	boss = nullptr;
}

void EnemySoldier::Update()
{
	Enemy::Update();
	
	reactionCount++;
}

EnemyBoss1* EnemySoldier::GetBoss()
{
	return boss;
}

void EnemySoldier::UpdateNormal()
{
	

	//アニメーションアップデート
	animator->Update();
	
	if (boss->GetState() == Fight)
	{
		state = Contact;
	}
	else
	{
		VECTOR3 forward = VECTOR3(0, 0, 1) * XMMatrixRotationY(transform.rotation.y);
		float ipF = Dot(forward, toPlayer);
		if (toPlayer.Length() < 5.0f) {
			if (ipF >= cosf(60.0f * DegToRad))
			{
				new ExclEffect(this);
				animator->MergePlay(0);
				state = Contact;
			}
		}
	}
}

void EnemySoldier::UpdateContact()
{
	if (boss) {
		animator->MergePlay(0);
		animator->Update();

		VECTOR3 toBoss = (boss->Position() - this->Position());

		if ((boss->GetState() != Fight) )//ボスが戦闘モードじゃなかったら
		{
			
			if (toBoss.Length() > 2.0f)
			{
				toBoss = XMVector3Normalize(toBoss);
				transform.rotation.y = atan2(toBoss.x, toBoss.z);
				velo = toBoss * 0.01;
			}
			else
			{
				//state = Normal;
			}
		}
		else
		{
			state = Fight;
		}
		transform.position += velo;
	}
	
}

void EnemySoldier::UpdateFight()
{
	animator->Update();

	if (reactionTime < reactionCount)
	{
		reactionTime = Random(10, 20);
		reactionCount = 0;

		velo = VECTOR3();

		VECTOR3 avgPos = VECTOR3();//集団の位置の平均				(結合用)
		VECTOR3 avgVelo = VECTOR3();//集団の速度の平均(向き、速さ)	(整列用)
		VECTOR3 avgLeave = VECTOR3();//近づきすぎたら離れる力の平均	(分離用)

		float sight = 10;//視界
		float volume = 0;		//視界内の個体数
		float socialDistance = 1;

		if ((boss->Position() - this->Position()).Length() < sight)
		{
			volume++;
			avgPos += boss->Position();
			avgVelo += boss->GetVelo();
		}

		for (auto node : *boss->GetFlock())
		{

			//同じボスを持つ群れの時
			if (node->boss == boss && node->state == Contact)
			{
				auto toNode = node->Position() - this->Position();
				auto length = toNode.Length();
				//自分の周囲一定範囲内にいたら
				if (length <= sight)
				{

					volume++;//計算する個体数
					avgPos += node->Position();
					avgVelo += node->velo;
				}
			}
		}
		//近く仲間がにいた場合
		if (volume > 0)
		{
			//個体数で割って平均を出す
			avgVelo /= volume;
			avgPos /= volume;
			avgPos = XMVector3Normalize(avgPos);

			VECTOR3 toAvgPos(XMVector3Normalize(avgPos - this->Position()) * 0.01);
			//速度を求めたベクトルの合計にする
			velo = (avgVelo * 1.5 + toAvgPos);
			velo = XMVector3Normalize(velo);
			velo *= 0.01;
		}

		//自分の視界内に仲間がいた場合
		if (toPlayer.Length() <= 5.0f)
		{
			//プレイヤーへ向かうベクトルを正規化
			VECTOR3 toVec = XMVector3Normalize(toPlayer);
			toVec *= 0.01f;

			//プレイヤーへ向かう割合の調整
			toVec * 2;

			//速度の要素にプレイヤーへ向かうベクトルも混ぜる
			velo += toVec;
			velo /= 2;

		}

		
	}
	
	//動いていないなら、アニメーションをダンスにする
	if (velo.Length() <= 0)
	{
		if (animator->PlayingID() != Dance)
		{
			animator->MergePlay(Dance);
		}
	}
	else
	{
		//キャラクターが動いているときにアニメーションが歩いていなかったら歩かせる
		if (animator->PlayingID() != Walk)
		{
			animator->MergePlay(Walk);
		}
	}
	
	
	transform.rotation.y = atan2(velo.x, velo.z);
	velo.y = 0;
	transform.position += velo;

}
