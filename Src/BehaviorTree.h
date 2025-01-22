#pragma once
#include "GameObject.h"
#include "SelectorNode.h"
#include "SequenceNode.h"
#include "TaskNode.h"
#include "ConditionNode.h"

class BehaviorTree
{
public:
	BehaviorTree(BehaviorNodeBase* node);
	virtual ~BehaviorTree();
	void Run();
private:
	BehaviorNodeBase* root;
};
