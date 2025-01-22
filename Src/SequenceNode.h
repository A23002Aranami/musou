//24.12.02 T.Aranami 新規作成：シーケンスノードクラス
#pragma once
#include "CompositeNode.h"

class SequenceNode : public CompositeNode
{
public:

	NodeState Tick()override;
};