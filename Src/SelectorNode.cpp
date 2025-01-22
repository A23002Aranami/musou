//24.12.02 T.Aranami 新規作成：セレクターノード
#include "SelectorNode.h"

NodeState SelectorNode::Tick()
{
    for (auto child : children)
    {
        auto state = child->Tick();

        //一つでも成功していればSucces
        if (state == Success)
        {
            return Success;
        }
        //実行中の場合、Runningを返す
        if (state == Running)
        {
            return Running;
        }
    }
    return Failure;
}
