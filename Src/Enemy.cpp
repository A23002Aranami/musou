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
CFbxMesh* Enemy::rangeMesh = nullptr;

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
		enemyMesh->LoadAnimation(aWalk, "data/models/Enemy/Gob/Walk.anmx", true);
		enemyMesh->LoadAnimation(aDance, "data/models/Enemy/Gob/Dance.anmx", true);
		enemyMesh->LoadAnimation(aAttackLight, "data/models/Enemy/Gob/AttackLight.anmx", false);

		//�U���͈͗p�̃��b�V��
		rangeMesh = new CFbxMesh();
		rangeMesh->Load("data/models/Common/Range.mesh");
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

	animator->Play(aDance);
	//�v���C�X�s�[�h�𓙑��ŏ�����
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
		delete enemyMesh;//�G�S�̂ŋ��ʂ̃��b�V�����f���[�g
		player = nullptr;//�v���C���[�̋��ʃ|�C���^���f���[�g
		stage = nullptr;//�X�e�[�W�̋��ʃ|�C���^���f���[�g
	}
	//�A�j���[�^�[�̃f���[�g
	SAFE_DELETE(animator);
	//�l�������Z
	num--;
}

void Enemy::Update()
{
	//�v���C���[�֌������x�N�g�����擾
	toPlayer = player->Position() - this->Position();

	//�A�j���[�V�����̃A�b�v�f�[�g
	animator->Update();

	switch (state)
	{
	case Normal:			//�ʏ���
		UpdateNormal();
		break;
	case Contact:			//�ڐG���
		UpdateContact();
		break;
	case Chase:				//�ǐՏ��
		UpdateChase();
		break;
	case Fight:				//�퓬���
		UpdateFight();
		break;
	case AttackLight:		//�U�����
		UpdateAttackLight();
		break;
	case KnockBack:			//�m�b�N�o�b�N���
		UpdateKnockBack();
		break;
	case Dead:				//���S���
		break;
	default:				//���̑�
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
				if ( (node->state != Dead) &&
					 (node->state != KnockBack) &&
					 (node->state != AttackLight)
					)
				{
					auto toNode = node->Position() - this->Position();
					auto length = toNode.Length();

					//���������ȉ��̂Ƃ�
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
	//�v���C���[�Ƃ̋������`�拗���ȓ��ł���A���S��ԂłȂ��Ƃ��`�悷��
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

void Enemy::UpdateAttackLight()
{
}


