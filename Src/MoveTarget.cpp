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
	float length = (this->Position() - pl->Position()).Length();

	//ターゲットプレイヤーがたどり着いたら消す
	if (length < 1.0f)
	{
		pl->target = nullptr;
		DestroyMe();
	}
}

