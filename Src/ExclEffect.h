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
		static int num;//全体でエフェクトが出ている個数

		Object3D* obj;

		float timer;
		float destroyTime;
};