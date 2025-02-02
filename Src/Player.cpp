#include "Player.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "CameraPlayScene.h"
#include "MoveTarget.h"
#include "Lerp.h"
#include "MeshCollider.h"


Player::Player() :
	cam(nullptr),					//�J����
	target(nullptr),				//�ړ���^�[�Q�b�gc
	doubleTapCount(10),				//�_�u���^�b�v����p�J�E���g�@
	doubleTapTime(10),				//�_�u���^�b�v�̋��e����
	invincibleCount(0),				//���G���Ԃ̃J�E���g�@
	invincibleTime(60),				//���G����
	countAttackFrame(0),			//�U����������̑��t���[��
	attackRangeLight(3.0f),			//�U���͈�(����)
	attackAngleLight(60.0f),		//�U���͈�(�p�x)
	attackFrameLight(5),			//�U���t���[��
	attackKnockBackHeightLight(0.1f)//�m�b�N�o�b�N���鍂��
{
	//�`�揇��x������
	ObjectManager::SetDrawOrder(this, -1000);

	GameDevice()->m_pDI->ShowMouseCursor(false);
	animator = nullptr;
	cam = ObjectManager::FindGameObject<CameraPlayScene>();
	toRot = transform.rotation.y;
	//�J�[�\���摜���[�h
	cursolImg = new CSpriteImage("data/images/ui/Cursol.png");
	sword = new CFbxMesh();
	sword->Load("data/models/chara/Night/Sword.mesh");
}

Player::~Player()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(cursolImg);
	SAFE_DELETE(sword);
	SAFE_DELETE(animator);
	GameDevice()->m_pDI->ShowMouseCursor(true);
}

void Player::Update()
{
	//�}�E�X�J�[�\�����W�擾
	currPos = GameDevice()->m_pDI->GetMousePos();
	switch (state)
	{
	case Player::Normal:
		UpdateNormal();
		break;

	case Player::Evasion:
		UpdateEvation();
		break;

	case AttackLight:
		UpdateAttackLight();
		break;

	case Player::Dead:
		break;

	default:
		break;
	}

	animator->Update();
}

void Player::Draw()
{
	Object3D::Draw();//�v���C���[���f���̕`��
	CSprite spr;//�X�v���C�g�`��N���X
	
	Transform swordTransform;

	swordTransform.rotation = VECTOR3(0, 0, -90);
	MATRIX4X4 swordMat = swordTransform.matrix();

	MATRIX4X4 bone = mesh->GetFrameMatrices(animator,14,1);
	sword->Render(swordMat * bone* transform.matrix());
	

	//�J�[�\���`��
	spr.Draw(
		cursolImg,
		currPos.x - cursolImg->m_dwImageWidth/2,
		currPos.y - cursolImg->m_dwImageHeight,
		0,0,cursolImg->m_dwImageWidth,cursolImg->m_dwImageHeight);
}


void Player::SetMesh(const TCHAR* file)
{
	animator = new Animator();

	mesh = new CFbxMesh();
	mesh->Load("data/models/chara/Night.mesh");

	
	animator->SetModel(mesh);
	mesh->LoadAnimation(0, "data/models/chara/Walking.anmx", true);
	mesh->LoadAnimation(1, "data/models/chara/Roll.anmx", false);
	mesh->LoadAnimation(2, "data/models/chara/Idle.anmx", true);
	mesh->LoadAnimation(3, "data/models/chara/Night/AttackLight.anmx", false);
	animator->Play(aWalk);
	animator->SetPlaySpeed(1.0f);
}

void Player::UpdateNormal()
{
	auto di = GameDevice()->m_pDI;//����

	//�i�ތ����֌����Ă��銄��(�ŏ��@��100%)
	float rotRate = 1.0f;

	doubleTapCount++;

	if (di->CheckMouse(KD_DAT, DIM_LBUTTON))//�N���b�N���Ă����
	{
		VECTOR3 cursolPos = GetCursolPos();
		
		if (doubleTapCount <= doubleTapTime)//�_�u���^�b�v���̏���
		{
			invincibleCount = 0;
			animator->MergePlay(aRoll);
			state = Evasion;
			return;
		}
		else
		{
			if (cursolPos.y > 0.1f)//�J�[�\�����n�ʂ��畂���Ă��鎞
			{
				//ToDo:�u���Ȃ��J�[�\����\������
			}
			else
			{
				if ((cursolPos - this->Position()).Length() > 1.1f)
				{
					if (!target) {//�^�[�Q�b�g�����݂��Ȃ�������C���X�^���X����
						target = new MoveTarget(cursolPos, this);
					}
					else
					{
						target->SetPosition(cursolPos);
					}

				}
			}
			
			
			VECTOR3 toTarget = cursolPos - this->Position();


			toRot = atan2(toTarget.x, toTarget.z);
			count = 0;
			time = 30;
			startRot = transform.rotation.y;
			rot = toRot - startRot;
		}

	}

	if (di->CheckMouse(KD_UTRG, DIM_LBUTTON))//�N���b�N����߂���
	{
		doubleTapCount = 0;
	}

	count++;
	rotRate = count / time;
	if (rotRate > 1.0f)
	{
		rotRate = 1.0f;
	}
	else
	{
		transform.rotation.y = rot * rotRate + startRot;

	}

	if (target) {

		if (animator->PlayingID() != 0)
		{
			animator->MergePlay(aWalk);
		}

		//Todo[Aranami]:�������d��������������Ȃ��̂ŁA�C������
		VECTOR3 toTarget = target->Position() - this->Position();
		toTarget = XMVector3Normalize(toTarget);
		toTarget *= 0.05;
		transform.position += toTarget;
	}
	else
	{
		if (animator->PlayingID() != 2)
		{
			animator->MergePlay(aIdle);
		}
		
	}

	//�E�N���b�N(�U��)
	if (di->CheckMouse(KD_TRG, DIM_RBUTTON))
	{
		VECTOR3 cursolPos = GetCursolPos();

		VECTOR3 toCursolPos = cursolPos - this->Position();
		transform.rotation.y  = atan2(toCursolPos.x, toCursolPos.z);
		
		

		animator->MergePlay(aAttackLight);
		state = AttackLight;//�U����Ԃɂ���
		
		//�ړ���^�[�Q�b�g������
		if (target)
		{
			target->DestroyMe();
			target = nullptr;
		}
	}
	
}

