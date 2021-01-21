#include "telop_bar.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CTelopBer::m_apTexture= {};

//------------------------------------
//コンストラクタ
//------------------------------------
CTelopBer::CTelopBer()
{
	//ポリゴンの初期化
	m_apScene2D = NULL;
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//デストラクタ
//------------------------------------
CTelopBer::~CTelopBer()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CTelopBer::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Telop.png", &m_apTexture);

	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CTelopBer::Unload(void)
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
CTelopBer * CTelopBer::Create(void)
{
	CTelopBer *pTelopBer;
	pTelopBer = new CTelopBer;
	pTelopBer->Init();
	return pTelopBer;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CTelopBer::Init(void)
{
	//メモリ確保
	m_apScene2D = new CScene2d;
	//位置
	m_apScene2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH-425, 25, 0.0f));
	//サイズ
	m_apScene2D->SetSize(D3DXVECTOR3(850, 50, 0.0f));
	//初期化処理
	m_apScene2D->CScene2d::Init();
	//テクスチャの設定
	m_apScene2D->BindTexture(m_apTexture);
	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CTelopBer::Uninit(void)
{
	m_apScene2D->CScene2d::Uninit();
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CTelopBer::Update(void)
{
	m_apScene2D->CScene2d::Update();
}

//------------------------------------
//描画処理
//------------------------------------
void CTelopBer::Draw(void)
{
	m_apScene2D->CScene2d::Draw();
}
