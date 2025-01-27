#include "CameraPlayScene.h"

void CameraPlayScene::Update()
{
	Object3D* pl = ObjectManager::FindGameObject<Player>();


	if (pl)//�v���C���[�����݂���ꍇ
	{
		VECTOR3 offsetPos;

		offsetPos = pl->Position() + VECTOR3(0, 15, -15);

		VECTOR3 toOffsetPos = offsetPos	 - this->Position();//�I�t�Z�b�g�|�W�V�����ֈړ�����x�N�g��
		VECTOR3 toPlayerPos = pl->Position() - this->Position();

		float length;//�����p�ϐ�
		length = (toOffsetPos).Length();

		
		//�J�������w��̂���������ȏ�
		if (length >= 0.2)
		{
			transform.position += toOffsetPos * camSpeed;
		}
		else
		{
			//this->SetPosition(offsetPos);
		}
		
		length = toPlayerPos.Length();

		if (length >= 0.2)
		{

			transform.rotation += toPlayerPos * lookSpeed;
		}
		

		//�����_���v���C���[�̈ʒu��
		//transform.rotation = pl->Position();
	}

	GameDevice()->m_vEyePt = transform.position;
	GameDevice()->m_vLookatPt = transform.rotation;
	GameDevice()->m_mView = XMMatrixLookAtLH
	(
		transform.position,
		transform.rotation,
		VECTOR3(0, 1, 0)
	);
}


CameraPlayScene::CameraPlayScene():camSpeed(0.015),lookSpeed(0.01)
{
	//�J�����̃|�W�V����
	transform.position = VECTOR3(0, 15, -15);
	//�J�����̒����_
	transform.rotation = VECTOR3(0, 0, 0);


	GameDevice()->m_mView = XMMatrixLookAtLH
	(
		transform.position,
		transform.rotation,
		VECTOR3(0, 1, 0)
	);
}
