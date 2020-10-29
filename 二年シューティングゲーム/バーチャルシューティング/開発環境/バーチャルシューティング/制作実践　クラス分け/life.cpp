//----------------------------------
//ヘッダファイル
//----------------------------------
#include "life.h"		//ライフファイル
#include "scene2d.h"	//シーン２D（2Dポリゴン）ファイル
#include "manager.h"	//マネージャーファイル
#include "renderer.h"	//レンダリングファイル	
#include "ui.h"			//UIファイル
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define LIFE_SIZE_X (200.0f,20.0f)
#define LIFE_SIZE_Y 30.0f

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CLife::m_apTexture = NULL;

//----------------------------------
//コンストラクタ
//----------------------------------
CLife::CLife(int nPriorit) :CScene(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	nLife = 0;
}

//----------------------------------
//デストラクタ
//----------------------------------
CLife::~CLife()
{
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CLife::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Life_UI.png", &m_apTexture);
	return S_OK;

}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CLife::Unload(void)
{
	//テクスチャの破棄
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}

//----------------------------------
//生成処理
//----------------------------------
CLife * CLife::Create(D3DXVECTOR3 pos)
{
	CLife *pLife;
	pLife = new CLife;
	pLife->SetPos(pos);			//ライフの位置
	pLife->Init();
	return pLife;
}

//----------------------------------
//初期化処理
//----------------------------------
HRESULT CLife::Init(void)
{
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		//メモリ確保
		m_apScene2D[nCount] = new CScene2d(PRIORIT_LIFE);
		//位置
		m_apScene2D[nCount]->SetPosition(D3DXVECTOR3((nCount*LIFE_SIZE_X + LIFE_SIZE_X/2)+ pos.x,(pos.y - LIFE_SIZE_Y / 2),0.0f));
		//サイズ
		m_apScene2D[nCount]->SetSizeition(D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f));
		//初期化処理
		m_apScene2D[nCount]->CScene2d::Init();
		//テクスチャの設定
		m_apScene2D[nCount]->BindTexture(m_apTexture);
	}
	m_Ui = CUi::Create(D3DXVECTOR3(LIFE_SIZE_X*(MAX_LIFE/2)+ pos.x, pos.y - LIFE_SIZE_Y / 2,0.0f), D3DXVECTOR3(LIFE_SIZE_X*(MAX_LIFE*1.5), LIFE_SIZE_Y*1.5,0.0f), CUi::TEXTURE_TYPE_LIFE);
	return S_OK;

}

//----------------------------------
//終了処理
//----------------------------------
void CLife::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->CScene2d::Uninit();
		}
	}
	if (m_Ui != NULL)
	{
		m_Ui->Uninit();
	}
	Release();
}

//----------------------------------
//更新処理
//----------------------------------
void CLife::Update(void)
{

}

//----------------------------------
//描画処理
//----------------------------------
void CLife::Draw(void)
{
	if (m_Ui != NULL)
	{
		m_Ui->Draw();
	}

	for (int nCount = 0; nCount < nLife; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->CScene2d::Draw();
		}
	}

}

void CLife::SetLife(int nLifeNumber)
{
	nLife = nLifeNumber;
}

void CLife::SetPos(D3DXVECTOR3 Lifepos)
{
	pos = Lifepos;
}

void CLife::DownLife(int nLifeDown)
{
	nLife -= nLifeDown;
}
