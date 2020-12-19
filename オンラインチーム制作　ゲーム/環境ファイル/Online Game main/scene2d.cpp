//=============================================================================
//
// ポリゴン2D処理 [scene2d.cpp]
// Author : 俵谷 健太郎
//
//=============================================================================
#include "scene2d.h"
#include "input_keyboard.h"
#include "manager.h"


//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_fAngle = 0;
	m_fAngle1 = 0;
	m_fDiagonal = 0;
	m_fChange = 0;
	m_fAdd = 0;
	m_fAngleChane = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D ::~CScene2D()
{
}

//=============================================================================
// ポリゴン作成処理
//=============================================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 size)
{
	CScene2D *pScene2D;
	//インスタンス生成
	pScene2D = new CScene2D;

	//初期化処理
	if (pScene2D != NULL)
	{
		pScene2D->Init(size);
	}

	return pScene2D;
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 size)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//pD3DDevice=GetRenderer()->GetDevice();	//一つにまとめることもできる　

	// 頂点バッファの生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//(固定)
		&m_pVtxBuff,
		NULL);

	m_fDiagonal = sqrtf((size.x / 2)*(size.x / 2) + (size.y / 2)*(size.y / 2));
	m_fAngle = atan2f((size.y / 2), (size.x / 2));
	m_fAngle1 = atan2f((size.y / 2), (size.x / 2));
	m_fChange = 1.0f;
	m_fAdd = 0.01f;
	m_fAngleChane = 0.01f;


	m_size = size;

	// 頂点情報を設定
	VERTEX_2D*pVtx;

	//頂点データの範囲をロックし頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定(右回りで設定する)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	//rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定(0～255の数値で設定)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;
	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;

}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 設置処理
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報を設定
	VERTEX_2D*pVtx;

	//頂点データの範囲をロックし頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定(右回りで設定する)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//pVtx += 4;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();

}

//=============================================================================
// テクスチャ座標取得
//=============================================================================
void CScene2D::SetTexPosition(int nCount, float nPattern)
{
	// 頂点情報を設定
	VERTEX_2D*pVtx;

	//頂点データの範囲をロックし頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((nPattern) / nCount, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern + 1) / nCount, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPattern) / nCount, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nPattern + 1) / nCount, 1.0f);


	//頂点データをアンロック
	m_pVtxBuff->Unlock();


}


//=============================================================================
// 位置情報取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// テクスチャの割り当て
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// カラー情報取得
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	m_pVtxBuff->Unlock();						//頂点データをアンロックする
}

//=============================================================================
// 角度情報取得
//=============================================================================
void CScene2D::SetRotate(float fAngle)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)*cosf(fAngle)), (m_pos.y - (m_size.y / 2)*sinf(fAngle)), 0);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)*cosf(fAngle)), (m_pos.y - (m_size.y / 2)*sinf(fAngle)), 0);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)*cosf(fAngle)), (m_pos.y + (m_size.y / 2)*sinf(fAngle)), 0);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)*cosf(fAngle)), (m_pos.y + (m_size.y / 2)*sinf(fAngle)), 0);

	m_pVtxBuff->Unlock();						//頂点データをアンロックする

}

//=============================================================================
// アニメーション情報取得
//=============================================================================
void CScene2D::SetAnimation(float nPattern, int nMaxAnimation)
{
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nMaxAnimation), 0);
	pVtx[1].tex = D3DXVECTOR2((nPattern *(1.0f / nMaxAnimation)) + (1.0f / nMaxAnimation), 0);
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nMaxAnimation), 1);
	pVtx[3].tex = D3DXVECTOR2((nPattern*(1.0f / nMaxAnimation)) + (1.0f / nMaxAnimation), 1);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// サイズ情報取得
//=============================================================================
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	// 頂点情報を設定
	VERTEX_2D*pVtx;

	//頂点データの範囲をロックし頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定(右回りで設定する)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (size.x / 2), m_pos.y - (size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (size.x / 2), m_pos.y - (size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (size.x / 2), m_pos.y + (size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (size.x / 2), m_pos.y + (size.y / 2), 0.0f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
