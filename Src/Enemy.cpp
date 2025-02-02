#include "Enemy.h"
#include "Stage.h"

namespace
{
	//�`�拗��
	static const float ableLength = 25.0f;

}

class Stage;

Player* Enemy::player = nullptr; // �ÓI�����o�ϐ��̒�`

CFbxMesh* Enemy::enemyMesh = nullptr;
Stage* Enemy::stage = nullptr;
int Enemy::num = 0;

Enemy::Enemy():state(Normal),knockBackVelo(VECTOR3(0,0,0))
{
	num++;//�l�������Z

	//�N���X�����ʂ̃����o��nullptr�̎��̂ݐݒ肷��
	if (!player) player = ObjectManager::FindGameObject<Player>();
	if (!stage) stage = ObjectManager::FindGameObject<Stage>(); 

	if (!enemyMesh)
	{
		enemyMesh = new CFbxMesh();
		enemyMesh->Load("data/models/Enemy/Gob/Gob.mesh");
		enemyMesh->LoadAnimation(Walk, "data/models/Enemy/Gob/Walk.anmx", true);
		enemyMesh->LoadAnimation(Dance, "data/models/Enemy/Gob/Dance.anmx", true);

	}
	

	mesh = enemyMesh;
	//�v���C���[�̃G�l�~�[���X�g�Ɏ�����ǉ�
	player->enemys.push_back(this);


	//mesh = new CFbxMesh();
	//mesh->Load("data/models/Enemy/Enemy1.mesh");
	//mesh->LoadAnimation(0, "data/models/Enemy/Walking.anmx", true);
	//mesh->LoadAnimation(1, "data/models/Enemy/Sitting.anmx", true);


	animator = new Animator();

	animator->SetModel(mesh);

	animator->Play(Dance);
	animator->SetPlaySpeed(1.0f);

	//�J�n���̌����������_���Őݒ�
	transform.rotation = VECTOR3(0, Random(0, 180) * DegToRad, 0);
}


Enemy::~Enemy()
{
	//24.12.19 T.Aranami �ǉ����ׂĂ̓G�����ʂ̃��b�V�����Q�Ƃ��Ă���̂Ńf���[�g�G���[���N����Ȃ��悤��mesh��nullptr�ɂ��Ă���
	mesh = nullptr;

	if (num == 1)//���\�[�X���f���[�g����Ă��Ȃ��Ƃ��f���[�g����
	{
		delete enemyMesh;
		player = nullptr;
	}
	SAFE_DELETE(animator);
	//�l�������Z
	num--;
}

void Enemy::Update()
{
	//�v���C���[�֌������x�N�g�����擾
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

	if ((this->state != Dead) && (this->state != KnockBack))
	{
		//���ׂẴ{�X�̂��ׂĂ̔z���ƃq�b�g����
		for (auto boss : *stage->GetBoss1())
		{
			for (auto node : *boss->GetFlock())
			{
				//�Ώۂ��������Ԃł���Ƃ�
				if ((node->state != Dead) && (node->state != KnockBack))
				{
					auto toNode = node->Position() - this->Position();
					auto length = toNode.Length();

					if (length < 1.0)
					{
						//�����������Ԃ������o��
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

	//�d�͕\��
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