void Player::UpdateAttackLight()
{
	//�U���t���[�����Z
	countAttackFrame++;

	//�U���L���t���[�����ł���ΓG�ɍU�����q�b�g������
	if (countAttackFrame <= attackFrameLight)
	{
		if (!enemys.empty())
		{
			//�G�̃��X�g��T������
			for (auto enemy : enemys)
			{
				if (enemy->toPlayer.Length() <= attackRangeLight)
				{
					//�G�̃X�e�[�g
					int eState = enemy->state;
					//�G���m�b�N�o�b�N���Ă�����ł����Ȃ��Ƃ�
					if ((eState != KnockBack) && (eState != Dead))
					{
						//ToDo[Aranami]:�U���͈͂ƍU���t���[���̎���

						//y���̉�]�s��
						MATRIX4X4 rotY = XMMatrixRotationY(transform.rotation.y);
						//�v���C���[�̑O���x�N�g��
						VECTOR3 forward = VECTOR3(0, 0, 1) * rotY;
						float ipF = Dot(forward, -(enemy->toPlayer));

						//���肪���U���͈͓��ɂ�����m�b�N�o�b�N������
						if (ipF >= cosf(attackAngleLight * DegToRad))
						{
							VECTOR3 KnockBack;
							KnockBack = XMVector3Normalize(-(enemy->toPlayer)) * 0.02;
							KnockBack.y = attackKnockBackHeightLight;
							enemy->SetKnockBackVelo(KnockBack);
						}
					}
				}

			}
		}
	}
	
	
	//�A�j���[�V�������I�������ʏ�ɖ߂�
	if (animator->Finished())
	{
		//�U���t���[��������������
		countAttackFrame = 0;
		state = Normal;

	}
	
}

void Player::UpdateEvation()
{
	invincibleCount++;//���G���ԃJ�E���g
	doubleTapCount = doubleTapTime + 1;
	
	auto target = ObjectManager::FindGameObject<MoveTarget>();
	if (target) {
		VECTOR3 toTarget = target->Position() - this->Position();
		toTarget = XMVector3Normalize(toTarget);//�x�N�g�����K��

		transform.rotation.y = atan2(toTarget.x, toTarget.z);//�N���b�N���������֌���

		transform.position += toTarget*0.07;

	}

	if (invincibleTime <= invincibleCount)
	{
		count = time;
		animator->MergePlay(aWalk);
		state = Normal;
	}
	

}

VECTOR3 Player::GetCursolPos()
{
	VECTOR3 start = cam->Position();

	//�J�[�\���̍��W�����[���h���W�ɕϊ��������̂𔻒�̏I���̍��W�ɂ���
	start = XMVector3Unproject(
		VECTOR3(currPos.x, currPos.y, 0.0),
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		GameDevice()->m_mProj, GameDevice()->m_mView, XMMatrixIdentity()
	);
	VECTOR3 end = XMVector3Unproject(
		VECTOR3(currPos.x, currPos.y, 1.0),
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		GameDevice()->m_mProj, GameDevice()->m_mView, XMMatrixIdentity()
	);

	MeshCollider::CollInfo targetInfo;
	targetInfo.hitPosition = this->Position();//�^�[�Q�b�g�������̈ʒu�ŏ�����
	//�^�[�Q�b�g�|�W�V������������
	ObjectManager::FindGameObject<StaticObject>()->HitLineToMesh(start, end, &targetInfo);

	//�����̏�����
	float minLength = (targetInfo.hitPosition - this->Position()).LengthSquare();


	auto objs = ObjectManager::FindGameObjects<StaticObject>();
	for (auto obj : objs)
	{

		MeshCollider::CollInfo hit;//�J���������Ray�ƃI�u�W�F�N�g�̐ڐG�ʒu
		if (obj->HitLineToMesh(start, end, &hit)) {
			float length = (hit.hitPosition - this->Position()).LengthSquare();
			//���߂��L�����N�^�[����̋������ŒZ��������^�[�Q�b�g�|�W�V������������
			if (minLength > length)
			{
				targetInfo.hitPosition = hit.hitPosition;
			}
		}
	}


	return targetInfo.hitPosition;
}
