//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "game.h"		//ゲームヘッダー
#include "score.h"		//スコアヘッダー
#include "life.h"		//ライフヘッダー
#include "player.h"		//プレイヤーヘッダー
#include "enemy.h"		//エネミーヘッダー
#include "Background.h"	//背景ヘッダー
#include "bullet.h"		//バレットヘッダー
#include "explosion.h"	//エクスプロージョンヘッダー
#include "effect.h"		//エフェクトヘッダー
#include "bg_game.h"	//ゲーム背景
#include "laser.h"		//レーザー
#include "boss.h"		//ボス
#include "boss_anime.h"	//ボスアニメーション
#include "fade.h"		//フェード	
#include "manager.h"	//マネージャーヘッダー
#include "warning.h"	//ワーニングヘッダー
#include "homing.h"		//ホーミングヘッダー
#include "result.h"		//リザルト
#include "sound.h"		//サウンド
#include "mouse pointer.h"//マウスポインター
//----------------------------------
//静的メンバー変数
//----------------------------------
CLife *CGame::m_Life = NULL;
CScore *CGame::m_Score = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CGame::STAGE_TYPE CGame::m_StageType = STAGE_TYPE_1;
//---------------------------------
//コンストラクタ
//---------------------------------
CGame::CGame()
{
	m_pPlayer = NULL;
	m_Life = NULL;
	m_pBg = NULL;
	m_nCountEnemy = 100;
	m_EnemyCreate = ENEMY_CREATE_NONE;
}

//---------------------------------
//デストラクタ
//---------------------------------
CGame::~CGame()
{
	if (m_StageType== STAGE_TYPE_MAX)
	{
		m_StageType = STAGE_TYPE_1;
	}
}

//---------------------------------
//生成処理
//---------------------------------
CGame * CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

//---------------------------------
//初期化処理
//---------------------------------
HRESULT CGame::Init(void)
{
	//サウンドクラス取得
	CSound *pSound = CManager::GetSound();
	//テクスチャの読み込み
	CBg::Load();			//背景
	CEnemy::Load();			//エネミー
	CBullet::Load();		//バレット
	CPlayer::Load();		//プレイヤー
	CExplosion::Load();		//エクスプロージョン
	CLife::Load();			//ライフ
	CEffect::Load();		//エフェクト
	CBgGame::Load();		//背景ゲーム
	CLaser::Load();			//レーザー
	CBoss::Load();			//ボス
	CBossAnime::Load();		//ボスエフェクト
	CWarning::Load();		//ワーニング
	CHoming::Load();		//ホーミング
	//クリエイト処理
	CBgGame::Create();		//背景ゲーム
	m_pBg = CBg::Create();
	m_Life = CLife::Create(D3DXVECTOR3(100, 100, 0.0f));
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(780, 600, 0.0f));
	m_Score	= CScore::Create(D3DXVECTOR3(35,670,0),D3DXVECTOR3(20,45,0.0f),true);
	m_Score->SetScore(CManager::GetScore());
	CPointer::Create(CPointer::POINTER_TYPE_GAME);

	switch (m_StageType)
	{
	case STAGE_TYPE_1:
		pSound->Play(CSound::LABEL_BGM_STAGE_1);

		break;
	case STAGE_TYPE_2:
		pSound->Play(CSound::LABEL_BGM_STAGE_2);

		break;

	case STAGE_TYPE_3:
		pSound->Play(CSound::LABEL_BGM_STAGE_3);

		break;

	}
	return S_OK;
}

//---------------------------------
//終了処理
//---------------------------------
void CGame::Uninit(void)
{
	//テクスチャの破棄
	CBg::Unload();			//背景
	CEnemy::Unload();		//エネミー
	CBullet::Unload();		//バレット
	CPlayer::Unload();		//プレイヤー
	CExplosion::Unload();	//エクスプロージョン
	CLife::Unload();		//ライフ
	CEffect::Unload();		//エフェクト
	CBgGame::Unload();	
	CLaser::Unload();		//レーザー
	CBoss::Unload();		//ボス
	CBossAnime::Unload();	//ボスアニメーション
	CWarning::Unload();		//ワーニング
	CHoming::Unload();		//ホーミング
	if (m_Life != NULL)
	{
		m_Life->Uninit();
	}


	Release();
}

