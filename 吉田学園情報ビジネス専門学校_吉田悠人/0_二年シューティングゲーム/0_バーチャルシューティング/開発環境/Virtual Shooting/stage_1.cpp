//=============================================================================
//
// ステージ1処理 [stage_1.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage_1.h"
#include "manager.h"
#include "sound.h"
#include "warning.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "boss base.h"
#include "boss type1.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PHASE_COUNT (200)	//フェーズが位置段階変わるまでのカウント数

//=============================================================================
// コンストラクト
//=============================================================================
CStage1::CStage1()
{
	m_EnemyCreate = ENEMY_CREATE_NULL;
	memset(&m_StageData, NULL, sizeof(m_StageData));
	m_nBossPhase = 0;
}

//=============================================================================
// デストラクト
//=============================================================================
CStage1::~CStage1()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CStage1 * CStage1::Create(void)
{
	//メモリの確保
	CStage1* pStage1 = NULL;
	pStage1 = new CStage1;

	//NULLチェック
	if (pStage1 != NULL)
	{
		//初期化処理
		pStage1->Init();
	}
	return pStage1;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage1::Init(void)
{
	//サウンドクラス取得
	CSound *pSound = CManager::GetSound();
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_STAGE_1);

	//ステージのエネミー出現データ取得
	m_StageData = GetStageEnemy(STAGE_TYPE_1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage1::Uninit(void)
{
	//サウンド取得
	CSound*	pSound = CManager::GetSound();
	//シーン破棄
	CScene::ReleaseAll();
	//サウンド停止
	pSound->Stop();

}

//=============================================================================
// 更新処理
//=============================================================================
void CStage1::Update(void)
{
	CStage::Update();
}

//=============================================================================
// ステージの進行処理
//=============================================================================
void CStage1::StageMode(void)
{
	//ステージ進行
	if (m_EnemyCreate < m_StageData.nCountPhase)
	{
		m_EnemyCreate = (STAGE_ENEMY)(m_EnemyCreate + 1);
	}


	//エネミー生成用のフェーズが終わっているか
	if (m_StageData.Phase[m_EnemyCreate].nEnemyCount>m_EnemyCreate)
	{
		EnemyCreate();
	}
	//ボス生成処理
	else
	{
		switch (m_nBossPhase)
		{
			//ボス出現処理
		case 0:
			WarningCreate();
			break;

			//ボス出現
		case 1:
			BossCreate();
			break;
			
			//リザルト
		case 2:
			//リザルト表示			
			Result(STAGE_TYPE_1);
			break;
		}

		//進める
		m_nBossPhase++;
	}
	SetEnemyCount(PHASE_COUNT);

}

//=============================================================================
// エネミーの生成処理
//=============================================================================
void CStage1::EnemyCreate(void)
{
	//エネミーのポインタ
	CEnemyBase* pEnemy = NULL;

	//エネミーの数分
	for (int nEnemy = 0; nEnemy<m_StageData.Phase[m_EnemyCreate].nEnemyCount + 1; nEnemy++)
	{
		//エネミーの行動数分
		for (int nMoveCount = 0; nMoveCount<m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nEnemyMoveNumber; nMoveCount++)
		{
			//位置取得
			D3DXVECTOR3 pos = m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].MoveData[nMoveCount].pos;
			//位置修正
			pos.x += STAGE_POS - (STAGE_SIZE / 2);
			//エネミーのクリエイト
			if (nMoveCount == 0)
			{
				//位置修正
				pos.y -= 200;

				switch (m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyType)
				{
				case ENEMY_TYPE_1:
					pEnemy = CEnemyType1::Create(pos);
					break;
				case ENEMY_TYPE_2:
					pEnemy = CEnemyType2::Create(pos);
					break;
				case ENEMY_TYPE_3:
					pEnemy = CEnemyType3::Create(pos);
					break;
				case ENEMY_TYPE_4:
					pEnemy = CEnemyType4::Create(pos);
					break;
				}
			}
			//エネミーの行動位置設定
			else
			{
				//スピード取得
				float fSpeed = m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].MoveData[nMoveCount].fSpeed;
				//最後の行動の場合
				if (nMoveCount + 1 == m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nEnemyMoveNumber)
				{
					//位置修正
					pos.y += 200;
				}
				//移動するポイント設定
				pEnemy->SetMovePointer(pos, nMoveCount, fSpeed);
			}
		}
	}

}

//=============================================================================
// ボスの生成処理
//=============================================================================
void CStage1::BossCreate(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();

	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_BOSS_1);
	//ボス生成
	CBossType1::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
}
