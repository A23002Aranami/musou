//24.12.02 T.Aranami �V�K�쐬�F�r�w�C�r�A�c���[�m�[�h���N���X
#pragma once
#include "GameObject.h"

//�m�[�h�̃X�e�[�g
enum NodeState
{
	Success,//����
	Failure,//���s
	Running,//���s��
};

class BehaviorNodeBase
{
public:
	virtual ~BehaviorNodeBase();

	/// <summary>
	/// ���������s����(��΂Ɍp�����Ȃ���΂Ȃ�Ȃ�)
	/// </summary>
	/// <returns>�m�[�h�̃X�e�[�^�X</returns>
	virtual  NodeState Tick() = 0;
};