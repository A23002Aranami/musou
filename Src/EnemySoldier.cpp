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

	/*
	//群れ
	auto flock = ObjectManager::FindGameObjects<EnemySoldier>();
	*/

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
			if ((boss->Position() - this->Position()).Length() < socialDistance)
			{
				avgLeave += (this->Position() - boss->Position());
			}
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

					if (toNode.Length() < socialDistance)
					{
						//離れるベクトル
						avgLeave += (-toNode);
					}
				}
			}
		}
		//近くにいた場合
		if (volume > 0)
		{
			//個体数で割って平均を出す
			avgVelo /= volume;
			avgPos /= volume;
			avgPos = XMVector3Normalize(avgPos);

			VECTOR3 toAvgPos(XMVector3Normalize(avgPos - this->Position()) * 0.01);
			//速度を求めたベクトルの合計にする
			velo = (avgVelo * 1.5 + toAvgPos)+avgLeave;
			velo = XMVector3Normalize(velo);
			velo *= 0.01;
		}

		
	}

	transform.rotation.y = atan2(velo.x, velo.z);
	velo.y = 0;
	transform.position += velo;

	for (auto node : *boss->GetFlock())
	{
		auto toNode = node->Position() - this->Position();
		auto length = toNode.Length();

		if (length < 1.0)
		{
			toNode = XMVector3Normalize(toNode);
			transform.position += -toNode * (1.0f - length);
		}
	}

	

}
