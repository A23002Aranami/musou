//24.12.02 T.Aranami �V�K�쐬�F����m�[�h���N���X
#pragma once
#include"BehaviorNodeBase.h"


class CompositeNode :public BehaviorNodeBase
{
public:
	//�q�m�[�h��ǉ�����
	void AddChild(BehaviorNodeBase* child);
protected:
	//���䂷��q�m�[�h
	std::vector<BehaviorNodeBase*> children;
};
