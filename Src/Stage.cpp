#include "Stage.h"
#include "CsvReader.h"
#include "Object3D.h"


Stage::Stage()
{
	CsvReader* csv = new CsvReader("data/stage1.csv");//CSV�t�@�C���ǂݍ���

	try
	{
		//�t�@�C������ǂݍ��񂾍s����0�ȉ��������ꍇ�̓G���[
		if (csv->GetLines() <= 0)
		{
			throw "CSV���ǂݍ��߂Ă��܂���";
		}
		else
		{
			for (int i = 0; i < csv->GetLines(); i++)
			{
				std::string str = csv->GetString(i,0);//i�s�ڂ̍ŏ��̕�������擾
				if (str.substr(0, 2) == "//")//�퓬�����񂪃R�����g�A�E�g�������ꍇ�͂��̍s�͏������Ȃ�
				{}
				else
				{
					Object3D* obj = nullptr;//�X�e�[�W�ɐݒu����I�u�W�F�N�g�͂��ׂ�3D�I�u�W�F�N�g�Ȃ̂ŋ��ʏ����p�̃|�C���^
					
					if (csv->GetString(i, 0) == "StaticObject")//�����Ȃ��X�e�[�W�I�u�W�F�N�g�̎�
					{
						StaticObject* stObj = new StaticObject();
						stObj->SetMesh(csv->GetString(i, 7).c_str());//�����񂩂�t�@�C�����w�肵�ă��b�V�������[�h
						obj = stObj;//
					}
					if (csv->GetString(i, 0) == "Player")
					{
						Player* player = new Player();
						player->SetMesh(csv->GetString(i, 7).c_str());//�����񂩂�t�@�C�����w�肵�ă��b�V�������[�h
						obj = player;
					}

					//�I�u�W�F�N�g�̍��W�󂯎��
					float x = csv->GetFloat(i, 1);
					float y = csv->GetFloat(i, 2);
					float z = csv->GetFloat(i, 3);
					obj->SetPosition(x, y, z);

					//�I�u�W�F�N�g�̉�]�󂯎��
					x = csv->GetFloat(i, 4);
					y = csv->GetFloat(i, 5);
					z = csv->GetFloat(i, 6);
					obj->SetRotation(x, y, z);


				}
			}
		}
	}
	catch (std::string str)
	{
		GameDevice()->m_pFont->Draw(0,0, str.c_str(), 64, RGB(0, 0, 0));
	}

	new EnemyVillage(VECTOR3(0,0,0),VECTOR3(10,0,10),10);

	new EnemyVillage(VECTOR3(20, 0, 20), VECTOR3(15,0,15), 15);

	new EnemyVillage(VECTOR3(-20, 0, -20), VECTOR3(30, 0, 30), 250);

	float mapSize = 200;
	float mapCenter = mapSize / 2;
	//���ڂ̕����T�C�Y(m)
	float divide = 5;

	
	for (int i = 0; i <= mapSize; i+=divide)
	{
		start.push_back(VECTOR3(0 - mapCenter, 0.1f, i - mapCenter));
		end.push_back(VECTOR3(0 + mapCenter, 0.1f, i - mapCenter));

		start.push_back(VECTOR3(i - mapCenter, 0.1f, 0 - mapCenter));
		end.push_back(VECTOR3(i - mapCenter, 0.1f, 0 + mapCenter));
	}

	
}

void Stage::Draw()
{
	CSprite spr;
	for (int i = 0; i < start.size();i++)
	{
		spr.DrawLine3D(start[i], end[i],RGB(255,0,255));
	}
}

void Stage::SetBoss1(EnemyBoss1* boss)
{
	boss1.push_back(boss);
}

std::list<EnemyBoss1*>* Stage::GetBoss1()
{
	return &boss1;
}
