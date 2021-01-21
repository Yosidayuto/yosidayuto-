//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "Background.h"	//背景ファイル
#include "scene2d.h"	//シーン２D（2Dポリゴン）ファイル
#include "manager.h"	//マネージャーファイル
#include "renderer.h"	//レンダリングファイル	

//----------------------------------
//マクロ定義
//----------------------------------

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
CBg::DATA CBg::m_Data[MAX_BG] =
{
	{ D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(800, SCREEN_HEIGHT , 0.0f) },
	{ D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(800, SCREEN_HEIGHT , 0.0f) },

};
char *CBg::m_dTexture[MAX_BG]=
{
	"data/TEXTURE/background_game_0.png",
	"data/TEXTURE/background_game_1.png",
};
//------------------------------------
//コンストラクタ
//------------------------------------
CBg::CBg(int nPriorit) :CScene(nPriorit)
{
	//アニメーションパターンの初期化
	for (int nCountBg = 0; nCountBg < MAX_PATTERN; nCountBg++)
	{
		m_nPatternAnim[nCountBg] = 0;		
	}
	//ポリゴンの初期化
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg] = NULL;		
	}
	//アニメーションカウント初期化
	m_nCounterAnim = 0;		

	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);


}

//------------------------------------
//デストラクタ
//------------------------------------
CBg::~CBg()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CBg::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	for (int nCont = 0; nCont < MAX_BG; nCont++)
	{
		D3DXCreateTextureFromFile(pDevice, m_dTexture[nCont], &m_apTexture[nCont]);
	}
	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CBg::Unload(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
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
CBg * CBg::Create(void)
{
	CBg *pBg;
	pBg = new CBg;
	pBg->Init();
	return pBg;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CBg::Init(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		//メモリ確保
		m_apScene2D[nCountBg] = new CScene2d (0);
		//位置
		m_apScene2D[nCountBg]->SetPos(m_Data[nCountBg].m_Pos);
		//サイズ
		m_apScene2D[nCountBg]->SetSize(m_Data[nCountBg].m_Size);
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
void CBg::Uninit(void)
{
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CBg::Update(void)
{
	D3DXVECTOR2 Texture1[4];
	D3DXVECTOR2 Texture2[4];
	Texture1[0] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f));
	Texture1[1] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f));
	Texture1[2] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f)+ (1.0f / 1.0f));
	Texture1[3] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f)+ (1.0f / 1.0f));
	
	Texture2[0] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f));
	Texture2[1] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f));
	Texture2[2] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f) + (1.0f / 1.0f));
	Texture2[3] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f) + (1.0f / 1.0f));





	m_apScene2D[0]->TextureAnim(Texture1);
	m_apScene2D[1]->TextureAnim(Texture2);
	
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim % 2)
	{
		//アニメーションの絵を次の絵に変える
		m_nPatternAnim[0]++;
		m_nPatternAnim[1]++;

		m_nCounterAnim = 0;
		if (m_nPatternAnim[0] >= 100)
		{
			m_nPatternAnim[0] = 0;
		}
		if (m_nPatternAnim[1] >= 1000)
		{
			m_nPatternAnim[1] = 0;
		}
	}


	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->CScene2d::Update();
	}
}

//------------------------------------
//描画処理
//------------------------------------
void CBg::Draw(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->CScene2d::Draw();
	}
}

