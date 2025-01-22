#include "SequenceNode.h"

NodeState SequenceNode::Tick()
{
    //すべての子ノードを実行
    for (auto child : children)
    {
        
        //子ノードを実行し、実行結果を得る
        NodeState state = child->Tick();
        
        //一つでも失敗したら、Failureを返す
        if (state == Failure)
        {
            return (Failure);
        }

        //実行中の場合、Runnningを返す
        if (state == Running)
        {
            return(Running);
        }
        

    }
    return Success;
}
