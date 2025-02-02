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
	Enemy::~Enemy();
	boss = nullptr;
}

void EnemySoldier::Update()
{
	//�e�N���X�̃A�b�v�f�[�g���Ă�
	Enemy::Update();
	
	reactionCount++;
}

EnemyBoss1* EnemySoldier::GetBoss()
{
	return boss;
}

void EnemySoldier::UpdateNormal()
{
	

	//�A�j���[�V�����A�b�v�f�[�g
	animator->Update();
	
	//�{�X���퓬���[�h��������
	if (boss->GetState() == Fight)
	{
		state = Contact;	//��Ԃ�A����ԂɕύX
	}
	else//�{�X���퓬���[�h����Ȃ�������
	{
		//�v���C���[�֌������x�N�g�����擾
		VECTOR3 forward = VECTOR3(0, 0, 1) * XMMatrixRotationY(transform.rotation.y);
		
		float ipF = Dot(forward, toPlayer);
	
		//�ǂ������鋗��
		float chaseRange = 5.0f;

		//�v���C���[�Ƃ̋��������ȉ��̂Ƃ�
		if (toPlayer.Length() < chaseRange) {
			//���E�͈͓��ł����
			if (ipF >= cosf(60.0f * DegToRad))
			{
				new ExclEffect(this);
				animator->MergePlay(Walk);
				state = Contact;
			}
		}
	}
}

void EnemySoldier::UpdateContact()
{
	//�{�X�����݂��Ă�����
	if (boss) {
		animator->MergePlay(Walk);
		animator->Update();

		//�{�X�֌������x�N�g�����擾
		VECTOR3 toBoss = (boss->Position() - this->Position());

		if ((boss->GetState() != Fight) )//�{�X���퓬���[�h����Ȃ�������
		{
			//�{�X�ւ̋��������ȏ�̂Ƃ�
			if (toBoss.Length() > 2.0f)
			{
				//�{�X�֌������x�N�g���𐳋K��
				toBoss = XMVector3Normalize(toBoss);
				//�����̌������{�X�Ɍ�������
				transform.rotation.y = atan2(toBoss.x, toBoss.z);
				velo = toBoss * 0.01;
			}
			else
			{
				state = Fight;
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

		VECTOR3 avgPos = VECTOR3();//�W�c�̈ʒu�̕���				(�����p)
		VECTOR3 avgVelo = VECTOR3();//�W�c�̑��x�̕���(�����A����)	(����p)

		float sight = 10;//���E
		float volume = 0;		//���E���̌̐�
		
		if ((boss->Position() - this->Position()).Length() < sight)
		{
			volume++;
			avgPos += boss->Position();
			avgVelo += boss->GetVelo();
		}

		for (auto node : *boss->GetFlock())
		{

			//�����{�X�����Q��̎�
			if (node->boss == boss && node->state == Contact)
			{
				auto toNode = node->Position() - this->Position();
				auto length = toNode.Length();
				//�����̎��͈��͈͓��ɂ�����
				if (length <= sight)
				{

					volume++;//�v�Z����̐�
					avgPos += node->Position();
					avgVelo += node->velo;
				}
			}
		}
		//�߂����Ԃ��ɂ����ꍇ
		if (volume > 0)
		{
			//�̐��Ŋ����ĕ��ς��o��
			avgVelo /= volume;
			avgPos /= volume;
			avgPos = XMVector3Normalize(avgPos);

			VECTOR3 toAvgPos(XMVector3Normalize(avgPos - this->Position()) * 0.01);
			//���x�����߂��x�N�g���̍��v�ɂ���
			velo = (avgVelo * 1.5 + toAvgPos);
			velo = XMVector3Normalize(velo);
			velo *= 0.01;
		}

		//�����̎��E���ɒ��Ԃ������ꍇ
		if (toPlayer.Length() <= 5.0f)
		{
			//�v���C���[�֌������x�N�g���𐳋K��
			VECTOR3 toVec = XMVector3Normalize(toPlayer);
			toVec *= 0.01f;

			//�v���C���[�֌����������̒���
			toVec * 2;

			//���x�̗v�f�Ƀv���C���[�֌������x�N�g����������
			velo += toVec;
			velo /= 2;

		}

		
	}
	
	//�����Ă��Ȃ��Ȃ�A�A�j���[�V�������_���X�ɂ���
	if (velo.Length() <= 0)
	{
		if (animator->PlayingID() != Dance)
		{
			animator->MergePlay(Dance);
		}
	}
	else
	{
		//�L�����N�^�[�������Ă���Ƃ��ɃA�j���[�V�����������Ă��Ȃ��������������
		if (animator->PlayingID() != Walk)
		{
			animator->MergePlay(Walk);
		}
	}
	
	
	transform.rotation.y = atan2(velo.x, velo.z);
	velo.y = 0;
	transform.position += velo;

}
