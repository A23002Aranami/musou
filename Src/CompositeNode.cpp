#include "CompositeNode.h"

void CompositeNode::AddChild(BehaviorNodeBase* child)
{
	//子ノードリストに追加する
	children.push_back(child);
}
