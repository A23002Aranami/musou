#include "ConditionNode.h"

ConditionNode::ConditionNode(BehaviorNodeBase* childNode, std::function<bool()> cond):
	condition(cond)
{
	child = childNode;
}

NodeState ConditionNode::Tick()
{
	//ðŒ•ª‚ªtrue‚È‚çŽÀs‚µ‚ÄSucces‚ð•Ï‚¦‚·
	if (condition())
	{
		return child->Tick();
	}
	else
	{
		return Failure;
	}
}
