#include "Stage.h"
#include "CsvReader.h"
#include "Object3D.h"


Stage::Stage()
{
	CsvReader* csv = new CsvReader("data/stage1.csv");//CSVファイル読み込み

	try
	{
		//ファイルから読み込んだ行数が0以下だった場合はエラー
		if (csv->GetLines() <= 0)
		{
			throw "CSVが読み込めていません";
		}
		else
		{
			for (int i = 0; i < csv->GetLines(); i++)
			{
				std::string str = csv->GetString(i,0);//i行目の最初の文字列を取得
				if (str.substr(0, 2) == "//")//戦闘文字列がコメントアウトだった場合はその行は処理しない
				{}
				else
				{
					Object3D* obj = nullptr;//ステージに設置するオブジェクトはすべて3Dオブジェクトなので共通処理用のポインタ
					
					if (csv->GetString(i, 0) == "StaticObject")//動かないステージオブジェクトの時
					{
						StaticObject* stObj = new StaticObject();
						stObj->SetMesh(csv->GetString(i, 7).c_str());//文字列からファイルを指定してメッシュをロード
						obj = stObj;//
					}
					if (csv->GetString(i, 0) == "Player")
					{
						Player* player = new Player();
						player->SetMesh(csv->GetString(i, 7).c_str());//文字列からファイルを指定してメッシュをロード
						obj = player;
					}

					//オブジェクトの座標受け取り
					float x = csv->GetFloat(i, 1);
					float y = csv->GetFloat(i, 2);
					float z = csv->GetFloat(i, 3);
					obj->SetPosition(x, y, z);

					//オブジェクトの回転受け取り
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

	
}
