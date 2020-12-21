//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "manager.h"		//マネージャーファイル
#include "renderer.h"		//レンダリングファイル	
#include "scene2d.h"		//シーン２D（2Dポリゴン）ファイル
#include "scene.h"			//シーン（ポリゴンの親）ファイル
#include "input.h"			//入力処理ファイル
#include "inihkeyboard.h"	//キーボード入力処理ファイル
#include "inputmouse.h"		//マウス入力処理ファイル
#include "sound.h"			//音楽ファイル
#include "title.h"			//タイトルファイル
#include "score.h"			//スコアファイル
#include "number.h"			//ナンバーファイル
#include "fade.h"			//フェードアウトファイル
#include "ui.h"				//UIファイル
#include "game.h"			//ゲームヘッダー
#include "select.h"			//セレクトヘッダー
#include "text.h"			//テキストヘッダー
#include "window.h"			//ウィンドウヘッダー
#include "player.h"			//プレイヤーヘッダー
#include "button.h"			//ボタンヘッダー
#include "clear.h"			//ゲームクリアヘッダー
#include "telop_bar.h"		//テロップバーヘッダー
#include "mouse pointer.h"	//マウスポインター
#include "telop_text.h"		//テロップテキストヘッダー
#include "tutorial.h"		//チュートリアルヘッダー
//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
CRenderer *CManager::m_pRenderer = NULL;
CInihKeyboard *CManager::m_pInput = NULL;
CInihMouse *CManager::m_pInihMouse = NULL;
CSound *CManager::m_pSound = NULL;
CManager::GAME_MODE CManager::m_Mode= GAME_MODE_TITLE;
CScene *CManager::m_pScene = NULL;
CTitle *CManager::m_pTitle = NULL;
CFade *CManager::m_pFade = NULL;
CGame *CManager::m_pGame = NULL;
CSelect *CManager::m_pSelect = NULL;
int CManager::m_nScore = 10000;
CManager::PLAYER_DATA CManager::m_Player = { 0,0,{ CPlayer::WEAPONS_MODE_BUTTOL , CPlayer::WEAPONS_MODE_NONE } };
CTutorial *CManager::m_pTutorial = NULL;

//---------------------------------
//コンストラクタ
//---------------------------------
CManager::CManager()
{

}

//---------------------------------
//デストラクタ
//---------------------------------
CManager::~CManager()
{
}

//---------------------------------
//初期化処理
//---------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//インプット(キーボード)生成
	m_pInput = new CInihKeyboard;
	m_pInput->Init(hInstance, hWnd);
	
	//インプット(マウス)生成
	m_pInihMouse = new CInihMouse;
	m_pInihMouse->Init(hInstance, hWnd);
	
	//レンダリング生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//フェイドアウト生成
	m_pFade = new CFade;
	m_pFade->Init();

	//サウンド生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//テクスチャの読み込み
	CClear::Load();			//クリア
	CTitle::Load();			//タイトル
	CNumber::Load();		//ナンバー
	CUi::Load();			//UI
	CText::Load();			//テキスト
	CWindow::Load();		//ウィンドウ
	CButton::Load();		//ボタン
	CTelopBer::Load();		//テロップバー
	CTelopText::Load();		//テロップテキスト
	CPointer::Load();		//マウスポインター
	CTutorial::Load();		//チュートリアル
	//オブジェクトクラス生成
	SetMode(m_Mode);
	return S_OK;
}

//---------------------------------
//終了処理
//---------------------------------
void CManager::Uninit(void)
{
	//キーボード破棄
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;

	}
	//マウス破棄
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Uninit();
		delete m_pInihMouse;
		m_pInihMouse = NULL;

	}
	//サウンド破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//フェードアウト破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
	
	//テクスチャの破棄
	CClear::Unload();			//クリア
	CButton::Unload();			//ボタン
	CTitle::Unload();			//タイトル
	CNumber::Unload();			//ナンバー
	CUi::Unload();				//UI
	CText::Unload();			//テキスト
	CWindow::Unload();			//ウィンドウ
	CTelopBer::Unload();		//テロップバー
	CTelopText::Unload();		//テロップテキスト
	CPointer::Unload();			//マウスポインター
	CTutorial::Unload();			//チュートリアル

	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)	//メモリが確保されているか
	{
		//レンダリング 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//---------------------------------
//更新処理
//---------------------------------
void CManager::Update()
{
	m_pInihMouse->Update();		//マウス更新
	m_pInput->Update();			//キーボード更新 (最初に行う)
	m_pRenderer->Update();		//レンダリング更新処理
	m_pFade->Update();			//フェードアウト更新処理

	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		break;
	case GAME_MODE_SELECT:
		m_pSelect->Update();
		break;
	case GAME_MODE_STAGE:
		m_pGame->Update();
		break;
	}

}

//---------------------------------
//描画処理
//---------------------------------
void CManager::Draw(void)
{
	m_pRenderer->Draw();				// レンダリング描画処理
}

//---------------------------------
//ゲームモードセット処理
//---------------------------------
void CManager::SetMode(GAME_MODE mode)
{
	m_Mode = mode;
	//初期化処理
	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		//シーン破棄
		CScene::ReleaseAll();
		//サウンド停止
		m_pSound->Stop();

		//タイトル生成
		m_pTitle = CTitle::Create();
		//サウンド再生
		m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;
	case GAME_MODE_TUTORIAL:
		//シーン破棄
		CScene::ReleaseAll();
		//チュートリアル制作
		m_pTutorial= CTutorial::Create();

		break;
	case GAME_MODE_SELECT:
		//シーン破棄
		CScene::ReleaseAll();
		//サウンド停止
		m_pSound->Stop();

		//セレクト生成処理
		m_pSelect = CSelect::Create();
		//サウンド再生
		m_pSound->Play(CSound::LABEL_BGM_SELECT);

		break;
	case GAME_MODE_STAGE:
		//シーン破棄
		CScene::ReleaseAll();
		//サウンド停止
		m_pSound->Stop();

		//ゲーム生成処理
		m_pGame = CGame::Create();

		break;
	case GAME_MODE_CLEAR:
		m_Player = { 0,0,{ CPlayer::WEAPONS_MODE_BUTTOL , CPlayer::WEAPONS_MODE_NONE } };
		m_nScore = 10000;
		//シーン破棄
		CScene::ReleaseAll();
		//サウンド停止
		m_pSound->Stop();

		//ゲームクリア
		CClear::Create();
		//サウンド再生
		m_pSound->Play(CSound::LABEL_SE_RESULT);

		break;

	}

}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInihKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CInihMouse * CManager::GetMouse(void)
{
	return m_pInihMouse;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

int  CManager::GetScore(void)
{
	return m_nScore;
}

int CManager::GetPlayer(int nPlayerData)
{
	if (nPlayerData == 0)
	{
		return m_Player.m_nLife;
	}
	else
	{
		return m_Player.m_nSpeed;
	}
}

void CManager::SetPlayer(int nLife, int nSpeed)
{
	m_Player.m_nLife = nLife;
	m_Player.m_nSpeed = nSpeed;
}

void CManager::SetWeapon(CPlayer::WEAPON_MODE nWeaponData1, CPlayer::WEAPON_MODE nWeaponData2)
{
	m_Player.m_nWeapon[0] = nWeaponData1;
	m_Player.m_nWeapon[1] = nWeaponData2;
}




