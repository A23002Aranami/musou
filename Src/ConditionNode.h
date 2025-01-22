//24.12.02 T.Aranami 新規作成：条件ノードクラス
#pragma once
#include "DecolatorNode.h"
#include <functional>

class ConditionNode :public DecolatorNode
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="child">子ノード</param>
	/// <param name="cond">条件式</param>
	ConditionNode(BehaviorNodeBase* childNode, std::function<bool()>cond);

	NodeState Tick()override;

private:

	//bool型の関数オブジェクト(条件分)
	std::function<bool()> condition;
};