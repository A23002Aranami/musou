#include "MoveTarget.h"


MoveTarget::MoveTarget(VECTOR3 vPos,Player* player):pl(player)
{
	transform.position = vPos;
	mesh = new CFbxMesh();
	transform.scale *= 2;
	mesh->Load("data/models/MoveTarget/Mark.mesh");
}

MoveTarget::~MoveTarget()
{
	if (mesh)
	{
		delete mesh;
	}
}

void MoveTarget::Update()
{
	//��
	transform.rotation.y += 1 * DegToRad;

	float length = (this->Position() - pl->Position()).Length();

	//�^�[�Q�b�g�v���C���[�����ǂ蒅���������
	if (length < 1.0f)
	{
		pl->target = nullptr;
		DestroyMe();
	}
}

