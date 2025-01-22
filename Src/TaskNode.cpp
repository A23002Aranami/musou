#include "TaskNode.h"

TaskNode::TaskNode(std::function<NodeState()> func):
	task(func)
{
}

NodeState TaskNode::Tick()
{
	return task();
}
