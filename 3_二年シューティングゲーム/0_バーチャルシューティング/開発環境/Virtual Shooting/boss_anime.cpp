#include "boss_anime.h"
#include "manager.h"
#include "renderer.h"
//----------------------------------
//マクロ定義
//----------------------------------
//----------------------------------
//静的メンバー変数
//----------------------------------
CBossAnime::ANIME_DATA CBossAnime::BossAnim[BOSS_ANIME_MAX] = 
{
	NULL,"data/TEXTURE/BossAnime_0.png",45,2,true,
	NULL,"data/TEXTURE/DeleteEffect_0.png",45,2,false,

	NULL,"data/TEXTURE/BossAnime_1.png",50,2,true,
	NULL,"data/TEXTURE/DeleteEffect_1.png",60,3,false,

	NULL,"data/TEXTURE/BossAnime_2.png",60,2,true,
	NULL,"data/TEXTURE/DeleteEffect_2.png",90,2,false,


};

//----------------------------------
//コンストラクタ
//----------------------------------
CBossAnime::CBossAnime(int nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
}

//----------------------------------
//デストラクタ
//----------------------------------
CBossAnime::~CBossAnime()
{
}


//----------------------------------
//生成処理
//----------------------------------
CBossAnime * CBossAnime::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, BOSS_ANIME Type)
{
	CBossAnime *pBossAnime;

	pBossAnime = new CBossAnime;
	pBossAnime->m_Type = Type;
	pBossAnime->SetPos(Pos);
	pBossAnime->Init(size);
	
	return pBossAnime;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CBossAnime::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < BOSS_ANIME_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, BossAnim[nCount].pTextName, &BossAnim[nCount].pTexture);

	}
	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CBossAnime::Unload(void)
{
	for (int nCount = 0; nCount < BOSS_ANIME_MAX; nCount++)
	{
		//テクスチャの破棄
		if (BossAnim[nCount].pTexture != NULL)
		{
			BossAnim[nCount].pTexture->Release();
			BossAnim[nCount].pTexture = NULL;
		}


	}
}

//----------------------------------
//初期化処理
//----------------------------------
HRESULT CBossAnime::Init(D3DXVECTOR3 size)
{
	D3DXVECTOR2 Texture[4];
	//サイズ
	SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));

	//初期化処理
	CScene2d::Init();
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 1.0f);
	
	TextureAnim(Texture);

	//テクスチャの設定
	BindTexture(BossAnim[m_Type].pTexture);

	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CBossAnime::Uninit(void)
{
	//終了処理
	CScene2d::Uninit();

}

//----------------------------------
//更新処理
//----------------------------------
void CBossAnime::Update(void)
{
	D3DXVECTOR2 Texture[4];

	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 0);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 0);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 1);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 1);

	TextureAnim(Texture);
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim>= BossAnim[m_Type].nCountAnime)
	{
		//アニメーションの絵を次の絵に変える
		m_nCounterAnim = 0;
		m_nPatternAnimX++;
		if (m_nPatternAnimX == BossAnim[m_Type].MaxCount)
		{
			m_nPatternAnimX = 0;
			if (BossAnim[m_Type].bLoop == false)
			{
				Uninit();
			}
		}
	}

}

//----------------------------------
//描画処理
//----------------------------------
void CBossAnime::Draw(void)
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

