//24.12.02 T.Aranami 新規作成：制御ノード基底クラス
#pragma once
#include"BehaviorNodeBase.h"


class CompositeNode :public BehaviorNodeBase
{
public:
	//子ノードを追加する
	void AddChild(BehaviorNodeBase* child);
protected:
	//制御する子ノード
	std::vector<BehaviorNodeBase*> children;
};
