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
	//rootがnullptrでなければ、rootから処理を走らせる
	if (root) {
		root->Tick();
	}
}
