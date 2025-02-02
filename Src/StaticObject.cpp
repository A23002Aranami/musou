#include "StaticObject.h"

StaticObject::StaticObject()
{

}

StaticObject::~StaticObject()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(meshCol);
}

void StaticObject::SetMesh(const TCHAR* file)
{
	//���b�V�������[�h
	mesh = new CFbxMesh();
	mesh->Load(file);

	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh);
}
