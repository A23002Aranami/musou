#include "StaticObject.h"

StaticObject::StaticObject()
{

}

void StaticObject::SetMesh(const TCHAR* file)
{
	//���b�V�������[�h
	mesh = new CFbxMesh();
	mesh->Load(file);
	//���b�V���R���C�_�[��ݒ�
	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh);
}
