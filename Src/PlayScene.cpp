#include "PlayScene.h"
#include "StageData.h"
#include "Stage.h"
#include "CameraPlayScene.h"
#include <memory>


PlayScene::PlayScene()
{
	x = 0;
	loading = true;

	back = new CSpriteImage("data/images/ui/Back.png");

	LoadingThread = std::thread
	(
		[&]()
		{
			/*
			new StageData();
			new CameraPlayScene();
			new Stage();
			*/
			loading = false;
		}
	);

	//new StageData();
	new CameraPlayScene();
	new Stage();
	
	
}

PlayScene::~PlayScene()
{
	delete back;
}

void PlayScene::Update()
{
	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_T)) {
		SceneManager::ChangeScene("TitleScene");
	}

	if (!loading && LoadingThread.joinable())//�X���b�h�������\�������猋��
	{
		LoadingThread.join();
	}
}

void PlayScene::Draw()
{
	/*
	x = (float)((int)(x++)%100) ;
	//���[�h���I���܂ŉ�ʂ��o���Ă���
	if (loading) {
		CSprite spr;
		spr.Draw(back, x, 0, 0, 0, back->m_dwImageWidth, back->m_dwImageHeight);
	}
	*/

}