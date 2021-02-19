//=============================================================================
//
// ステージ3処理 [stage_3.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage_3.h"
#include "manager.h"
#include "sound.h"
#include "enemy.h"
#include "boss.h"
#include "warning.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
//=============================================================================
// コンストラクト
//=============================================================================
CStage3::CStage3()
{
	m_EnemyCreate = ENEMY_CREATE_NONE;
}

//=============================================================================
// デストラクト
//=============================================================================
CStage3::~CStage3()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CStage3 * CStage3::Create(void)
{
	//メモリの確保
	CStage3* pStage3;
	pStage3 = new CStage3;
	//初期化処理
	pStage3->Init();
	return pStage3;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage3::Init(void)
{
	//サウンドクラス取得
	CSound *pSound = CManager::GetSound();
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_STAGE_1);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage3::Uninit(void)
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
void CStage3::Update(void)
{
	CStage::Update();
}

//=============================================================================
// エネミーのスポーンモード
//=============================================================================
void CStage3::StageMode(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();
	//ステージ進行
	m_EnemyCreate = (STAGE_3_ENEMY)(m_EnemyCreate + 1);

	//780中心　幅400
	switch (m_EnemyCreate)
	{
	case ENEMY_CREATE_1:
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
	
		SetEnemyCount(350);
		break;
	case ENEMY_CREATE_2:
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_3:
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
	
		SetEnemyCount(300);
		break;
	case ENEMY_CREATE_4:
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_5:
		//サウンドストップ
		pSound->Stop(CSound::LABEL_BGM_STAGE_3);
	
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
	
		SetEnemyCount(300);
		break;
	case ENEMY_CREATE_6:
		//サウンド再生
		pSound->Play(CSound::LABEL_BGM_BOSS_3);
	
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_3, D3DXVECTOR3(500, 500, 0));
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_7:
		//リザルト表示
		Result(STAGE_TYPE_3);
		break;
	}
}
