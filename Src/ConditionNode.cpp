#include "ConditionNode.h"

ConditionNode::ConditionNode(BehaviorNodeBase* childNode, std::function<bool()> cond):
	condition(cond)
{
	child = childNode;
}

NodeState ConditionNode::Tick()
{
	//��������true�Ȃ���s����Succes��ς���
	if (condition())
	{
		return child->Tick();
	}
	else
	{
		return Failure;
	}
}
