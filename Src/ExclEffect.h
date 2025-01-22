#pragma once

#include "Object3D.h"

class ExclEffect : public Object3D
{
	public:
		ExclEffect(Object3D* vobj);
		virtual ~ExclEffect();

		void Update()override;
		void Draw()override;

	private:
		static CSpriteImage* exclImg;
		static int num;//�S�̂ŃG�t�F�N�g���o�Ă����

		Object3D* obj;

		float timer;
		float destroyTime;
};