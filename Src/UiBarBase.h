#pragma once
#include "GameObject.h"

class UiBarBase :public GameObject
{
public:

	/// <summary>
	/// �o�[��UI
	/// </summary>
	/// <param name="vRate">�\�����銄��</param>
	/// <param name="size">�`��T�C�Y</param>
	/// <param name="dir">true:���o�[,false:�c�o�[</param>
	UiBarBase(float *vRate,VECTOR2 position,VECTOR2 size);
	virtual ~UiBarBase();

	void Draw()override;

	

private:
	//�`�抄��
	float *rate;

	//�`����W
	VECTOR2 position;
	//�`��T�C�Y
	VECTOR2 maxSize;

};