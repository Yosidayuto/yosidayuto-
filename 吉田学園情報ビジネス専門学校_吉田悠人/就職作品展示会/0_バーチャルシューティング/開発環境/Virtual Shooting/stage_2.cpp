//=============================================================================
//
// ステージ2処理 [stage_2.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage_2.h"
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
CStage2::CStage2()
{
	m_EnemyCreate = ENEMY_CREATE_NONE;
}

//=============================================================================
// デストラクト
//=============================================================================
CStage2::~CStage2()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CStage2 * CStage2::Create(void)
{
	//メモリの確保
	CStage2* pStage2;
	pStage2 = new CStage2;
	//初期化処理
	pStage2->Init();
	return pStage2;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage2::Init(void)
{
	//サウンドクラス取得
	CSound *pSound = CManager::GetSound();
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_STAGE_2);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage2::Uninit(void)
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
void CStage2::Update(void)
{
	CStage::Update();
}

//=============================================================================
// エネミーのスポーンモード
//=============================================================================
void CStage2::StageMode(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();
	//ステージ進行
	m_EnemyCreate = (STAGE_2_ENEMY)(m_EnemyCreate + 1);

	//780中心　幅400
	switch (m_EnemyCreate)
	{
	case ENEMY_CREATE_1:
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS ,		-100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STOP, 75);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
		SetEnemyCount(350);
		break;
	case ENEMY_CREATE_2:
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
		
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_3:
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);
		SetEnemyCount(300);
		break;
	case ENEMY_CREATE_4:
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_5:
		CEnemy::Create(D3DXVECTOR3(STAGE_POS, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS +100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS -100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
	
		SetEnemyCount(300);
		break;
	case ENEMY_CREATE_6:
		CEnemy::Create(D3DXVECTOR3(STAGE_POS, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS + 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		CEnemy::Create(D3DXVECTOR3(STAGE_POS - 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_7:
		//サウンドストップ
		pSound->Stop(CSound::LABEL_BGM_STAGE_2);
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
		SetEnemyCount(350);
		break;
	case ENEMY_CREATE_8:
		//サウンド再生
		pSound->Play(CSound::LABEL_BGM_BOSS_2);
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_9:
		//リザルト表示
		Result(STAGE_TYPE_2);
		break;
	}
}
