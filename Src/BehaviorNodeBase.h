//24.12.02 T.Aranami 新規作成：ビヘイビアツリーノード基底クラス
#pragma once
#include "GameObject.h"

//ノードのステート
enum NodeState
{
	Success,//成功
	Failure,//失敗
	Running,//実行中
};

class BehaviorNodeBase
{
public:
	virtual ~BehaviorNodeBase();

	/// <summary>
	/// 処理を実行する(絶対に継承しなければならない)
	/// </summary>
	/// <returns>ノードのステータス</returns>
	virtual  NodeState Tick() = 0;
};