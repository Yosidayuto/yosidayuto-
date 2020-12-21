//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "scene2d.h"	//シーン２D（2Dポリゴン）ファイル
#include "manager.h"	//マネージャーファイル
#include "renderer.h"	//レンダリングファイル	
#include "title.h"		//タイトルファイル
#include "inputmouse.h"	//マウス入力ファイル
#include "fade.h"		//フェードアウトファイル
#include "sound.h"		//サウンド

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE] = {};

//------------------------------------
//コンストラクタ
//------------------------------------
CTitle::CTitle()
{
	//ポリゴンの初期化
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_bFade = false;
}

//------------------------------------
//デストラクタ
//------------------------------------
CTitle::~CTitle()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CTitle::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &m_apTexture[0]);
	
	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//------------------------------------
//生成処理
//------------------------------------
CTitle * CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CTitle::Init(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		//メモリ確保
		m_apScene2D[nCount] = new CScene2d;
		//位置
		m_apScene2D[nCount]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		//サイズ
		m_apScene2D[nCount]->SetSizeition(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//初期化処理
		m_apScene2D[nCount]->CScene2d::Init();
		//テクスチャの設定
		m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
	}

	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CTitle::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Uninit();
	}
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CTitle::Update(void)
{
	CSound *pSound = CManager::GetSound();				//サウンド取得
	CInihMouse *pMouse = CManager::GetMouse();			//マウス取得
	CFade *pFade = CManager::GetFade();
	if (pMouse->GetClickTrigger(0) == true)
	{
		if (pFade->Set(CManager::GAME_MODE_SELECT) == true)
		{
			pSound->Play(CSound::LABEL_SE_CLICK);
		}
	}
	else if (pMouse->GetClickTrigger(1) == true)
	{
		if (pFade->Set(CManager::GAME_MODE_TUTORIAL) == true)
		{
			pSound->Play(CSound::LABEL_SE_CLICK);
		}

	}
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Update();
	}

}

//------------------------------------
//描画処理
//------------------------------------
void CTitle::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Draw();
	}
}
