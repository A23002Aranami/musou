//24.12.02 T.Aranami �V�K�쐬�F�f�R���[�^�[�m�[�h���N���X
#pragma once
#include "BehaviorNodeBase.h"

class DecolatorNode : public BehaviorNodeBase
{
public:
	DecolatorNode() { ; }
	DecolatorNode(BehaviorNodeBase* childNode);

protected:
	//�q�m�[�h
	BehaviorNodeBase* child;
};
