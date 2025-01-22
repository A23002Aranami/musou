#include "SequenceNode.h"

NodeState SequenceNode::Tick()
{
    //���ׂĂ̎q�m�[�h�����s
    for (auto child : children)
    {
        
        //�q�m�[�h�����s���A���s���ʂ𓾂�
        NodeState state = child->Tick();
        
        //��ł����s������AFailure��Ԃ�
        if (state == Failure)
        {
            return (Failure);
        }

        //���s���̏ꍇ�ARunnning��Ԃ�
        if (state == Running)
        {
            return(Running);
        }
        

    }
    return Success;
}
