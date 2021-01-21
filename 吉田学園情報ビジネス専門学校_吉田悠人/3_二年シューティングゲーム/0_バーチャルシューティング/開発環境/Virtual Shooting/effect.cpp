//アップデートで大きさ色（α値）を変更
//描画処理で加算合計の設定(DESTBLENDをONE)してから２Dの描画処理を呼ぶ
//そのあとに加算合計の設定(DESTBLENDをINVSRCALPHA)を元に戻す
//

//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"renderer.h"		//レンダリング
#include"manager.h"			//マネージャー
#include "effect.h"
//----------------------------------
//マクロ定義
//----------------------------------
#define EFFECT_LIFE 8		//バレットの射程距離
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[EFFECT_TYPE_MAX] = {};
char * CEffect::pTexture[EFFECT_TYPE_MAX]=
{
	"data/TEXTURE/Bullet.png",
	"data/TEXTURE/Laser.png"
};

CEffect::CEffect(int nPriorit):CScene2d(nPriorit)
{
	nLife = 0;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);

}

CEffect::~CEffect()
{
}

CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXCOLOR col, D3DXVECTOR3 size ,EFFECT_TYPE type)
{
	CEffect *pEffect;
	pEffect = new CEffect;
	pEffect->SetPos(Pos);
	pEffect->m_Type=type;
	pEffect->Init(size, col);

	return pEffect;
}

void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}

	}
}

HRESULT CEffect::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_pTexture[nCount]);

	}
	return S_OK;
}

HRESULT CEffect::Init(D3DXVECTOR3 size, D3DXCOLOR col)
{
	//射程距離
	nLife = EFFECT_LIFE;
	//カラー
	m_col = col;
	//サイズ
	SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));
	//テクスチャの設定
	BindTexture(m_pTexture[m_Type]);
	//初期化処理
	CScene2d::Init();

	return S_OK;
}

void CEffect::Uninit(void)
{
	//終了処理
	CScene2d::Uninit();

}

void CEffect::Update(void)
{
	//エフェクトの存在
	nLife--;

	switch (m_Type)
	{
	case EFFECT_TYPE_BULLET:
		//大きさの取得
		m_size = GetSize();
		//大きさの処理
		m_size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//ポリゴンの大きさを渡す
		SetSize(m_size);
		break;
	}
	m_col = D3DXCOLOR(m_col.r - 0.05f, m_col.g - 0.05f, m_col.b - 0.05f, m_col.a-0.05f);
	//カラーセット
	SetCol(m_col);

	//更新処理
	CScene2d::Update();
	//エフェクトの終了処理
	if (nLife<0)
	{
		Uninit();	//終了処理
	}

}

void CEffect::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	/*レンダリングステート(加算合成処理)*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画処理
	CScene2d::Draw();

	/*レンダーステート*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}
