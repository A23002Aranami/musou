//24.12.02 T.Aranami �V�K�쐬�F�^�X�N���s�m�[�h
#pragma once
#include "BehaviorNodeBase.h"
#include <functional>

class TaskNode : public BehaviorNodeBase
{
public:
	TaskNode(std::function<NodeState()> func);
	NodeState Tick()override;
private:
	//���s����֐��I�u�W�F�N�g
	std::function<NodeState()> task;
};
