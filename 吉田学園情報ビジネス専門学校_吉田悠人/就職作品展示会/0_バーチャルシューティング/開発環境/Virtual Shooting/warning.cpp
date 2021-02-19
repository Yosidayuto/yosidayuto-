//警告
#include "renderer.h"
#include "manager.h"
#include "warning.h"
#include "sound.h"
//----------------------------------
//静的メンバー変数
//----------------------------------
CWarning::ANIME_DATA CWarning::WarningAnim =
{
	NULL,"data/TEXTURE/Warning.png",20,2,false,
};

//----------------------------------
//コンストラクタ
//----------------------------------
CWarning::CWarning(int nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
	nStopCount = 0;
}

//----------------------------------
//デストラクタ
//----------------------------------
CWarning::~CWarning()
{
}


//----------------------------------
//生成処理
//----------------------------------
CWarning * CWarning::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size)
{
	CWarning *pWarning;

	pWarning = new CWarning;
	pWarning->SetPos(Pos);
	pWarning->Init(size);

	return pWarning;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CWarning::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, WarningAnim.pTextName, &WarningAnim.pTexture);
	return S_OK;

}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CWarning::Unload(void)
{
	//テクスチャの破棄
	if (WarningAnim.pTexture != NULL)
	{
		WarningAnim.pTexture->Release();
		WarningAnim.pTexture = NULL;
	}

}

HRESULT CWarning::Init(D3DXVECTOR3 size)
{
	CSound *pSound = CManager::GetSound();	//サウンド取得
	//サウンド再生
	pSound->Play(CSound::LABEL_SE_WARNING);

	D3DXVECTOR2 Texture[4];
	//サイズ
	SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));

	//初期化処理
	CScene2d::Init();
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1.0f);

	TextureAnim(Texture);

	//テクスチャの設定
	BindTexture(WarningAnim.pTexture);

	return S_OK;
}

//----------------------------------
//初期化処理
//----------------------------------
void CWarning::Uninit(void)
{
	//終了処理
	CScene2d::Uninit();
}

//----------------------------------
//終了処理
//----------------------------------
void CWarning::Update(void)
{
	D3DXVECTOR2 Texture[4];

	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1);

	TextureAnim(Texture);
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim >= WarningAnim.nCountAnime)
	{
		//アニメーションの絵を次の絵に変える
		m_nCounterAnim = 0;
		
		if (m_nPatternAnimX !=14)
		{
			m_nPatternAnimX++;
		}
		else
		{
			nStopCount++;
			if (nStopCount >= 50)
			{
				m_nPatternAnimX++;
			}
		}
		if (m_nPatternAnimX == WarningAnim.MaxCount)
		{
			m_nPatternAnimX = 0;
			if (WarningAnim.bLoop == false)
			{
				Uninit();
			}
		}
	}

}

//----------------------------------
//更新処理
//----------------------------------
void CWarning::Draw(void)
{
	//描画処理
	CScene2d::Draw();
}
