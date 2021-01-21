//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "resultBg.h"
#include "manager.h"
#include "renderer.h"
//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CResultBg::m_apTexture = NULL;

//------------------------------------
//コンストラクタ
//------------------------------------
CResultBg::CResultBg(int nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//デストラクタ
//------------------------------------
CResultBg::~CResultBg()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CResultBg::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ResultBg.png", &m_apTexture);
	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CResultBg::Unload(void)
{
	//テクスチャの破棄
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}


}

//------------------------------------
//生成処理
//------------------------------------
CResultBg * CResultBg::Create(void)
{
	CResultBg *pResultBg;
	pResultBg = new CResultBg;
	pResultBg->Init();
	return pResultBg;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CResultBg::Init(void)
{
	//位置
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//サイズ
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//テクスチャの設定
	BindTexture(m_apTexture);
	//初期化処理
	CScene2d::Init();

	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CResultBg::Uninit(void)
{
	CScene2d::Uninit();
}

//------------------------------------
//更新処理
//------------------------------------
void CResultBg::Update(void)
{
}

//------------------------------------
//描画処理
//------------------------------------
void CResultBg::Draw(void)
{
	CScene2d::Draw();
}
