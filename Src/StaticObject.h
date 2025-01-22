//24.1210 動かないオブジェクトクラス(判定あり)
#pragma once
#include "Object3D.h"

class StaticObject : public Object3D
{
public:
	StaticObject();

	void SetMesh( const TCHAR* file );

};