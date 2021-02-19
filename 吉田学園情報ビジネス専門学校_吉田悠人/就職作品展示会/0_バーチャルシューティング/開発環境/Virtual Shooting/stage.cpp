//=============================================================================
//
// ステージ処理 [stage.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage.h"
#include "manager.h"
#include "renderer.h"
#include "boss.h"
#include "game.h"
#include "result.h"
#include "score.h"
#include<thread>
//=============================================================================
// 静的メンバー変数
//=============================================================================
char* CStage::pFileName[STAGE_TYPE_MAX] = {
"data/TEXT/Data", 
"",
""};
PHASE_DATA CStage::m_Enemy[ENEMY_CREATE_MAX][MAX_STAGE] = {};
//=============================================================================
// コンストラクト
//=============================================================================
CStage::CStage()
{
	m_nCountEnemy = 0;
}

//=============================================================================
// デストラクト
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CStage::Update(void)
{
	//カウント
	EnemeyCreate();
}

//=============================================================================
// リザルト
//=============================================================================
void CStage::Result(STAGE_TYPE stage)
{
	//スコアセット
	CManager::SetScore(CGame::GetScore()->GetScore());
	//リザルト表示
	CResult::Create(stage);

}

//=============================================================================
// エネミー出現までのカウント
//=============================================================================
void CStage::SetEnemyCount(int nConut)
{
	m_nCountEnemy = nConut;
}

//=============================================================================
// エネミー出現までのカウント
//=============================================================================
void CStage::EnemeyCreate(void)
{
	if (CBoss::GetEnemyNumber() == false)
	{
		m_nCountEnemy--;
	}

	if (m_nCountEnemy <= 0)
	{
		StageMode();
	}

}

//=============================================================================
// ロードファイル
//=============================================================================
void CStage::LoadFile(void)
{
	//ファイルポインタ
	FILE*	pFile[STAGE_TYPE_MAX];
	// エネミー数
	int		nEnemyCount;
	// フェーズ数
	int		nPhase;
	// 移動回数
	int		nMoveNumber;

	//読み込み用のデータ
	char cFileString[256];
	//初期化
	memset(&cFileString, 0, sizeof(cFileString));

	//テキストファイル読み込み
	for (int nStage = 0; nStage < STAGE_TYPE_MAX; nStage++)
	{
		//初期化
		nPhase		= 0;
		nEnemyCount = 0;
		//テキスト読み込み
		fopen_s(&pFile[nStage], pFileName[nStage], "r");
		if (pFile[nStage] != NULL)
		{
			//そのデータがを終わるまで読み込み
			while (strcmp(cFileString, "STAGE_END") != 0)
			{
				//初期化
				memset(cFileString, 0, sizeof(cFileString));
				//読み込み
				fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));

				//文字の比較
				if (strcmp(cFileString, "PHASE_START") == 0)
				{
					while (strcmp(cFileString, "PHASE_END") != 0)
					{
						//初期化
						memset(cFileString, 0, sizeof(cFileString));
						//読み込み
						fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));
						
						//エネミーデータ
						if (strcmp(cFileString, "ENEMY_DATA") == 0)
						{
							while (strcmp(cFileString, "ENEMY_END") != 0)
							{
								//初期化
								memset(cFileString, 0, sizeof(cFileString));
								//読み込み
								fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));

								//エネミータイプ取得
								if (strcmp(cFileString, "ENEMY_TYPE") == 0)
								{
									int nType;
									fscanf_s(pFile[nStage], " = %d", &nType);

									//読み込んだ数値でタイプ分け
									switch (nType)
									{
									case 0:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType= ENEMY_TYPE_1;
										break;
									case 1:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_2;
										break;
									case 2:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_3;
										break;
									case 3:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_4;
										break;

									}									
								}
								//エネミーの移動情報取得
								if (strcmp(cFileString, "STATUS_DATA") == 0)
								{
									//エネミーの移動情報を読み終わるまで
									while (strcmp(cFileString, "STATUS_EMD") != 0)
									{
										//初期化
										memset(cFileString, 0, sizeof(cFileString));
										//読み込み
										fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));

										//何回目かの移動か取得
										if (strcmp(cFileString, "ENEMY_MOVE_NUMBER") == 0)
										{
											fscanf_s(pFile[nStage], " = %d", &nMoveNumber);
										}
										if (strcmp(cFileString, "ENEMY_SPEED") == 0)
										{
											fscanf_s(pFile[nStage], " = %f", &m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].moveData[nMoveNumber].fSpeed);
										}
										if (strcmp(cFileString, "ENEMY_POS") == 0)
										{
											fscanf_s(pFile[nStage], " = %f %f",
												&m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].moveData[nMoveNumber].pos.x,
												&m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].moveData[nMoveNumber].pos.y);
										}
									}
								}

							}
							//エネミー数カウント
							nEnemyCount++;
						}
					}
					//フェーズを進める
					nPhase++;
				}
			}
			fclose(pFile[nStage]);	//ファイルを閉じる

		}

	}
}

