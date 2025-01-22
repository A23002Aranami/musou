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
	//root��nullptr�łȂ���΁Aroot���珈���𑖂点��
	if (root) {
		root->Tick();
	}
}
