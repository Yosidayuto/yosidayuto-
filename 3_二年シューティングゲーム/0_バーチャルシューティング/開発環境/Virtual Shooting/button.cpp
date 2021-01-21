//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "button.h"			
#include "manager.h"		
#include "renderer.h"		
#include "input.h"			
#include "inputmouse.h"		
#include "text.h"			
#include "select.h"			
#include "ui.h"				
#include "number.h"			
#include "player.h"			
#include "fade.h"			
#include "score.h"			
#include "weapon_UI.h"		
#include "game.h"			
#include "telop_text.h"		
#include "sound.h"			
#include "ui count.h"
//----------------------------------
//静的メンバー変数
//----------------------------------
int CButton::nCountSpeed = 0;
CButton::BUTTON_TYPE_TEXTURE CButton::TypeTextureData[BUTTON_TYPE_MAX] =
{
	BUTTON_TYPE_TEXTURE_1,
	BUTTON_TYPE_TEXTURE_1,
	BUTTON_TYPE_TEXTURE_1,
	BUTTON_TYPE_TEXTURE_1,
	BUTTON_TYPE_TEXTURE_1,
	BUTTON_TYPE_TEXTURE_1,
};

CButton::BUTTON_DATA CButton::ButtonData[BUTTON_TYPE_TEXTURE_MAX]=
{
	"data/TEXTURE/buttonA.png","data/TEXTURE/buttonC_over.png",NULL,NULL,
	"data/TEXTURE/plateA_2.png","data/TEXTURE/plateA_2_over.png",NULL,NULL,
};
//------------------------------------
//コンストラクタ
//------------------------------------
CButton::CButton(int nPriorit) :CScene2d(nPriorit)
{
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);		//タイプ処理
	m_pText = NULL;
	m_pUi = NULL;
	m_pNumber = NULL;
	m_Text= false;
	
}

//------------------------------------
//デストラクタ
//------------------------------------
CButton::~CButton()
{
}

//------------------------------------
//生成処理
//------------------------------------
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Type)
{
	CButton *pButton;
	pButton = new CButton;
	pButton->m_pos = pos;	//位置設定
	pButton->m_size = size;	//サイズ設定
	pButton->m_Type = (BUTTON_TYPE)Type;
	pButton->SetPos(pButton->m_pos);	//位置取得
	pButton->SetSize(pButton->m_size);	//サイズ取得
	pButton->BindTexture(ButtonData[TypeTextureData[pButton->m_Type]].m_Texture);//テクスチャ設定

	pButton->Init();

	return pButton;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CButton::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < BUTTON_TYPE_TEXTURE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, ButtonData[nCount].pTexture, &ButtonData[nCount].m_Texture);
	}
	for (int nCount = 0; nCount < BUTTON_TYPE_TEXTURE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, ButtonData[nCount].pTextureOver, &ButtonData[nCount].m_TextureOver);
	}

	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CButton::Unload(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < MAX_BUTTON_TEXTURE; nCount++)
	{
		if (ButtonData[nCount].m_Texture != NULL)
		{
			ButtonData[nCount].m_Texture->Release();
			ButtonData[nCount].m_Texture = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_BUTTON_TEXTURE; nCount++)
	{
		if (ButtonData[nCount].m_TextureOver != NULL)
		{
			ButtonData[nCount].m_TextureOver->Release();
			ButtonData[nCount].m_TextureOver = NULL;
		}
	}

}

