#include "StaticObject.h"

StaticObject::StaticObject()
{

}

void StaticObject::SetMesh(const TCHAR* file)
{
	//メッシュをロード
	mesh = new CFbxMesh();
	mesh->Load(file);
	//メッシュコライダーを設定
	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh);
}
