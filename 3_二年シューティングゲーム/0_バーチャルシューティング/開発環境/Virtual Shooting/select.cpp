//=============================================================================
//
// セレクト処理 [select.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "select.h"		
#include "select bg.h"	
#include "button.h"		
#include "window.h"		
#include "score.h"		
#include "number.h"		
#include "weapon_UI.h"	
#include "telop_bar.h"	
#include "telop_text.h"	
#include "mouse pointer.h"
#include "start button.h"
#include "inputmouse.h"
#include "sound.h"
#include "fade.h"
#include "ui count.h"
//----------------------------------
//静的メンバー変数
//----------------------------------
CScore * CSelect::m_pScore = NULL;
CScore * CSelect::m_pMinusScore = NULL;
CTelopText * CSelect::m_pTelopText = NULL;
CWeapon_Ui*CSelect::m_pWindowUi[2]=
{
	NULL,NULL
};
CUiCount *CSelect::Number[MAX_NUMBER]=
{
	NULL,NULL
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSelect::CSelect()
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{	
		Number[nCount] = NULL;
	}
	for (int nCount = 0; nCount < 6; nCount++)
	{
		m_pButton[nCount] = NULL;
	}
	m_pTelopText = NULL;
	m_pMinusScore = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSelect::~CSelect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSelect::Init(void)
{
	CSound*	pSound = CManager::GetSound();	//サウンド取得
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_SELECT);

	//追加マウスカーソル非表示
	ShowCursor(false);
	//クリエイト処理
	m_pButton[0]=CButton::Create(D3DXVECTOR3(140,150,0.0f), D3DXVECTOR3(270.0f,35.0f,0.0f), CButton::BUTTON_TYPE_1);
	m_pButton[1]=CButton::Create(D3DXVECTOR3(140, 250, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_2);
	m_pButton[2]=CButton::Create(D3DXVECTOR3(140, 300, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_3);
	m_pButton[3]=CButton::Create(D3DXVECTOR3(140, 350, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_4);
	m_pButton[4] = CButton::Create(D3DXVECTOR3(140, 400, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_5);
	m_pButton[5] = CButton::Create(D3DXVECTOR3(140, 450, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_6);

	m_pWindowUi[0]=CWeapon_Ui::Create(D3DXVECTOR3(1000, 400, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CManager::GetWeapon(0));
	m_pWindowUi[1]= CWeapon_Ui::Create(D3DXVECTOR3(1150, 400, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CManager::GetWeapon(1));
	
	m_pScore = CScore::Create(D3DXVECTOR3(35.0f,585.0f,0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pScore ->AddScore(CManager::GetScore());
	m_pWindow=CWindow::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f), D3DXVECTOR3(500, 400,0.0f), CWindow::WINDOW_TYPE_SELECT);
	CTelopBer::Create();
	CSelectBg::Create();
	m_pTelopText=CTelopText::Create();
	m_pMinusScore = CScore::Create(D3DXVECTOR3(35.0f, 500.0f, 0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pMinusScore->ColChange(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	CPointer::Create(CPointer::POINTER_TYPE_SELECR);
	Number[NUMBER_TYPE_LIEF] = CUiCount::Create(D3DXVECTOR3(580.0f, 225.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_LIEF]->SetCount(CManager::GetPlayer(NUMBER_TYPE_LIEF));
	Number[NUMBER_TYPE_SPEED] = CUiCount::Create(D3DXVECTOR3(580.0f, 465.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_SPEED]->SetCount(CManager::GetPlayer(NUMBER_TYPE_SPEED));

	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void CSelect::Uninit(void)
{
	//サウンド取得
	CSound*	pSound = CManager::GetSound();
	//サウンド停止
	pSound->Stop();

	for (int nCount = 0; nCount < 6; nCount++)
	{
		if (m_pButton[nCount] != NULL)
		{
			m_pButton[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (Number[nCount]!=NULL)
		{
			Number[nCount]->Uninit();
			Number[nCount] = NULL;
		}
	}
	if (m_pScore != NULL)
	{
		CManager::SetScore(m_pScore->GetScore());
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	//シーン破棄
	CScene::ReleaseAll();

}

//=============================================================================
// 更新処理
//=============================================================================
void CSelect::Update(void)
{
	//CSound*		pSound	= CManager::GetSound();	//サウンド取得
	//CInihMouse*	pMouse	= CManager::GetMouse();	//マウス取得
	//CFade*		pFade	= CManager::GetFade();	//フェイド取得
	//CScore*		pMinusScore = CSelect::GetMinusScore();

	//WEAPON_MODE nPlayerWeapon[MAX_WEAPON];
	//for (int nCount = 0; nCount < 2; nCount++)
	//{
	//	nPlayerWeapon[nCount] = CManager::GetWeapon(nCount);
	//}

	//if (m_pStartButton->Hit()==true)
	//{
	//	pMinusScore->SetScore(0);

	//	//クリックしているか
	//	if (pMouse->GetClickTrigger(0) == true)
	//	{
	//		//武装がどちらも装備しているか
	//		if (nPlayerWeapon[0] != WEAPONS_MODE_NONE
	//			|| nPlayerWeapon[1] != WEAPONS_MODE_NONE)
	//		{
	//			//SE音
	//			pSound->Play(CSound::LABEL_SE_START);
	//			//フェイドアウト判定
	//			pFade->SetFade(GAME_MODE_STAGE);
	//		}
	//	}
	//}


	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (Number[nCount] != NULL)
		{
			Number[nCount]->Update();
		}
	}

}

//=============================================================================
// 描画関数
//=============================================================================
void CSelect::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (Number[nCount] != NULL)
		{
			Number[nCount]->Draw();
		}
	}
}
//---------------------------------
//ゲットナンバー
//---------------------------------
CUiCount * CSelect::GetNumber(NUMBER_TYPE NumberType)
{
	return Number[NumberType];
}

CWeapon_Ui * CSelect::GetWeaponUi(int nWeaponUi)
{
	return m_pWindowUi[nWeaponUi];
}

CScore * CSelect::GetScore(void)
{
	return m_pScore;
}

CScore * CSelect::GetMinusScore(void)
{
	return m_pMinusScore;
}


