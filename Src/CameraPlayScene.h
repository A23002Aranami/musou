#pragma once
#include "Object3D.h"
#include "Player.h"

class CameraPlayScene : public Object3D
{
public :
	void Update()override;
	void Draw()override {};

	CameraPlayScene();

private:
	float camSpeed,lookSpeed;

};
