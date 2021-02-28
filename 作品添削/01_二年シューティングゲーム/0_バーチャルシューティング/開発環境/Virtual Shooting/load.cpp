//=============================================================================
//
// ロード画面処理 [load.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "load.h"
#include "renderer.h"
#include "sound.h"
#include "manager.h"
#include "load bg.h"
#include "clear.h"
#include "number.h"
#include "telop.h"
#include "mouse pointer.h"
#include "title bg.h"
#include "tutorial bg.h"
#include "select bg.h"
#include "life ui.h"
#include "weapon manager.h"
#include "button manager.h"
#include "result bg.h"
#include "score bar.h"
#include "stage.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLoad::CLoad()
{
	m_bLoad = false;
	m_pLoadBg = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLoad::~CLoad()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CLoad::Load(void)
{
	CLoadBg::Load();
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CLoad::Unload(void)
{
	CLoadBg::Unload();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLoad::Init(void)
{
	//サウンド取得
	CSound*	pSound = CManager::GetSound();
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_LOAD);
	//背景生成
	m_pLoadBg = CLoadBg::Create();

	//アップデート（マルチスレッド）
	std::thread LoadUpdate(&CLoad::Update,this);
	//描画（マルチスレッド）
	std::thread LoadDraw(&CLoad::Draw, this);
	//ファイルロード(マルチスレッド)
	std::thread Load(&CLoad::FileLoad, this);

	//スレッドが終了するまで待機する
	LoadUpdate.join();
	LoadDraw.join();
	Load.join();
	//ここまで
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLoad::Uninit(void)
{
	//シーン破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLoad::Update(void)
{

	while (!m_bLoad)
	{
		//レンダラーポインタ取得
		CRenderer* Renderer = NULL;
		Renderer = CManager::GetRenderer();

		//NULLチェック
		if (Renderer != NULL)
		{
			std::lock_guard<std::mutex> lock(m_mtx_);
			Renderer->Update();
		}
	}

}

//=============================================================================
// 描画関数
//=============================================================================
void CLoad::Draw(void)
{

	while (!m_bLoad)
	{
		//レンダラーポインタ取得
		CRenderer* Renderer = NULL;
		Renderer = CManager::GetRenderer();


		//NULLチェック
		if (Renderer != NULL)
		{
			std::lock_guard<std::mutex> lock(m_mtx_);
			Renderer->Draw();
		}

	}
}

void CLoad::FileLoad(void)
{
	std::lock_guard<std::mutex> lock(m_mtx_);
	
	//テクスチャの読み込み
	CClear::Load();
	CNumber::Load();
	CTelop::Load();
	CPointer::Load();
	CTitleBg::Load();
	CTutorialBg::Load();
	CSelectBg::Load();
	CLifeUi::Load();
	CWeaponManager::Load();
	CButtonManager::Load();
	CGame::Load();
	CResultBg::Load();
	CScoreBar::Load();
	//テキスト読み込み
	CStage::LoadFile();
	
	//読み終えたか
	m_bLoad = true;
}
