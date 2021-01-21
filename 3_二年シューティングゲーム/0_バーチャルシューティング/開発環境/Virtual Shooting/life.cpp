//----------------------------------
//ヘッダファイル
//----------------------------------
#include "life.h"		
#include "scene2d.h"	
#include "manager.h"	
#include "renderer.h"	
#include "ui.h"			
#include "life ui.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define LIFE_SIZE_X (200.0f,20.0f)
#define LIFE_SIZE_Y (30.0f)

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
		m_LifeUi[nCount] = CLifeUi::Create(D3DXVECTOR3((nCount*LIFE_SIZE_X + LIFE_SIZE_X / 2) + pos.x, (pos.y - LIFE_SIZE_Y / 2), 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f));
	}
	m_Ui = CUi::Create(D3DXVECTOR3((float)(LIFE_SIZE_X*(MAX_LIFE/2)+ pos.x), (float)(pos.y - LIFE_SIZE_Y / 2),0.0f), D3DXVECTOR3((float)(LIFE_SIZE_X*(MAX_LIFE*1.5f)), LIFE_SIZE_Y*1.5,0.0f), CUi::TEXTURE_TYPE_LIFE);
	return S_OK;

}

//----------------------------------
//終了処理
//----------------------------------
void CLife::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		if (m_LifeUi[nCount] != NULL)
		{
			m_LifeUi[nCount]->Uninit();
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
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		if (nCount>=nLife)
		{
			m_LifeUi[nCount]->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
		}
		else
		{
			m_LifeUi[nCount]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		}
	}
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
