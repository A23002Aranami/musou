//24.12.02 T.Aranami �V�K�쐬�F�V�[�P���X�m�[�h�N���X
#pragma once
#include "CompositeNode.h"

class SequenceNode : public CompositeNode
{
public:

	NodeState Tick()override;
};