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
#include "scene.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "warning.h"
#include "score.h"
#include<thread>
//=============================================================================
// 静的メンバー変数
//=============================================================================
char* CStage::pFileName[STAGE_TYPE_MAX] = {
"data/TEXT/stage1", 
"data/TEXT/stage2",
""};
STAGE_DATA CStage::m_Stage[STAGE_TYPE_MAX] = {};
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
	//ステージセット
	CGame::SetStageType((STAGE_TYPE)(stage + 1));
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
// スコアポインタセッター
//=============================================================================
void CStage::SetScore(CScore * pScore)
{
	m_pScore = pScore;
}

//=============================================================================
// エネミー出現までのカウント
//=============================================================================
void CStage::EnemeyCreate(void)
{
	//ボスが出現しているか
	if (!BossSearch())
	{
		m_nCountEnemy--;
	}

	//カウントが0になったら
	if (m_nCountEnemy <= 0)
	{
		//ステージを進める
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
	// 読み込んだ移動回数
	int		nMoveNumber;
	// 総合移動回数
	int		nTotalMove;

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
		memset(cFileString, 0, sizeof(cFileString));

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
							//初期化
							nTotalMove = 0;

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
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType= ENEMY_TYPE_1;
										break;		   
									case 1:			   
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_2;
										break;		   
									case 2:			   
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_3;
										break;
									case 3:
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_4;
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
											nTotalMove++;
										}
										if (strcmp(cFileString, "ENEMY_SPEED") == 0)
										{
											fscanf_s(pFile[nStage], " = %f", &m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].MoveData[nMoveNumber].fSpeed);
										}
										if (strcmp(cFileString, "ENEMY_POS") == 0)
										{
											fscanf_s(pFile[nStage], " = %f %f",
												&m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].MoveData[nMoveNumber].pos.x,
												&m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].MoveData[nMoveNumber].pos.y);
										}
									}
									//行動回数取得
									m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].nEnemyMoveNumber = nTotalMove;
								}

							}
							//エネミー数カウント
							nEnemyCount++;
						}
					}
					//エネミー総数
					m_Stage[nStage].Phase[nPhase].nEnemyCount = nEnemyCount;
					//フェーズを進める
					nPhase++;
				}
			}
			m_Stage[nStage].nCountPhase = nPhase;
			fclose(pFile[nStage]);	//ファイルを閉じる

		}

	}
}

//=============================================================================
// ステージ情報ゲッター
//=============================================================================
STAGE_DATA CStage::GetStageEnemy(STAGE_TYPE stage)
{
	return m_Stage[stage];
}

//=============================================================================
// ボスがいるか
//=============================================================================
bool CStage::BossSearch(void)
{
	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//ボス索敵処理
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//ボスがいた場合
				if (pNext->GetObjType() == CScene::OBJ_TYPE_BOSS)
				{

					return true;
				}
				
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
	//ボスがいない場合
	return false;
}


//=============================================================================
// ボス演出生成
//=============================================================================
void CStage::WarningCreate(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();

	//サウンドストップ
	pSound->Stop();
	//ワーニング生成
	CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));

}

