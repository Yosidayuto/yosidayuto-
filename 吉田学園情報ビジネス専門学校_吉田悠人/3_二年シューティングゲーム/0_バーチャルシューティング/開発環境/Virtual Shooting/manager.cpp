//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"		
#include "renderer.h"		
#include "scene2d.h"		
#include "scene.h"			
#include "input.h"			
#include "inihkeyboard.h"	
#include "inputmouse.h"		
#include "sound.h"			
#include "score.h"			
#include "number.h"			
#include "fade.h"			
#include "ui.h"				
#include "game.h"			
#include "select.h"			
#include "text.h"			
#include "window.h"			
#include "player.h"			
#include "button.h"			
#include "clear.h"			
#include "telop_bar.h"		
#include "mouse pointer.h"	
#include "telop_text.h"		
#include "title bg.h"
#include "title.h"
#include "tutorial bg.h"
#include "tutorial.h"
#include "select bg.h"
#include "weapon_UI.h"
#include "start button.h"
#include "button p.h"
#include "life button.h"
#include "life ui.h"
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer	= NULL;
CInihKeyboard *CManager::m_pInput	= NULL;
CInihMouse *CManager::m_pInihMouse	= NULL;
CSound *CManager::m_pSound			= NULL;
GAME_MODE CManager::m_Mode			= GAME_MODE_TITLE;
CScene *CManager::m_pScene			= NULL;
CFade *CManager::m_pFade			= NULL;
CGame *CManager::m_pGame			= NULL;
CSelect *CManager::m_pSelect		= NULL;
int CManager::m_nScore				= 10000;
CManager::PLAYER_DATA CManager::m_Player =
{ 0,0,{ WEAPONS_MODE_BUTTOL , WEAPONS_MODE_NONE } };
CTitle *CManager::m_pTitle			= NULL;
CTutorial *CManager::m_pTutorial	= NULL;
//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//初期化関数
//=============================================================================
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
	//タイトル処理
	m_pTitle	= new CTitle;
	//チュートリアル処理
	m_pTutorial	= new CTutorial;
	//セレクト処理
	m_pSelect	= new CSelect;
	//ゲーム処理
	m_pGame		= new CGame;
	//ファイルロード
	LoadFile();

	//オブジェクトクラス生成
	m_pFade->SetFade(m_Mode);
	return S_OK;
}

//=============================================================================
//終了関数
//=============================================================================
void CManager::Uninit(void)
{
	//シーンの終了
	CScene::ReleaseAll();

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

	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)	//メモリが確保されているか
	{
		//レンダリング 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//ファイルアンロード処理
	UnLoadFile();
}

//=============================================================================
//更新関数
//=============================================================================
void CManager::Update()
{
	// キーボード更新 (最初に行う)
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}

	// マウス更新
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Update();		
	}

	// レンダリング更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();		
	}

	// フェードアウト更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();			
	}

	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTitle != NULL)
		{
			m_pTutorial->Update();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		break;
	case GAME_MODE_STAGE:
		if (m_pSelect != NULL)
		{
			m_pGame->Update();
		}
		break;
	}

}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw(void)
{

	//レンダラの描画
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//ゲームモードセット処理
//=============================================================================
void CManager::SetMode(GAME_MODE mode)
{
	//終了処理
	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//タイトルシーン破棄
			m_pTitle->Uninit();
		}

		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			//セレクトシーン破棄
			m_pSelect->Uninit();
		}

		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}
		//シーン破棄
		CScene::ReleaseAll();
		//サウンド停止
		m_pSound->Stop();
		break;
	case GAME_MODE_CLEAR:
		m_Player = { 0,0,{ WEAPONS_MODE_BUTTOL , WEAPONS_MODE_NONE } };
		m_nScore = 10000;
		//シーン破棄
		CScene::ReleaseAll();
		//サウンド停止
		m_pSound->Stop();
		break;
	}

	m_Mode = mode;

	//初期化処理
	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//タイトル初期化処理
			m_pTitle->Init();
		}
		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//チュートリアル初期化処理
			m_pTutorial->Init();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			//セレクト初期化処理
			m_pSelect->Init();
		}
		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			//ゲーム生成処理
			m_pGame->Init();
		}
		break;
	case GAME_MODE_CLEAR:
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

//=============================================================================
// ファイルロード関数
//=============================================================================
void CManager::LoadFile(void)
{
	//テクスチャの読み込み
	CClear::Load();			
	CNumber::Load();		
	CUi::Load();			
	CText::Load();			
	CWindow::Load();		
	CButton::Load();		
	CTelopBer::Load();		
	CTelopText::Load();		
	CPointer::Load();		
	CTitleBg::Load();
	CTutorialBg::Load();
	CSelectBg::Load();		
	CWeapon_Ui::Load();
	CStartButton::Load();
	CButtonp::Load();
	CLifeButton::Load();
	CLifeUi::Load();
}

//=============================================================================
// ファイルアンロード関数
//=============================================================================
void CManager::UnLoadFile(void)
{
	//テクスチャの破棄
	CClear::Unload();			
	CButton::Unload();			
	CNumber::Unload();			
	CUi::Unload();				
	CText::Unload();			
	CWindow::Unload();			
	CTelopBer::Unload();		
	CTelopText::Unload();		
	CPointer::Unload();			
	CTitleBg::Unload();
	CTutorialBg::Unload();
	CSelectBg::Unload();
	CWeapon_Ui::Unload();
	CStartButton::Unload();
	CButtonp::Unload();
	CLifeButton::Unload();
	CLifeUi::Unload();

}

void CManager::SetPlayer(int nLife, int nSpeed)
{
	m_Player.m_nLife = nLife;
	m_Player.m_nSpeed = nSpeed;
}

void CManager::SetWeapon(WEAPON_MODE nWeaponData1, WEAPON_MODE nWeaponData2)
{
	m_Player.m_nWeapon[0] = nWeaponData1;
	m_Player.m_nWeapon[1] = nWeaponData2;
}




