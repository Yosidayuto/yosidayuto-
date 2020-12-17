//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "ui.h"
#include "manager.h"
#include "renderer.h"

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TEXTURE_TYPE_MAX] = {};
char * CUi::pTexture[TEXTURE_TYPE_MAX] =
{
	"data/TEXTURE/UI_score.png",
	"data/TEXTURE/UI_Life.png",
	"data/TEXTURE/UI_Bullet.png",
	"data/TEXTURE/UI_Laser.png",
	"data/TEXTURE/UI_Homing.png",
};
//------------------------------------
//コンストラクタ
//------------------------------------
CUi::CUi()
{
	m_nTexture = NULL;
	m_pVtxBuff = NULL;
}

//------------------------------------
//デストラクタ
//------------------------------------
CUi::~CUi()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CUi::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < TEXTURE_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_pTexture[nCount]);
	}
	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CUi::Unload(void)
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{			  
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}

	}
}

//------------------------------------
//生成処理
//------------------------------------
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture)
{
	CUi *pUi;
	pUi = new CUi;
	pUi->Init(pos, size, nTexture);
	return pUi;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture)
{
	m_nTexture = nTexture;
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&m_pVtxBuff,//変数名が変わると変更が必要
		NULL);
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点バッファの生成
	pVtx[0].pos = D3DXVECTOR3(-size.x / 2 + pos.x, -size.y / 2 + pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2 + pos.x, -size.y / 2 + pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2 + pos.x, size.y / 2 + pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2 + pos.x, size.y / 2 + pos.y, 0.0f);

	// 頂点情報を設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;

}

//------------------------------------
//終了処理
//------------------------------------
void CUi::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//------------------------------------
//更新処理
//------------------------------------
void CUi::Update(void)
{
}

//------------------------------------
//描画処理
//------------------------------------
void CUi::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture[m_nTexture]);
	
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

