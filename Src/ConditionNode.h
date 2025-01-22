//24.12.02 T.Aranami �V�K�쐬�F�����m�[�h�N���X
#pragma once
#include "DecolatorNode.h"
#include <functional>

class ConditionNode :public DecolatorNode
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="child">�q�m�[�h</param>
	/// <param name="cond">������</param>
	ConditionNode(BehaviorNodeBase* childNode, std::function<bool()>cond);

	NodeState Tick()override;

private:

	//bool�^�̊֐��I�u�W�F�N�g(������)
	std::function<bool()> condition;
};