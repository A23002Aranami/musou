//24.12.02 T.Aranami �V�K�쐬�F�Z���N�^�[�m�[�h
#include "SelectorNode.h"

NodeState SelectorNode::Tick()
{
    for (auto child : children)
    {
        auto state = child->Tick();

        //��ł��������Ă����Succes
        if (state == Success)
        {
            return Success;
        }
        //���s���̏ꍇ�ARunning��Ԃ�
        if (state == Running)
        {
            return Running;
        }
    }
    return Failure;
}