//---------------------------------
//更新処理
//---------------------------------
void CGame::Update(void)
{

	EnemeyCreate();
}

//---------------------------------
//描画処理
//---------------------------------
void CGame::Draw(void)
{
}

//---------------------------------
//ライフ取得
//---------------------------------
CLife * CGame::GetLife(void)
{
	return m_Life;
}

//---------------------------------
//スコア取得
//---------------------------------
CScore * CGame::GetScore(void)
{
	return m_Score;
}

void CGame::EnemeyCreate(void)
{
	if (CBoss::GetEnemyNumber() == false)
	{
		m_nCountEnemy--;
	}
	

	if (m_nCountEnemy <= 0)
	{

	int nModo =	m_EnemyCreate +1;

		m_EnemyCreate = (ENEMY_CREATE)nModo;
		StageMode();
	}


}

void CGame::StageMode(void)
{
	CSound *pSound = CManager::GetSound();

	switch (m_StageType)
	{
	case STAGE_TYPE_1:
		//780中心　幅400
		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);


			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_2:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -250, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -350, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_3:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_4:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);


			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);


			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_5:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_6:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70, CEnemy::BULLET_PATTERN_HOMING);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70, CEnemy::BULLET_PATTERN_HOMING);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70, CEnemy::BULLET_PATTERN_HOMING);

			m_nCountEnemy += 450;

			break;
		case ENEMY_CREATE_7:
			//サウンドストップ
			pSound->Stop(CSound::LABEL_BGM_STAGE_1);
			//ワーニング生成
			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
			m_nCountEnemy += 350;

			break;

		case ENEMY_CREATE_8:
			//サウンド再生
			pSound->Play(CSound::LABEL_BGM_BOSS_1);

			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));


			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_9:
			CManager::SetScore(m_Score->GetScore());

			CResult::Create();
			int nStage = m_StageType + 1;
			m_StageType = (STAGE_TYPE)nStage;

			break;


		}

		break;
	case STAGE_TYPE_2:
		//780中心　幅400
		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH ,		-100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STOP, 75);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
			m_nCountEnemy += 350;
			break;
		case ENEMY_CREATE_2:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70,CEnemy::BULLET_PATTERN_HOMING);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70,CEnemy::BULLET_PATTERN_HOMING);
			
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_3:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);
			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_4:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_5:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80, CEnemy::BULLET_PATTERN_SHOTS);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH+100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80, CEnemy::BULLET_PATTERN_SHOTS);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH-100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80, CEnemy::BULLET_PATTERN_SHOTS);

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_6:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_7:
			//サウンドストップ
			pSound->Stop(CSound::LABEL_BGM_STAGE_2);

			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
			m_nCountEnemy += 350;

			break;

		case ENEMY_CREATE_8:
			//サウンド再生
			pSound->Play(CSound::LABEL_BGM_BOSS_2);

			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));


			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_9:
			CManager::SetScore(m_Score->GetScore());

			CResult::Create();
			int nStage = m_StageType + 1;
			m_StageType = (STAGE_TYPE)nStage;
			break;


		}


		break;
	case STAGE_TYPE_3:

		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:
			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));

			m_nCountEnemy += 350;
			break;
		case ENEMY_CREATE_2:
			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_3:
			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_4:
			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_5:
			//サウンドストップ
			pSound->Stop(CSound::LABEL_BGM_STAGE_3);

			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_6:
			//サウンド再生
			pSound->Play(CSound::LABEL_BGM_BOSS_3);

			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_3, D3DXVECTOR3(500, 500, 0));

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_7:


			CManager::SetScore(m_Score->GetScore());

			CResult::Create();
			int nStage = m_StageType + 1;
			m_StageType = (STAGE_TYPE)nStage;


			m_nCountEnemy += 450;
			break;

		}
		break;


	}
}
