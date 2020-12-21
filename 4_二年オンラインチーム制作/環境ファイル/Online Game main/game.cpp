//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 俵谷 健太郎　吉田 悠人
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "polygon.h"
#include "mouse_pointer.h"
#include "communication.h"
#include "manager.h"
#include "fade.h"
#include "turn wait.h"
#include "ui.h"
#include "death.h"
#include "die screen.h"
#include "sound.h"
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CCommunication * CGame::pCommunication = NULL;
CPolygon * CGame::pPolgon = NULL;
bool CGame::m_bLoad = false;
bool CGame::m_bPlayerDie[4] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	//変数初期化
	Mode = MODE_CONTINUE;					
	m_bSelect = false;						
	m_nTouch = MAX_NUMBER;
	CommuMode = COMMUNICATTION_MODE_GAME;
	m_pUi = NULL;
	m_pDieScreen = NULL;
	for (int nCount = 0; nCount < 4; nCount++)
	{
		m_bPlayerDie[nCount] = false;
	}
	m_bLoad = false;
	pCommunication = NULL;
	pPolgon = NULL;

}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 作成処理
//=============================================================================
CGame * CGame::Create(D3DXVECTOR3 size)
{
	CGame *pGame;
	//インスタンス生成
	pGame = new CGame;

	//初期化処理
	if (pGame != NULL)
	{
		pGame->Init(size);
	}

	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 size)
{
	//背景生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//通信データの取得
	pCommunication = CManager::GetCommunication();
	//牙の生成
	pPolgon = CPolygon::Create(D3DXVECTOR3(TEXTURE_WIDTH, TEXTURE_HEIGHT, 0.0f));
	//マウスポインター生成
	CPointer::Create();

	//UI
	//枠
	CUi::Create(D3DXVECTOR3(150, 75, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_1P);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 150, 75, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_2P);
	CUi::Create(D3DXVECTOR3(150, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_3P);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_4P);


	//キャラクター
	CUi::Create(D3DXVECTOR3(75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_CAT);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DOG);
	CUi::Create(D3DXVECTOR3(75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_RABBIT);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_SQUIRREL);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	CSound *pSound = CManager::GetSound();
	//ゲーム状況
	switch (CommuMode)
	{
	case COMMUNICATTION_MODE_GAME:
		//決着がついたか
		if (pCommunication->GetMode() != MODE_CONTINUE)
		{
			//決着がついた場合
			pCommunication->SetMode(MODE_SETTLED);
			CommuMode = COMMUNICATTION_MODE_WINNER;
		}
		else
		{
			//つかなかった場合
			CommuMode = COMMUNICATTION_MODE_TURN;
		}
		break;

	case COMMUNICATTION_MODE_TURN:
		//プレイヤー一人ひとりの生存確認
		if (pCommunication->GetnDie()!=-1)
		{
			//プレイヤー１の処理
			if (pCommunication->GetnDie() == 0 && m_bPlayerDie[0] == false)
			{
				m_bPlayerDie[0] = true;
				CUi::Create(D3DXVECTOR3(75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
			//プレイヤー２の処理
			if (pCommunication->GetnDie() == 1 && m_bPlayerDie[1] == false)
			{
				m_bPlayerDie[1] = true;
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
			//プレイヤー３の処理
			if (pCommunication->GetnDie() == 2 && m_bPlayerDie[2] == false)
			{
				m_bPlayerDie[2] = true;
				CUi::Create(D3DXVECTOR3(75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
			//プレイヤー４の処理
			if (pCommunication->GetnDie() == 3 && m_bPlayerDie[3] == false)
			{
				m_bPlayerDie[3] = true;
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
		}
		//勝敗が決まったか判定
		if (pCommunication->GetbRecv() == true)
		{
			//UIの消去
			if (m_pUi != NULL)
			{
				m_pUi->Uninit();
				m_pUi = NULL;
			}
			//ゲームモード処理
			CommuMode = COMMUNICATTION_MODE_GAME;
			pCommunication->SetbRecv();

		}
		//自分が死んだときの画面演出
		if (pCommunication->GetbPlayer() == false)
		{
			if (m_pDieScreen==NULL)
			{
				//死んだ演出
				m_pDieScreen = CDieScreen::Create();
				//噛みつきSE
				pSound->Play(CSound::SOUND_LABEL_SE_BYTE);
				//死亡アニメーション
				CDeath::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));

			}

		}

		//自分のターン
		if (pCommunication->GetnPlayer() == 0)
		{
			//ターン表示のUI
			if (m_pUi == NULL)
			{
				m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0), D3DXVECTOR3(650, 100, 0), CUi::TEX_YOUTRUN);
			}
			if (pCommunication->GetbPlayer() == true)//生きてる場合
			{
				//選んだ歯を代入
				int nTooth = pPolgon->Touch();
				if (m_nTouch != CPolygon::GetTooth())
				{
					if (CCommunication::GetabTooth(nTooth) == true)
					{
						//掃除SE
						pSound->Play(CSound::SOUND_LABEL_SE_CLEAN);		
						pCommunication->PicPlayer(nTooth);
						m_nTouch = CPolygon::GetTooth();

						//情報受信
						if (m_bLoad == false)
						{
							std::thread thWorker(Load);
							thWorker.detach();
						}
					}
				}
			}
			else//死んでる場合
			{

				//選択した歯をを送る
				pCommunication->PicPlayer(-1);
				if (m_bLoad == false)
				{
					std::thread thWorker(Load);
					thWorker.detach();
				}
			}
		}
		//自分以外のターン
		else
		{
			//ターン表示のUI
			if (m_pUi == NULL&&m_pDieScreen==NULL)
			{
				m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0), D3DXVECTOR3(700, 100, 0), CUi::TEX_WAIT);
			}

			if (m_bLoad == false)
			{
				std::thread thWorker(Load);
				thWorker.detach();
			}

		}
		break;
		//勝利判定
	case COMMUNICATTION_MODE_WINNER:
		//勝者
		if (pCommunication->GetMode() == MODE_SETTLED)
		{
			CFade *pFade = CManager::GetFade();
			pCommunication->Winner();
			pFade->SetFade(CManager::MODE_RESULT);
		}
		break;


	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// ロード処理
//=============================================================================
void CGame::Load(void)
{
	//ロード処理を開始
	m_bLoad = true;
	//情報受信
	pCommunication->RecvPlayer();
	//受信した歯の処理
	if (CCommunication::GetnTooth() != -1)
	{
		pPolgon->TouchCol(CCommunication::GetnTooth());
	}
	//ロード処理終了
	m_bLoad = false;
}

//=============================================================================
// プレイヤーが死んでいるかの確認関数
//=============================================================================
bool CGame::GetPlayerDie(int nPlayer)
{
	return m_bPlayerDie[nPlayer];
}


