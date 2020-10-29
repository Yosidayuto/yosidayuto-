//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "select.h"		//セレクト
#include "selectbg.h"	//セレクト画面背景
#include "button.h"		//ボタンヘッダー
#include "window.h"		//ウィンドウヘッダー
#include "score.h"		//スコアヘッダー
#include "number.h"		//ナンバーヘッダー
#include "weapon_UI.h"	//武器UIヘッダー
#include "telop_bar.h"	//テロップバーヘッダー
#include "telop_text.h"	//テロップテキストヘッダー
#include "mouse pointer.h"	//マウスポインター
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
CNumber *CSelect::Number[MAX_NUMBER]=
{
	NULL,NULL
};
//---------------------------------
//コンストラクタ
//---------------------------------
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

//---------------------------------
//デストラクタ
//---------------------------------
CSelect::~CSelect()
{
}

//---------------------------------
//生成処理
//---------------------------------
CSelect * CSelect::Create(void)
{
	CSelect *pSelect;
	pSelect = new CSelect;
	pSelect->Init();
	return pSelect;
}

//---------------------------------
//初期化処理
//---------------------------------
HRESULT CSelect::Init(void)
{
	//追加マウスカーソル非表示
	ShowCursor(false);


	//テクスチャの読み込み
	CSelectBg::Load();		//背景
	CWeapon_Ui::Load();
	//クリエイト処理
	m_pButton[0]=CButton::Create(D3DXVECTOR3(140,150,0.0f), D3DXVECTOR3(270.0f,35.0f,0.0f), CButton::BUTTON_TYPE_1);
	m_pButton[1]=CButton::Create(D3DXVECTOR3(140, 250, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_2);
	m_pButton[2]=CButton::Create(D3DXVECTOR3(140, 300, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_3);
	m_pButton[3]=CButton::Create(D3DXVECTOR3(140, 350, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_4);
	m_pButton[4] = CButton::Create(D3DXVECTOR3(140, 400, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_5);
	m_pButton[5] = CButton::Create(D3DXVECTOR3(140, 450, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), CButton::BUTTON_TYPE_6);

	m_pWindowUi[0]=CWeapon_Ui::Create(D3DXVECTOR3(1000, 400, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CManager::GetWeapon(0));
	m_pWindowUi[1]= CWeapon_Ui::Create(D3DXVECTOR3(1150, 400, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CManager::GetWeapon(1));
	
	Number[NUMBER_TYPE_LIEF] = CNumber::Create(D3DXVECTOR3(580.0f,225.0f,0.0f), D3DXVECTOR3(25.0f,50.0f,0.0f));
	Number[NUMBER_TYPE_LIEF]->SetNumber(CManager::GetPlayer(NUMBER_TYPE_LIEF));
	Number[NUMBER_TYPE_SPEED] = CNumber::Create(D3DXVECTOR3(580.0f, 465.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_SPEED]->SetNumber(CManager::GetPlayer(NUMBER_TYPE_SPEED));
	m_pScore = CScore::Create(D3DXVECTOR3(35.0f,585.0f,0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pScore ->AddScore(CManager::GetScore());
	m_pWindow=CWindow::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f), D3DXVECTOR3(500, 400,0.0f), CWindow::WINDOW_TYPE_SELECT);
	CTelopBer::Create();
	CSelectBg::Create();
	m_pTelopText=CTelopText::Create();
	m_pMinusScore = CScore::Create(D3DXVECTOR3(35.0f, 500.0f, 0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pMinusScore->ColChange(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	CPointer::Create(CPointer::POINTER_TYPE_SELECR);
	return S_OK;

}

//---------------------------------
//終了処理
//---------------------------------
void CSelect::Uninit(void)
{
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
	CSelectBg::Unload();	//背景
	Release();
}

//---------------------------------
//更新処理
//---------------------------------
void CSelect::Update(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (Number[nCount] != NULL)
		{
			Number[nCount]->Update();
		}
	}

}

//---------------------------------
//描画処理
//---------------------------------
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
CNumber * CSelect::GetNumber(NUMBER_TYPE NumberType)
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


