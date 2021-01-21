//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "weapon_UI.h"
#include "manager.h"
#include "renderer.h"
#include "ui.h"
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CWeapon_Ui::m_Texture = NULL;
//------------------------------------
//コンストラクタ
//------------------------------------
CWeapon_Ui::CWeapon_Ui(int nPriorit)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pUi = NULL;
}

//------------------------------------
//デストラクタ
//------------------------------------
CWeapon_Ui::~CWeapon_Ui()
{
}

//------------------------------------
//生成処理
//------------------------------------
CWeapon_Ui * CWeapon_Ui::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, WEAPON_MODE Type)
{
	CWeapon_Ui *pWeaponUi;
	pWeaponUi = new CWeapon_Ui;	
	pWeaponUi->m_pos = pos;		//位置設定
	pWeaponUi->m_size = size;	//サイズ設定
	pWeaponUi->m_Type = Type;
	pWeaponUi->SetPos(pWeaponUi->m_pos);		//位置取得
	pWeaponUi->SetSize(pWeaponUi->m_size);		//サイズ取得
	pWeaponUi->BindTexture(pWeaponUi->m_Texture);	//テクスチャ設定
	pWeaponUi->Init();
	return pWeaponUi;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CWeapon_Ui::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_WeaponFrame.png", &m_Texture);

	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CWeapon_Ui::Unload(void)
{
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CWeapon_Ui::Init(void)
{

	switch (m_Type)
	{
	case WEAPONS_MODE_BUTTOL:
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_BULLET);
		break;
	case WEAPONS_MODE_LASER:
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_LASER);
		break;
	case WEAPONS_MODE_HOMING:
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_HOMING);
		break;

	}
	//初期化処理
	CScene2d::Init();


	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CWeapon_Ui::Uninit(void)
{
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = NULL;
	}
	CScene2d::Uninit();

}

//------------------------------------
//更新処理
//------------------------------------
void CWeapon_Ui::Update(void)
{

	switch (m_Type)
	{
	case WEAPONS_MODE_NONE:
		if (m_pUi != NULL)
		{
			m_pUi->Uninit();
			m_pUi = NULL;
		}
		break;
	case WEAPONS_MODE_BUTTOL:
		if (m_pUi != NULL)
		{
			return;
		}
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_BULLET);

		break;
	case WEAPONS_MODE_LASER:
		if (m_pUi != NULL)
		{
			return;
		}
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_LASER);
		break;
	case WEAPONS_MODE_HOMING:
		if (m_pUi != NULL)
		{
			return;
		}
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_HOMING);
		break;

	}
}

//------------------------------------
//描画処理
//------------------------------------
void CWeapon_Ui::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	CScene2d::Draw();
	
	if (m_pUi != NULL)
	{
		m_pUi->Draw();
	}
}

void CWeapon_Ui::SetUI(WEAPON_MODE Type)
{
	m_Type = Type;
}

