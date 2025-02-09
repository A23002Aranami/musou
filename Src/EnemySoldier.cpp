#include "EnemySoldier.h"

EnemySoldier::EnemySoldier(EnemyBoss1* vBoss):Enemy()
{

	reactionCount = 0;
	reactionTime = Random(10,20);
	state = Normal;
	boss = vBoss;
	velo = VECTOR3(0, 0, 0);

	attackFrame = 0;
	startUpFrameLight = 100;
	attackFrameLight = 5;

	//攻撃範囲の初期化
	attackLength = 1.0f;
	attackRange = 2.0f;

	//攻撃のクールタイム
	coolTime = 60;
	coolCount = 0;

	boss->AddFlock(this);

	isHitAttack = false;

	
}

EnemySoldier::~EnemySoldier()
{
	Enemy::~Enemy();
	boss = nullptr;
}

void EnemySoldier::Update()
{
	//親クラスのアップデートを呼ぶ
	Enemy::Update();
	
	if (coolTime > 0)//クールタイムが0以上のとき
	{
		coolCount--;
	}
	reactionCount++;
}

void EnemySoldier::Draw()
{
	Enemy::Draw();

	//攻撃状態の時は攻撃範囲を描画 
	if (state == AttackLight)
	{
		//描画に使う割合
		float drawRate = min(attackFrame / (float)startUpFrameLight, 1.0f);
		drawRate = max(drawRate, 0.0f);

	    

		rangeTransform.scale = VECTOR3(1,1,1)*attackRange *  drawRate;
		rangeMesh->m_vDiffuse = VECTOR4(1,0.3,0,min(drawRate,0.8f));

		//攻撃範囲の描画処理
		rangeMesh->Render(rangeTransform.matrix());

		//攻撃範囲の枠の描画処理
		rangeTransform.scale = VECTOR3(1, 1, 1) * attackRange;
		circleMesh->m_vDiffuse = VECTOR4(1, 0.1, 0, 1.0f);
		circleMesh->Render(rangeTransform.matrix());
	}


}

EnemyBoss1* EnemySoldier::GetBoss()
{
	return boss;
}

void EnemySoldier::UpdateNormal()
{
	
	//ボスが戦闘モードだったら
	if (boss->GetState() == Fight)
	{
		state = Contact;	//状態を連絡状態に変更
	}
	else//ボスが戦闘モードじゃなかったら
	{
		//プレイヤーへ向かうベクトルを取得
		VECTOR3 forward = VECTOR3(0, 0, 1) * XMMatrixRotationY(transform.rotation.y);
		
		float ipF = Dot(forward, toPlayer);
	
		//追いかける距離
		float chaseRange = 5.0f;

		//プレイヤーとの距離が一定以下のとき
		if (toPlayer.Length() < chaseRange) {
			//視界範囲内であれば
			if (ipF >= cosf(60.0f * DegToRad))
			{
				new ExclEffect(this);
				animator->MergePlay(aWalk);
				state = Contact;
			}
		}
	}
}

void EnemySoldier::UpdateContact()
{
	//ボスが存在していたら
	if (boss) {
		animator->MergePlay(aWalk);
		
		//ボスへ向かうベクトルを取得
		VECTOR3 toBoss = (boss->Position() - this->Position());

		if ((boss->GetState() != Fight) )//ボスが戦闘モードじゃなかったら
		{
			//ボスへの距離が一定以上のとき
			if (toBoss.Length() > 3.5f)
			{
				//ボスへ向かうベクトルを正規化
				toBoss = XMVector3Normalize(toBoss);
				//自分の向きをボスに向かせる
				transform.rotation.y = atan2(toBoss.x, toBoss.z);
				velo = toBoss * 0.01;
			}
			else
			{
				boss->state = Fight;
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
	
	
	
	//プレイヤーとの距離が一定範囲内であれば攻撃をする 
	if (toPlayer.Length() <= 2.0f)
	{
		if (coolCount <= 0)
		{
			state = AttackLight;
		}
	}
	else//一定範囲外であれば、Boidsアルゴリズムを実行
	{
		//Boidsアルゴリズムの処理
		Boids();
	}
	//動いていないなら、アニメーションをダンスにする
	if (velo.Length() <= 0)
	{
		if (animator->PlayingID() != aDance)
		{
			animator->MergePlay(aDance);
		}
	}
	else
	{
		//キャラクターが動いているときにアニメーションが歩いていなかったら歩かせる
		if (animator->PlayingID() != aWalk)
		{
			animator->MergePlay(aWalk);
		}
	}
	
	
	transform.rotation.y = atan2(velo.x, velo.z);
	velo.y = 0;
	transform.position += velo;

}

void EnemySoldier::UpdateAttackLight()
{
	//攻撃フレームの加算
	attackFrame++;

	//攻撃範囲のTransform
	rangeTransform = transform;
	//攻撃範囲までの距離
	VECTOR3 length = VECTOR3(0, 0.1f, attackLength);
	//Y軸の回転行列
	MATRIX4X4 rotY = XMMatrixRotationY(transform.rotation.y);

	rangeTransform.position = transform.position + (length * rotY);

	float attackLength = (rangeTransform.position - player->Position()).Length();

	if(startUpFrameLight < attackFrame && attackFrame <= startUpFrameLight + attackFrameLight) {
		

		if (attackLength < attackRange)
		{
			if (!isHitAttack)
			{
				player->Damage(5);
				isHitAttack = true;
			}
		}

	}


	//攻撃アニメーションを再生
	if (animator->PlayingID() != aAttackLight)
	{
		animator->MergePlay(aAttackLight);
	}
	
	
	//攻撃が終了したら
	if (animator->Finished())
	{
		attackFrame = 0;

		//クールタイムを設定する
		coolCount = coolTime;

		isHitAttack = false;

		//ステートを戦闘状態に戻す
		state = Fight;

	}
	
}

void EnemySoldier::Boids()
{

	if (reactionTime < reactionCount)
	{
		reactionTime = Random(10, 20);
		reactionCount = 0;

		//スピードの初期化
		velo = VECTOR3();

		VECTOR3 avgPos = VECTOR3();//集団の位置の平均				(結合用)
		VECTOR3 avgVelo = VECTOR3();//集団の速度の平均(向き、速さ)	(整列用)

		float sight = 5;//視界
		float volume = 0;		//視界内の個体数

		if ((boss->Position() - this->Position()).Length() < sight)
		{
			volume++;
			//avgPos += boss->Position();
			avgVelo += boss->GetVelo();
		}

		for (auto node : *boss->GetFlock())
		{

			//同じボスを持つ群れの時
			if (node->boss == boss && node->state == Fight)
			{

				auto toNode = node->Position() - this->Position();
				auto length = toNode.Length();

				//自分の周囲一定範囲内にいたら
				if (length <= sight)
				{

					volume++;//計算する個体数
					avgPos += node->Position();
					
					//速度を正規化したものの平均を求める
					avgVelo += XMVector3Normalize(node->velo);

				}
			}
		}
		//近く仲間がにいた場合
		if (volume > 0)
		{
			//個体数で割って平均を出す
			avgVelo /= volume;
			avgPos /= volume;

			//群れの中心へ向かうベクトル

			VECTOR3 toAvgPos((avgPos -this->Position()) * 0.001);

			//速度を求めたベクトルの合計にする
			velo = (avgVelo * 1.0 + toAvgPos);
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
}
