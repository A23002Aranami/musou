#pragma once
#include "CompositeNode.h"

class SelectorNode : public CompositeNode
{
public:

	NodeState Tick()override;
};