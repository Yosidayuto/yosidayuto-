#include "telop_text.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//----------------------------------------------
//静的メンバー変数
//----------------------------------------------
LPDIRECT3DTEXTURE9 CTelopText::m_apTexture[TEXT_TYPE_MAX] = {};
char *CTelopText::m_pText[TEXT_TYPE_MAX]=
{
	"data/TEXTURE/Telop_Normal.png",
	"data/TEXTURE/Telop_LifeUp.png",
	"data/TEXTURE/Telop_SpeedUp.png",
	"data/TEXTURE/Telop_Bullet.png",
	"data/TEXTURE/Telop_Laser.png",
	"data/TEXTURE/Telop_Homing.png",
};
//------------------------------------
//コンストラクタ
//------------------------------------
CTelopText::CTelopText(int nPriorit) :CScene(nPriorit)
{
	//ポリゴンの初期化
	m_apScene2D = NULL;
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_Type = TEXT_TYPE_TUTORIAL;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
}

//------------------------------------
//デストラクタ
//------------------------------------
CTelopText::~CTelopText()
{
}

//------------------------------------
//テクスチャ読み込み
//------------------------------------
HRESULT CTelopText::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < TEXT_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, m_pText[nCount], &m_apTexture[nCount]);
	}

	return S_OK;
}

//------------------------------------
//テクスチャの破棄
//------------------------------------
void CTelopText::Unload(void)
{
	for (int nCount = 0; nCount < TEXT_TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}

	}
}

//------------------------------------
//生成処理
//------------------------------------
CTelopText * CTelopText::Create(void)
{
	CTelopText *pCelopText;
	pCelopText = new CTelopText;
	pCelopText->Init();
	return pCelopText;
}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CTelopText::Init(void)
{
	//メモリ確保
	m_apScene2D = new CScene2d;
	//位置
	m_apScene2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 455, 20, 0.0f));
	//サイズ
	m_apScene2D->SetSize(D3DXVECTOR3(775, 40, 0.0f));
	//初期化処理
	m_apScene2D->CScene2d::Init();
	//テクスチャの設定
	m_apScene2D->BindTexture(m_apTexture[m_Type]);
	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CTelopText::Uninit(void)
{
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CTelopText::Update(void)
{
	D3DXVECTOR2 Texture[4];
	m_apScene2D->CScene2d::Update();
	if (m_Type == TEXT_TYPE_TUTORIAL)
	{
		Texture[0] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f),0.0f);
		Texture[1] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 0.0f);
		Texture[2] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f), 1.0f);
		Texture[3] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 1.0f);
		m_apScene2D->TextureAnim(Texture);
		//アニメーションカウント
		m_nCounterAnim++;
		if (m_nCounterAnim >=1)
		{
			//アニメーションの絵を次の絵に変える
			m_nPatternAnim++;

			m_nCounterAnim = 0;
			if (m_nPatternAnim >= 10000)
			{
				m_nPatternAnim = 0;
			}
		}
	}
}

//------------------------------------
//描画処理
//------------------------------------
void CTelopText::Draw(void)
{
	m_apScene2D->CScene2d::Draw();
}

//------------------------------------
//テキスト変更
//------------------------------------
void CTelopText::TypeChange(TEXT_TYPE Type)
{
	D3DXVECTOR2 Texture[4];
	m_Type = Type;

	
	
	if (m_Type == TEXT_TYPE_TUTORIAL)
	{
		Texture[0] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f), 0.0f);
		Texture[1] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f) + (1.0f / 6.0f), 0.0f);
		Texture[2] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f), 1.0f);
		Texture[3] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f) + (1.0f / 6.0f), 1.0f);
	}
	else
	{
		Texture[0] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f), 0.0f);
		Texture[1] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f) + (1.0f / 1.0f), 0.0f);
		Texture[2] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f), 1.0f);
		Texture[3] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f) + (1.0f / 1.0f), 1.0f);
	}

	//テクスチャの設定
	m_apScene2D->BindTexture(m_apTexture[m_Type]);

	//テクスチャの設定
	m_apScene2D->TextureAnim(Texture);


}
