//=============================================================================
//	
//	テクスチャ[texture.cpp]
//	テキスト画像やUIアイコンなどの表示
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================

//=============================================================================
// コンストラクト
//=============================================================================
CTexture::CTexture()
{
	m_Texture = NULL;
	memset(m_pos, 0, sizeof(m_pos));
	memset(m_size, 0, sizeof(m_size));
}

//=============================================================================
// デストラクト
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTexture::Init(void)
{
	//頂点情報へのポインター
	VERTEX_2D *pVtx;
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,			//バッファサイズ
		D3DUSAGE_WRITEONLY,				//(固定)
		FVF_VERTEX_2D,					//頂点フォーマット
		D3DPOOL_MANAGED,				//（固定）
		&m_pVtxBuff,					//変数名が変わると変更が必要
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報を設定
	pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点情報を設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //aは透明度
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //aは透明度
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //aは透明度
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //aは透明度

														//頂点データをアンロックする
	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTexture::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CTexture::Update(void)
{
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標更新
	pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	m_pVtxBuff->Unlock();


}

//=============================================================================
// 描画処理
//=============================================================================
void CTexture::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// 位置セッター処理
//=============================================================================
void CTexture::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズセッター処理
//=============================================================================
void CTexture::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 位置ゲッター処理
//=============================================================================
D3DXVECTOR3 CTexture::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// サイズゲッター処理
//=============================================================================
D3DXVECTOR3 CTexture::GetSize(void)
{
	return m_size;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
void CTexture::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_Texture = pTexture;
}

//=============================================================================
// テクスチャアニメーション関数
//=============================================================================
void CTexture::TextureAnim(D3DXVECTOR2 * Texture)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].tex = Texture[0];
	pVtx[1].tex = Texture[1];
	pVtx[2].tex = Texture[2];
	pVtx[3].tex = Texture[3];

	m_pVtxBuff->Unlock();						//頂点データをアンロックする

}
