//24.12.02 T.Aranami 新規作成：デコレーターノード基底クラス
#pragma once
#include "BehaviorNodeBase.h"

class DecolatorNode : public BehaviorNodeBase
{
public:
	DecolatorNode() { ; }
	DecolatorNode(BehaviorNodeBase* childNode);

protected:
	//子ノード
	BehaviorNodeBase* child;
};
