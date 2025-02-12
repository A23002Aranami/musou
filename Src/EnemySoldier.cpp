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

	//�U���͈͂̏�����
	attackLength = 1.0f;
	attackRange = 2.0f;

	//�U���̃N�[���^�C��
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
	//�e�N���X�̃A�b�v�f�[�g���Ă�
	Enemy::Update();
	
	if (coolTime > 0)//�N�[���^�C����0�ȏ�̂Ƃ�
	{
		coolCount--;
	}
	reactionCount++;
}

void EnemySoldier::Draw()
{
	Enemy::Draw();

	//�U����Ԃ̎��͍U���͈͂�`�� 
	if (state == AttackLight)
	{
		//�`��Ɏg������
		float drawRate = min(attackFrame / (float)startUpFrameLight, 1.0f);
		drawRate = max(drawRate, 0.0f);

	    

		rangeTransform.scale = VECTOR3(1,1,1)*attackRange *  drawRate;
		rangeMesh->m_vDiffuse = VECTOR4(1,0.3,0,min(drawRate,0.8f));

		//�U���͈͂̕`�揈��
		rangeMesh->Render(rangeTransform.matrix());

		//�U���͈̘͂g�̕`�揈��
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
				animator->MergePlay(aWalk);
				state = Contact;
			}
		}
	}
}

void EnemySoldier::UpdateContact()
{
	//�{�X�����݂��Ă�����
	if (boss) {
		animator->MergePlay(aWalk);
		
		//�{�X�֌������x�N�g�����擾
		VECTOR3 toBoss = (boss->Position() - this->Position());

		if ((boss->GetState() != Fight) )//�{�X���퓬���[�h����Ȃ�������
		{
			//�{�X�ւ̋��������ȏ�̂Ƃ�
			if (toBoss.Length() > 3.5f)
			{
				//�{�X�֌������x�N�g���𐳋K��
				toBoss = XMVector3Normalize(toBoss);
				//�����̌������{�X�Ɍ�������
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
	
	
	
	//�v���C���[�Ƃ̋��������͈͓��ł���΍U�������� 
	if (toPlayer.Length() <= 2.0f)
	{
		if (coolCount <= 0)
		{
			state = AttackLight;
		}
	}
	else//���͈͊O�ł���΁ABoids�A���S���Y�������s
	{
		//Boids�A���S���Y���̏���
		Boids();
	}
	//�����Ă��Ȃ��Ȃ�A�A�j���[�V�������_���X�ɂ���
	if (velo.Length() <= 0)
	{
		if (animator->PlayingID() != aDance)
		{
			animator->MergePlay(aDance);
		}
	}
	else
	{
		//�L�����N�^�[�������Ă���Ƃ��ɃA�j���[�V�����������Ă��Ȃ��������������
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
	//�U���t���[���̉��Z
	attackFrame++;

	//�U���͈͂�Transform
	rangeTransform = transform;
	//�U���͈͂܂ł̋���
	VECTOR3 length = VECTOR3(0, 0.1f, attackLength);
	//Y���̉�]�s��
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


	//�U���A�j���[�V�������Đ�
	if (animator->PlayingID() != aAttackLight)
	{
		animator->MergePlay(aAttackLight);
	}
	
	
	//�U�����I��������
	if (animator->Finished())
	{
		attackFrame = 0;

		//�N�[���^�C����ݒ肷��
		coolCount = coolTime;

		isHitAttack = false;

		//�X�e�[�g��퓬��Ԃɖ߂�
		state = Fight;

	}
	
}

void EnemySoldier::Boids()
{

	if (reactionTime < reactionCount)
	{
		reactionTime = Random(10, 20);
		reactionCount = 0;

		//�X�s�[�h�̏�����
		velo = VECTOR3();

		VECTOR3 avgPos = VECTOR3();//�W�c�̈ʒu�̕���				(�����p)
		VECTOR3 avgVelo = VECTOR3();//�W�c�̑��x�̕���(�����A����)	(����p)

		float sight = 5;//���E
		float volume = 0;		//���E���̌̐�

		if ((boss->Position() - this->Position()).Length() < sight)
		{
			volume++;
			//avgPos += boss->Position();
			avgVelo += boss->GetVelo();
		}

		for (auto node : *boss->GetFlock())
		{

			//�����{�X�����Q��̎�
			if (node->boss == boss && node->state == Fight)
			{

				auto toNode = node->Position() - this->Position();
				auto length = toNode.Length();

				//�����̎��͈��͈͓��ɂ�����
				if (length <= sight)
				{

					volume++;//�v�Z����̐�
					avgPos += node->Position();
					
					//���x�𐳋K���������̂̕��ς����߂�
					avgVelo += XMVector3Normalize(node->velo);

				}
			}
		}
		//�߂����Ԃ��ɂ����ꍇ
		if (volume > 0)
		{
			//�̐��Ŋ����ĕ��ς��o��
			avgVelo /= volume;
			avgPos /= volume;

			//�Q��̒��S�֌������x�N�g��

			VECTOR3 toAvgPos((avgPos -this->Position()) * 0.001);

			//���x�����߂��x�N�g���̍��v�ɂ���
			velo = (avgVelo * 1.0 + toAvgPos);
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
}
