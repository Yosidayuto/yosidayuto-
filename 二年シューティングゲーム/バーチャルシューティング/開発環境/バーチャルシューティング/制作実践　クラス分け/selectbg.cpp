//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "selectbg.h"	//セレクト背景ファイル
#include "scene2d.h"	//シーン２D（2Dポリゴン）ファイル
#include "manager.h"	//マネージャーファイル
#include "renderer.h"	//レンダリングファイル	

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CSelectBg::m_apTexture[MAX_SELECT_BG] = {};
CSelectBg::SELECT_DATA CSelectBg::m_Data[MAX_SELECT_BG] =
{
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT , 0.0f) },
	{ D3DXVECTOR3(SCREEN_WIDTH /2+150, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(SCREEN_WIDTH-320, SCREEN_HEIGHT -220, 0.0f) },
};
char *CSelectBg::m_dTexture[MAX_SELECT_BG] =
{
	"data/TEXTURE/background_Select.png",
	"data/TEXTURE/Select_status.png",
};

//------------------------------------
//コンストラクタ
//------------------------------------
CSelectBg::CSelectBg(int nPriorit) :CScene(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//デストラクタ
//------------------------------------
CSelectBg::~CSelectBg()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CSelectBg::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	for (int nCont = 0; nCont < MAX_SELECT_BG; nCont++)
	{
		D3DXCreateTextureFromFile(pDevice, m_dTexture[nCont], &m_apTexture[nCont]);
	}
	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CSelectBg::Unload(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCountBg] != NULL)
		{
			m_apTexture[nCountBg]->Release();
			m_apTexture[nCountBg] = NULL;
		}
	}

}

//------------------------------------
//生成処理
//------------------------------------
CSelectBg * CSelectBg::Create(void)
{
	CSelectBg *pSelectBg;
	pSelectBg = new CSelectBg;
	pSelectBg->Init();
	return pSelectBg;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CSelectBg::Init(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		//メモリ確保
		m_apScene2D[nCountBg] = new CScene2d(0);
		//位置
		m_apScene2D[nCountBg]->SetPosition(m_Data[nCountBg].m_Pos);
		//サイズ
		m_apScene2D[nCountBg]->SetSizeition(m_Data[nCountBg].m_Size);
		//初期化処理
		m_apScene2D[nCountBg]->CScene2d::Init();
		//テクスチャの設定
		m_apScene2D[nCountBg]->BindTexture(m_apTexture[nCountBg]);
	}

	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CSelectBg::Uninit(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		if (m_apScene2D[nCountBg] != NULL)
		{
			m_apScene2D[nCountBg]->CScene2d::Uninit();
			m_apScene2D[nCountBg] = NULL;
		}
	}
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CSelectBg::Update(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->CScene2d::Update();
	}

}

//------------------------------------
//描画処理
//------------------------------------
void CSelectBg::Draw(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		if (m_apScene2D[nCountBg] != NULL)
		{
			m_apScene2D[nCountBg]->CScene2d::Draw();
		}
	}

}
