#include"scene2d.h"

#include"manager.h"
#include"input.h"
#include"inihkeyboard.h"
#include"renderer.h"
CScene2d::CScene2d(int nPriorit):CScene(nPriorit)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}
CScene2d::~CScene2d()
{

}
HRESULT CScene2d::Init(void)
{
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


	////距離計算
	g_fLengthpos = sqrtf(pow(m_sizePolygon.x / 2, 2.0f) + pow(m_sizePolygon.y / 2, 2.0f));
	g_Angle = atan2(m_sizePolygon.x / 2, m_sizePolygon.y / 2);


	// テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);


	// 頂点バッファの生成
	pVtx[0].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);


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

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();


	return S_OK;
}


void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//オブジェクトの破棄
	Release();
}

void CScene2d::Set(D3DXVECTOR3 Pos)
{
	m_posPolygon = Pos;
}

void CScene2d::TextureAnim(D3DXVECTOR2 *Texture)//sizeは１/テクスチャの分割数
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].tex = Texture[0];
	pVtx[1].tex = Texture[1];
	pVtx[2].tex = Texture[2];
	pVtx[3].tex = Texture[3];
	
	m_pVtxBuff->Unlock();						//頂点データをアンロックする
}

//ポリゴン回転処理
void CScene2d::SetRotate(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	float fAngleX = g_fLengthpos*cos(g_Angle);
	float fAngleY = g_fLengthpos*sin(g_Angle);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点バッファの移動
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);
	fAngleX = g_fLengthpos*cos(g_Angle + D3DXToRadian(90));
	fAngleY = g_fLengthpos*sin(g_Angle + D3DXToRadian(90));
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);
	fAngleX = g_fLengthpos*cos(g_Angle + D3DXToRadian(-90));
	fAngleY = g_fLengthpos*sin(g_Angle + D3DXToRadian(-90));

	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);
	fAngleX = g_fLengthpos*cos(g_Angle + D3DXToRadian(180));
	fAngleY = g_fLengthpos*sin(g_Angle + D3DXToRadian(180));

	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
	g_Angle += 0.1f;

}




void CScene2d::ColChange(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();						//頂点データをアンロックする

}

void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_pTexture = pTexture;
}

CScene2d *CScene2d::Create(D3DXVECTOR3 Pos)
{
	CScene2d *pScene2d;
	pScene2d = new CScene2d;
	pScene2d->Set(Pos);
	pScene2d->Init();
	
	return pScene2d;
}


void CScene2d::Update(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点バッファの移動
	pVtx[0].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);


	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2d::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