//------------------------------------
//初期化処理
//------------------------------------
HRESULT CButton::Init(void)
{
	switch (m_Type)
	{
	case BUTTON_TYPE_1:
		if (CGame::SetStage()+1 < CGame::STAGE_TYPE_3+1)
		{
			m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3 - 50, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x - 100, m_size.y, m_size.z), CText::TEXT_START);
			m_pNumber = CNumber::Create(D3DXVECTOR3(m_pos.x + 85, m_pos.y, 0.0f), D3DXVECTOR3(25.0f, m_size.y, 0.0f));
			m_pNumber->SetNumber(CGame::SetStage()+1);
		}
		else
		{
			m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3 - 50, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x - 100, m_size.y, m_size.z), CText::TEXT_START_LAST);

		}
		break;
	case BUTTON_TYPE_2:
		m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3, m_pos.y, 0.0f), m_size, CText::TEXT_LIFE);
		break;
	case BUTTON_TYPE_3:
		m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3, m_pos.y, 0.0f), m_size, CText::TEXT_SPEED);
		break;
	case BUTTON_TYPE_4:
		m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3, m_pos.y, 0.0f), m_size, CText::TEXT_BULLET);
		break;
	case BUTTON_TYPE_5:
		m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3, m_pos.y, 0.0f), m_size, CText::TEXT_LASER);
		break;
	case BUTTON_TYPE_6:
		m_pText = CText::Create(D3DXVECTOR3(m_pos.x + m_size.x / 3-20, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x-20, m_size.y, m_size.z), CText::TEXT_HOMING);

		break;

	}

	//初期化処理
	CScene2d::Init();

	return S_OK;
}

//------------------------------------
//終了処理
//------------------------------------
void CButton::Uninit(void)
{
	if (m_pText != NULL)
	{
		m_pText->Uninit();
		delete m_pText;
		m_pText = NULL;
	}
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		m_pNumber = NULL;
	}
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = NULL;
	}
	Release();
}

