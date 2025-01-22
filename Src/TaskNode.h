//24.12.02 T.Aranami 新規作成：タスク実行ノード
#pragma once
#include "BehaviorNodeBase.h"
#include <functional>

class TaskNode : public BehaviorNodeBase
{
public:
	TaskNode(std::function<NodeState()> func);
	NodeState Tick()override;
private:
	//実行する関数オブジェクト
	std::function<NodeState()> task;
};
