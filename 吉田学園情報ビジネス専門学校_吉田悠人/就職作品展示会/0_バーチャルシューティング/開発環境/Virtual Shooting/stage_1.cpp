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
#include "enemy.h"
#include "boss.h"
#include "warning.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "boss type1.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
//=============================================================================
// コンストラクト
//=============================================================================
CStage1::CStage1()
{
	m_EnemyCreate = ENEMY_CREATE_NONE;
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
	CStage1* pStage1;
	pStage1 = new CStage1;
	//初期化処理
	pStage1->Init();
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
// エネミーのスポーンモード
//=============================================================================
void CStage1::StageMode(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();
	//ステージ進行
	m_EnemyCreate = (STAGE_1_ENEMY)(m_EnemyCreate + 1);

		//780中心　幅400
		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:
			//CBossType1::Create(D3DXVECTOR3(STAGE_POS,100.0f,0.0f));
			//CEnemyType2::Create(D3DXVECTOR3(STAGE_POS - 100, 50, 0.0f), BULLET_PATTERN_SHOTS);
			//CEnemyType2::Create(D3DXVECTOR3(STAGE_POS - 100, 50, 0.0f), BULLET_PATTERN_NONE);
			//CEnemyType3::Create(D3DXVECTOR3(STAGE_POS + 100, 50, 0.0f), BULLET_PATTERN_NONE);
			//CEnemyType4::Create(D3DXVECTOR3(STAGE_POS + 100, 150, 0.0f), BULLET_PATTERN_NONE);
			
			CEnemy::Create(D3DXVECTOR3(STAGE_POS, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STOP, 50);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS , -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STOP, 50);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS , 0, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STOP, 55);


			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);


			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);

			SetEnemyCount(300) ;
			break;
		case ENEMY_CREATE_2:
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 150, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -250, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -350, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			SetEnemyCount(300);
			break;
		case ENEMY_CREATE_3:
			CEnemy::Create(D3DXVECTOR3(STAGE_POS, -50, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
			SetEnemyCount(300);
			break;
		case ENEMY_CREATE_4:
			CEnemy::Create(D3DXVECTOR3(STAGE_POS, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);


			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 50, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 200, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 250, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 300, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 350, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 400, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);


			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 50, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 150, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 200, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 250, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 300, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 350, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 400, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			SetEnemyCount(450);
			break;
		case ENEMY_CREATE_5:
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
			SetEnemyCount(300);
			break;
		case ENEMY_CREATE_6:
			CEnemy::Create(D3DXVECTOR3(STAGE_POS, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN);
			CEnemy::Create(D3DXVECTOR3(STAGE_POS - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN);

			SetEnemyCount(450);

			break;
		case ENEMY_CREATE_7:
			//サウンドストップ
			pSound->Stop(CSound::LABEL_BGM_STAGE_1);
			//ワーニング生成
			CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
			SetEnemyCount(350);

			break;

		case ENEMY_CREATE_8:
			//サウンド再生
			pSound->Play(CSound::LABEL_BGM_BOSS_1);
			//ボス生成
			CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));


			SetEnemyCount(450);
			break;
		case ENEMY_CREATE_9:
			//リザルト表示
			Result(STAGE_TYPE_1);
			break;


	}
}
