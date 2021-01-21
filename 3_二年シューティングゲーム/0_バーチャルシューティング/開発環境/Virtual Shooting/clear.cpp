//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "scene2d.h"	
#include "manager.h"	
#include "renderer.h"	
#include "inputmouse.h"	
#include "fade.h"		
#include "clear.h"
//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CClear::m_apTexture[MAX_ClEAR] = {};

//------------------------------------
//コンストラクタ
//------------------------------------
CClear::CClear()
{
	//ポリゴンの初期化
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
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
CClear::~CClear()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CClear::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Result.png", &m_apTexture[0]);

	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CClear::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
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
CClear * CClear::Create(void)
{
	CClear *pClear;
	pClear = new CClear;
	pClear->Init();
	return pClear;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CClear::Init(void)
{
	//追加マウスカーソル非表示
	ShowCursor(true);

	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		//メモリ確保
		m_apScene2D[nCount] = new CScene2d;
		//位置
		m_apScene2D[nCount]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		//サイズ
		m_apScene2D[nCount]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
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
void CClear::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Uninit();
	}
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CClear::Update(void)
{
	CInihMouse *pMouse = CManager::GetMouse();			//マウス取得
	CFade *pFade = CManager::GetFade();
	if (pMouse->GetClickTrigger(0) == true)
	{
		pFade->SetFade(GAME_MODE_TITLE);
	}
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Update();
	}

}

//------------------------------------
//描画処理
//------------------------------------
void CClear::Draw(void)
{
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Draw();
	}
}
