#include "BehaviorTree.h"

BehaviorTree::BehaviorTree(BehaviorNodeBase* node):
	root(node)
{
}

BehaviorTree::~BehaviorTree()
{
	if (!root)
	{
		delete root;
	}
}

void BehaviorTree::Run()
{
	//root‚ªnullptr‚Å‚È‚¯‚ê‚ÎAroot‚©‚çˆ—‚ð‘–‚ç‚¹‚é
	if (root) {
		root->Tick();
	}
}
