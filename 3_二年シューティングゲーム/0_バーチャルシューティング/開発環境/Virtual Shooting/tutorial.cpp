#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "inputmouse.h"
#include "fade.h"
#include "sound.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define TEXTURE_X 0.25f

//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_Texture = NULL;
char * CTutorial::pTexture = "data/TEXTURE/tutorial.png";

//----------------------------------
//コンストラクタ
//----------------------------------
CTutorial::CTutorial(int nPriorit)
{
	m_nCountTexture = 0;
}

//----------------------------------
//デストラクタ
//----------------------------------
CTutorial::~CTutorial()
{
}

//----------------------------------
//生成処理
//----------------------------------
HRESULT CTutorial::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, pTexture, &m_Texture);

	return S_OK;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
void CTutorial::Unload(void)
{
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	pTutorial->SetSizeition(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f));
	
	pTutorial->Init();

	return pTutorial;
}

//----------------------------------
//初期化処理
//----------------------------------
HRESULT CTutorial::Init(void)
{
	D3DXVECTOR2 Texture[4];
	//テクスチャ処理
	Texture[0] = D3DXVECTOR2(0.0f, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(0.0f, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X, 1.0f);

	BindTexture(m_Texture);
	//初期化処理
	CScene2d::Init();


	TextureAnim(&Texture[0]);

	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CTutorial::Uninit(void)
{
	CScene2d::Uninit();
}

//----------------------------------
//更新処理
//----------------------------------
void CTutorial::Update(void)
{
	CSound *pSound = CManager::GetSound();				//サウンド取得
	CInihMouse *pMouse = CManager::GetMouse();			//マウス取得
	CFade *pFade = CManager::GetFade();					//フェード取得	
	D3DXVECTOR2 Texture[4];								//テクスチャ

	if (pMouse->GetClickTrigger(0) == true)
	{
		if (m_nCountTexture < 3)
		{
			m_nCountTexture++;
			pSound->Play(CSound::LABEL_SE_CLICK);
		}
		else
		{
			if (pFade->Set(CManager::GAME_MODE_SELECT) == true)
			{
				pSound->Play(CSound::LABEL_SE_CLICK);
			}

		}

	}
	if (pMouse->GetClickTrigger(1) == true && m_nCountTexture>0)
	{
		m_nCountTexture--;
	}
	Texture[0] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture + TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture + TEXTURE_X, 1.0f);
	TextureAnim(&Texture[0]);
	
	CScene2d::Update();
}

//----------------------------------
//描画処理
//----------------------------------
void CTutorial::Draw(void)
{
	CScene2d::Draw();
}
