#pragma once


#include "EnemySoldier.h"
class EnemyVillage : public GameObject
{
public :

	/// <summary>
	/// �G�l�~�[�̏W������
	/// </summary>
	/// <param name="center">�W���̒��S</param>
	/// <param name="size">�W���̃T�C�Y(x,y,z)</param>
	/// <param name="num">�o��������G�l�~�[�̐�</param>
	EnemyVillage(VECTOR3 center,VECTOR3 size, int num);
	virtual ~EnemyVillage();

	void Draw()override;

private:
	VECTOR3 center;
	VECTOR3 lu, rd;
};
