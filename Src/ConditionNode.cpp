#include "ConditionNode.h"

ConditionNode::ConditionNode(BehaviorNodeBase* childNode, std::function<bool()> cond):
	condition(cond)
{
	child = childNode;
}

NodeState ConditionNode::Tick()
{
	//条件分がtrueなら実行してSuccesを変えす
	if (condition())
	{
		return child->Tick();
	}
	else
	{
		return Failure;
	}
}
