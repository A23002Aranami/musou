//24.1210 �����Ȃ��I�u�W�F�N�g�N���X(���肠��)
#pragma once
#include "Object3D.h"

class CCollision;
class StaticObject : public Object3D
{
public:
	StaticObject();
	virtual ~StaticObject();

	void SetMesh( const TCHAR* file );
	CCollision* col;
};