//------------------------------------
//更新処理
//------------------------------------
void CButton::Update(void)
{
	CSound *pSound = CManager::GetSound();				//サウンド取得
	CInihMouse *pMouse = CManager::GetMouse();			//マウス取得
	int nPlayerLife= CManager::GetPlayer(0);			//プレイヤー情報取得
	int nPlayerSpeed= CManager::GetPlayer(1);			//プレイヤー情報取得
	WEAPON_MODE nPlayerWeapon[MAX_WEAPON];
	for (int nCount = 0; nCount < 2; nCount++)
	{
		nPlayerWeapon[nCount] = CManager::GetWeapon(nCount);
	}

	CScore *pScore= CSelect::GetScore();
	CScore *pMinusScore = CSelect::GetMinusScore();
	int nScore= pScore->GetScore();
	CUiCount *pNumber;
	CWeapon_Ui *WeaponUi;
	CFade *pFade = CManager::GetFade();

	int nCount=0;
	if (m_pText != NULL)
	{
		m_pText->Update();
	}
	if (m_pUi != NULL)
	{
		m_pUi->Update();
	}
	if (m_Text == true)
	{
		CSelect::GetpTelopText()->TypeChange((CTelopText::TEXT_TYPE)0);
		pMinusScore->SetScore(0);

		m_Text = false;
	}
	//マウスポインターがボタンに乗っているか

	if (Hit(D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f), TypeTextureData[m_Type]) == true)
	{
		//ボタン判定
		switch (m_Type)
		{
		case BUTTON_TYPE_1:
			pMinusScore->SetScore(0);

			//クリックしているか
			if (pMouse->GetClickTrigger(0) == true)
			{
				//武装がどちらも装備しているか
				if (nPlayerWeapon[0] != WEAPONS_MODE_NONE
					|| nPlayerWeapon[1] != WEAPONS_MODE_NONE)
				{
					//SE音
					pSound->Play(CSound::LABEL_SE_START);
					//フェイドアウト判定
					pFade->SetFade(GAME_MODE_STAGE);
				}
			}
			break;
		case BUTTON_TYPE_2:
			//ライフの強化回数取得
			pNumber = CSelect::GetNumber(CSelect::NUMBER_TYPE_LIEF);
			//マウスポインターがボタンに乗っているか

			CSelect::GetpTelopText()->TypeChange((CTelopText::TEXT_TYPE)BUTTON_TYPE_2);
			if (nPlayerLife<5)
			{
				pMinusScore->SetScore((nPlayerLife + 2) * 1000);
			}
			if (pMouse->GetClickTrigger(0) == true)
			{
				if (nPlayerLife<5 && nScore>(nPlayerLife + 1) * 1000)
				{
					//クリック音SE
					pSound->Play(CSound::LABEL_SE_CLICK);

					nPlayerLife++;
					CManager::SetPlayer(nPlayerLife, nPlayerSpeed);
					pNumber->SetCount(nPlayerLife);
					pScore->AddScore(-(nPlayerLife + 1) * 1000);
				}
			}
			else if (pMouse->GetClickTrigger(1) == true)
			{
				if (nPlayerLife>0)
				{
					//キャンセル音SE
					pSound->Play(CSound::LABEL_SE_CANCEL);
					pScore->AddScore((nPlayerLife + 1) * 1000);
					nPlayerLife--;
					CManager::SetPlayer(nPlayerLife, nPlayerSpeed);
					pNumber->SetCount(nPlayerLife);
				}

			}


			break;
			//スピード強化
		case BUTTON_TYPE_3:
			pNumber = CSelect::GetNumber(CSelect::NUMBER_TYPE_SPEED);


			CSelect::GetpTelopText()->TypeChange((CTelopText::TEXT_TYPE)BUTTON_TYPE_3);
			if (nPlayerSpeed<5)
			{
				pMinusScore->SetScore((nPlayerSpeed + 2) * 1000);

			}
			if (pMouse->GetClickTrigger(0) == true)
			{
				if (nPlayerSpeed<5 && nScore >(nPlayerSpeed + 1) * 1000)
				{
					//クリック音SE
					pSound->Play(CSound::LABEL_SE_CLICK);

					nPlayerSpeed++;
					CManager::SetPlayer(nPlayerLife, nPlayerSpeed);
					pNumber->SetCount(nPlayerSpeed);
					pScore->AddScore(-(nPlayerSpeed + 1) * 1000);
				}
				else
				{
					//エラー音
				}
			}
			else if (pMouse->GetClickTrigger(1) == true)
			{
				if (nPlayerSpeed>0)
				{
					//キャンセル音SE
					pSound->Play(CSound::LABEL_SE_CANCEL);

					pScore->AddScore((nPlayerSpeed + 1) * 1000);

					nPlayerSpeed--;
					CManager::SetPlayer(nPlayerLife, nPlayerSpeed);
					pNumber->SetCount(nPlayerSpeed);
				}
				else
				{
					//エラー音
				}

			}


			break;
		case BUTTON_TYPE_4:
			CSelect::GetpTelopText()->TypeChange((CTelopText::TEXT_TYPE)BUTTON_TYPE_4);
			pMinusScore->SetScore(5000);
			if (pMouse->GetClickTrigger(0) == true)
			{
				if (nScore >= 5000)
				{
					for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
					{

						if (nPlayerWeapon[nCount] == WEAPONS_MODE_NONE)
						{
							//クリック音SE
							pSound->Play(CSound::LABEL_SE_CLICK);

							pScore->AddScore(-5000);
							//UI取得
							WeaponUi = CSelect::GetWeaponUi(nCount);
							//UI変更
							WeaponUi->SetUI(WEAPONS_MODE_BUTTOL);
							//武装変更
							nPlayerWeapon[nCount] = WEAPONS_MODE_BUTTOL;
							CManager::SetWeapon(nPlayerWeapon[0], nPlayerWeapon[1]);
							return;
						}
					}
				}
			}
			else if (pMouse->GetClickTrigger(1) == true)
			{
				for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
				{
					if (nPlayerWeapon[nCount] == WEAPONS_MODE_BUTTOL)
					{
						//キャンセル音SE
						pSound->Play(CSound::LABEL_SE_CANCEL);

						pScore->AddScore(5000);
						WeaponUi = CSelect::GetWeaponUi(nCount);

						WeaponUi->SetUI(WEAPONS_MODE_NONE);
						nPlayerWeapon[nCount] = WEAPONS_MODE_NONE;
						CManager::SetWeapon(nPlayerWeapon[0], nPlayerWeapon[1]);
						return;
					}
				}
			}
			break;
		case BUTTON_TYPE_5:

			CSelect::GetpTelopText()->TypeChange((CTelopText::TEXT_TYPE)BUTTON_TYPE_5);
			pMinusScore->SetScore(10000);

			if (pMouse->GetClickTrigger(0) == true)
			{
				if (nScore >= 10000)
				{
					for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
					{

						if (nPlayerWeapon[nCount] == WEAPONS_MODE_NONE)
						{
							//クリック音SE
							pSound->Play(CSound::LABEL_SE_CLICK);

							pScore->AddScore(-10000);

							//UI取得
							WeaponUi = CSelect::GetWeaponUi(nCount);

							WeaponUi->SetUI(WEAPONS_MODE_LASER);
							nPlayerWeapon[nCount] = WEAPONS_MODE_LASER;
							CManager::SetWeapon(nPlayerWeapon[0], nPlayerWeapon[1]);
							return;
						}
					}
				}
			}
			else if (pMouse->GetClickTrigger(1) == true)
			{
				for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
				{
					if (nPlayerWeapon[nCount] == WEAPONS_MODE_LASER)
					{
						//キャンセル音SE
						pSound->Play(CSound::LABEL_SE_CANCEL);

						pScore->AddScore(10000);
						WeaponUi = CSelect::GetWeaponUi(nCount);

						WeaponUi->SetUI(WEAPONS_MODE_NONE);
						nPlayerWeapon[nCount] = WEAPONS_MODE_NONE;
						CManager::SetWeapon(nPlayerWeapon[0], nPlayerWeapon[1]);
						return;
					}
				}
			}
			break;
		case BUTTON_TYPE_6:

			CSelect::GetpTelopText()->TypeChange((CTelopText::TEXT_TYPE)BUTTON_TYPE_6);
			pMinusScore->SetScore(15000);
			if (pMouse->GetClickTrigger(0) == true)
			{
				if (nScore >= 15000)
				{
					for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
					{
						if (nPlayerWeapon[nCount] == WEAPONS_MODE_NONE)
						{
							//クリック音SE
							pSound->Play(CSound::LABEL_SE_CLICK);

							pScore->AddScore(-15000);

							//UI取得
							WeaponUi = CSelect::GetWeaponUi(nCount);

							WeaponUi->SetUI(WEAPONS_MODE_HOMING);
							nPlayerWeapon[nCount] = WEAPONS_MODE_HOMING;
							CManager::SetWeapon(nPlayerWeapon[0], nPlayerWeapon[1]);
							return;
						}
					}
				}
			}
			else if (pMouse->GetClickTrigger(1) == true)
			{
				for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
				{
					if (nPlayerWeapon[nCount] == WEAPONS_MODE_HOMING)
					{
						//キャンセル音SE
						pSound->Play(CSound::LABEL_SE_CANCEL);

						pScore->AddScore(15000);
						WeaponUi = CSelect::GetWeaponUi(nCount);

						WeaponUi->SetUI(WEAPONS_MODE_NONE);
						nPlayerWeapon[nCount] = WEAPONS_MODE_NONE;
						CManager::SetWeapon(nPlayerWeapon[0], nPlayerWeapon[1]);
						return;
					}
				}
			}
			break;
		}
	}

	CScene2d::Update();

}

//------------------------------------
//描画処理
//------------------------------------
void CButton::Draw(void)
{
	CScene2d::Draw();
	if (m_pText != NULL)
	{
		m_pText->Draw();
	}
	if (m_pUi != NULL)
	{
		m_pUi->Draw();
	}
	if (m_pNumber != NULL)
	{
		m_pNumber->Draw();
	}
}



bool CButton::Hit(D3DXVECTOR3 pos, int nType)
{
	if (pos.x > m_pos.x - m_size.x / 2
		&& pos.x  < m_pos.x + m_size.x / 2
		&& pos.y > m_pos.y - m_size.y / 2
		&& pos.y < m_pos.y + m_size.y / 2)
	{
		BindTexture(ButtonData[nType].m_TextureOver);
		m_Text = true;
		return true;
	}
	else
	{
		BindTexture(ButtonData[nType].m_Texture);

		return false;
	}
}

