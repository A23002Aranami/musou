#include "EnemyBoss1.h"

EnemyBoss1::EnemyBoss1():
	Enemy::Enemy()//�e�N���X�̃R���X�g���N�^���g��
{
	transform.scale *= 1.5;

	state = Normal;
}

EnemyBoss1::~EnemyBoss1()
{
	flock.clear();
}

void EnemyBoss1::Update()
{
	switch (state)
	{
	case Enemy::Normal:
		UpdateNormal();
		break;
	case Enemy::Fight:
		UpdateChase();
		break;
	case Enemy::Dead:
		break;
	default:
		break;
	}
}

void EnemyBoss1::Draw()
{
	if (mesh) {
		mesh->m_vDiffuse = VECTOR4(1.0, 0.5, 0.7, 1.0f);
		Object3D::Draw();
		mesh->m_vDiffuse = VECTOR4(1, 1, 1, 1.0f);
	}

}

int EnemyBoss1::GetState()
{
	return state;
}

VECTOR3 EnemyBoss1::GetVelo()
{
	return velo;
}

void EnemyBoss1::AddFlock(EnemySoldier* soldier)
{
	flock.push_back(soldier);
}

std::list<EnemySoldier*>* EnemyBoss1::GetFlock()
{
	return &flock;
}

void EnemyBoss1::UpdateNormal()
{
	auto soldiers = ObjectManager::FindGameObjects<EnemySoldier>();

	for (auto soldier : soldiers)
	{
		//�����̃{�X�������ł���Ƃ�
		if (soldier->GetBoss() == this)
		{
			float length = (soldier->Position() - this->Position()).Length();

			if (length < 1.0f && soldier->state == Contact)
			{
				state = Fight;
			}
		}
	}
}

void EnemyBoss1::UpdateChase()
{
	toPlayer = player->Position() - this->Position();

	if (toPlayer.Length() > 1.0f)
	{
		VECTOR3 toPlayerNormal = XMVector3Normalize(toPlayer);
		transform.rotation.y = atan2(toPlayer.x, toPlayer.z);

		velo = toPlayerNormal * 0.01;
		transform.position += velo;
	}
	else
	{
		state = Normal;
	}
}
