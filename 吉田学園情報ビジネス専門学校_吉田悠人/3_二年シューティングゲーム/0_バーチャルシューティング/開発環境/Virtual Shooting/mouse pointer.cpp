//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SIZE (100)


#include "mouse pointer.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPointer::m_pTexture[POINTER_TYPE_MAX] = {};
char *CPointer::pTexture[POINTER_TYPE_MAX]=
{
	"data/TEXTURE/MousePointer_Select.png",
	"data/TEXTURE/MousePointer_Game.png"
};
//=============================================================================
// コンストラクタ
//=============================================================================
CPointer::CPointer(int nPriorit) :CScene2d(nPriorit)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPointer::~CPointer()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CPointer::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// テクスチャの生成
	for (int nCount = 0; nCount < POINTER_TYPE_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_pTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CPointer::Unload(void)
{
	for (int nCount = 0; nCount < POINTER_TYPE_MAX; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 作成処理
//=============================================================================
CPointer * CPointer::Create(POINTER_TYPE Type)
{
	CPointer *pPointer;
	//インスタンス生成
	pPointer = new CPointer;

	//初期化処理
	if (pPointer != NULL)
	{
		pPointer->Init(Type);
	}
	pPointer->SetPos(D3DXVECTOR3(0.0f,0.0f,0.0f));
	return pPointer;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPointer::Init(POINTER_TYPE Type)
{
	//テクスチャ設定
	BindTexture(m_pTexture[Type]);
	//サイズ
	SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	//初期化処理
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPointer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPointer::Update(void)
{
	//マウス取得
	CInihMouse *pMouse = CManager::GetMouse();
	

	D3DXVECTOR3 MousePos = D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f);
	SetPos(MousePos);
	CScene2d::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPointer::Draw(void)
{
	CScene2d::Draw();
}
