//=============================================================================
// ヘッダファイル
//=============================================================================
#include "scene.h"
#include <typeinfo.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "manager.h"
#include "inputmouse.h"
#include "inihkeyboard.h"

//=============================================================================
//静的メンバー変数宣言
//=============================================================================
CScene * CScene::m_apScene[MAX_PRIORITY][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;
bool CScene::bPause = true;
//CPause * CScene::m_pPause = NULL;
//=============================================================================
//コンストラクト
//=============================================================================
CScene::CScene(int nPriorit)
{
	for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
	{
		if (m_apScene[nPriorit][nCutScene] == NULL)
		{
			m_nID = nCutScene;
			m_apScene[nPriorit][nCutScene] = this;
			m_nPiority= nPriorit;
			m_nNumAll++;
			break;
		}
	}

}
//=============================================================================
//デストラクト
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCut = 0; nCut < MAX_PRIORITY; nCut++)
	{
		for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
		{
			if (m_apScene[nCut][nCutScene] != NULL && typeid(*m_apScene[nCut][nCutScene]) != typeid(CScene2d))
			{
				m_apScene[nCut][nCutScene]->Update();
			}
		}
	}
}
//=============================================================================
//描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCut = 0; nCut < MAX_PRIORITY; nCut++)
	{
		for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
		{
			if (m_apScene[nCut][nCutScene] != NULL && typeid(*m_apScene[nCut][nCutScene]) != typeid(CScene2d))
			{
				m_apScene[nCut][nCutScene]->Draw();
			}
		}
	}
}

//=============================================================================
//終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCut = 0; nCut < MAX_PRIORITY; nCut++)
	{
		for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
		{
			if (m_apScene[nCut][nCutScene] != NULL)
			{
				m_apScene[nCut][nCutScene]->Uninit();	
			}
		}
	}
}

//=============================================================================
//セットタイプ モード処理
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_nType = objType;
}

//=============================================================================
//タイプゲット処理
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_nType;
}

//=============================================================================
//シーンゲット処理
//=============================================================================
CScene * CScene::GetScene(int nPriorty, int nCntScene)
{
	return m_apScene[nPriorty][nCntScene];
}

//=============================================================================
//シーン破棄処理
//=============================================================================
void CScene::Release(void)
{
		if (m_apScene[m_nPiority][m_nID] != NULL)
		{
			int nID = m_nID;
			int nPiority = m_nPiority;
			delete m_apScene[nPiority][nID];
			m_apScene[nPiority][nID] = NULL;
			m_nNumAll--;
		}

}