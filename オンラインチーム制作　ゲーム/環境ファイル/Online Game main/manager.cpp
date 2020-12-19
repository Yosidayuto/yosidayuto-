//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 俵谷 健太郎　吉田悠人
//
//=============================================================================
#include "manager.h"
#include "scene2d.h"
#include "polygon.h"
#include "tooth.h"
#include "bg.h"
#include "input_mouse.h"
#include "mouse_pointer.h"
#include "clean.h"
#include "fade.h"
#include "title.h"
#include "wait.h"
#include "game.h"
#include "result.h"
#include "communication.h"
#include "turn wait.h"
#include "ui.h"
#include "death.h"
#include "sound.h"
#include "die screen.h"
#include "load.h"
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CPolygon *CManager::m_pPolygon = NULL;
CInhMouse *CManager::m_pInputMouse = NULL;
CTitle *CManager::m_pTitle = NULL;
CLoad *CManager::m_pLoad = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = {};
CCommunication *CManager::pCommunication=NULL;
CSound *CManager::m_pSound = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
	m_mode = MODE_TITLE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//接続処理
	WSADATA wsaData;
	//winsockの初期化
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		//初期化できなかった時
		printf("初期化に失敗しました\n");

		return 1;
	}


	//レンダラー生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//キーボード生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//マウス生成
	m_pInputMouse = new CInhMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//サウンド生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);


	//テクスチャ生成
	CUi::Load();
	CTurnWait::Load();
	CTooth::Load();
	CClean::Load();
	CBg::Load();
	CPointer::Load();
	CTitle::Load();
	CWait::Load();
	CResult::Load();
	CDeath::Load();
	CDieScreen::Load();
	//フェード生成
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));


	SetMode(MODE_TITLE);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//全てのオブジェクトを破棄
	CScene::ReleaseAll();

	//テクスチャ破棄
	CUi::Unload();
	CTurnWait::Unload();
	CTooth::Unload();
	CClean::Unload();
	CBg::Unload();
	CPointer::Unload();
	CTitle::Unload();
	CWait::Unload();
	CResult::Unload();
	CDeath::Unload();
	CDieScreen::Unload();
	//サウンド終了
	if (m_pSound != NULL)
	{
		//終了処理
		m_pSound->Uninit();

		//インスタンス破棄
		delete m_pSound;
		m_pSound = NULL;
	}

	//フェード終了
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = NULL;
	}

	//通信終了
	if (pCommunication != NULL)
	{
		pCommunication->Uninit();
		delete pCommunication;
		pCommunication = NULL;
	}

	//キーボード終了
	if (m_pInputKeyboard != NULL)
	{
		//終了処理
		m_pInputKeyboard->Uninit();

		//インスタンス破棄
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//マウス終了
	if (m_pInputMouse != NULL)
	{
		//終了処理
		m_pInputMouse->Uninit();

		//インスタンス破棄
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//レンダラー終了
	if (m_pRenderer != NULL)
	{
		//終了処理
		m_pRenderer->Uninit();

		//インスタンス破棄
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	//入力処理更新(キーボード)
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//入力処理更新(マウス)
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	//レンダラー更新
	if (m_pRenderer != NULL)
	{
		//更新処理
		m_pRenderer->Update();
	}

	//フェード更新
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE://タイトル画面の終了処理
		if (m_pInputKeyboard->GetKeyTrigger(DIK_RETURN))
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);				//決定音

			m_pFade->SetFade(MODE_LOAD);
		}
		break;
	case MODE_LOAD://ロード画面の終了処理
		if (CCommunication::GetbRecv()==true)
		{

			m_pFade->SetFade(MODE_GAME);
		}
		break;
	case MODE_GAME://ゲーム画面の終了処理
		if (m_pInputKeyboard->GetKeyTrigger(DIK_RETURN))
		{
			m_pFade->SetFade(MODE_RESULT);
		}
		break;

	case MODE_RESULT://リザルト画面の終了処理
		if (m_pInputKeyboard->GetKeyTrigger(DIK_RETURN))
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);		//決定音
																		
			m_pFade->SetFade(MODE_TITLE);						//フェイド
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//描画処理
		m_pRenderer->Draw();
	}
}

//=============================================================================
// レンダリングを取得
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボードを取得
//=============================================================================
CInputKeyboard * CManager::Getkeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// マウスを取得
//=============================================================================
CInhMouse * CManager::GetMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
// ポリゴンナンバー取得
//=============================================================================
CPolygon * CManager::GetPolygon(void)
{
	return m_pPolygon;
}

//=============================================================================
// サウンドを取得
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// モード切替
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pSound->Stop();				//サウンド停止
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
		}
		break;
	case MODE_LOAD:
		m_pSound->Stop();				//サウンド停止

		if (m_pLoad != NULL)
		{
			m_pLoad->Uninit();
		}
		break;

	case MODE_GAME:
		m_pSound->Stop();				//サウンド停止
		if (pCommunication != NULL)		//通信終了
		{
			pCommunication->Uninit();
			delete pCommunication;
			pCommunication = NULL;
		}


		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}

		break;

	case MODE_RESULT:
		m_pSound->Stop();				//サウンド停止

		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
		}
		break;
	}

	CScene::ReleaseAll();

	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE://タイトル画面の初期化
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		m_pTitle->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		break;
	case MODE_LOAD:	//ロード画面
		m_pSound->Play(CSound::SOUND_LABEL_BGM_LOAD);
		m_pLoad->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		pCommunication = CCommunication::Create();
		break;

	case MODE_GAME://ゲーム画面の初期化
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		pCommunication->SetbRecv();
		m_pGame->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		break;

	case MODE_RESULT:
		m_pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
		m_pSound->Play(CSound::SOUND_LABEL_SE_WINNER);

		m_pResult->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		break;
	}
}

//=============================================================================
// モードの取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// フェードの取得
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// 通信データの取得
//=============================================================================
CCommunication * CManager::GetCommunication(void)
{
	return pCommunication;
}
