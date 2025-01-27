#include "CameraPlayScene.h"

void CameraPlayScene::Update()
{
	Object3D* pl = ObjectManager::FindGameObject<Player>();


	if (pl)//プレイヤーが存在する場合
	{
		VECTOR3 offsetPos;

		offsetPos = pl->Position() + VECTOR3(0, 15, -15);

		VECTOR3 toOffsetPos = offsetPos	 - this->Position();//オフセットポジションへ移動するベクトル
		VECTOR3 toPlayerPos = pl->Position() - this->Position();

		float length;//距離用変数
		length = (toOffsetPos).Length();

		
		//カメラが指定のいちから一定以上
		if (length >= 0.2)
		{
			transform.position += toOffsetPos * camSpeed;
		}
		else
		{
			//this->SetPosition(offsetPos);
		}
		
		length = toPlayerPos.Length();

		if (length >= 0.2)
		{

			transform.rotation += toPlayerPos * lookSpeed;
		}
		

		//注視点をプレイヤーの位置に
		//transform.rotation = pl->Position();
	}

	GameDevice()->m_vEyePt = transform.position;
	GameDevice()->m_vLookatPt = transform.rotation;
	GameDevice()->m_mView = XMMatrixLookAtLH
	(
		transform.position,
		transform.rotation,
		VECTOR3(0, 1, 0)
	);
}


CameraPlayScene::CameraPlayScene():camSpeed(0.015),lookSpeed(0.01)
{
	//カメラのポジション
	transform.position = VECTOR3(0, 15, -15);
	//カメラの注視点
	transform.rotation = VECTOR3(0, 0, 0);


	GameDevice()->m_mView = XMMatrixLookAtLH
	(
		transform.position,
		transform.rotation,
		VECTOR3(0, 1, 0)
	);
}
