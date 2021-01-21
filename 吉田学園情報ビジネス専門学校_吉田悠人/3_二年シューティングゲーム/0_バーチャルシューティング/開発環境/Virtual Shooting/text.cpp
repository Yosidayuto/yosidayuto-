//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "text.h"
#include "manager.h"
#include "renderer.h"
//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CText::m_pTexture[TEXT_MAX] = {};
char * CText::m_cTexture[TEXT_MAX]=
{
	"data/TEXTURE/Text_Start.png",
	"data/TEXTURE/Text_Start_Last.png",
	"data/TEXTURE/Text_Life.png",
	"data/TEXTURE/Text_Speed.png",
	"data/TEXTURE/Text_Bullet.png",
	"data/TEXTURE/Text_Laser.png",
	"data/TEXTURE/Text_Homing.png",

};
//------------------------------------
//コンストラクタ
//------------------------------------
CText::CText()
{
	m_pVtxBuff = NULL;
	
}

//------------------------------------
//デストラクタ
//------------------------------------
CText::~CText()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CText::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	for (int nCount = 0; nCount < TEXT_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_cTexture[nCount], &m_pTexture[nCount]);
	}
	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CText::Unload(void)
{
	for (int nCount = 0; nCount < TEXT_MAX; nCount++)
	{
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
CText * CText::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXT_TYPE Text)
{
	CText *pText;
	pText = new CText;
	pText->Init(pos, size, Text);
	return pText;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CText::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXT_TYPE Text)
{
	m_Type = Text;
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
void CText::Uninit(void)
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
void CText::Update(void)
{
}

//------------------------------------
//描画処理
//------------------------------------
void CText::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture[m_Type]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
