//=============================================================================
//
// 牙の並び計算処理 [polygon.cpp]
// Author : 俵谷 健太郎
//
//=============================================================================

#include "polygon.h"
#include "tooth.h"
#include "manager.h"
#include "input_mouse.h"
#include "clean.h"
#include "game.h"
#include "communication.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
int CPolygon::nCountTooth = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon::CPolygon()
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			m_apTooth[nCount] = NULL;
		}
	}
	nCountTooth = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
// 作成処理
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 size)
{
	CPolygon *pPolygon;
	//インスタンス生成
	pPolygon = new CPolygon;

	//初期化処理
	if (pPolygon != NULL)
	{
		pPolygon->Init(size);
	}

	return pPolygon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] == NULL)
		{
			//左上5個,右上5個,下10個
			if (nCount < 5)
			{															//歯同士の間隔	　X軸											 　Y軸
				m_apTooth[nCount] = CTooth::Create(D3DXVECTOR3(nCount + (50 * nCount) + 390.0f, -5 * ((nCount*nCount) - (5 * nCount) + 9) + 395.0f, 0.0f), size);	//ワニ左上部歯 (U字型)
			}
			else if (nCount >= 5 && nCount < 10)
			{
				m_apTooth[nCount] = CTooth::Create(D3DXVECTOR3((nCount - 5) + (50 * (nCount - 5)) + 680.0f, -4 * (((nCount - 5)*(nCount - 5)) - (3 * (nCount - 5)) + 9) + 405.0f, 0.0f), size);	//ワニ右上部歯 (U字型)
			}
			else if (nCount >= 10 && nCount < MAX_NUMBER)
			{
				m_apTooth[nCount] = CTooth::Create(D3DXVECTOR3((nCount - 10) + (50 * (nCount - 10)) + 410.0f, -3 * ((nCount - 10)*(nCount - 10) - (9 * (nCount - 10)) + 30.0f) + 580.0f, 0.0f), D3DXVECTOR3(80.0f, 65.0f, 0.0f)); //ワニ下部歯 U字型
				m_apTooth[nCount]->SetRotation(180);
			}
			nCountTooth += 1;
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			m_apTooth[nCount]->Uninit();
			m_apTooth[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPolygon::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CPolygon::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			m_apTooth[nCount]->Draw();
		}
	}
}

//=============================================================================
// タッチ処理
//=============================================================================
int CPolygon::Touch(void)
{
	//マウス取得
	CInhMouse *pMouse = CManager::GetMouse();

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			//マウスポインター取得
			D3DXVECTOR3 MousePos = D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f);
			//マウスポインターでクリックした処理
			m_pos = m_apTooth[nCount]->GetPosition();
			if (MousePos.x >= m_pos.x - (TEXTURE_WIDTH / 2) &&
				MousePos.x < m_pos.x + (TEXTURE_WIDTH / 2) &&
				MousePos.y >= m_pos.y - (TEXTURE_HEIGHT / 2) &&
				MousePos.y < m_pos.y + (TEXTURE_HEIGHT / 2))
			{
				if (pMouse->GetClickTrigger(0) == true)
				{
					CClean::Create(D3DXVECTOR3(100, 100, 100))->SetPosition(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f));
					m_apTooth[nCount]->Color();
					nCountTooth -= 1;
					return nCount;
				}
			}
		}
	}
	return 0;
}

//=============================================================================
// カラー処理
//=============================================================================
void CPolygon::TouchCol(int nTooth)
{
	m_apTooth[nTooth]->Color();
}

//=============================================================================
// 歯のゲッター処理
//=============================================================================
int CPolygon::GetTooth(void)
{
	return nCountTooth;
}



