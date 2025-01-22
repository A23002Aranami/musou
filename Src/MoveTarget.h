//24.12.17 T.Aranami
#pragma once
#include "Object3D.h"
#include "Player.h"

class Player;

class MoveTarget : public Object3D
{
public :
	MoveTarget(VECTOR3 vPos,Player* pl);
	virtual ~MoveTarget();
	void Update()override;
private:
	Player* pl;
};