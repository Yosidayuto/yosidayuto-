//=============================================================================
//
//	プレイヤーデータ[player data.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player data.h"

//=============================================================================
// コンストラクト
//=============================================================================
CPlayerData::CPlayerData()
{
	m_nLifeData = 0;
	m_fSpeedData = 0.0f;
	m_WeaponData.Left = WEAPONS_MODE_BUTTOL;
	m_WeaponData.Right = WEAPONS_MODE_NONE;

}

//=============================================================================
// デストラクト
//=============================================================================
CPlayerData::~CPlayerData()
{
}


//=============================================================================
// 生成処理
//=============================================================================
CPlayerData* CPlayerData::Create(void)
{
	CPlayerData* pPlayerData = NULL;
	pPlayerData = new CPlayerData;

	return pPlayerData;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayerData::Uninit(void)
{
	delete this;
}

//=============================================================================
// ライフデータセッター
//=============================================================================
void CPlayerData::SetLifeData(int nLife)
{
	m_nLifeData = nLife;
}

//=============================================================================
// スピードデータセッター
//=============================================================================
void CPlayerData::SetSpeedData(float fSpeed)
{
	m_fSpeedData = fSpeed;
}

//=============================================================================
// ウェポンデータセッター
//=============================================================================
void CPlayerData::SetWeaponData(WEAPON_DATA wepon)
{
	m_WeaponData = wepon;
}

//=============================================================================
// ライフデータゲッター
//=============================================================================
int CPlayerData::GetLifeData(void)
{
	return m_nLifeData;
}

//=============================================================================
// スピードデータゲッター
//=============================================================================
float CPlayerData::GetSpeedData(void)
{
	return m_fSpeedData;
}

//=============================================================================
// ウェポンデータゲッター	
//=============================================================================
WEAPON_DATA CPlayerData::GetWeaponData(void)
{
	return m_WeaponData;
}
