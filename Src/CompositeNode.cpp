#include "CompositeNode.h"

void CompositeNode::AddChild(BehaviorNodeBase* child)
{
	//�q�m�[�h���X�g�ɒǉ�����
	children.push_back(child);
}
