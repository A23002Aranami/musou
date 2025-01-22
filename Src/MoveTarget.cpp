#include "MoveTarget.h"


MoveTarget::MoveTarget(VECTOR3 vPos,Player* player):pl(player)
{
	auto list =ObjectManager::FindGameObjects<MoveTarget>();
	
	for (auto node : list)
	{
		if (node != this)
		{
			node->DestroyMe();
		}
	}
	transform.position = vPos;
	mesh = new CFbxMesh();
	mesh->Load("data/models/MoveTarget/missile.mesh");
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
	float length = (this->Position() - pl->Position()).Length();

	//�^�[�Q�b�g�v���C���[�����ǂ蒅���������
	if (length < 1.0f)
	{
		pl->target = nullptr;
		DestroyMe();
	}
}

